#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = 0);

    MyCoin(QString btnImg);

    //设置金币图片
    void initCoinPicture(QString path);

    int posX;   //x坐标
    int posY;   //y坐标
    bool flag;  //正反标识

    //改变标志的方法
    void changeFlag();

    QTimer *postToNega;  //正面翻反面的定时器
    QTimer *negaToPost;  //反面翻正面的定时器

    bool isAnimation = false;   //正在翻转动画

    int min = 1;
    int max = 8;

signals:

public slots:

};

#endif // MYCOIN_H
