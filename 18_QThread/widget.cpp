#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    myTimer = new QTimer(this);

    connect(myTimer, &QTimer::timeout, this, &Widget::dealTimeout);

    //分配空间
    thread = new MyThread(this);

    connect(thread, &MyThread::isDone, this, &Widget::dealDone);

    //当关闭窗口时触发
    connect(this, &Widget::destroyed, this, &Widget::stopThread);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealTimeout()
{
    static int i = 0;
    ++i;
    //设置lcd的值
    ui->lcdNumber->display(i);
}

void Widget::on_pushButton_clicked()
{
    //如果定时器未工作
    if(myTimer->isActive() == false)
    {
        myTimer->start(100);
    }

    //启动线程，处理数据
    thread->start();
}

void Widget::dealDone()
{
    qDebug() << "it is over";
    myTimer->stop(); //关闭定时器
}

void Widget::stopThread()
{
    //停止线程
    thread->quit();
    //等待线程处理完当前工作
    thread->wait();
}
