#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

#include "mainwindow.h"
#include "rmiserver.h"

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    
    setWindowTitle(QString::fromUtf8("DNS-Server client 1.0 - Jens Kallup"));
    move(0,0);
    resize(800,600);
    
    createActions();
    createMenus();
}

void MainWindow::addServer()
{
    fileActionA->parentWidget()->hide();
    fileActionB->parentWidget()->show();

    try {
        if (nullptr == server)
        server = new RMIServer;    
        server->startServer();
    } catch (...) {
        QMessageBox::critical(0,"Listen Error!","Port already in use.");
    }
}

void MainWindow::delServer()
{
    fileActionA->parentWidget()->show();
    fileActionB->parentWidget()->hide();
}

void MainWindow::options() {
}

void MainWindow::closeWin() {
    close();
}

void MainWindow::about() {
}

void MainWindow::aboutFrameWork()
{
    QApplication::aboutQt();
} 

void MainWindow::createActions()
{
    fileActionA = new QAction("Start server", this);
    fileActionB = new QAction("Stop server", this);
    
    connect(fileActionA, &QAction::triggered, this, &MainWindow::addServer);
    connect(fileActionB, &QAction::triggered, this, &MainWindow::delServer);
    
    fileAction1 = new QAction("&Options ...", this);
    fileAction2 = new QAction("Exit",this);
    fileAction2->setShortcuts(QKeySequence::Quit);
    
    connect(fileAction1, &QAction::triggered, this, &MainWindow::options);
    connect(fileAction2, &QAction::triggered, this, &MainWindow::closeWin);
    
    helpAction1 = new QAction("About Qt", this);
    helpAction2 = new QAction("About",this);
    
    connect(helpAction1, &QAction::triggered, this, &MainWindow::aboutFrameWork);
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu("File");
    helpMenu = new QMenu("Help");

    fileMenu->addAction(fileActionA);    
    fileMenu->addAction(fileAction1);
    fileMenu->addSeparator();
    fileMenu->addAction(fileAction2);
    
    helpMenu->addAction(helpAction1);
    helpMenu->addAction(helpAction2);
    
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

