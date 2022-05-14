#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //添加图标、本地图片路径
    //ui->actionNew->setIcon(QIcon("D:/MLZ107/Pictures/图标/03083511.gif"));

    //使用添加Qt资源               ": + 前缀 + 文件名"
    ui->actionNew->setIcon(QIcon(":/icon/03083511.gif"));
    ui->actionOpen->setIcon(QIcon(":/icon/03083520.gif"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
