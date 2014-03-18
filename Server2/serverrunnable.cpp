#include <QTcpSocket>
#include <QTextCodec>
#include <QDebug>
#include <QThread>
#include "serverrunnable.h"


ServerRunnable::ServerRunnable(QTcpSocket *socket){
    tcpClient = socket;
}


void ServerRunnable::disConnect(){
    tcpClient->disconnectFromHost();
}

void ServerRunnable::run(){
    sendMessage();
    disConnect();
    qDebug()<<"running";
    while(true)
        ;
    qDebug()<<"Thread exit";
}

void ServerRunnable::sendMessage(){
    QByteArray buffer;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    out<<QObject::tr("Hello");
    qDebug()<<"Send message to Client:Hello";
    //out.flush();
    tcpClient->write(buffer);
    tcpClient->flush();


}
