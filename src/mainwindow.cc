#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QAction>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QPainter>
#include <QPushButton>
#include <QSettings>
#include <QStatusBar>
#include <QScrollArea>
#include <QListWidget>
#include <QMessageBox>

#include "label.h"
#include "mainwindow.h"
#include "rmiserver.h"

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    
    setWindowTitle(QString::fromUtf8("DNS-Server client 1.0 - Jens Kallup"));
    move(0,0);
    resize(800,600);

    warnLabel = nullptr;
    loginBox  = nullptr;
    scroller  = nullptr;
    mainTab   = nullptr;
    
    createActions();
    createMenus();
    createView();
}

void MainWindow::addServer()
{
    try {
        //if (nullptr == server)
        server = new RMIServer;    
        server->startServer();
    } catch (...) {
        QMessageBox::critical(0,"Listen Error!","Port already in use.");
    }
}

void MainWindow::delServer()
{

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
    fileMenu->addAction(fileActionB);
    fileMenu->addAction(fileAction1);
    fileMenu->addSeparator();
    fileMenu->addAction(fileAction2);
    
    helpMenu->addAction(helpAction1);
    helpMenu->addAction(helpAction2);
    
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::createView()
{
    groupBoxL = new QGroupBox(this);
    groupBoxL->move(10,35);
    groupBoxL->resize(140,532);
    groupBoxL->setStyleSheet(
    "background-color:cyan; " \
    "border: 1px solid black; border-radius: 10px;");
    
    MyWidget *pixwid1 = new MyWidget(groupBoxL);
    QLabel *pix1 = new QLabel(pixwid1);
    QImage  img1("./img/pc2.png");
    QImage  imgA = img1.scaled(120,130,Qt::KeepAspectRatio);
    
    pix1->setPixmap(QPixmap::fromImage(imgA));
    pix1->setAlignment(Qt::AlignCenter);
    
    pixwid1->move(10,10);
    pixwid1->resize(120,96);
    
    MyLabel *pixA = new MyLabel(groupBoxL,QString("New connection"));
    pixA->move(9,100);
 
    connect(pixwid1, SIGNAL(clicked()), this, SLOT(createConnectionView()));
    connect(pixA   , SIGNAL(clicked()), this, SLOT(createConnectionView()));
    //
    
    MyWidget *pixwid2 = new MyWidget(groupBoxL);
    QLabel *pix2 = new QLabel(pixwid2);
    QImage  img2("./img/settings.png");
    pix2->setScaledContents(true);
    QImage  imgB = img2.scaled(120,130,Qt::KeepAspectRatio);
    
    pix2->setPixmap(QPixmap::fromImage(imgB));
    pix2->setAlignment(Qt::AlignCenter);
    
    pixwid2->move(10,150);
    pixwid2->resize(120,122);
    
    MyLabel *pixB = new MyLabel(groupBoxL,QString("Settings"));
    pixB->move(40,260);
    
    connect(pixwid2, SIGNAL(clicked()), this, SLOT(createSettingsView()));
    connect(pixB   , SIGNAL(clicked()), this, SLOT(createSettingsView()));
    //
    
    groupBoxR = new QGroupBox(this);
    groupBoxR->move(160,35);
    groupBoxR->resize(620,532);
    groupBoxR->setStyleSheet(
    "background-color:white; " \
    "border: 1px solid black; border-radius: 10px;");
    
    statusBar()->show();
}

void MainWindow::createConnectionView()
{
    if (warnLabel) warnLabel->hide();
    if (loginBox)  loginBox ->hide();
    if (scroller)  scroller ->hide();
    if (mainTab)   mainTab  ->hide();
    
    loginBox = new QWidget(groupBoxR);
    loginBox->setStyleSheet(
    "background-color:rgb(200,200,100); " \
    "border: 1px solid black; border-radius: 10px;");
    
    QLabel *ltext = new QLabel(loginBox);
    ltext->setFont(QFont("Arial",12));
    ltext->setText("Please Enter Login Data:");
    ltext->move(80,10);
    ltext->setStyleSheet("border: 0px;");
    
    QLabel *userLabel = new QLabel(loginBox);
    QLabel *passLabel = new QLabel(loginBox);
    
    userLabel->setText("user:");
    passLabel->setText("pass:");
    
    userLabel->setFont(QFont("Arial",12));
    passLabel->setFont(QFont("Arial",12));
    
    userLabel->move(10,60);
    passLabel->move(10,100);
    
    userLabel->setStyleSheet("border: 0px;");
    passLabel->setStyleSheet("border: 0px;");


    userEdit = new QLineEdit(loginBox);
    passEdit = new QLineEdit(loginBox);
    
    passEdit->setEchoMode(QLineEdit::Password);
    
    userEdit->setFont(QFont("Arial",12));
    passEdit->setFont(QFont("Arial",12));
    
    userEdit->move(60,60);
    passEdit->move(60,100);
    
    userEdit->resize(200,30);
    passEdit->resize(200,30);
    
    userEdit->setStyleSheet("background-color:white;");
    passEdit->setStyleSheet("background-color:white;");
       
    QPushButton *loginButton = new QPushButton(loginBox);
    loginButton->setText("Login ...");
    loginButton->setFont(QFont("Arial",12));
    loginButton->setStyleSheet(
    "background-color:lime;"\
    "border: 2px solid black; border-radius: 10px");
    loginButton->move(100,140);
    loginButton->resize(100,40);
    
    connect(loginButton, SIGNAL(clicked()), this, SLOT(intoLogin()));
    
    loginBox->move(130,170);
    loginBox->resize(340,190);
    loginBox->show();
}

void MainWindow::createSettingsView()
{
    if (warnLabel) warnLabel->hide();
    if (loginBox)  loginBox ->hide();
    if (scroller)  scroller ->hide();
    if (mainTab)   mainTab  ->hide();

    mainTab = new QTabWidget(groupBoxR);
    mainTab->setFont(QFont("Arial",12));
    mainTab->move(10,10);
    mainTab->resize(600,500);
    mainTab->setTabShape(QTabWidget::Rounded);

    QWidget *tab1 = new QWidget(mainTab);
    QWidget *tab2 = new QWidget(mainTab);
    QWidget *tab3 = new QWidget(mainTab);
    
    mainTab->addTab(tab1,"Common");
    mainTab->addTab(tab2,"Network");
    mainTab->addTab(tab3,"User");

    tab1->setStyleSheet("background-color:rgb(200,200,100);");
    tab2->setStyleSheet("background-color:rgb(200,200,100);");
    tab3->setStyleSheet("background-color:rgb(200,200,100);");
    
    QLabel *hostLabel = new QLabel(tab2);
    hostLabel->setFont(QFont("Arial",12));
    hostLabel->setText("Host:");
    hostLabel->move(10,22);
    
    QLabel *portLabel = new QLabel(tab2);
    portLabel->setFont(QFont("Arial",12));
    portLabel->setText("Port:");
    portLabel->move(10,62);
    
    QLabel *proxLabel = new QLabel(tab2);
    proxLabel->setFont(QFont("Arial",12));
    proxLabel->setText("Proxy:");
    proxLabel->move(10,102);
 
    hostLabel->setStyleSheet("border: 0px;");
    portLabel->setStyleSheet("border: 0px;");
    proxLabel->setStyleSheet("border: 0px;");
    
    QLineEdit *hostEdit = new QLineEdit(tab2);
    QLineEdit *portEdit = new QLineEdit(tab2);
    QLineEdit *proxEdit = new QLineEdit(tab2);
    
    hostEdit->setFont(QFont("Arial",12));
    hostEdit->move(70,20);
    hostEdit->resize(260,25);
    
    portEdit->setFont(QFont("Arial",12));
    portEdit->move(70,60);
    portEdit->resize(260,25);
    
    proxEdit->setFont(QFont("Arial",12));
    proxEdit->move(70,100);
    proxEdit->resize(260,25);
    
    hostEdit->setStyleSheet("background-color:white;");
    portEdit->setStyleSheet("background-color:white;");
    proxEdit->setStyleSheet("background-color:white;");
    
    //
    QLabel *userLabel = new QLabel(tab3);
    userLabel->move(10,10);
    userLabel->setFont(QFont("Arial",12));
    userLabel->setText("Personal:");
    userLabel->setStyleSheet("border: 0px;");
    
    QListWidget *userList = new QListWidget(tab3);
    userList->move(10,40);
    userList->resize(200,200);
    userList->setStyleSheet("background-color:white;");
    
    QListWidgetItem *item1 = new QListWidgetItem(userList);
    item1->setFont(QFont("Arial",12));
    item1->setText("admin");
    
    //

    QLabel *userLabel2 = new QLabel(tab3);
    userLabel2->move(260,10);
    userLabel2->setFont(QFont("Arial",12));
    userLabel2->setText("User-Profile's:");
    userLabel2->setStyleSheet("border: 0px;");
    
    QListWidget *userList2 = new QListWidget(tab3);
    userList2->move(260,40);
    userList2->resize(200,200);
    userList2->setStyleSheet("background-color:white;");

    QPushButton *userOrderButton = new QPushButton(tab3);
    userOrderButton->move(470,40);
    userOrderButton->resize(100,30);
    userOrderButton->setFont(QFont("Arial",12));
    userOrderButton->setText("Order");
    userOrderButton->setStyleSheet("background-color:lime;");
    
    QPushButton *personalButton = new QPushButton(tab3);
    personalButton->move(10,260);
    personalButton->resize(120,30);
    personalButton->setFont(QFont("Arial",12));
    personalButton->setText("Add New ...");
    personalButton->setStyleSheet("background-color:lime;");

    QPushButton *personalButton2 = new QPushButton(tab3);
    personalButton2->move(10,300);
    personalButton2->resize(120,30);
    personalButton2->setFont(QFont("Arial",12));
    personalButton2->setText("Delete ...");
    personalButton2->setStyleSheet("background-color:rgb(255,100,0);");


    QPushButton *profileButton = new QPushButton(tab3);
    profileButton->move(260,260);
    profileButton->resize(120,30);
    profileButton->setFont(QFont("Arial",12));
    profileButton->setText("Add New ...");
    profileButton->setStyleSheet("background-color:lime;");

    QPushButton *profileButton2 = new QPushButton(tab3);
    profileButton2->move(260,300);
    profileButton2->resize(120,30);
    profileButton2->setFont(QFont("Arial",12));
    profileButton2->setText("Delete ...");
    profileButton2->setStyleSheet("background-color:rgb(255,100,0);");
    
    mainTab->show();

/*    
    scroller = new QScrollArea(groupBoxR);

    scroller->viewport()->setBackgroundRole(QPalette::Dark);
    scroller->viewport()->setAutoFillBackground(true);

    scroller->move(10,10);
    scroller->resize(598,505);

    scroller->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroller->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    scroller->show();
    */
}

void MainWindow::intoLogin()
{
    QSettings ini("app.ini",QSettings::NativeFormat);
    
    QString user = ini.value("loginuser", "").toString();
    QString pass = ini.value("loginpass", "").toString();

    if ((user.length() < 1)
    ||  (pass.length() < 1)) {
        return;
    }
    
    if (userEdit->text() == user)
    if (passEdit->text() == pass)
    {
        if (warnLabel) warnLabel->hide();
        if (loginBox)  loginBox ->hide();
        if (scroller)  scroller ->hide();
        if (mainTab)   mainTab  ->hide();
        
    }
}
