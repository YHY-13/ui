#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include<QDebug>
#include<QButtonGroup>
#include"qcustomplot.h"
#include"calculate.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //打开数据库
    connectDB();
    //初始化数据
    initData();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//获得查询字符串,获得四个指标的数据表名字
QVector<QString> MainWindow::getMysqlStr(QComboBox *varity1, QComboBox *speed, QComboBox *wait, QComboBox *water){
    QVector<QString>result;
    QString str_ratio=varity.at(varity1->currentIndex()) +"_"+"ratio"+"_"+water->currentText()+"_"
            +QString::number( speed->currentText().toDouble()*10)+"_"+wait->currentText();//干燥时间表
    QString str_time=varity.at(varity1->currentIndex()) +"_"+"time"+"_"+water->currentText()+"_"
            +QString::number( speed->currentText().toDouble()*10)+"_"+wait->currentText();//干燥速率表
    QString str_temp=varity.at(varity1->currentIndex()) +"_"+"temp"+"_"+water->currentText()+"_"
            +QString::number( speed->currentText().toDouble()*10)+"_"+wait->currentText();//干燥积温表
    QString str_fatty=varity.at(varity1->currentIndex()) +"_"+"fatty"+"_"+water->currentText()+"_"
            +QString::number( speed->currentText().toDouble()*10)+"_"+wait->currentText();//干燥脂肪酸表
    result.push_back(str_ratio);
    result.push_back(str_time);
    result.push_back(str_temp);
    result.push_back(str_fatty);
    return result;
}

//初始化折线图
void MainWindow::showView(QVector<double>x,QVector<double>y,QCustomPlot* view){
    ui->widget=view;
    ui->widget->addGraph();
    ui->widget->xAxis->setLabel("粮温");
   // ui->widget->yAxis->setLabel("干燥速率");每个指标都得改

    ui->widget->graph(0)->setData(x,y);//装数据
    ui->widget->xAxis->setRange(x[0]*0.9,x[x.size()-1]*1.1);
    ui->widget->yAxis->setRange(y[0]*0.9,y[y.size()-1]*1.1);

    //    // 设置背景色
    ui->widget->setBackground(QColor(0, 0, 0));
          // pGraph->setPen(QPen(QColor(32, 178, 170)));//这个画笔咋用
    ui->widget->graph(0)->setPen(QPen(QColor(32, 178, 170)));
    //       // 设置x/y轴文本色、轴线色、字体等
    ui->widget->xAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->setLabelColor(QColor(0, 160, 230));
    ui->widget->xAxis->setBasePen(QPen(QColor(32, 178, 170)));
    ui->widget->xAxis->setTickPen(QPen(QColor(128, 0, 255)));
    ui->widget->xAxis->setSubTickPen(QColor(255, 165, 0));
    QFont xFont = ui->widget->xAxis->labelFont();
          xFont.setPixelSize(20);
    ui->widget->xAxis->setLabelFont(xFont);

    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->yAxis->setLabelColor(QColor(0, 160, 230));
    ui->widget->yAxis->setBasePen(QPen(QColor(32, 178, 170)));
    ui->widget->yAxis->setTickPen(QPen(QColor(128, 0, 255)));
    ui->widget->yAxis->setSubTickPen(QColor(255, 165, 0));
    QFont yFont = ui->widget->yAxis->labelFont();
    yFont.setPixelSize(20);
    ui->widget->yAxis->setLabelFont(yFont);
    ui->widget->replot();//画出来

   // ui->widget->show();
}



