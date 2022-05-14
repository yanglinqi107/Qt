#include "chooselevelscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(320, 588);

    setWindowTitle("选择关卡场景");

    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar *menuBar = new QMenuBar();
    setMenuBar(menuBar);

    //创建开始菜单
    QMenu *startMenu = menuBar->addMenu("开始");
    //退出
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //选择关卡的音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav", this);
    //返回按钮的音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav", this);

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &QPushButton::clicked, [=](){
        //qDebug() << "点击了返回按钮";
        //播放返回按钮的音效
        backSound->play();
        //告诉主场景 返回 主场景监听ChooseLevelScene的返回按钮
        this->hide();
        emit chooseSceneBack();
    });

    //创建选择关卡的按钮
    for(int i = 0; i < 20; ++i)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

        //点击按钮，进入游戏界面
        connect(menuBtn, &QPushButton::clicked, [=](){
            //播放选择关卡的音效
            chooseSound->play();
            //qDebug() << "这是第" << i + 1 << "关";
            playScene = new PlayScene(i + 1);
            this->hide();
            //设置场景的出现位置和切换的窗口位置一致
            playScene->setGeometry(this->geometry());
            playScene->show();

            connect(playScene, &PlayScene::playSceneBack, [=](){
                //设置场景的出现位置和切换的窗口位置一致
                this->setGeometry(this->geometry());
                this->show();
                delete playScene;
                playScene = NULL;
                backSound->play();
            });
        });

        QLabel *label = new QLabel(menuBtn);
        label->setText(QString::number(i + 1));
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        //设置文字对齐方式 水平居中 Qt::AlignHCenter  垂直居中Qt::AlignVCenter  中间Qt::AlignCenter
        label->setAlignment(Qt::AlignCenter);

        //便签覆盖在按钮上，会挡住鼠标的点击，要设置label的属性为穿透鼠标事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

//重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //加载背景
    QPixmap pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
