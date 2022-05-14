#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //启动定时器
    id1 = startTimer(1000);
    id2 = startTimer(2000);

    //定时器的第二种方式
    QTimer *timer = new QTimer(this);   //创建对象
    timer->start(500);                  //定时 0.5s
    connect(timer, &QTimer::timeout, [=](){ //每隔0.5s label_4显示的数字加1
        static int num = 1;
        ui->label_4->setText(QString::number(num++));
    });

    static bool flag = true;
    connect(ui->btn, &QPushButton::clicked, [=](){  //点击按钮，定时器暂停或恢复
        if(flag) {
            timer->stop();
            ui->btn->setText("恢复");
        }
        else {
            timer->start(500);
            ui->btn->setText("暂停");
        }
        flag = !flag;
    });

    //步骤1：给label安装事件过滤器
    ui->label->installEventFilter(this);
    //步骤2：重写eventFilter事件

}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *ev)
{
    if(id1 == ev->timerId())
    {
        static int num1 = 1;
        ui->label_2->setText(QString::number(num1++));
    }
    if(id2 == ev->timerId())
    {
        static int num2 = 1;
        ui->label_3->setText(QString::number(num2++));
    }
}

//步骤2：重写eventFilter事件
bool Widget::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->label)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *ev = static_cast<QMouseEvent*>(e);
            QString str = QString("事件过滤器中：鼠标按下 x = %1 y = %2 globalX = %3 globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
            qDebug() << str;
            return true; //true代表用户自己处理，不向下分发
        }
    }
    //其他事件 交给父类处理 默认处理
    return QWidget::eventFilter(obj, e);
}
