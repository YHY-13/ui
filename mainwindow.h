#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"qcustomplot.h"
#include<QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectDB(); //连接数据库
    void initData(); //初始化
    QVector<double> load_x();//x轴装数据
    QVector<double>load_y(int index);//y轴装数据
    void showView(QVector<double>x,QVector<double>y,QCustomPlot*view);//初始化折线图
    QVector<QString> getMysqlStr(QComboBox*varity1,QComboBox*speed,QComboBox*wait,QComboBox*water);
private slots:
    void on_pushButton_clicked();

    void on_comboBox_Variety_currentIndexChanged(int index);

    void on_comboBox_temp_currentIndexChanged(const QString &arg1);

    void on_comboBox_water_currentIndexChanged(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_page1_clicked();

    void on_pushButton_page2_clicked();

    void on_pushButton_page3_clicked();

    void on_pushButton_page4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_page5_clicked();

    void on_pushButton_page6_clicked();

    void on_button_search_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_listWidget_clicked(const QModelIndex &index);  

    void on_comboBox_5_varity_currentIndexChanged(int index);

    void on_pushButton_viewButton_clicked();

private:
    Ui::MainWindow *ui;
    QStringList moisture;//水分对应的字母【字段】
    QStringList varity;//varity对应的字符串
    QString varity1;//当前选取的品类,是每个表
    int choiceId;//选择的指标，
    QStringList target;//target对应的字符串【用choiceId选取】
    QString SqlName;//生成的表名
//    double i;
//    int j;
    QMap<int,QString>map;//index,表第一个字段的品类字符串
    QVector<QString>result;//先查表，每个品类四个表

   int catalogNum;
};

#endif // MAINWINDOW_H
