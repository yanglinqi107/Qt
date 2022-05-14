#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers();

    //添加Sqlite服务器
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库
    db.setDatabaseName("../info.db");

    //打开数据库
    if(!db.open()) //数据库打开失败
    {
        qDebug() << db.lastError().text();
    }

    QSqlQuery query;
    query.exec("create table if not exists student(id int primary key, name varchar(255), age int, score int);");

    //1、odbc风格
    //预处理语句
    query.prepare("insert into student(name, age, score) values(?, ?, ?)"); //?是占位符
    //给字段设置内容
    QVariantList nameList, ageList, scoreList;
    nameList << "张三" << "李四" << "王五";
    ageList << 11 << 22 << 33;
    scoreList << 59 << 69 << 79;
    //将字段值和占位符对应，需按顺序对应
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    query.addBindValue(scoreList);
    //执行预处理命令
    query.execBatch();

    query.exec("select * from student;");

    while(query.next()) //一行行读取返回结果
    {
        //取出当前行的内容，从0开始按列下标计数，或使用字段
        qDebug() << query.value(0).toInt()
                 << query.value(1).toString()
                 << query.value("age").toInt()
                 << query.value("score").toInt();
    }
}

Widget::~Widget()
{
    delete ui;
}
