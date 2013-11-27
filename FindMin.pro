#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T01:27:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FindMin
TEMPLATE = app
CONFIG += c++11
INCLUDEPATH += .

SOURCES += main.cpp\
        mainwindow.cpp \
    drawwidget.cpp \
    point.cpp \
    myrand.cpp \
    minimization.cpp \
    methods.cpp \
    expression.cpp \
    base.cpp \
    functionandlimits.cpp \
    changedialog.cpp

HEADERS  += mainwindow.h \
    drawwidget.h \
    point.h \
    myrand.h \
    minimization.h \
    methods.h \
    function.h \
    expression.h \
    base.h \
    functionandlimits.h \
    changedialog.h

OTHER_FILES += \
    input.txt
