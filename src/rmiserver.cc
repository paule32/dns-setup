#include <iostream>

#include <QThread>
#include <QMessageBox>
#include <QLabel>
#include "mainwindow.h"
#include "rmiserver.h"
#include "thread.h"

RMIServer::RMIServer(QObject *parent) :
    QTcpServer(parent)
{
}

void RMIServer::startServer()
{
    int port = 1234;

    if(!this->listen(QHostAddress::Any, port))
    {
        if (app_window->loginBox)
        app_window->loginBox->hide();
               
        app_window->warnLabel = new QLabel(app_window->groupBoxR);
        app_window->warnLabel->setText("Could Not Connect To Server !!!");
        app_window->warnLabel->setFont(QFont("Arial",20));
        app_window->warnLabel->move(10,10);
        app_window->warnLabel->resize(420,50);
        app_window->warnLabel->show();
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
