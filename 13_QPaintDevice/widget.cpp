#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QPicture>
#include <QBitmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    //Pixmap绘图设备，300x300的画布
//    QPixmap pix(300, 300);
//    //画布填充颜色，默认黑色
//    pix.fill(Qt::white);
//    //创建画家
//    QPainter painter(&pix);
//    //设置画笔
//    painter.setPen(QPen(Qt::green));
//    //画一个圆
//    painter.drawEllipse(QPoint(150, 150), 100, 100);
//    //保存图片
//    pix.save("E:/QT/pix.png");

//    //QImage 绘图设备
//    QImage img(300, 300, QImage::Format_ARGB32);
//    img.fill(Qt::white);

//    QPainter painter(&img);
//    painter.setPen(QPen(Qt::blue));
//    painter.drawEllipse(QPoint(150, 150),100,100);
//    //保存
//    img.save("E:/QT/img.png");

//    //QPicture 绘图设备 可以记录和重现绘图指令
//    QPicture pic;
//    QPainter painter;
//    painter.begin(&pic);    //开始记录 往pic上画的指令
//    painter.setPen(QPen(Qt::blue));
//    painter.drawEllipse(QPoint(150, 150), 100, 100);
//    painter.end();  //结束画画
//    pic.save("E:/QT/pic.pic");  //保存
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    //利用QImage修改像素
//    QImage img;
//    img.load(":/Image/Luffy.png"); //加载图片
//    //修改像素点
//    for(int i = 50; i < 100; ++i)
//    {
//        for(int j = 50; j < 100; ++j)
//        {
//            QRgb value = qRgb(255,0,0);
//            img.setPixel(i, j, value); //修改某点像素值
//        }
//    }
//    painter.drawImage(0, 0, img); //画QImage

//    QPainter painter(this);
//    //重现QPicture的绘图指令
//    QPicture pic;
//    pic.load("E:/QT/pic.pic");
//    painter.drawPicture(0, 0, pic);

    QPixmap pixmap(":/Image/butterfly.png");
    QPixmap pixmap1(":/Image/butterfly1.png");
    QBitmap bitmap(":/Image/butterfly.png");
    QBitmap bitmap1(":/Image/butterfly1.png");

    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
    painter.drawPixmap(200, 0, pixmap1);
    painter.drawPixmap(0, 130, bitmap);
    painter.drawPixmap(200, 130, bitmap1);
}
