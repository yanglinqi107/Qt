#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    enum MsgType {Msg, UsrEnter, UsrLeft};

public:
    explicit Widget(QWidget *parent, QString name);
    ~Widget();

    void closeEvent(QCloseEvent *); //重写关闭窗口事件

    void sndMsg(MsgType type); //广播UDP消息
    void usrEnter(QString userName); //处理新用户加入
    void usrLeft(QString usrname, QString time); //处理用户离开
    QString getUsr(); //获取用户名
    QString getMsg(); //获取聊天信息

private:
    void ReceiverMessage(); //接受UDP消息

signals:
    //关闭窗口发送关闭信号
    void closeWinget();

private:
    Ui::Widget *ui;

    QUdpSocket *udpSocket; //udp套接字
    qint16 port; //端口
    QString uName; //用户名
};

#endif // WIDGET_H
