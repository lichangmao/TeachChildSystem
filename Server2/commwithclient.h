#ifndef COMMWITHCLIENT_H
#define COMMWITHCLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QImage>
#include <QVector>
#include <QPixmap>
#include <QByteArray>
#include "records.h"
#include "student.h"

class QTcpSocket;


/**
 * @brief The CommWithClient class
 * 这个类用于处理和client的通信
 */

class CommWithClient : public QObject
{
    Q_OBJECT
public:
    explicit CommWithClient(QTcpSocket *socket);
    //
    //void sendPoints();
    //接收图片
    void receivePixmap();
    //接收到一个学生类的对象
    void receiveStudentObject();

//    Student& getStudent();


private:
    //用于标志学生对象中收到了多少个字段
    int total;
    //用于存储收到学生对象中的字段
    Student stu;
    QTcpSocket *tcpClient;
    //数据的总长度
    quint64 totalMessageSize;
    //表示当前数据流中数据类型：有以下的类型
    quint16 status;

    static const quint16 STATUS_NULL = 0x0000;
    static const quint16 DATA_HEAD_PICTURE = 0x0001;
    static const quint16 DATA_RESULT = 0x0002;
    static const quint16 DATA_POINT_CAST = 0x0003;
    static const quint16 DATA_POINT_PAINT = 0x0004;
    static const quint16 DATA_STU_ID = 0x0005;
    static const quint16 DATA_STU_NAME = 0x0006;

    //缓冲区
    QByteArray buffer;

private:
    void receiveID();
    void receiveName();

public slots:
    //显示错误
    void displayError(QAbstractSocket::SocketError);
    //从socket中读取信息
    void readMessage();
    //向学生播放
    void Play(QList<records> pointList);
    //发送多个点
    void sendPoints(QList<records> &points);

signals:
    //信号:提示接收到图片
    void recePixmap(QPixmap pixmap);
    //信号:提示接收到学生对象
    void receStuObject();

};

#endif // COMMWITHCLIENT_H
