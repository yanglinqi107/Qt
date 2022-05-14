#ifndef MULTIWIDGET_H
#define MULTIWIDGET_H
#include "childwidget.h"
#include <QWidget>

namespace Ui {

class multiWidget;
}

class multiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit multiWidget(QWidget *parent = 0);
    ~multiWidget();
    void showChildWidget();

private:
    Ui::multiWidget *ui;
    QWidget cw;
    bool isOpen;
};

#endif // MULTIWIDGET_H
