#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = 0);

signals:


public slots:
    //早期QT版本 必须写道public slots下，高级版本可以写到 public或者全局下
    //返回值  void 需要声明和实现
    //可以有参数，可以重载
    void treat();

    void treat(QString foodName);
};

#endif // STUDENT_H
