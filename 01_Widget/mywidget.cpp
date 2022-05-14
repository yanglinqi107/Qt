#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPushButton>
#include <mypushbutton.h>
#include <QDebug>

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{

    //创建一个按钮
    QPushButton *btn = new QPushButton();
    //btn->show();    //show以顶层方式弹出窗口控件
    //让btn对象 依赖在主窗口中
    btn->setParent(this);
    //显示文本
    btn->setText("第一个按钮");

    //创建第二个按钮，安装控件的大小创建窗口，需要设置窗口的大小
    QPushButton *btn2 = new QPushButton("第二个按钮", this);
    btn2->move(100, 100);

    //按钮重置大小
    btn2->resize(50, 50);

    //设置窗口大小
    resize(600, 400);

    //设置固定窗口大小
    setFixedSize(600, 400);

    //设置窗口的标题
    setWindowTitle("第一个窗口");

    //创建一个自己的按钮对象
    MyPushButton *myBtn = new MyPushButton();
    myBtn->setText("我自己的按钮");
    myBtn->move(200, 0);
    myBtn->setParent(this);

    //需求 点击我的按钮 关闭窗口
    //参数 信号的发送者 发送的信号（函数的地址）
    connect(myBtn, &QPushButton::clicked, this, &myWidget::close);
}

myWidget::~myWidget()
{
    qDebug() << "myWidget析构调用";
    delete ui;
}
