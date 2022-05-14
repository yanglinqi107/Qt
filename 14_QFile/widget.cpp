#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        QString str = QFileDialog::getOpenFileName(this, "打开文件", "D:\\MLZ107\\Desktop");
        ui->lineEdit->setText(str);

        QTextCodec *codec = QTextCodec::codecForName("GBK");   //设置编码格式

        QFile file(str);//str文件路径   QFile默认编码格式UTF-8
        file.open(QIODevice::ReadOnly);//打开方式
        QByteArray array = file.readAll();//读取所有内容
        //ui->textEdit->setText(array);//在textEdit中显示
        ui->textEdit->setText(codec->toUnicode(array));

        file.close();   //关闭文件


//        file.open(str);
//        file.open(QIODevice::Append);
//        file.write("fjeofj都无可哦");
//        file.close();
        QFileInfo info(str);
        qDebug() << "文件大小：" << info.size() << " 后缀名：" << info.suffix() << " 文件名：" << info.fileName() << " 文件路径：" << info.filePath();
        qDebug() << "创建日期：" << info.created().toString("yyyy/MM/dd hh:mm:ss");
        qDebug() << "最后修改时间：" << info.lastModified().toString("yyyy/MM/dd hh:mm:ss");

    });
}

Widget::~Widget()
{
    delete ui;
}
