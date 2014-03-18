#include <QDataStream>
#include <QTcpSocket>
#include <QTextCodec>
#include <QThread>
#include <QVector>
#include <QFile>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QBuffer>
#include "commwithclient.h"

CommWithClient::CommWithClient(QTcpSocket *socket){
    tcpClient = socket;
    //初始化
    status = 0;
    totalMessageSize = 0;
    total= 0;
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    //connect(tcpClient,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    connect(this,SIGNAL(receStuObject()),&stu,SLOT(print()));
}

/**
 * @brief CommWithClient::displayError
 * 显示出错信息
 */
void CommWithClient::displayError(QAbstractSocket::SocketError){
    qDebug()<<tcpClient->errorString();
}


/**
 * @brief CommWithClient::readMessage
 * 发送数据的格式:数据的长度 + 命令 + 数据(数据长度包括数据本身的长度和命令的长度)
 * 数据的长度:sizeof(quint64)
 * 命令的长度:sizeof(quint16)
 * 命令类型:
 * 发送图片:DATA_IMAGE
 * 发送坐标:DATA_POINT
 */
void CommWithClient::readMessage(){

    qDebug()<<"readMessage";
    QDataStream stream(tcpClient);
    stream.setVersion(QDataStream::Qt_4_7);

    //qDebug()<<"bytesAvailable= "<<tcpClient->bytesAvailable();
    //如果totalMessageSize的长度为0，表明这是一段新的数据
    if(0 ==  totalMessageSize){
        if(tcpClient->bytesAvailable()<(int)(sizeof(quint64)+sizeof(quint16)))
            return;
        //总长度
        stream >> totalMessageSize;
        quint16 cmdType;

        //命令
        stream>>cmdType;
        qDebug()<<"cmdTyed= "<<cmdType;
        //数据部分的长度要减去 sizeof(quint16)和sizeof(quint64)
        totalMessageSize -= sizeof(quint16);
        totalMessageSize -= sizeof(quint64);

        switch(cmdType){
        /*
        case DATA_POINTS:
            status = DATA_POINTS;
            //
            break;
            */
        case DATA_HEAD_PICTURE:
            status = DATA_HEAD_PICTURE;
            receivePixmap();
            break;
        case DATA_RESULT:
            status = DATA_RESULT;
            receivePixmap();
            break;
        case DATA_STU_ID:
            status = DATA_STU_ID;
            receiveID();
            break;
        case DATA_STU_NAME:
            status = DATA_STU_NAME;
            receiveName();
            break;
        default:
            qDebug()<<"Error cmdType: "<<cmdType;
        }
    }else{
        //否则表示这不是一段新的数据
        switch(status){
        case DATA_HEAD_PICTURE:
            receivePixmap();
            break;
         /*
        case DATA_POINTS:
            //
            break;
            */
        case DATA_RESULT:
            receivePixmap();
            break;
        case DATA_STU_ID:
            receiveID();
            break;
        case DATA_STU_NAME:
            receiveName();
            break;
        }
    }


}

void CommWithClient::receiveID(){
    if((quint64)tcpClient->bytesAvailable()<totalMessageSize)
        return;
    int id;
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_7);
    in>>id;
    status = STATUS_NULL;
    total++;
    stu.setId(id);
    if(total == 4){
        emit receStuObject();
        total = 0;
    }
    totalMessageSize =0;

}

void CommWithClient::receiveName(){
    if((quint64)tcpClient->bytesAvailable()<totalMessageSize)
        return;
    QString name;
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_7);
    in>>name;
    status = STATUS_NULL;
    total++;
    stu.setName(name);
    if(total == 4){
        emit receStuObject();
        total = 0;
    }
    totalMessageSize =0;
}

/**
 * @brief CommWithClient::receivePixmap 接收图片
 */
void CommWithClient::receivePixmap(){
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_7);

   while(!tcpClient->atEnd()){
       QByteArray temp = tcpClient->read(totalMessageSize);
       totalMessageSize -= temp.size();
       buffer.push_back(temp);
   }
    //当totalMessageSize == 0,表示图片已经接收完
   if(totalMessageSize == 0){
        QPixmap pixmap;
        pixmap.loadFromData(buffer,"PNG");

        //发出图片已经接收完的信号
        emit recePixmap(pixmap);
        qDebug()<<"Rece pixmap";
        //把状态置为STATUS_NULL

        //清空缓冲区
        buffer.clear();
        if(status == DATA_HEAD_PICTURE){
            total++;
            stu.setHeadPicture(pixmap);
            if(total == 4){
                emit receStuObject();
                total = 0;
            }
        }else if(status == DATA_RESULT){
            total++;
            stu.setResult(pixmap);
            if(total == 4){
                emit receStuObject();
                total = 0;
            }
        }
        status = STATUS_NULL;
    }

}

//Student& CommWithClient::getStudent(){
//    return stu;
//}


/**
 * @brief CommWithClient::broadcast 从文件中读出数据，并把它们发送到client
 */
void CommWithClient::Play(QList<records> pointList){
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);

    out<<(quint64)0<<(quint16)0;
    for(int i=0;i<pointList.size();i++){
        out<<pointList[i].x<<pointList[i].y<<pointList[i].w;
    }
    out.device()->seek(0);

    out<<(quint64)buf.size()<<(quint16)DATA_POINT_CAST;
    tcpClient->write(buf);
    tcpClient->flush();
}
/**
 * @brief CommWithClient::sendPoints  发送多个坐标极其颜色
 * @param points  点的链表，包含多个点
 */

void CommWithClient::sendPoints(QList<records> &points){
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    //在数据包的首部留下两个字段，第一个字段为数据的总长度，第二个字段为数据的类型
    out<<(quint64)0<<(quint16)0;
    //把多个坐标写入到buf中
    for(int i=0;i<points.size();i++){
        out<<points.at(i).x<<points.at(i).y<<points.at(i).w;
    }

    out.device()->seek(0);
    //第一个字段为数据的总长度，第二个字段为数据的类型
    out<<(quint64)buf.size()<<(quint16)DATA_POINT_PAINT;
    tcpClient->write(buf);
    tcpClient->flush();
}