QVector<double> MainWindow:: load_x(){//x轴，粮温，固定值，不需要index，但是更改品类时需要index参数【先这么地】
    QVector<double>x(40);
    QString str1=QString("select %1 from %2")
            .arg(map[ui->comboBox_5_varity->currentIndex()])
            .arg(result[1]);//result是哪个都行，只要第一列的数据作为横坐标
    qDebug()<<str1<<endl;
    QSqlQuery query1;
    query1.exec(str1);
    int i=0;
    while(query1.next()){
        x[i]=query1.value(0).toDouble();
        i++;
    }
    QVector<double>::iterator k=x.begin();
    x.erase(k);//有两个数开头的是没用的，所以删掉(是)
    return x;
}
QVector<double>MainWindow::load_y(int index){
    QVector<double>y(40);
    QString str=QString("select %1 from %2")
            .arg(moisture.at(ui->comboBox_4_water->currentIndex()))
            .arg(result[index]);//固定的表，【自由选择的再说,多表联查是不该搞一搞】
    QSqlQuery query;
    query.exec(str);
    int i=0;
    while (query.next()) {
       y[i]=query.value(0).toDouble();
       i++;
    }
    QVector<double>::iterator m=y.begin();
    y.erase(m);//有两个数开头的是没用的，所以删掉(是)
    return y;
}

