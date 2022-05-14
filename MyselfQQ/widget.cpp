#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QDateTime>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化操作
    udpSocket = new QUdpSocket(this);
    //用户名
    uName = name;
    //端口号
    this->port = 9999;

    //绑定端口号  绑定模式 共享地址|断线重连
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    //发送新用户进入
    sndMsg(UsrEnter);

    connect(ui->sendBtn, &QPushButton::clicked, [=](){
        sndMsg(Msg);
    });

    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::ReceiverMessage);

    connect(ui->exitBtn, &QPushButton::clicked, this, &Widget::close);

    ////////////////////////辅助功能/////////////////////////////
    //字体
    connect(ui->fontCbx, &QFontComboBox::currentFontChanged, [=](const QFont &font){
        ui->msgTxtEdit->setCurrentFont(font);
        ui->msgTxtEdit->setFocus();
    });

    //字号
    void (QComboBox:: *cbxsingal)(const QString &text) = &QComboBox::currentIndexChanged;
    connect(ui->sizeCbx, cbxsingal, [=](const QString &text){
        ui->msgTxtEdit->setFontPointSize(text.toDouble());
        ui->msgTxtEdit->setFocus();
    });

    //加粗
    connect(ui->boldTBtn, &QToolButton::clicked, [=](bool isCheck){
        if(isCheck)
        {
            ui->msgTxtEdit->setFontWeight(QFont::Bold);
        }
        else
        {
            ui->msgTxtEdit->setFontWeight(QFont::Normal);
        }
    });

    //倾斜
    connect(ui->italicTBtn, &QToolButton::clicked, [=](bool check){
        ui->msgTxtEdit->setFontItalic(check);
    });

    //下划线
    connect(ui->underlineTBtn, &QToolButton::clicked, [=](bool check){
        ui->msgTxtEdit->setFontUnderline(check);
    });

    //字体颜色
    connect(ui->colorTBtn, &QToolButton::clicked, [=](){
        QColor color = QColorDialog::getColor(Qt::black);
        ui->msgTxtEdit->setTextColor(color);
    });

    //保存
    connect(ui->saveTBtn, &QToolButton::clicked, [=](){
        if(ui->msgBrowser->document()->isEmpty()) return;
        QString path = QFileDialog::getSaveFileName(this, "保存记录", "聊天记录", "(*.txt)");
        if(path.isEmpty()) return;

        QFile file(path); //只写  追加   文本换行
        file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        QTextStream stream(&file);
        stream << ui->msgBrowser->toPlainText();
        file.close();
    });

    //清空
    connect(ui->clearTBtn, &QToolButton::clicked, [=](){
        ui->msgBrowser->clear();
    });
}

QString Widget::getUsr()
{
    return uName;
}

void Widget::ReceiverMessage()
{
    //拿到数据报文
    qint64 size = udpSocket->pendingDatagramSize(); //获取报文长度
    QByteArray arr = QByteArray(size, 0);
    udpSocket->readDatagram(arr.data(), size);

    //解析数据
    //第一段 类型  第二段 用户名 第三段 数据
    QDataStream stream(&arr, QIODevice::ReadOnly);
    int msgType; //类型
    QString usrName; //用户名
    QString msg; //消息

    //获取当前时间
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    stream >> msgType; //类型
    stream >> usrName; //用户

    switch (msgType) {
    case Msg:
        stream >> msg;
        //最近聊天记录
        ui->msgBrowser->setTextColor(Qt::blue);
        ui->msgBrowser->append("[" + usrName + " " + time + "]");
        ui->msgBrowser->append(msg);
        break;
    case UsrEnter:
        //更新右侧TableWidget
        usrEnter(usrName);
        break;
    case UsrLeft:
        //更新右侧TableWidget
        usrLeft(usrName, time);
        break;
    }
}

void Widget::usrEnter(QString userName)
{
    bool isEmpty = ui->usrTblWidget->findItems(userName, Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem *usr = new QTableWidgetItem(userName);

        //插入行
        ui->usrTblWidget->insertRow(0);
        ui->usrTblWidget->setItem(0, 0, usr);

        //追加聊天记录
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(QString("%1 上线了").arg(userName));
        //在线人数更新
        ui->usrNumLbl->setText(QString("在线用户：%1人").arg(ui->usrTblWidget->rowCount()));

        //把自身信息广播出去
        sndMsg(UsrEnter);
    }
} //处理新用户加入

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *e)
{
    emit this->closeWinget();

    sndMsg(UsrLeft);
    //断开套接字
    udpSocket->close();
    udpSocket->destroyed();

    QWidget::closeEvent(e);
}

void Widget::sndMsg(MsgType type)
{
    //发送的消息分为3中类型
    //数据做分段处理 第一段 类型 第二段 用户名 第三段 内容

    QByteArray arr;

    QDataStream stream(&arr, QIODevice::WriteOnly);

    stream << type << getUsr(); //第一段类型 第二段用户名 添加到流中

    switch(type)
    {
    case Msg: //普通消息发送
    {
        if(ui->msgTxtEdit->toPlainText() != "") //输入内容不为空
        {
            stream << getMsg();
        }
        break;
    }
    case UsrEnter:
        break;
    case UsrLeft:
        break;
    };

    //书写报文广播发送
    udpSocket->writeDatagram(arr, QHostAddress::Broadcast, port);

}

QString Widget::getMsg()
{
    QString str = ui->msgTxtEdit->toHtml(); //因为由字体、大小、加粗等，要用toHtml;

    //清空输入框
    ui->msgTxtEdit->clear();
    //光标
    ui->msgTxtEdit->setFocus();

    return str;
}

void Widget::usrLeft(QString usrname, QString time)
{
    bool isEmpty = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).isEmpty();
    if(!isEmpty)
    {
        int row = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).first()->row();
        ui->usrTblWidget->removeRow(row);

        //追加聊天记录
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(QString("%1 于 %2 离开").arg(usrname).arg(time));

        //在线人数更新
        ui->usrNumLbl->setText(QString("在线用户：%1人").arg(ui->usrTblWidget->rowCount()));
    }
}//处理用户离开
