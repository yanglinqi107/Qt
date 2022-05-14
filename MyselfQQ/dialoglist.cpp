#include "dialoglist.h"
#include "ui_dialoglist.h"
#include <QToolButton>
#include "widget.h"

DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);

    QList<QString> nameList;
    nameList << "水票奇缘" << "忆梦如澜" <<"北京出版人"<<"Cherry"<<"淡然"
             <<"娇娇girl"<<"落水无痕"<<"青墨暖暖"<<"无语";

    QStringList iconNameList; //图标资源列表
    iconNameList << "spqy"<< "ymrl" <<"qq" <<"Cherry"<< "dr"
                 <<"jj"<<"lswh"<<"qmnn"<<"wy";

    QVector<QToolButton*> vToolBtn; //保存按钮的容器

    for(int i = 0; i < 9; ++i)
    {
        //设置标题
        setWindowTitle("MyselfQQ 2022");
        //设置图标
        setWindowIcon(QPixmap(":/images/qq.png"));

        //QToolButton显示头像和文字信息
        QToolButton *btn = new QToolButton;
        //设置文件
        btn->setText(nameList.at(i));
        //设置头像
        QString str = QString(":/images/%1.png").arg(iconNameList.at(i));
        btn->setIcon(QPixmap(str));
        //设置头像大小
        btn->setIconSize(QPixmap(str).size());
        //设置按钮风格 透明
        btn->setAutoRaise(true);
        //设置文字和图片一起显示
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        //加到 垂直布局中
        ui->vLayout->addWidget(btn);

        vToolBtn.push_back(btn);
        isShow.push_back(false);
    }

    //对9个按钮 添加信号槽
    for(int i = 0; i < vToolBtn.size(); ++i)
    {
        connect(vToolBtn[i], &QToolButton::clicked, [=]()mutable{
            //如果窗口已被打开，就不再打开
            if(isShow[i])
            {
                vToolBtn[i]->show();
                return;
            }
            isShow[i] = true;

            //弹出聊天对话框
            //构造聊天对话框，告诉该窗口在和谁聊天
            Widget *widget = new Widget(0, vToolBtn[i]->text());
            //设置窗口标题
            widget->setWindowTitle(vToolBtn[i]->text());
            widget->setWindowIcon(vToolBtn[i]->icon());
            widget->show();

            connect(widget, &Widget::closeWinget, [=]()
            {
                 isShow[i] = false;
            });
        });
    }
}

DialogList::~DialogList()
{
    delete ui;
}
