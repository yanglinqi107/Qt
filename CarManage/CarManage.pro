#-------------------------------------------------
#
# Project created by QtCreator 2022-05-11T17:14:18
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CarManage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    domxml.cpp \
    histogram.cpp \
    pie.cpp

HEADERS  += mainwindow.h \
    domxml.h \
    histogram.h \
    pie.h

FORMS    += mainwindow.ui
