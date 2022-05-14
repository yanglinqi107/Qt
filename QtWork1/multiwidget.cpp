#include "multiwidget.h"
#include "ui_multiwidget.h"
#include <QPushButton>

multiWidget::multiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::multiWidget)
{
    ui->setupUi(this);
    QPushButton *openBtn = new QPushButton("open", this);
    openBtn->move(0, 100);
    QPushButton *closeBtn = new QPushButton("close", this);
    closeBtn->move(100, 100);

    //cw.setParent(this);

    connect(closeBtn, &QPushButton::clicked, this, [=](){ cw.hide(); });

    //void(multiWidget::*cw)(void) = &multiWidget::createChildWidget;

    connect(openBtn, &QPushButton::clicked, this, &multiWidget::showChildWidget);
}

multiWidget::~multiWidget()
{
    delete ui;
}

void multiWidget::showChildWidget() {
    cw.show();
}

