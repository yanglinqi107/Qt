#include "widget.h"
#include "ui_widget.h"
#include <QPainter> //画家类
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //点击移动按钮，移动图片
    connect(ui->btn, &QPushButton::clicked, [=](){
        posX += 20;
        update();   //手动调用绘图事件，repaint也可以，但推荐update，
    });
    QTimer *timer = new QTimer(this);
    timer->start(500);
    connect(timer, &QTimer::timeout, [=](){
        posX += 10;
        update();   //手动调用绘图事件，repaint也可以，但推荐update，
    });
}

Widget::~Widget()
{
    delete ui;
}

////绘图事件，自动调用
//void Widget::paintEvent(QPaintEvent *)
//{
//    //实例化回家对象
//    QPainter painter(this); //this指定绘图设备

//    //设置画笔
//    QPen pen(QColor(255, 0, 0));
//    //设置画笔宽度
//    pen.setWidth(3);
//    //设置画笔风格
//    pen.setStyle(Qt::DotLine);

//    //画刷
//    QBrush brush(Qt::cyan);
//    //设置画刷风格
//    brush.setStyle(Qt::Dense7Pattern);
//    //让画家使用画刷
//    painter.setBrush(brush);


//    //让画家使用该画笔
//    painter.setPen(pen);
//    painter.

//    //画线
//    painter.drawLine(QPoint(0, 0), QPoint(100, 100));   //线段两端点的坐标
//    //画圆 Ellipse椭圆
//    painter.drawEllipse(QPoint(100, 100), 50, 50);  //圆心 半长轴 和 半短轴
//    //画矩形
//    painter.drawRect(QRect(20, 20, 50, 50));
//    //画文字
//    painter.drawText(QRect(10, 200, 150, 50), "好好学习，天天向上");
//}

//void Widget::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this); //创建画家

//    painter.setRenderHint(QPainter::Antialiasing); //设置抗锯齿

//    painter.drawEllipse(QPoint(50, 50), 50, 50);    //画圆

//    painter.translate(100, 0);  //将画家从当前位置（0,0）移动x:100、y:0的距离 （100,0）
//    painter.drawRect(20, 20, 50, 50);   //画矩形

//    painter.translate(100, 0);  //将画家从当前位置（100,0）移动x:100、y:0的距离 （200,0）
//    painter.drawRect(20, 20, 50, 50);   //画矩形

//    painter.save();             //保存当前状态
//    painter.translate(0, 100);  //将画家从当前位置（200,0）移动x:0、y:100的距离 （200,100）
//    painter.restore();          //恢复保存的画家状态
//    painter.drawEllipse(QPoint(30, 30), 10, 10);
//}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //如果超出屏幕，从0开始
    if(posX > this->width()) //width()获取窗口宽度，height是高度
    {
        posX = -QPixmap(":/Image/Luffy.png").width();
    }
    painter.drawPixmap(posX, 0, QPixmap(":/Image/Luffy.png"));
}
