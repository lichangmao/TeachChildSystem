#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T08:52:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network

TARGET = Server2
TEMPLATE = app


SOURCES += main.cpp\
    server.cpp \
    commwithclient.cpp \
    student.cpp \
    myscene.cpp \
    myview.cpp \
    mainwindow.cpp

HEADERS  += \
    server.h \
    commwithclient.h \
    student.h \
    myscene.h \
    myview.h \
    records.h \
    mainwindow.h

FORMS    +=

RESOURCES +=
