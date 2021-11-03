#-------------------------------------------------
#
# Project created by QtCreator 2020-12-18T09:04:58
#
#-------------------------------------------------

QT       += core gui sql printsupport #charts datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test11
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    qcustomplot.cpp \
    calculate.cpp
HEADERS  += mainwindow.h \
    qcustomplot.h \
    calculate.h

FORMS    += mainwindow.ui
CONFIG +=c++11
