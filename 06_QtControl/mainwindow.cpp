#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置单选按钮 男默认选中
    ui->rBtnMan->setChecked(true);

    //选中女后 打印信息
    connect(ui->rBtnWoman, &QRadioButton::clicked, [=](){
       qDebug() << "选中性别女" <<endl;
    });

    //多选按钮  2 选中  0 未选中
    connect(ui->cBox, &QCheckBox::stateChanged, [=](int state) {
        qDebug() << state;
    });

//    //利用listWidget写诗
//    QListWidgetItem * item = new QListWidgetItem("锄禾日当午");
//    //将一行诗放入到listWidget控件中
//    ui->listWidget->addItem(item);
//    //设置文本水平居中
//    item->setTextAlignment(Qt::AlignHCenter);

    //QStringList  QList<QString>
    QStringList list;
    list << "锄禾日当午" << "汗滴禾下土" << "谁知盘中餐" << "粒粒皆辛苦" ;
    ui->listWidget->addItems(list);
}

MainWindow::~MainWindow()
{
    delete ui;
}
