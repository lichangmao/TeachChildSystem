#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QHostAddress>
#include <QThread>

#include <QPoint>
#include <QList>

#include "student.h"
#include "records.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    //发送图片
    void sendPixmap(QPixmap pixmap, quint16 cmd);
    void sendStudentObject(Student &student);
    //关闭socket
    void close();

protected:
    void run();

public slots:
    //从socket中读取数据
    void  readMessage();
    //接收点
    QList<records> receivePoint();
    //错误处理
    void displayError(QAbstractSocket::SocketError);
    //连接服务器
    void connecToHost(QHostAddress &address,quint16 port);
    void connecToHost(QHostAddress::SpecialAddress address, quint16 port);
private:
    void bytesWriteSocket(QByteArray &buf);


    QList<records> pointList;

    QTcpSocket *tcpSocket;
    //表示当前数据流中数据类型：
    quint16 status;
    static const quint16 STATUS_NULL = 0x0000;
    static const quint16 DATA_HEAD_PICTURE = 0x0001;
    static const quint16 DATA_RESULT = 0x0002;
    static const quint16 DATA_POINT_CAST = 0x0003;
    static const quint16 DATA_POINT_PAINT = 0x0004;
    static const quint16 DATA_STU_ID = 0x0005;
    static const quint16 DATA_STU_NAME = 0x0006;

    //数据的总长度
    quint64 totalMessageSize;
    //缓冲区
    QByteArray buffer;

    void Broadcast();

    void Paint();
signals:
    void BroadcastSignal(QList<records>);
    void PaintSignal(QList<records>);
};

#endif // CLIENT_H
