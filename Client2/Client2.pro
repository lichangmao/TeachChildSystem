#-------------------------------------------------
#
# Project created by QtCreator 2014-03-10T09:26:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network

TARGET = Client2
TEMPLATE = app


SOURCES += main.cpp\
    client.cpp \
    student.cpp \
    cmainwindow.cpp \
    myscene.cpp \
    myview.cpp

HEADERS  += \
    client.h \
    student.h \
    cmainwindow.h \
    myscene.h \
    myview.h \
    records.h

FORMS    +=

RESOURCES += \
    Images.qrc
