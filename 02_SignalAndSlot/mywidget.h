#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "student.h"
#include "teacher.h"

namespace Ui {
class myWidget;
}

class myWidget : public QWidget
{
    Q_OBJECT

public:
    explicit myWidget(QWidget *parent = 0);
    ~myWidget();
    void classIsOver();

private:
    Ui::myWidget *ui;
    Student *st;
    Teacher *zt;
};

#endif // MYWIDGET_H
