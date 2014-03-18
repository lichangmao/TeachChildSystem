#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QThreadPool>
#include <QTcpServer>
#include <QList>

#include "records.h"

class MainWindow;


class CommWithClient;
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void listen(quint16 port);
    ~Server();

private:
   // MainWindow *window;
    QTcpServer *tcpServer;
    QList<CommWithClient*> clientList;

signals:

public slots:
    void sendClientPoint(QList<records> points);
    void replayNewConnection();
    void BroadCast();

};

#endif // SERVER_H
