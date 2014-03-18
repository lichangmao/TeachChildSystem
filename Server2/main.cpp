
#include <QApplication>
#include <QThread>
#include <QDebug>
#include <QTextCodec>

#include "mainwindow.h"
#include "myview.h"
#include "myscene.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    MainWindow* masterwindow=new MainWindow;
    masterwindow->show();
    masterwindow->setWindowTitle("Server");

    //add
    Server server;
    //开始监听
    server.listen((quint16)8989);
    QObject::connect(masterwindow->scene,SIGNAL(canSend(QList<records>)),&server,SLOT(sendClientPoint(QList<records>)));
    //add end
    return a.exec();
}
