#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QPixmap>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    //设置窗口标题
    setWindowTitle("翻金币");

    //设置固定大小
    setFixedSize(320, 588);

    //设置窗体左上角图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    connect(ui->actionQuit, &QAction::triggered, [=](){
        this->close();
    });

    //准备点击开始按钮的音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav", this);


    //开始按钮
    MyPushButton *startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);  //设定父亲
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7); //设置按钮位置

    this->chooseLevelScene = new ChooseLevelScene(this);

    //按钮点击后 按钮跳到
    connect(startBtn, &QPushButton::clicked, [=](){
        startSound->play(); //播放音效
        startBtn->zoomDown(); //向下跳
        startBtn->zoomUp();     //向上跳
        //延时进入选择关卡
        QTimer *timer = new QTimer(this);
        timer->start(500);
        connect(timer, &QTimer::timeout, [=](){
            //设置场景的出现位置和切换的窗口位置一致
            this->chooseLevelScene->setGeometry(this->geometry());
            this->chooseLevelScene->show();
            this->hide();
            timer->stop();
        });
        //5.3版本不支持
//        QTimer::singleShot(500, this, [=](){
//            this->hide();
//            this->chooseLevelScene->show();
//        });


    });

    //监听选择关卡的返回按钮的信号
    connect(chooseLevelScene, &ChooseLevelScene::chooseSceneBack, this, [=](){
        chooseLevelScene->hide();   //将选择关卡场景 隐藏
        //设置场景的出现位置和切换的窗口位置一致
        this->setGeometry(chooseLevelScene->geometry());
        this->show();               //显示主场景
    });
}

MainScene::~MainScene()
{
    delete ui;
}

//重写paintEvent事件 或背景图
void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家
    QPainter painter(this);
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    //设置起点0，0 和 图片的长高 使其铺满屏幕
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上的图标
    pix.load(":/res/Title.png");
    //图片长宽各缩一半
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);
}
