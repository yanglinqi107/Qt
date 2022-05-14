#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) :
//    QWidget(parent)
//{
//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    //设置按钮图片和大小
    initPushButton(normalImg);
}

//按钮图片和大小
void MyPushButton::initPushButton(QString pixPath)
{
    QPixmap pix;
    bool ret = pix.load(pixPath);
    if(!ret)
    {
        qDebug() << "图片加载失败" << endl;
    }

    //设置按钮固定大小
    this->setFixedSize(pix.width(), pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}

//向下跳
void MyPushButton::zoomDown()
{
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));

    //设置弹跳效果
    animation->setEasingCurve(QEasingCurve::OutElastic);

    //执行动画
    animation->start();
}

//向上跳
void MyPushButton::zoomUp()
{
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //设置弹跳效果
    animation->setEasingCurve(QEasingCurve::OutElastic);

    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "") //传入的按下图片不为空 说明需要有按下状态 切换图片
    {
        initPushButton(this->pressImgPath);
    }

    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "") //传入的按下图片不为空 说明需要有按下状态 切换图片
    {
        initPushButton(this->normalImgPath);
    }

    return QPushButton::mouseReleaseEvent(e);
}
