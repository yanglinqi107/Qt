#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>  //包含头文件 QWidget窗口类

namespace Ui {
class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT    // 宏，允许类中使用信号和槽的机制

public:
    explicit myWidget(QWidget *parent = 0); //构造函数
    ~myWidget();

private:
    Ui::myWidget *ui;
};

#endif // MYWIDGET_H