//连接数据库
void MainWindow::connectDB()
{
    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("132465");
    db.setDatabaseName("liangqing");

    //打开数据库
    if(!db.open())
    {
        QMessageBox::warning(this, "数据库打开失败", db.lastError().text());
        return;
    }
}
void MainWindow::initData()
{
    moisture<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
          <<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T"<<"U";

    varity<<"maize"<<"paddy"<<"wheat"<<"peanut"<<"potato";

    target<<"time"<<"ratio"<<"temp"<<"bud"<<"fatty";
    map[0]="玉米";map[1]="稻谷";map[2]="小麦";map[3]="花生";map[4]="马铃薯";

    QButtonGroup*buttonGroup=new QButtonGroup;//target单选区域
    buttonGroup->addButton(ui->radioButtonTime,0);
    buttonGroup->addButton(ui->radioButton_Velocity,1);
    buttonGroup->addButton(ui->radioButton_Tem,2);
    buttonGroup->addButton(ui->radioButton_Bud,3);
    buttonGroup->addButton(ui->radioButton_Fatty,4);
    //信号重载
    void(QButtonGroup::*p)(QAbstractButton*button)=&QButtonGroup::buttonClicked;
//获取单选框文本id
    connect(buttonGroup,p,[=](QAbstractButton*button){
        choiceId=buttonGroup->id(button);//【得将中文转换成英语】
       // qDebug()<<choiceId<<endl;
    });


}
//查找模块---数据预览
void MainWindow::on_pushButton_clicked()
{
    //组合各个关键词生成表名，然后直接查询表明
    QString str_Name;//组合的表名
    QString str;

    QString target_str;//单选框关键词

    double i;//风速
    i=(ui->comboBox_Wind->currentText().toDouble())*10;//风速乘10对应表名，因为表名不许含小数
    varity1=varity.at(ui->comboBox_Variety->currentIndex()-1);//从下拉框选取的品类
    target_str=target.at(choiceId);//选好的指标
        str_Name=//表名字
            varity1//品类
            +"_"
            +target_str//指标
            +"_"
            +ui->comboBox_Water->currentText()//湿度
            +"_"
            +QString::number(i)//静态方法，将double转换为字符型,风速
            +"_"
            +ui->comboBox_Wait->currentText();//缓苏比
        str="select * from "+str_Name;//生成好的表名,查询语句
    qDebug()<<str<<endl;
    SqlName=str_Name;//生成好的表名赋值给全局变量
   QSqlQueryModel*queryMode=new QSqlQueryModel(this);//新建模型
   queryMode->setQuery(str);//模型赋值
   ui->tableView->setModel(queryMode);//设置模型

//查找模块---初始化粮温和水分下拉框
   //初始化水分列表,根据上面个选好的表放模型
   QSqlQuery query;
   double a;//a是第一个水分值，后续的水分值有序递增
   QString query_str=QString ("select A from %1 limit 1").arg(SqlName);//SqlName全局变量，之前选好的
   qDebug()<<query_str<<endl;
   query.exec(query_str);
   while(query.next()){
       a=query.value(0).toDouble();
   }
   qDebug()<<a;
   for(int i=0;i<21;i++){
       QString string=QString::number(a+i*0.50,'f',1);
       ui->comboBox_water->addItem(string);//初始化水分列表，根据一个数据自动计算后面数据
   }

   //初始化粮温列表,查找第一列，放入模型
   QSqlQueryModel*queryModel=new QSqlQueryModel(this);
   QString querymod_str=QString("select %1 from %2").arg(map[ui->comboBox_Variety->currentIndex()-1]).arg(SqlName);//这里用了map
   qDebug()<<querymod_str<<endl;
   queryModel->setQuery(querymod_str);
   ui->comboBox_temp->setModel(queryModel);
   // ui->stackedWidget->setCurrentIndex(1);//切换页面
}
//查找模块---数据预览----二级下拉菜单(不同的表对应的风速，湿度，缓苏比不同)【数据库多表联查也可以做】
void MainWindow::on_comboBox_Variety_currentIndexChanged(int index)//品类下拉框
{
    //湿度下拉框，内联查询，放入模型
    QSqlQueryModel*queryModel1=new QSqlQueryModel(this);
    QString water_str=QString("SELECT water.water FROM varity INNER JOIN water on water.varity_id=varity.id AND varity.id =%1; ").arg(index);
    queryModel1->setQuery(water_str);
    ui->comboBox_Water->setModel(queryModel1);
    //风速，同上
    QSqlQueryModel*queryModel2=new QSqlQueryModel(this);
    QString speed_str=QString("SELECT speed.speed FROM varity INNER JOIN speed on speed.varity_id=varity.id AND varity.id =%1; ").arg(index);
    queryModel2->setQuery(speed_str);
    ui->comboBox_Wind->setModel(queryModel2);
    //缓苏比
    QSqlQueryModel*queryModel3=new QSqlQueryModel(this);
    QString wait_str=QString("SELECT wait.wait FROM varity INNER JOIN wait on wait.varity_id=varity.id AND varity.id =%1; ").arg(index);
    queryModel3->setQuery(wait_str);
    ui->comboBox_Wait->setModel(queryModel3);    
}
//【干燥模块】品质下拉框，代码复用
void MainWindow::on_comboBox_5_varity_currentIndexChanged(int index)
{
    //湿度下拉框，内联查询，放入模型
    QSqlQueryModel*queryModel1=new QSqlQueryModel(this);
    QString water_str=QString("SELECT water.water FROM varity INNER JOIN water on water.varity_id=varity.id AND varity.id =%1; ").arg(index+1);
    queryModel1->setQuery(water_str);
    ui->comboBox_9_water->setModel(queryModel1);
    //风速，同上
    QSqlQueryModel*queryModel2=new QSqlQueryModel(this);
    QString speed_str=QString("SELECT speed.speed FROM varity INNER JOIN speed on speed.varity_id=varity.id AND varity.id =%1; ").arg(index+1);
    queryModel2->setQuery(speed_str);
    ui->comboBox_6_speed->setModel(queryModel2);
    //缓苏比
    QSqlQueryModel*queryModel3=new QSqlQueryModel(this);
    QString wait_str=QString("SELECT wait.wait FROM varity INNER JOIN wait on wait.varity_id=varity.id AND varity.id =%1; ").arg(index+1);
    queryModel3->setQuery(wait_str);
    ui->comboBox_7_wait->setModel(queryModel3);
    //水分。粮温
    QVector<QString>sql_name;
    sql_name=getMysqlStr(ui->comboBox_5_varity,ui->comboBox_6_speed,ui->comboBox_7_wait,ui->comboBox_9_water);
    QSqlQuery query;
    double a;//a是第一个水分值，后续的水分值有序递增
    QString query_str=QString ("select A from %1 limit 1").arg(sql_name[1]);//不能再用SqlName了，和之前选的没有关系
   // qDebug()<<query_str<<endl;
    query.exec(query_str);
    while(query.next()){
        a=query.value(0).toDouble();
    }
    for(int i=0;i<21;i++){
        QString string=QString::number(a+i*0.50,'f',1);
        ui->comboBox_4_water->addItem(string);//初始化水分列表，根据一个数据自动计算后面数据
    }

    //初始化粮温列表,查找第一列，放入模型
    QSqlQueryModel*queryModel=new QSqlQueryModel(this);
    QString querymod_str=QString("select %1 from %2").arg(map[ui->comboBox_5_varity->currentIndex()]).arg(sql_name[1]);//不能再用SqlName了，和之前选的没有关系
    //qDebug()<<querymod_str<<endl;
    queryModel->setQuery(querymod_str);
    ui->comboBox_8_tempreture->setModel(queryModel);
}
//精准查询，粮温与水分（粮温动作）
void MainWindow::on_comboBox_temp_currentIndexChanged(const QString &arg1)//粮温是下拉框的数字
{
     if(ui->comboBox_water->currentIndex()==0){//如果水分还没选取，就显示提示信息
        ui->lineEdit->setText("请选择粮温");
    }
    //【这里只查了干燥时间，还有别的没有实现】
    QSqlQuery query;
    QString sql=QString("select %1 from %2 where %3=%4")
            .arg(moisture.at(ui->comboBox_Water->currentIndex()))
            .arg(SqlName)
            .arg(map[ui->comboBox_Variety->currentIndex()-1])
            .arg(arg1);
    //选择水分，从表里，温度符合的条件
    qDebug()<<sql<<endl;
    query.exec(sql);
    while(query.next())
    {
        QString str=query.value(0).toString();
        ui->lineEdit->setText(str);
    }
}
//精准查询，水分动作
void MainWindow::on_comboBox_water_currentIndexChanged(int index)
{

    QSqlQuery query;
    QString sql=QString("select %1 from %2 where 小麦=%3").arg(moisture.at(index))
                                                         .arg(SqlName)
                                                         .arg(ui->comboBox_temp->currentText());
    query.exec(sql);
    while(query.next())
    {
        QString str=query.value(0).toString();
        ui->lineEdit->setText(str);
    }
}
//自定义干燥方案(未完成)
void MainWindow::on_pushButton_3_clicked()
{
    QString str_variety,result;
    //str_variety=ui->lineEdit_variety->text();//品种
    //str_time=ui->lineEdit_time->text();//干燥时间要求

    
   result="hhhh %1";
   ui->textEdit->setText(result);
}
//页面切换
void MainWindow::on_pushButton_page1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_page2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_page3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_page4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_page5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}
void MainWindow::on_pushButton_page6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

