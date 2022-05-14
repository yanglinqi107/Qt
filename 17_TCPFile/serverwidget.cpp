#include "serverwidget.h"
#include "ui_serverwidget.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    //设置按钮不可用
    ui->ButtonFile->setEnabled(false);
    ui->ButtonSend->setEnabled(false);

    tcpServer = new QTcpServer(this); //分配空间，指定父对象

    tcpServer->listen(QHostAddress::Any, 8888); //监听，并绑定端口号8888
    setWindowTitle("服务器端口：8888");

    //如果客户端成功和服务器连接，QTcpServer会自动触发newConnection信号
    connect(tcpServer, &QTcpServer::newConnection, [=](){
        //取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //获取对方的ip和端口
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        //弹出对话框
        QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
        //QMessageBox::information(this, "info", str);
        ui->textEdit->setText(str);
        //成功连接后，才能选择文件
        ui->ButtonFile->setEnabled(true);

        connect(tcpSocket, &QTcpSocket::readyRead, [=](){
            //取客户端的信息
            QByteArray buf = tcpSocket->readAll();
            if(QString(buf) == "file done") //客户端文件接收完毕
            {
                ui->textEdit->append("文件发送完毕");
            }
        });
    });

    connect(&timer, &QTimer::timeout, [=](){
        timer.stop();
        sendData();
    });
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_ButtonFile_clicked()
{
    file.close();
    QString filePath = QFileDialog::getOpenFileName(this, "open", "../");
    qDebug() << filePath << endl;
    if(!filePath.isEmpty()) //如果选择文件路径有效
    {
        fileName.clear();
        fileSize = 0;
        //获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName(); //获取文件名字
        fileSize = info.size();     //获取文件大小
        sendSize = 0;
        //只读方式打开文件
        file.setFileName(filePath); //指定文件路径
        bool isOK = file.open(QIODevice::ReadOnly);
        if(false == isOK)
        {
            qDebug() << "只读方式打开文件失败";
        }

        //提示打开文件的路径
        ui->textEdit->append(filePath);

        ui->ButtonSend->setEnabled(true);
    }
    else
    {
        qDebug() << "选择文件路径出错";
    }
}

void ServerWidget::on_ButtonSend_clicked()
{
    ui->textEdit->append("文件正在发送...");
    //先发送文件头信息  文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket->write(head.toUtf8().data());
    if(len > 0) //头部信息发送成功
    {
        //发送真正文件内容
        //防止TCP黏包问题，需要使用定时器延时
        timer.start(20);
    }
    else
    {
        qDebug() << "头部信息发送失败" ;
        file.close();
    }
}

void ServerWidget::sendData()
{
    qint64 len = 0;
    do
    {
        //每次发送4KB数据
        char buf[4 * 1024] = {0};
        len = 0;
        //从文件中读取数据
        len = file.read(buf, sizeof(buf));
        //发送数据，读多少，发多少
        tcpSocket->write(buf, len);

        //当前发送数据总量
        sendSize += len;
    }while(len > 0);

    //是否发送文件完毕
    if(sendSize == fileSize)
    {
        ui->textEdit->append("文件发送完毕");
        file.close();
        ui->ButtonSend->setEnabled(false);
        ui->ButtonFile->setEnabled(false);
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
    }
}
