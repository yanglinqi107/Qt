#include "multiwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    multiWidget w;
    w.show();

    return a.exec();
}
