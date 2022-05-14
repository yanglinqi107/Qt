#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "domxml.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectDB();  // 连接数据库
    void initSellCarPage();  //初始化出售车辆界面
    void initInCarPage();  //初始化新车入库界面

private slots:
    void on_actionCar_triggered();

    void on_actionCalc_triggered();

    void on_comboBoxFactory_currentIndexChanged(const QString &arg1);

    void on_comboBoxBrand_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_buttonCancel_clicked();

    void on_buttonSure_clicked();

    void on_cbBFactory_currentIndexChanged(const QString &arg1);

    void on_cbBBrand_currentIndexChanged(const QString &arg1);

    void drawHistogram();

    void drawPie(QString arg);

    void on_toolBox_currentChanged(int index);

    void on_btnAdd_clicked();

    void on_btnDel_clicked();

    void on_btnCommit_clicked();

    void on_btnCannel_clicked();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;
};

#endif // MAINWINDOW_H
