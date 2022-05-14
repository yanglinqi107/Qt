#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置水平头
    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "英雄介绍");

    QTreeWidgetItem * liItem = new QTreeWidgetItem(QStringList() << "力量");
    QTreeWidgetItem * miItem = new QTreeWidgetItem(QStringList() << "敏捷");
    QTreeWidgetItem * zhiItem = new QTreeWidgetItem(QStringList() << "智力");

    //加载顶层的节点
    ui->treeWidget->addTopLevelItem(liItem);
    ui->treeWidget->addTopLevelItem(miItem);
    ui->treeWidget->addTopLevelItem(zhiItem);

    //追加子结点
    QStringList heroL1, heroL2;
    heroL1 << "赵云" << "天美亲儿子";
    heroL2 << "李白" << "打野一哥";
    QTreeWidgetItem *l1 = new QTreeWidgetItem(heroL1);
    QTreeWidgetItem *l2 = new QTreeWidgetItem(heroL2);
    liItem->addChild(l1);
    liItem->addChild(l2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
