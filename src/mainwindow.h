#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QTabWidget>
#include <QMainWindow>

#include "rmiserver.h"

class QAction;
class QMenu;

class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow();
   
    QGroupBox * groupBoxL;
    QGroupBox * groupBoxR;
    
    QLabel  * warnLabel;
    QWidget * loginBox;
    
protected:
private slots:
    void addServer();
    void delServer();

    void createConnectionView();    
    void createSettingsView();
    void intoLogin();
    
    void options();
    void closeWin();
    void about();
    void aboutFrameWork();
    
private:
    void createActions();
    void createMenus();
    void createView();

    QLineEdit * userEdit;
    QLineEdit * passEdit;
    
    QScrollArea * scroller;
    QTabWidget  * mainTab;
    
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
