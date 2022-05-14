#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CarManage");

    //开始界面默认 车辆管理
    on_actionCar_triggered();

    //连接数据库
    connectDB();

    model = new QSqlTableModel(this);

    //初始化出售车辆界面
    initSellCarPage();

    //初始化新车入库界面
    initInCarPage();

    //测试xml的代码
    DomXML::createXML("demo.xml"); //创建空的xml文件
//    QStringList list;
//    list << "一汽大众" << "毕加索" << "39" << "1" << "39";
//    DomXML::appendXML("demo.xml", list);

//    QStringList fList, bList, pList, nList, tList;
//    DomXML::readXML("demo.xml", fList, bList, pList, nList, tList);

//    for(int i = 0; i < fList.size(); ++i)
//    {
//        QString str = QString("%1:%2:卖出了%3，单价：%4，总价：%5")
//                .arg(fList.at(i))
//                .arg(bList.at(i))
//                .arg(nList.at(i))
//                .arg(pList.at(i))
//                .arg(tList.at(i));
//        qDebug() << str;
//    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

//车辆管理菜单
void MainWindow::on_actionCar_triggered()
{
    //切换到车辆管理页面
    ui->stackedWidget->setCurrentWidget(ui->car);
    ui->label->setText("车辆管理");
    ui->toolBox->setCurrentIndex(0); // 车辆管理页面默认显示出售车辆
}

//销售统计菜单
void MainWindow::on_actionCalc_triggered()
{
    //切换到销售统计页面
    ui->stackedWidget->setCurrentWidget(ui->calc);
    ui->label->setText("销售统计");

    QSqlQueryModel *queryModel = new QSqlQueryModel(this); //新建模型
    queryModel->setQuery("SELECT NAME FROM FACTORY"); //执行sql语句，数据在模型中
    ui->cbBFactory->setModel(queryModel); //厂家下拉框
}

//连接数据库
void MainWindow::connectDB()
{
    //添加数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1"); //ip
    db.setUserName("root"); //用户
    db.setPassword("yanglinqi"); //密码
    db.setDatabaseName("car"); //数据库
    //打开数据库
    if(!db.open())
    {
        QMessageBox::warning(this, "数据库打开失败", db.lastError().text());
        return;
    }
}

//初始化数据
void MainWindow::initSellCarPage()
{
    QSqlQueryModel *queryModel = new QSqlQueryModel(this); //新建模型
    queryModel->setQuery("SELECT NAME FROM FACTORY"); //执行sql语句，数据在模型中

    ui->comboBoxFactory->setModel(queryModel); //厂家下拉框

    ui->labelLast->setText("0"); // 剩余数量
    ui->lineEditTotal->setEnabled(false); // 金额
}

//厂家下拉框槽函数
void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "请选择厂家")
    {// 内容清空
        ui->comboBoxBrand->clear(); //品牌下拉框清空
        ui->lineEditPrice->clear(); //报价清空
        ui->labelLast->setText("0"); //剩余数量
        ui->lineEditTotal->clear(); //金额清空
        ui->spinBox->setValue(0); //数量选择框清0
        ui->spinBox->setEnabled(false);
        ui->buttonSure->setEnabled(false);
    }
    else
    {
        ui->comboBoxBrand->clear(); //先清空品牌下拉框
        QSqlQuery query;
        QString sql = QString("select name from brand where factory='%1'").arg(arg1);
        //执行sql语句
        query.exec(sql);

        //获取内容
        while(query.next())
        {
            QString name = query.value(0).toString();
            ui->comboBoxBrand->addItem(name);
        }
        ui->spinBox->setEnabled(true);
    }
}

//品牌下拉框槽函数
void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    QString sql = QString("select price,last from brand where factory='%1' and name='%2'")
            .arg(ui->comboBoxFactory->currentText())
            .arg(arg1);
    qDebug() << ui->comboBoxFactory->currentText() << arg1;
    qDebug() << sql;
    //执行sql语句
    query.exec(sql);

    //获取内容
    while(query.next())
    {
        int price = query.value("price").toInt(); //报价
        int last = query.value("last").toInt(); //剩余
        ui->lineEditPrice->setText(QString::number(price));
        ui->labelLast->setText(QString::number(last));
        ui->spinBox->setMaximum(last);
    }
    ui->spinBox->setValue(0);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->buttonSure->setEnabled(false);
    }
    else
    {
        ui->buttonSure->setEnabled(true);
    }
    QString factory = ui->comboBoxFactory->currentText();
    QString brand = ui->comboBoxBrand->currentText();
    QSqlQuery query;
    QString sql = QString("select last from brand where factory='%1' and name='%2'")
            .arg(factory)
            .arg(brand);
    query.exec(sql);
    int last = 0;
    while(query.next())
    {
        last = query.value("last").toInt();
    }
    //更新剩余数量
    int tmp = last - arg1;
    ui->labelLast->setText(QString::number(tmp)); //剩余数量

    //金额
    int price = ui->lineEditPrice->text().toInt(); //报价
    int sum = price * arg1;
    ui->lineEditTotal->setText(QString::number(sum));
}

