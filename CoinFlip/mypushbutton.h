#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = 0);

    //构造函数 参数1 正常显示的图片路径   参数2 按下后显示的图片路径
    MyPushButton(QString normalImg, QString pressImg = "");

    //按钮图片和大小
    void initPushButton(QString pixPath);

    //按钮弹跳特效
    void zoomUp();
    void zoomDown();

    //重写按钮 按下 和 释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QString normalImgPath;
    QString pressImgPath;

signals:

public slots:

};

#endif // MYPUSHBUTTON_H
