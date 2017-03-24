#ifndef MYTHREAD_H_
#define MYTHREAD_H_

#include <QThread>
#include <QTcpSocket>

class RMIThread: public QThread
{
    Q_OBJECT
public:
    explicit RMIThread(qintptr ID, QObject *parent = 0);
    void run();
    
signals:
    void error(QTcpSocket::SocketError socketerror);
    
public slots:
    void readyRead();
    void disconnected();
    
private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
};

#endif
