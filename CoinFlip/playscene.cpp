#include "playscene.h"
#include <QIcon>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QFont>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>

//PlayScene::PlayScene(QWidget *parent) :
//    QWidget(parent)
//{
//}

PlayScene::PlayScene(int levelNum)
{
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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

    //胜利的音效
    winSound = new QSound(":/res/LevelWinSound.wav", this);
    //点击金币的音效
    flipSound = new QSound(":/res/ConFlipSound.wav", this);
    //返回按钮的音效
    backSound = new QSound(":/res/BackButtonSound.wav", this);

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &QPushButton::clicked, [=](){
        //由于点击返回按钮之后，选择关卡页面会把该游戏界面的内存释放掉，速度很快，所以听不到返回音效
        backSound->play();

        //告诉主场景 返回 主场景监听ChooseLevelScene的返回按钮
        this->hide();
        emit playSceneBack();
    });

    QLabel *label = new QLabel(this);
    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);  //设置字号
    QString str = QString("Level: %1").arg(this->levelIndex);//显示的文字
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str);
    //设置标签位置
    label->setGeometry(QRect(30, this->height() - 50, 150, 50));

    //初始化游戏地图
    dataConfig data;

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            gameArray[i][j] = data.mData[this->levelIndex][i][j];
        }
    }

    //胜利的标签和图片
    winLabel = new QLabel(this);
    QPixmap pix(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, pix.width(), pix.height()); //标签大小
    winLabel->setPixmap(pix); //设置图片
    winLabel->move((this->width() - pix.width()) * 0.5, -pix.height());

    gameMap();
}

void PlayScene::gameMap()
{
    //显示金币背景图案
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            //绘制背景图片
            QLabel *label = new QLabel;
            QPixmap pix(":/res/BoardNode.png");
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            //创建金币
            QString str = QString(":/res/Coin0001.png");
            if(gameArray[i][j] == 0)
            {
                str = ":/res/Coin0008.png";
            }
            MyCoin *coin = new MyCoin(str);
            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];   //1正面 0反面
            coin->setParent(label);
            coin->move((label->width() - coin->width()) * 0.5, (label->height() - coin->height()) * 0.5);

            //将金币放入到金币的二维数组，以便后期 的维护
            coinBtn[i][j] = coin;

            //监听金币是否翻转
            connect(coin, &QPushButton::clicked, [=](){
                if(this->isAnimation || isWin) return;
                flipSound->play(); //播放金币翻转的音效
                turnCoin(coin); //翻转金币
                if(justWin())
                {
                    animationOfWin();
                }
            });
        }
    }
}

//翻转金币
void PlayScene::turnCoin(MyCoin *coin)
{
    this->isAnimation = true;
    coin->changeFlag();

    //翻转周围硬币操作
    if(coin->posX + 1 < 4) //右侧金币
    {
        coinBtn[coin->posX + 1][coin->posY]->changeFlag();
    }
    if(coin->posX - 1 >= 0) //左侧金币
    {
        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
    }
    if(coin->posY + 1 < 4) //下方金币
    {
        coinBtn[coin->posX][coin->posY + 1]->changeFlag();
    }
    if(coin->posY - 1 >= 0) //上方金币
    {
        coinBtn[coin->posX][coin->posY - 1]->changeFlag();
    }
    this->isAnimation = false;
}

//判断是否胜利
bool PlayScene::justWin()
{
    //判断是否胜利
    this->isWin = true;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if(coinBtn[i][j]->flag == false)
            {
                this->isWin = false;
                i = 4; // 跳出循环
                break;
            }
        }
    }
    return this->isWin;
}

//胜利的特效
void PlayScene::animationOfWin()
{
    winSound->play(); //播放胜利的音效
    //动效
    QPropertyAnimation *animation = new QPropertyAnimation(winLabel, "geometry");
    //设置时间间隔
    animation->setDuration(1000);
    //设置起始位置
    animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
    //设置终点位置
    animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 114, winLabel->width(), winLabel->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

//重写paintEvent事件
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
