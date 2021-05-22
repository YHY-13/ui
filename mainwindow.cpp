#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include<QDebug>
#include<QButtonGroup>
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
    list<<"A"<<"B"<<"C"<<"D"<<"E"<<"F"<<"G"<<"H"<<"I"<<"J"<<"K"<<"L"<<"M"<<"N"
          <<"N"<<"O"<<"P"<<"Q"<<"R"<<"S"<<"T"<<"U";

    Name<<"corn"<<"paddy"<<"wheat"<<"peanut"<<"potato";

    Choice<<"time"<<"velocity"<<"tem"<<"bud"<<"fatty";

    QButtonGroup*buttonGroup=new QButtonGroup;
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
        qDebug()<<choiceId<<endl;
    });

}
//数据预览
void MainWindow::on_pushButton_clicked()
{
    //组合各个关键词生成表名，然后直接查询表明
    QString str_Name;//组合的表名
    QString str;
    QString varity;//品类
    QString choice_str;//单选框关键词

    double i;//风速
    i=(ui->comboBox_Wind->currentText().toDouble())*10;
      qDebug()<<i<<endl;
    varity=Name.at(ui->comboBox_Variety->currentIndex()-1);
    choice_str=Choice.at(choiceId);
        str_Name=//表名字
            varity
            +"_"
            +choice_str
            +"_"
            +ui->comboBox_Water->currentText()
            +"_"
            +QString::number(i)//静态方法，将double转换为字符型
            +"_"
            +ui->comboBox_Wait->currentText();
        str="select * from "+str_Name;
    qDebug()<<str<<endl;
        SqlName=str_Name;
   QSqlQueryModel*queryMode=new QSqlQueryModel(this);//新建模型

   queryMode->setQuery(str);
   ui->tableView->setModel(queryMode);

   //初始化粮温和水分下拉框
   QSqlQuery query;
   double a;
   QString query_str=QString ("select A from %1 limit 1").arg(SqlName);
   qDebug()<<query_str<<endl;
   query.exec(query_str);
   while(query.next()){
       a=query.value(0).toDouble();
   }
   for(int i=0;i<20;i++){
       QString string=QString::number(a+i*0.50,'f',1);
       ui->comboBox_water->addItem(string);//初始化水分列表，根据一个数据自动计算后面数据
   }

   //初始化粮温列表
   QSqlQueryModel*queryModel=new QSqlQueryModel(this);
   QString querymod_str=QString("select 小麦 from %1").arg(SqlName);
   queryModel->setQuery(querymod_str);
   ui->comboBox_temp->setModel(queryModel);
    ui->stackedWidget->setCurrentIndex(1);//切换页面
}
//二级下拉菜单
void MainWindow::on_comboBox_Variety_currentIndexChanged(int index)
{
    switch (ui->comboBox_Variety->currentIndex()) {
    case 0://【重新选择时不能清空】【其实问题不大】
        ui->comboBox_Wait->clear();
        ui->comboBox_Water->clear();
        ui->comboBox_Wind->clear();
    case 1://玉米
        ui->comboBox_Water->clear();
        ui->comboBox_Wind->clear();
        ui->comboBox_Wait->clear();

        ui->comboBox_Water->insertItem(0,"30");
         ui->comboBox_Water->insertItem(1,"45");
          ui->comboBox_Water->insertItem(2,"60");

          ui->comboBox_Wind->insertItem(0,"0.4");
           ui->comboBox_Wind->insertItem(1,"0.7");
            ui->comboBox_Wind->insertItem(2,"1");

         ui->comboBox_Wait->insertItem(0,"0");
          ui->comboBox_Wait->insertItem(1,"1.5");
          ui->comboBox_Wait->insertItem(2,"3");
        break;
    case 2://稻谷
        ui->comboBox_Water->clear();
        ui->comboBox_Wind->clear();
        ui->comboBox_Wait->clear();

        ui->comboBox_Water->insertItem(0,"40");
         ui->comboBox_Water->insertItem(1,"53");
          ui->comboBox_Water->insertItem(2,"65");

          ui->comboBox_Wind->insertItem(0,"0.4");
           ui->comboBox_Wind->insertItem(1,"0.6");
            ui->comboBox_Wind->insertItem(2,"0.8");

         ui->comboBox_Wait->insertItem(0,"0");
          ui->comboBox_Wait->insertItem(1,"2.5");
          ui->comboBox_Wait->insertItem(2,"5");

        break;
    case 3://小麦
        ui->comboBox_Water->clear();
        ui->comboBox_Wind->clear();
        ui->comboBox_Wait->clear();

        ui->comboBox_Water->insertItem(0,"43");
        ui->comboBox_Water->insertItem(1,"55");
         ui->comboBox_Water->insertItem(2,"67");


          ui->comboBox_Wind->insertItem(0,"0.4");
           ui->comboBox_Wind->insertItem(1,"0.6");
            ui->comboBox_Wind->insertItem(2,"0.8");

         ui->comboBox_Wait->insertItem(0,"0");
          ui->comboBox_Wait->insertItem(1,"3");
          ui->comboBox_Wait->insertItem(2,"6");
        break;
    case 4://花生
        ui->comboBox_Water->clear();
        ui->comboBox_Wind->clear();
        ui->comboBox_Wait->clear();

        ui->comboBox_Water->insertItem(0,"20");
         ui->comboBox_Water->insertItem(1,"30");
          ui->comboBox_Water->insertItem(2,"40");

          ui->comboBox_Wind->insertItem(0,"0.4");
           ui->comboBox_Wind->insertItem(1,"0.8");
            ui->comboBox_Wind->insertItem(2,"1.2");

        break;
    case 5://马铃薯
        ui->comboBox_Water->clear();
        ui->comboBox_Wind->clear();
        ui->comboBox_Wait->clear();

          ui->comboBox_Wind->insertItem(0,"0.5");
           ui->comboBox_Wind->insertItem(1,"0.7");
            ui->comboBox_Wind->insertItem(2,"1.0");
           ui->comboBox_Wind->insertItem(3,"1.3");
           ui->comboBox_Wind->insertItem(4,"1.5");


    default:
        break;
    }
}
//精准查询，粮温与水分
void MainWindow::on_comboBox_temp_currentIndexChanged(const QString &arg1)
{
    int l=0;
    if(ui->comboBox_water->currentIndex()!=0)
    {
        int k;
        k=ui->comboBox_water->currentText().toDouble();
        l=k*2-29;//【这是个坑，不同的表，数量关系不确定】
    }
    else if(ui->comboBox_water->currentIndex()==0){
        ui->lineEdit->setText("请选择粮温");
    }
    QSqlQuery query;
    QString sql=QString("select %1 from %2 where 小麦=%3 ").arg(list.at(l)).arg(SqlName).arg(arg1);
    qDebug()<<sql<<endl;
    query.exec(sql);
    while(query.next())
    {
        QString str=query.value(0).toString();
        ui->lineEdit->setText(str);
    }
}

void MainWindow::on_comboBox_water_currentIndexChanged(const QString &arg1)
{
    i=arg1.toDouble();
    j=i*2-29;
    QSqlQuery query;
    QString sql=QString("select %1 from %2 where 小麦=%3").arg(list.at(j))
                                                            .arg(SqlName)
                                    .arg(ui->comboBox_temp->currentText());
    query.exec(sql);
    while(query.next())
    {
        QString str=query.value(0).toString();
        ui->lineEdit->setText(str);
    }
}

void MainWindow::on_pushButton_3_clicked()
{

    QSqlQueryModel*queryModel=new QSqlQueryModel(this);
    QString querymod_str=QString("select * from 自定义数据库");
    queryModel->setQuery(querymod_str);
    ui->tableWidge->setModel(queryModel);
}
