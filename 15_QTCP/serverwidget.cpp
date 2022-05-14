#include "serverwidget.h"
#include "ui_serverwidget.h"

#include <QByteArray>

ServerWidget::ServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    this->setWindowTitle("服务器: 8888");

    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字
    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any, 8888);  //监听

    connect(tcpServer, &QTcpServer::newConnection, [=](){
        // 取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //获取对方ip和端口
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        QString tmp = QString("[%1:%2]:成功连接").arg(ip).arg(port);
        //在窗口显示
        ui->textEditRead->setText(tmp);

        connect(tcpSocket, &QTcpSocket::readyRead, [=](){
            //从通信套接字中取出内容
            QByteArray array = tcpSocket->readAll();
            //在显示textEdit中追加内容
            ui->textEditRead->append(array);
        });

    });

}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::on_ButtonSend_clicked()
{
    if(tcpSocket == NULL) return;
    // 获取编辑区内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发送数据
    tcpSocket->write(str.toUtf8().data());
}

void ServerWidget::on_ButtonClose_clicked()
{
    if(tcpSocket == NULL) return;
    //主动和客户端端口断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket = NULL;
}
