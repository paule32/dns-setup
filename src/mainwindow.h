#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QTabWidget>
#include <QListWidget>
#include <QMainWindow>

#include "cafemessage.h"
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
    
    QStringList guestAction;
    
    QListWidget * nameserverList;
    QLineEdit   * nameserverEdit;
    
protected:
public slots:
    void hostEditchanged(QString text);
    void portEditchanged(QString text);
    void proxEditchanged(QString text);
    
    void nameserverEditChange(QString text);
    
private slots:
    void nameserverAddClick();
    void nameserverEditClick();
    void nameserverDeleteClick();
    
    void showSettingsTabPrinter1();
    void showSettingsTabPrinter2();
    void showSettingsTabPrinter3();
    void showSettingsTabPrinter4();
    
    void setupPrinter1();
    
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
    
    void initData();

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

    MyCafeMessage * message;
    
    QWidget * printer_tab1;
    QWidget * printer_tab2;
    QWidget * printer_tab3;
    QWidget * printer_tab4;
    QWidget * printer_tab5;
    
    QTabWidget * printerTab;
   
    RMIServer * server;
};

extern class MainWindow *app_window;

#endif
