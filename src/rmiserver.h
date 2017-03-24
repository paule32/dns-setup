#ifndef RMISERVER_H
#define RMISERVER_H

#include <QTcpServer>

class RMIServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit RMIServer(QObject *parent = 0);
    void startServer();
signals:
    
public slots:
    
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif
