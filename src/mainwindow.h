#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QMainWindow>

#include "rmiserver.h"

class QAction;
class QMenu;

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow();
    void createConnectionView();
    
    QGroupBox * groupBoxL;
    QGroupBox * groupBoxR;
    
    QLabel  * warnLabel;
    QWidget * loginBox;
    
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
    void createView();
    
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

extern class MainWindow *app_window;

#endif
