#ifndef DIALOGLIST_H
#define DIALOGLIST_H

#include <QWidget>

namespace Ui {
class DialogList;
}

class DialogList : public QWidget
{
    Q_OBJECT

public:
    explicit DialogList(QWidget *parent = 0);
    ~DialogList();

private:
    Ui::DialogList *ui;

    QVector<bool> isShow; //保存聊天窗口是否打开的标识，避免一直创建聊天窗口
};

#endif // DIALOGLIST_H
