#include <QDebug>
#include <QFile>
#include <QTcpSocket>
#include "server.h"
#include "mainwindow.h"
#include "commwithclient.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(replayNewConnection()));
    //window = new MainWindow();
    //window->show();
}


void Server::replayNewConnection(){
    QTcpSocket *tcpClient = tcpServer->nextPendingConnection();

    CommWithClient *dealClient = new CommWithClient(tcpClient);
    clientList.push_back(dealClient);

    //connect(dealClient,SIGNAL(recePixmap(QPixmap)),window,SLOT(showImage(QPixmap)));
    QThread *thread = new QThread(this);

    dealClient->moveToThread(thread);

    thread->start();
    qDebug()<<"New connection";

}

void Server::BroadCast(){
    QList<records> pointList;
    //文件名为MyRecordPoints.txt
    QFile file("MyRecordPoints.txt");
    //以只读和文本方式打开
    if(!file.open(QFile::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream stream(&file);
    records re;
    char c;
    while(!stream.atEnd()){
        stream>>re.x>>re.y>>re.w>>c;
        pointList.append(re);
    }

    QList<CommWithClient*>::const_iterator it = clientList.begin();
    for(;it != clientList.end();it++)
        (*it)->Play(pointList);
}

void Server::listen(quint16 port){
    if(!tcpServer->listen(QHostAddress::Any,port)){
        qDebug()<<tcpServer->errorString();
        tcpServer->close();
    }
    
    qDebug()<<"Server listen";
}

//void Server::

void Server::sendClientPoint(QList<records> points){
    QList<CommWithClient*>::const_iterator it = clientList.begin();
    for(;it != clientList.end();it++)
        (*it)->sendPoints(points);
    qDebug()<<"send point to all client";
}

Server::~Server(){
    //while(clientList.)
}
