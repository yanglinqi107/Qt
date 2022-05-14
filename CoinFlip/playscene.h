#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
#include <QLabel>
#include <QSound>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = 0);

    PlayScene(int levelNum);

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    //游戏地图
    void gameMap();

    //翻转金币
    void turnCoin(MyCoin *coin);

    //判断是否胜利
    bool justWin();

    //胜利的动画
    void animationOfWin();

    int levelIndex; //记录关卡号

    int gameArray[4][4];

    MyCoin *coinBtn[4][4];

    bool isAnimation = false; //是否有金币正在翻转，金币翻转时不能点击

    bool isWin = false;

    QLabel *winLabel; //胜利的图片

    QSound *flipSound; //点击音乐的音效

    QSound *backSound; //点击返回的音效

    QSound *winSound; //胜利的音效

signals:
    void playSceneBack();

public slots:

};

#endif // PLAYSCENE_H