//模型预测
void MainWindow::on_pushButton_2_clicked()
{
        //选择品类模型，输出数值部分
        //int category;

        float x1,x2,x3,x4,x5,y_time,y_ratio,y_temp,y_bud,y_fatty;
        x1=ui->lineEdit_x1->text().toFloat();
        x2=ui->lineEdit_x2->text().toFloat();
        x3=ui->lineEdit_x3->text().toFloat();
        x4=ui->lineEdit_x4->text().toFloat();
        x5=ui->lineEdit_x5->text().toFloat();
        QVector<Calculate*>catalog;
        corn aaa(x1,x2,x3,x4,x5);
        paddy bbb(x1,x2,x3,x4,x5);
        wheat ccc(x1,x2,x3,x4,x5);//无发芽率
        peanut ddd(x1,x2,x3,x4,x5);
        potato eee(x1,x2,x3,x4,x5);//无发芽率，无脂肪酸，有能耗比

        catalog.push_back(&aaa);
        catalog.push_back(&bbb);
        catalog.push_back(&ccc);
        catalog.push_back(&ddd);
        catalog.push_back(&eee);
        if(catalogNum==2){
            
        }
        else if(catalogNum==4){
            y_time=catalog[catalogNum]->func_time();
            y_ratio=catalog[catalogNum]->func_speed();
            y_temp=catalog[catalogNum]->func_temp();
            //能耗比咋写
            
        }
        else{
            y_time=catalog[catalogNum]->func_time();
            y_ratio=catalog[catalogNum]->func_speed();
            y_temp=catalog[catalogNum]->func_temp();
            y_bud=catalog[catalogNum]->func_bud();
            y_fatty=catalog[catalogNum]->func_fatty();
        }
       


        //结果显示部分
        QString str_time=QString("%1").arg(y_time);
        QString str_ratio=QString("%1").arg(y_ratio);
        QString str_temp=QString("%1").arg(y_temp);
        QString str_bud=QString("%1").arg(y_bud);
        QString str_fatty=QString("%1").arg(y_fatty);
        ui->result_time->setText(str_time);
        ui->result_speed->setText(str_ratio);
        ui->result_tem->setText(str_temp);
        ui->result_bud->setText(str_bud);
        ui->result_fatty->setText(str_fatty);
}

