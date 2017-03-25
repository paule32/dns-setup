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
    
    QWidget *pixwid1 = new QWidget(groupBoxL);
    QLabel *pix1 = new QLabel(pixwid1);
    QImage  img1("./img/pc2.png");
    QImage  imgA = img1.scaled(120,130,Qt::KeepAspectRatio);
    
    pix1->setPixmap(QPixmap::fromImage(imgA));
    pix1->setAlignment(Qt::AlignCenter);
    
    pixwid1->move(10,10);
    pixwid1->resize(120,96);
    
    MyLabel *pixA = new MyLabel(groupBoxL,QString("New connection"));
    pixA->move(9,100);
    
    connect(pixA, SIGNAL(clicked()), this,  SLOT(createConnectionView()));
    //
    
    QWidget *pixwid2 = new QWidget(groupBoxL);
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
    
    connect(pixB, SIGNAL(clicked()), this, SLOT(createSettingsView()));
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
    
    mainTab->addTab(tab1,"Common");
    mainTab->addTab(tab2,"Network");
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
