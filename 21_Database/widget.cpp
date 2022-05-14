#include "widget.h"
#include "ui_widget.h"

#include <QSqlDatabase>
#include <qDebug>
#include <QMessageBox>
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

    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //连接数据库
    db.setHostName("127.0.0.1"); //数据库服务器IP
    db.setUserName("root");      //数据库用户名
    db.setPassword("yanglinqi"); //密码
    db.setDatabaseName("mytest");  //使用的数据库名称，要先创建

    //打开数据库
    if(!db.open()) //数据库打开失败
    {
        QMessageBox::warning(this, "错误", db.lastError().text());
        return;
    }
    QSqlQuery query;
    query.exec("create table if not exists student(id int primary key auto_increment, name varchar(255), age int, score int);");

//    //添加数据库
//    QSqlDatabase db1 = QSqlDatabase::addDatabase("QMYSQL", "b");
//    //连接数据库
//    db1.setHostName("127.0.0.1"); //数据库服务器IP
//    db1.setUserName("root");      //数据库用户名
//    db1.setPassword("yanglinqi"); //密码
//    db1.setDatabaseName("temp");  //使用的数据库名称，要先创建
//    //打开数据库
//    if(!db1.open()) //数据库打开失败
//    {
//        QMessageBox::warning(this, "错误", db1.lastError().text());
//        return;
//    }
//    QSqlQuery query1(db1);
//    query1.exec("create table student(id int primary key auto_increment, name varchar(255), age int, score int);");

    //插入
    //query.exec("insert into student(id, name, age, score)  values(1, 'mike', 18, 59);");

    //批量插入

    //1、odbc风格
//    //预处理语句
//    query.prepare("insert into student(name, age, score) values(?, ?, ?)"); //?是占位符
//    //给字段设置内容
//    QVariantList nameList, ageList, scoreList;
//    nameList << "张三" << "李四" << "王五";
//    ageList << 11 << 22 << 33;
//    scoreList << 59 << 69 << 79;
//    //将字段值和占位符对应，需按顺序对应
//    query.addBindValue(nameList);
//    query.addBindValue(ageList);
//    query.addBindValue(scoreList);
//    //执行预处理命令
//    query.execBatch();

    //2、oracle风格
//    //预处理语句
//    query.prepare("insert into student(name, age, score) values(:name, :age, :score)"); //占位符 :+自定义名字 通常和字段名相同
//    //给字段设置内容
//    QVariantList nameList, ageList, scoreList;
//    nameList << "张三1" << "李四1" << "王五1";
//    ageList << 12 << 23 << 34;
//    scoreList << 60 << 70 << 80;
//    //将字段值和占位符对应
//    query.bindValue(":name", nameList);
//    query.bindValue(":age", ageList);
//    query.bindValue(":score", scoreList);
//    //执行预处理命令
//    query.execBatch();

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

void Widget::on_pushButton_clicked()
{
    //获取行编辑内容
    QString name = ui->lineEdit->text();

    QString sql = QString("delete from student where name='%1'").arg(name);

    //开启一个事务
    QSqlDatabase::database().transaction(); //QSqlDatabase::database()返回打开的数据库对象
    QSqlQuery query;
    query.exec(sql);
}

void Widget::on_pushButton_2_clicked()
{
    //提交事务，确定删除
    QSqlDatabase::database().commit();
}

void Widget::on_pushButton_3_clicked()
{
    //事务回滚，撤销
    QSqlDatabase::database().rollback();
}
