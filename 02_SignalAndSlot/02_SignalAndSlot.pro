#-------------------------------------------------
#
# Project created by QtCreator 2022-03-09T15:50:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 02_SignalAndSlot
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    teacher.cpp \
    student.cpp

HEADERS  += mywidget.h \
    teacher.h \
    student.h

FORMS    += mywidget.ui

CONFIG   += C++11