//取消按钮
void MainWindow::on_buttonCancel_clicked()
{
    ui->comboBoxFactory->setCurrentIndex(0);
}

//确定按钮
void MainWindow::on_buttonSure_clicked()
{
    //获取信息
    int num = ui->spinBox->value(); //销售数量
    int last = ui->labelLast->text().toInt(); //剩余数量

    //获取数据库 中的 销量
    QSqlQuery query;
    QString sql = QString("select sell from brand where factory='%1' and name='%2'")
            .arg(ui->comboBoxFactory->currentText())
            .arg(ui->comboBoxBrand->currentText());
    //执行sql语句
    query.exec(sql);

    //把确认后的数据更新到xml中
    QStringList list;
    list << ui->comboBoxFactory->currentText() << ui->comboBoxBrand->currentText() << ui->lineEditPrice->text()
         << QString::number(num) << ui->lineEditTotal->text();
    DomXML::appendXML("demo.xml", list);

    QStringList fList, bList, pList, nList, tList, timeList;
    DomXML::readXML("demo.xml", fList, bList, pList, nList, tList, timeList);
    ui->textEdit->clear(); //先清空显示区

    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    ui->textEdit->append(dateStr);

    for(int i = 0; i < fList.size(); ++i)
    {
        QString str = QString("%1 卖出了%2-%3，单价：%4，数量：%5，总价：%6")
                .arg(timeList.at(i))
                .arg(fList.at(i))
                .arg(bList.at(i))
                .arg(pList.at(i))
                .arg(nList.at(i))
                .arg(tList.at(i));
        ui->textEdit->append(str);
        qDebug() << str.toUtf8();
    }

    int sell;
    while(query.next())
    {
        sell = query.value("sell").toInt();
    }
    sell += num;
    //更新数据库，剩余数量 销售总量
    sql = QString("update brand set sell = %1, last = %2 where factory='%3' and name='%4'")
            .arg(sell)
            .arg(last)
            .arg(ui->comboBoxFactory->currentText())
            .arg(ui->comboBoxBrand->currentText());
    query.exec(sql);
}

//销售统计页面 厂家下拉框
void MainWindow::on_cbBFactory_currentIndexChanged(const QString &arg1)
{
    QSqlQueryModel *queryModel = new QSqlQueryModel(this); //新建模型
    QString sql = QString("SELECT NAME FROM BRAND WHERE FACTORY='%1'").arg(arg1);
    queryModel->setQuery(sql); //执行sql语句，数据在模型中
    ui->cbBBrand->setModel(queryModel); //品牌下拉框
    drawHistogram();
}

void MainWindow::on_cbBBrand_currentIndexChanged(const QString &arg1)
{
    drawPie(arg1);
}

void MainWindow::drawHistogram()
{
    ui->widgetHistogram->SetMaxValue(70);
    QSqlQuery query;
    QString sql = QString("select name, sell from brand where factory='%1';")
            .arg(ui->cbBFactory->currentText());
    query.exec(sql);
    ui->widgetHistogram->Clear();

    while(query.next())
    {
        QString name = query.value(0).toString();
        int sell = query.value(1).toInt();
        QColor color(qrand()%255, qrand()%255, qrand()%255);
        ui->widgetHistogram->AddItem(name, sell, color);
    }
}

void MainWindow::drawPie(QString arg)
{
    QSqlQuery query;
    QString sql = QString("select sell, last from brand where factory='%1' and name='%2';")
            .arg(ui->cbBFactory->currentText())
            .arg(arg);
    query.exec(sql);
    float sell, last;
    while(query.next())
    {
        sell = query.value(0).toInt();
        last = query.value(1).toInt();
    }

    QVector<SectorInfo> data;
    SectorInfo info;
    info.description="已出售";
    info.percent = (sell / (sell + last)) * 100;
    data.push_back(info);

    info.description="剩余";
    info.percent = 100 - info.percent;
    data.push_back(info);

    ui->widgetPie->setData(data);
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    if(index == 0)
    {
        ui->textEdit->show();
    }
    else
    {
        ui->textEdit->hide();
    }
}

void MainWindow::initInCarPage()
{
    model->setTable("brand"); // 设置使用哪个表

    //把model放在view中
    ui->tableView->setModel(model);

    //显示model中的数据
    model->select();

    //设置编辑策略，手动提交
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

void MainWindow::on_btnAdd_clicked()
{
    //添加空记录
    QSqlRecord record = model->record();
    //获取model的行数
    int row = model->rowCount();
    model->insertRecord(row, record);
}

void MainWindow::on_btnDel_clicked()
{
    //取出选中的模型
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    //取出模型中每行的索引
    QModelIndexList indexList = selectModel->selectedRows();
    //删除所有选中的行
    for(int i = 0; i < indexList.size(); ++i)
    {
        model->removeRow(indexList.at(i).row());
    }
}

void MainWindow::on_btnCommit_clicked()
{
    model->submitAll(); //提交所有动作
}

void MainWindow::on_btnCannel_clicked()
{
    model->revertAll();  //取消所有动作
    model->submitAll();  //提交所有动作
}
