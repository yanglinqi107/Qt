#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = 0);

    //鼠标进入
    void enterEvent(QEvent *ev);

    //鼠标离开
    void leaveEvent(QEvent *ev);

    //鼠标按下
    virtual void mousePressEvent(QMouseEvent *ev);

    //鼠标移动
    virtual void mouseMoveEvent(QMouseEvent *ev);

    //鼠标释放
    virtual void mouseReleaseEvent(QMouseEvent *ev);

    //通过event事件分发器 拦截 鼠标按下事件
    bool event(QEvent *e);

signals:

public slots:

};

#endif // MYLABEL_H
