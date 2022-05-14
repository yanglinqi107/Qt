#-------------------------------------------------
#
# Project created by QtCreator 2022-03-11T17:26:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 10_smallWidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    smallwidget.cpp

HEADERS  += widget.h \
    smallwidget.h

FORMS    += widget.ui \
    smallwidget.ui

CONFIG   += C++11
