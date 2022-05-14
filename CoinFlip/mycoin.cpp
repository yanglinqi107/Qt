#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) :
//    QPushButton(parent)
//{
//}

MyCoin::MyCoin(QString btnImg)
{
    initCoinPicture(btnImg);

    //初始化定时器对象
    postToNega = new QTimer(this);
    negaToPost = new QTimer(this);

    //监听正面翻反面的信号，并翻转金币
    connect(postToNega, &QTimer::timeout, [=](){
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        initCoinPicture(str);

        if(this->min > this->max)
        {
            this->isAnimation = false;
            this->min = 1;
            postToNega->stop();
        }
    });

    //监听正面翻反面的信号，并翻转金币
    connect(negaToPost, &QTimer::timeout, [=](){
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        initCoinPicture(str);

        if(this->max < this->min)
        {
            this->isAnimation = false;
            this->max = 8;
            negaToPost->stop();
        }
    });
}

void MyCoin::initCoinPicture(QString path)
{
    QPixmap pix;
    bool ret = pix.load(path);
    if(!ret)
    {
        qDebug() << path << "图片加载失败";
    }
    //设置按钮大小
    this->setFixedSize(pix.width(), pix.height());
    //设置图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //按钮添加图片
    this->setIcon(pix);
    //设置图片大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}

//改变标志的方法
void MyCoin::changeFlag()
{
    if(this->isAnimation)
    {
        return;
    }
    this->isAnimation = true;
    if(this->flag)
    {
        postToNega->start(30);
    }
    else
    {
        negaToPost->start(30);
    }
    this->flag = !flag;
}
