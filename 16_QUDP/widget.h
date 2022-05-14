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

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void dealMsg();  //槽函数，处理对方发送过来的数据

private slots:
    void on_ButtonSend_clicked();

private:
    Ui::Widget *ui;

    QUdpSocket *udpSocket; // UDP套接字
};

#endif // WIDGET_H
