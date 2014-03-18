#include <QTcpSocket>
#include <QDebug>
#include <QTextCodec>
#include "serverthread.h"
#include "commwithclient.h"

ServerThread::ServerThread(QTcpSocket *socket){
    tcpSocket = socket;
}

void ServerThread::run(){
    qDebug()<<"running";
    CommWithClient dealClient(tcpSocket);
    connect(tcpSocket,SIGNAL(readyRead()),&dealClient,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(disconnected()),tcpSocket,SLOT(deleteLater()));
    dealClient.moveToThread(this);
    //dealClient.readMessage();
    dealClient.sendMessage();
    tcpSocket->disconnectFromHost();
    qDebug()<<"Thread exit";
    exec();
}
