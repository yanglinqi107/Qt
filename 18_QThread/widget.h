#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>  //定时器头文件
#include "mythread.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void dealTimeout();  //定时器槽函数
    void dealDone();  //线程结束槽函数
    void stopThread(); //线程停止槽函数

private:
    Ui::Widget *ui;

    QTimer *myTimer;  //声明一个变量
    MyThread *thread; //线程对象
};

#endif // WIDGET_H
