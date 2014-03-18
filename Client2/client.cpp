#include <QDataStream>
#include <QByteArray>
#include <QDebug>
#include <QHostAddress>
#include <QTextCodec>
#include <QLabel>
#include <QBuffer>
#include <QPixmap>
#include <QFile>
#include <QList>
#include "client.h"

Client::Client(QObject *parent):QObject(parent)
{
    //初始化
    totalMessageSize = 0;
    //状态我初始值为STATUS_NULL
    status= STATUS_NULL;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}



/**
* @brief Client::connecToHost :连接服务器
* @param address 服务器地址
* @param port 服务器端口
*/
void Client::connecToHost(QHostAddress &address,quint16 port){
    tcpSocket->connectToHost(address,port);
}
void Client::connecToHost(QHostAddress::SpecialAddress address, quint16 port){
    tcpSocket->connectToHost(address,port);
}

/**
 * @brief Client::readMessage
 * 发送数据的格式:数据的长度 + 命令 + 数据(数据长度包括数据本身的长度和命令的长度)
 * 数据的长度:sizeof(quint64)
 * 命令的长度:sizeof(quint16)
 *
 * 命令类型:
 * 发送图片:DATA_IMAGE
 * 发送坐标:DATA_POINT
 */
void Client::readMessage(){
    //如果totalMessageSize ==0,说明收到的是一段新的数据
    if(totalMessageSize == 0){

        if(tcpSocket->bytesAvailable()<(int)(sizeof(quint16)+sizeof(quint64)))
            return;
        quint16 cmdType;

        QDataStream in(tcpSocket);
        in.setVersion(QDataStream::Qt_4_7);

        in>>totalMessageSize;
        in>>cmdType;
        qDebug()<<"totalMessageSize="<<totalMessageSize;
        qDebug()<<"cmdType= "<<cmdType;
        //数据部分的长度要减去 sizeof(quint16)和sizeof(quint64)
        totalMessageSize -= sizeof(quint16);
        totalMessageSize -= sizeof(quint64);

        switch(cmdType){
        case DATA_POINT_CAST:
            status = DATA_POINT_CAST;
            Broadcast();
            break;
        case DATA_POINT_PAINT:
            status = DATA_POINT_PAINT;
            Paint();
            break;
        default:
            qDebug()<<"Error cmdType: "<<cmdType;
        }
    }else{
    //如果totalMessageSize ！= 0,说明此数据还没有接收完
        switch (status) {        
        case DATA_POINT_CAST:
            status = DATA_POINT_CAST;
            Broadcast();
            break;
        case DATA_POINT_PAINT:
            status = DATA_POINT_PAINT;
            Paint();
            break;
            //写到这
        default:
            break;
            qDebug()<<"Error status: "<<status;
        }
    }
}

void Client::Broadcast(){
    receivePoint();
    //emit BroadcastSignal(points);
}

void Client::Paint(){
     QList<records> points = receivePoint();

     for(int i=0;i<points.size();i++){
         qDebug()<<points[i].x<<" "<<points[i].y<<"  "<<points[i].w;
     }
    // if(points != pointList){
       // pointList = points;
        emit PaintSignal(points);

   //  }

}

QList<records> Client::receivePoint(){
    //QByteArray buffer;
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_7);
    QList<records> Tpoints;

    records record;

    while(!in.atEnd()){
        in>>record.x>>record.y>>record.w;
        qDebug()<<"( "<<record.x<<","<<record.y<<","<<record.w<<")";
        Tpoints.append(record);
    }
    //qDebug()<<"pointList.size()= "<<pointList.size();
    //qDebug()<<sizeof(records);
    //qDebug()<<pointList.size()*sizeof(records);
    totalMessageSize -= (Tpoints.size()*(sizeof(record.x)+sizeof(record.y)+sizeof(record.w)));
    qDebug()<<"totalMessageSize ="<<totalMessageSize;

    if(totalMessageSize == 0)
        status = STATUS_NULL;

    return Tpoints;

}

/**
 * @brief Client::sendPixmap 发送图片
 * @param pixmap
 */

void Client::sendPixmap(QPixmap pixmap, quint16 cmd){

    QByteArray buffer;
    QBuffer b;
    QDataStream out(&buffer,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    //留下两个空位，第一个是数据的总长度,第二个是命令
    out<<(quint64)0 <<(quint16)0;
    pixmap.save(&b, "PNG", -1);

    buffer.append(b.buffer());
    out.device()->seek(0);
    out<<(quint64)buffer.size()<<(quint16)cmd;

    bytesWriteSocket(buffer);

}

void Client::bytesWriteSocket(QByteArray &buf){
    quint64 writenSize = 0;
    qint64 n = 0;
    quint64 total = buf.size();
    while(writenSize != total){
        n = tcpSocket->write(buf);
        if(n == -1){
            qDebug()<<"send to server error";
            continue;
        }
        writenSize += n;

    }
    tcpSocket->flush();
    qDebug()<<"send finish. size have write to socket ="<<writenSize;
}

void Client::sendStudentObject(Student &student){
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    //发送Student::id
    out<<(quint64)0 <<(quint16)0;
    out<<student.getId();
    out.device()->seek(0);
    out<<(quint64)buf.size()<<(quint16)DATA_STU_ID;
    bytesWriteSocket(buf);

    //发送Student::name
    buf.clear();
    out.device()->seek(0);
    out<<(quint64)0 <<(quint16)0;
    out<<student.getName();
    out.device()->seek(0);
    out<<(quint64)buf.size()<<(quint16)DATA_STU_NAME;
    bytesWriteSocket(buf);

    //发送Student::headPicture
    /*
    buf.clear();
    out.device()->seek(0);
    out<<(quint64)0 <<(quint16)0;
    out<<student.getHeadPicture();
    out.device()->seek(0);
    out<<(quint64)buf.size()<<(quint16)DATA_HEAD_PICTURE;
    bytesWriteSocket(buf);
    */
    quint16 cmd=DATA_HEAD_PICTURE;
    sendPixmap(student.getHeadPicture(),(quint16)DATA_HEAD_PICTURE);

    //发送Student::result
    /*
    buf.clear();
    out.device()->seek(0);
    out<<(quint64)0 <<(quint16)0;
    out<<student.getResult();
    out.device()->seek(0);
    out<<(quint64)buf.size()<<(quint16)DATA_RESULT;
    bytesWriteSocket(buf);
    */
    cmd = DATA_RESULT;
    sendPixmap(student.getResult(),cmd);

}

/**
 * @brief Client::close  关闭socket
 */

void Client::close(){
    tcpSocket->close();
}
/**
 * @brief Client::displayError 显示出错
 */
void Client::displayError(QAbstractSocket::SocketError){
    qDebug()<<tcpSocket->errorString();
}
