#include "mylabel.h"
#include <QDebug>
#include <QString>

myLabel::myLabel(QWidget *parent) :
    QLabel(parent)
{
    //setMouseTracking(true);
}

//鼠标进入
void myLabel::enterEvent(QEvent *ev)
{
    qDebug() << "鼠标进入myLabel";
}

//鼠标离开
void myLabel::leaveEvent(QEvent *ev)
{
    qDebug() << "鼠标离开myLabel";
}

//鼠标按下
void myLabel::mousePressEvent(QMouseEvent *ev)
{
    //左键按下
    if(ev->button() == Qt::LeftButton)
    {
        qDebug () << "鼠标按下：x = " << ev->x() << " y = " << ev->y() << " globalX = " << ev->globalX() << " globalY = " << ev->globalY();
    }
}

//鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *ev)
{
    //左键按下移动
    if(ev->buttons() & Qt::LeftButton)
    {
        qDebug () << "鼠标移动：x = " << ev->x() << " y = " << ev->y() << " globalX = " << ev->globalX() << " globalY = " << ev->globalY();
    }
}

//鼠标释放
void myLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    //右键释放
    if(ev->button() == Qt::RightButton)
    {
        QString str = QString("鼠标释放：x = %1 y = %2 globalX = %3 globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        //qDebug () << "鼠标释放：x = " << ev->x() << " y = " << ev->y() << " globalX = " << ev->globalX() << " globalY = " << ev->globalY();
        qDebug() << str;
    }
}


bool myLabel::event(QEvent *e)
{
    //如果是鼠标按下， 在event事件分发中做拦截
    if(QEvent::MouseButtonPress == e->type()) {
        QMouseEvent *ev = static_cast<QMouseEvent*>(e);
        QString str = QString("Event函数中：鼠标按下 x = %1 y = %2 globalX = %3 globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
        return true; //true代表用户自己处理，不向下分发
    }

    //其他事件 交给父类处理 默认处理
    return QLabel::event(e);
}
