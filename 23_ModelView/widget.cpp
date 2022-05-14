#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>

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

    //设置模型
    model = new QSqlTableModel(this);
    model->setTable("student");  //设置使用哪个表

    //把model放在view中
    ui->tableView->setModel(model);

    //显示model里面的数据
    model->select();

    //设置表头columns 不设置默认数据库表的表头
    model->setHeaderData(0, Qt::Horizontal, "学号"); // section：第几列

    //设置编辑策略（不能直接修改，默认view可以直接修改，并且view的修改能改变数据库）
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置手动提交修改

    //设置view不可以修改，则数据库没法对应修改了
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_buttonAdd_clicked()
{
    //添加空记录
    QSqlRecord record = model->record();
    //获取model即数据库的表的行数
    int row = model->rowCount();
    model->insertRecord(row, record);
}

void Widget::on_buttonSure_clicked()
{
    model->submitAll(); //提交所有动作
}

void Widget::on_buttonCancel_clicked()
{
    model->revertAll(); //取消所有动作
    model->submit();    //提交动作
}

void Widget::on_buttonDel_clicked()
{
    //取出选中的模型
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    //取出模型中每行的索引
    QModelIndexList list = selectModel->selectedRows();
    //删除所有选中的行
    for(int i = 0; i < list.size(); ++i)
    {
        model->removeRow(list.at(i).row());
    }
}

void Widget::on_buttonFind_clicked()
{
    QString name = ui->lineEdit->text();
    QString str = QString("name = '%1'").arg(name);
    if(name == "")
    {
        str = "";
    }
    model->setFilter(str); //过滤条件
    model->select();
}
