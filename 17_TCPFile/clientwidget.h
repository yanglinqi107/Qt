#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();

private slots:
    void on_ButtonConnect_clicked();

private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;  //通信套接字
    QFile file;    //文件对象
    QString fileName; //文件名
    qint64 fileSize; //文件大小
    qint64 recvSize; //已发送文件大小
    bool isStart;  //标志位
};

#endif // CLIENTWIDGET_H
