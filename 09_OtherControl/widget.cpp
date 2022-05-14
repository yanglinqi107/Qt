#include "widget.h"
#include "ui_widget.h"
#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //栈控件的使用

    //设置默认定位 ScrollArea
    ui->stackedWidget->setCurrentIndex(2);

    //ScrollArea按钮
    connect(ui->btn_ScrollArea, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(2);
    });

    //ToolBox按钮
    connect(ui->btn_ToolBox, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });

    //TabWidget按钮
    connect(ui->btn_TabWidget, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    //下拉框
    ui->comboBox->addItem("奔驰");
    ui->comboBox->addItem("宝马");
    ui->comboBox->addItem("拖拉机");

    //点击按钮 选择拖拉机选项
    connect(ui->btn_Select, &QPushButton::clicked, [=](){
        //ui->comboBox->setCurrentIndex(2);
        ui->comboBox->setCurrentText("拖拉机");
    });

    //利用QLabel显示图片
    ui->label_Pic->setPixmap(QPixmap("E:/QT/HeiMa_jiaocheng/06_QtControl/Image/butterfly.png"));
    //利用QLabel显示动图
    QMovie * movie = new QMovie("E:/QT/HeiMa_jiaocheng/06_QtControl/Image/mario.gif");
    ui->label_movie->setMovie(movie);
    //播放动图
    movie->start();
}

Widget::~Widget()
{
    delete ui;
}
