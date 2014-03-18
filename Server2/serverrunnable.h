#ifndef SERVERRUNNABLE_H
#define SERVERRUNNABLE_H

#include <QRunnable>

class QTcpSocket;

class ServerRunnable : public QRunnable
{

public:
    explicit ServerRunnable(QTcpSocket *socket);
    void sendMessage();
    void disConnect();

protected:
    void run();

private:
    QTcpSocket *tcpClient;

};

#endif // SERVERTHREAD_H
