#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include<QString>
QT_CHARTS_USE_NAMESPACE
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

private slots:
    void on_pushButton_clicked();

    void on_comboBox_Variety_currentIndexChanged(int index);

    void on_comboBox_temp_currentIndexChanged(const QString &arg1);

    void on_comboBox_water_currentIndexChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_viewButton_clicked();

    void on_pushButton_page1_clicked();

    void on_pushButton_page2_clicked();

    void on_pushButton_page3_clicked();

    void on_pushButton_page4_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    QStringList list;
    QStringList Name;
    int choiceId;
    QStringList Choice;
    QString SqlName;
    double i;
    int j;
};

#endif // MAINWINDOW_H
