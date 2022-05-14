#include "mythread.h"

MyThread::MyThread(QObject *parent) :
    QThread(parent)
{
}

void MyThread::run()
{
    //复杂数据处理，耗时较长
    sleep(5); //耗时5s
    emit isDone();
}
