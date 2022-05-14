#include "widget.h"
#include "ui_widget.h"

#include <QHostAddress>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //分配空间，指定父对象
    udpSocket = new QUdpSocket(this);

    //绑定
    udpSocket->bind(8880);

//    //绑定端口要指定IPv4地址
//    udpSocket->bind(QHostAddress::AnyIPv4, 8888);
//    //加入组播，组播地址是D类地址
//    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.2"));
//    //离开组播
//    udpSocket->leaveMulticastGroup();

    setWindowTitle("端口号：8880");

    //当对方成功发送数据过来，自动触发readyRead信号
    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::dealMsg);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::dealMsg()
{
    //获取对方发送的内容
    char buf[1024] = {0};
    QHostAddress peerIP;
    quint16 peerPort;
    qint64 len = udpSocket->readDatagram(buf, sizeof(buf), &peerIP, &peerPort); // 返回值为读取数据大小
    if(len > 0)
    {
        //格式化 [192.78.2.2:8888]
        QString str = QString("[%1:%2] %3").arg(peerIP.toString()).arg(peerPort).arg(buf);
        //给编辑区设置内容
        ui->textEdit->setText(str);
    }
}

void Widget::on_ButtonSend_clicked()
{
    //先获取对方的IP和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    //获取编辑区内容
    QString str = ui->textEdit->toPlainText();

    //给指定的IP发送数据
    udpSocket->writeDatagram(str.toUtf8(), QHostAddress(ip), port);
}
