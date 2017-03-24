#include <iostream>

#include "rmiserver.h"
#include "thread.h"

RMIServer::RMIServer(QObject *parent) :
    QTcpServer(parent)
{
}

void RMIServer::startServer()
{
    int port = 1234;

    if(!this->listen(QHostAddress::Any, port)) {
        std::cout << "Could not start server" << std::endl;
    }
    else {
        std::cout << "Listening to port " << port << "...\n";
    }
}

// This function is called by QTcpServer when a new connection is available. 
void RMIServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    std::cout << socketDescriptor << " Connecting..." << std::endl;
    
    // Every new connection will be run in a newly created thread
    RMIThread *thread = new RMIThread(socketDescriptor, this);
    
    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    
    thread->start();
}
