#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPushButton>
#include <QDebug>

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);

    //创建一个老师对象
    this->zt = new Teacher(this);
    //创建一个学生对象
    this->st = new Student(this);
    //老师饿了，学生请客的连接  //未重载时的写法
    //connect(zt, &Teacher::hungry, st, &Student::treat);

    //指针 -> 地址  函数指针 -> 函数地址   //重载后使用函数指针区分
    void (Teacher:: *teacherSignal)(QString) = &Teacher::hungry;
    void (Student:: *studentSlot)(QString) = &Student::treat;
    connect(zt, teacherSignal, st, studentSlot);

    //调用下课函数
    classIsOver();

    //点击 下课按钮， 触发下课
    QPushButton *btn = new QPushButton("下课", this);
    //connect(btn, &QPushButton::clicked, this, &myWidget::classIsOver);

    void (Teacher:: *teacherSignal2)() = &Teacher::hungry;
    void (Student:: *studentSlot2)() = &Student::treat;
    connect(zt, teacherSignal2, st, studentSlot2);
    connect(btn, &QPushButton::clicked, zt, teacherSignal2);

    //断开信号
    //disconnect(zt, teacherSignal2, st, studentSlot2);

    //拓展
    //1、信号是可以连接信号
    //2、一个信号可以连接多个槽函数
    //3、多个信号 可以连接 同一个槽函数
    //4、信号和槽函数的参数必须一一对应
    //5、信号的参数个数 可以多于 槽函数的参数，但前面的类型还是要对应

    //connect(btn, &QPushButton::clicked, this, &myWidget::close);

    //Qt4版本信号和槽连接，优点：参数直挂；缺点：类型不做检测
    //connect(zt, SIGNAL(hungry()), st, SLOT(treat()));

//    //lambda表达式
//    QPushButton *mbtn1 = new QPushButton(this);
//    QPushButton *mbtn2 = new QPushButton(this);
//    mbtn1->move(100, 0);
//    mbtn2->move(100, 50);
//    int m = 10;
//    //mutable允许值传递的只读数据在lambda内可修改，但不会导致外部改变
//    connect(mbtn1, &QPushButton::clicked, this, [m]()mutable{ m = 100 + 10; qDebug() << m; });
//    connect(mbtn2, &QPushButton::clicked, this, [=](){ qDebug() << m; });

    //利用lambda表达式，实现点击按钮 关闭窗口
    QPushButton *btn2 = new QPushButton("关闭", this);
    btn2->move(100, 100);
    connect(btn2, &QPushButton::clicked, this, [=](){ this->close(); emit zt->hungry("宫保鸡丁"); });
}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::classIsOver()
{
    //下课函数，调用后 触发老师饿了的信号
    emit zt->hungry();
    emit zt->hungry("宫保鸡丁");
}
