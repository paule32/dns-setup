#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QApplication>
#include <QWidget>
#include <QMainWindow>

#include "rmiserver.h"

class QAction;
class QMenu;

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    
protected:
private slots:
    void addServer();
    void delServer();
    
    void options();
    void closeWin();
    void about();
    void aboutFrameWork();
    
private:
    void createActions();
    void createMenus();
    
    QMenu * fileMenu;
    QMenu * helpMenu;
    
    QAction * fileActionA;
    QAction * fileActionB;
    
    QAction * fileAction1;
    QAction * fileAction2;
    
    QAction * helpAction1;
    QAction * helpAction2;
    
    RMIServer * server;
};

#endif
