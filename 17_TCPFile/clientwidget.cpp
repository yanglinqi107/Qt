#include "clientwidget.h"
#include "ui_clientwidget.h"

#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    isStart = true;

    tcpSocket = new QTcpSocket(this);

    //进度条位于0
    ui->progressBar->setValue(0);

    connect(tcpSocket, &QTcpSocket::readyRead, [=](){
        //取出接收到的内容
        QByteArray buf = tcpSocket->readAll();
        if(isStart == true)  //接收头
         {
             isStart = false;
             //解析头部信息 QString s = "hello##1024"
             // s.section()可以拆分字符串，和Python的split()类似
             fileName = QString(buf).section("##", 0, 0);
             fileSize = QString(buf).section("##", 1, 1).toInt();
             recvSize = 0;
             file.setFileName(fileName);
             bool isOK = file.open(QIODevice::WriteOnly);
             if(isOK == false)
             {
                 qDebug() << "writeOnly error" ;
                 tcpSocket->disconnectFromHost();
                 tcpSocket->close();
                 return; // 如果打开文件失败，中断函数
             }
             QString str = QString("接收文件：[%1: %2kb]").arg(fileName).arg(fileSize/1024);
             QMessageBox::information(this, "文件信息", str);

             //设置进度条
             ui->progressBar->setMinimum(0); // 最小值
             ui->progressBar->setMaximum(fileSize/1024); //最大值
             ui->progressBar->setValue(0);  //当前值
         }
         else   //文件信息
         {
             qint64 len = file.write(buf);
             recvSize += len;
             if(recvSize == fileSize)   //文件接收完毕
             {
                 file.close();
                 //先给服务器发送信息
                 tcpSocket->write("file done");
                 QMessageBox::information(this, "提示", QString("文件接收完成"));

                 tcpSocket->disconnectFromHost();
                 tcpSocket->close();
             }
             //更新进度条
             ui->progressBar->setValue(recvSize/1024);
         }
    });
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::on_ButtonConnect_clicked()
{
    //获取服务器IP和端口
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip), port);
}