//问答模块(未完成)
void MainWindow::on_button_search_clicked()
{
    QString question=ui->lineEdit_question->text();
    qDebug()<<question;
}
//数据录入
void MainWindow::on_pushButton_4_clicked()
{
    QString variety=ui->lineEditvariety->text();
    QString wait=ui->lineEditwait->text();
    QString water=ui->lineEditwater->text();
    QString wind=ui->lineEditwind->text();
    QString time=ui->lineEdittime->text();
    QString bud=ui->lineEditbud->text();
    QString fatty=ui->lineEditfatty->text();
    QString tem=ui->lineEdittem->text();
    QString velocity=ui->lineEditvelocity->text();
    QString sumtemp=ui->lineEditsumtemp->text();
    QSqlQuery query;
    QString str=QString("INSERT INTO person("
                        "variety,"
                        "wait,"
                        "water,"
                        "wind,"
                        "time,"
                        "bud,"
                        "fatty,"
                        "tem,"
                        "velocity,"
                        "sumtemp)"
                        "VALUES("
                        "'%1', "
                        "'%2', "
                        "'%3', "
                        "'%4', "
                        "'%5', "
                        "'%6', "
                        "'%7', "
                        "'%8', "
                        "'%9', "
                        "'%10'); ").arg(variety).arg(wait).arg(water).arg(wind).arg(time).arg(bud).arg(fatty)
                                    .arg(tem).arg(velocity).arg(sumtemp);


    query.prepare(str);
    if(!query.exec()){
        qDebug()<<"query error"<<query.lastError();
    }
    else{
        qDebug()<<"insert data success!";
    }

}
//刷新用户自定义表格（未完成）
void MainWindow::on_pushButton_5_clicked()
{
    QSqlQueryModel*queryMode=new QSqlQueryModel(this);
    queryMode->setQuery("select *from  person");
    ui->tableView_2->setModel(queryMode);
}
//干燥方案选择(未完成)
void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    int num=index.row();//转换QModelIndex为int
    switch (num) {
    case 0:
        ui->textEdit_2->setText("降低干燥指标，缩短干燥作业流程，达到最短干燥时间。");
        break;
    case 1:
        ui->textEdit_2->setText("干燥效果主要指标为粮食总不饱和脂肪酸含量及干燥后发芽率，实际推荐干燥方案会主要提供这两种指标的最优干燥方案。");
        break;
    case 2:
        ui->textEdit_2->setText("干燥成本主要包括实际用电量及热量等因素，通过降低风机风速，减少干燥积温等因素，完成干燥作业。");
        break;
    case 3:
        ui->textEdit_2->setText("综合考量干燥成本及干燥效果，提出最平衡的干燥方案。");
        break;
    default:
        break;
    }
}

//折线图绘制(应该自定义x轴和y轴，实现函数根据用户选择自由装数据)【要优化】
void MainWindow::on_pushButton_viewButton_clicked()
{
//   只实现了固定的粮温变量，四个手写的干燥特性
    result=getMysqlStr(ui->comboBox_5_varity,ui->comboBox_6_speed,ui->comboBox_7_wait,ui->comboBox_9_water);
    QVector<double>x1(40),y1(40),x2(40),y2(40),x3(40),y3(40),x4(40),y4(40);
    x1=load_x(); x2=load_x(); x3=load_x(); x4=load_x();
    y1=load_y(0);y2=load_y(1);y3=load_y(2);y4=load_y(3);
    showView(x1,y1,ui->widget);
    qDebug()<<x1<<endl;
    showView(x2,y2,ui->widget_3);//每种特性指标的大小范围不一样，需要指定大小
    showView(x3,y3,ui->widget_4);
    showView(x4,y4,ui->widget_5);

    qDebug()<<result;//【小麦的语句不对啊？？？】
}
