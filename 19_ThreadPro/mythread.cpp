#include "mythread.h"

#include <QThread>
#include <QDebug>

MyThread::MyThread(QObject *parent) :
    QObject(parent)
{
    isStop = false;
}

//线程处理函数
void MyThread::myTimeout()
{
    while(!isStop)
    {
        QThread::sleep(1);
        emit mySignal();
        qDebug() << "子线程号：" << QThread::currentThread();
    }
}

void MyThread::setFlag(bool flag)
{
    isStop = flag;
}
