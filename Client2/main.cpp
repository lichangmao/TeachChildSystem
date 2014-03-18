#include <QApplication>
#include <QTextCodec>
#include <QHostAddress>
#include "cmainwindow.h"
#include "myview.h"
#include "myscene.h"
#include "client.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    MainWindow* masterwindow=new MainWindow;
    masterwindow->show();
    masterwindow->setWindowTitle("client");
    Client client;
    QObject::connect(&client,SIGNAL(PaintSignal(QList<records>)),masterwindow->scene,SLOT(SynShow(QList<records>)));
    client.connecToHost(QHostAddress::LocalHost,8989);



    return a.exec();
}
