#include "customplot.h"
#include "ui_customplot.h"
#include"qcustomplot.h"
#include <QSqlQuery>
#include<mainwindow.h>
customplot::customplot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customplot)
{
    ui->setupUi(this);

    QCustomPlot*pCustomPlot=new QCustomPlot(this);
            pCustomPlot->resize(300,300);
            // 可变数组存放绘图的坐标的数据，分别存放x和y坐标的数据，101为数据长度
            QVector<double>x(40),y(40);
      QString str=QString("select %1 from wheat_time_43_4_0").arg(list.at(index));
//    QList<float> a,b;
   QSqlQuery query;
   QSqlQuery query1;

//    QString str=QString("select %1 from wheat_time_43_4_0 ").arg(list.at(index));//【只固定了一个表，不能自由选择】【改我数，都成整数了】

    QString str1="select 小麦 from wheat_time_43_4_0";
    query1.exec(str1);
    query.exec(str);
    int i=0,j=0;
    while (query.next()) {
       y[i]=query.value(0).toDouble();
       i++;
    }
     while(query1.next()){
         x[j]=query1.value(0).toDouble();
         j++;
     }

     QVector<double>::iterator k=x.begin();
     x.erase(k);
     QVector<double>::iterator m=y.begin();
     y.erase(m);//有两个数开头的是没用的，所以删掉
//     qDebug()<<x;
//     qDebug()<<y;
    QCPGraph*pGraph=pCustomPlot->addGraph();
    pCustomPlot->graph(0)->setData(x,y);
    pCustomPlot->xAxis->setLabel("粮温");
    pCustomPlot->yAxis->setLabel("干燥速率");
    pCustomPlot->xAxis->setRange(30,60);
    pCustomPlot->yAxis->setRange(20,80);
    pCustomPlot.show();
}

customplot::~customplot()
{
    delete ui;
}
