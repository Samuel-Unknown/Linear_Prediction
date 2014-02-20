#-------------------------------------------------
#
# Project created by QtCreator 2013-11-20T22:14:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Linear_Prediction
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    matrices.cpp \
    linearprediction.cpp \
    graphics.cpp

HEADERS  += mainwindow.h \
    matrices.h \
    linearprediction.h \
    graphics.h

FORMS    += mainwindow.ui

OTHER_FILES +=
