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
    QWidget  *menuWidget = new QWidget(this);
    menuWidget->setAutoFillBackground(true);
    menuWidget->move(0,0);
    menuWidget->resize(800,35);
    menuWidget->setStyleSheet("background-color:gray;");

    QString menustr = "background-color:gray;font-weight:900;";
    QMenuBar * menu = new QMenuBar(menuWidget);
    
    menu->setAutoFillBackground(true);
    menu->setStyleSheet(menustr);
    menu->setFont(QFont("Arial",12));
    menu->move(4,7);
    menu->resize(800,30);

   
    fileMenu = new QMenu("File");
    helpMenu = new QMenu("Help");
    
    fileMenu->setAutoFillBackground(true);
    fileMenu->move(4,4);
    fileMenu->setStyleSheet(menustr);
    fileMenu->setFont(QFont("Arial",12));

    helpMenu->setAutoFillBackground(true);
    helpMenu->setStyleSheet(menustr);
    helpMenu->setFont(QFont("Arial",12));

    menu->addMenu(fileMenu);
    menu->addMenu(helpMenu);
    
    fileMenu->addAction(fileActionA);
    fileMenu->addAction(fileActionB);
    fileMenu->addAction(fileAction1);
    fileMenu->addSeparator();
    fileMenu->addAction(fileAction2);
    
    helpMenu->addAction(helpAction1);
    helpMenu->addAction(helpAction2);
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
    QWidget *tab4 = new QWidget(mainTab);
    QWidget *tab5 = new QWidget(mainTab);
    
    mainTab->addTab(tab1,"Common");
    mainTab->addTab(tab2,"Network");
    mainTab->addTab(tab3,"User");
    mainTab->addTab(tab4,"Statistik");
    mainTab->addTab(tab5,"Order");

    QString color_str = "background-color:rgb(200,200,100);";
    
    tab1->setStyleSheet(color_str);
    tab2->setStyleSheet(color_str);
    tab3->setStyleSheet(color_str);
    tab4->setStyleSheet(color_str);
    tab5->setStyleSheet(color_str);
    
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
    QLabel *nameserverLabel = new QLabel(tab2);
    nameserverLabel->move(10,150);
    nameserverLabel->setFont(QFont("Arial",12));
    nameserverLabel->setText("Nameserver:");
    nameserverLabel->setStyleSheet("border: 0px;");
    
    QListWidget *nameserverList = new QListWidget(tab2);
    nameserverList->move(10,174);
    nameserverList->resize(200,200);
    nameserverList->setStyleSheet("background-color:white;");
    

    QPushButton *nameserverAddButton = new QPushButton(tab2);
    nameserverAddButton->move(240,174);
    nameserverAddButton->resize(100,30);
    nameserverAddButton->setFont(QFont("Arial",12));
    nameserverAddButton->setText("Add New ...");
    nameserverAddButton->setStyleSheet("background-color:lime;");
    
    QPushButton *nameserverDeleteButton = new QPushButton(tab2);
    nameserverDeleteButton->move(240,234);
    nameserverDeleteButton->resize(100,30);
    nameserverDeleteButton->setFont(QFont("Arial",12));
    nameserverDeleteButton->setText("Delete");
    nameserverDeleteButton->setStyleSheet("background-color:rgb(255,100,0);");

    QPushButton *nameserverEditButton = new QPushButton(tab2);
    nameserverEditButton->move(240,294);
    nameserverEditButton->resize(100,30);
    nameserverEditButton->setFont(QFont("Arial",12));
    nameserverEditButton->setText("Edit");
    nameserverEditButton->setStyleSheet("background-color:cyan;");
    
    
    QLineEdit *nameserverEdit = new QLineEdit(tab2);
    nameserverEdit->move(390,177);
    nameserverEdit->resize(170,30);
    nameserverEdit->setFont(QFont("Arial",12));
    nameserverEdit->setStyleSheet("background-color:white;");

    QPushButton *nameserverPingButton = new QPushButton(tab2);
    nameserverPingButton->move(10,400);
    nameserverPingButton->resize(100,30);
    nameserverPingButton->setFont(QFont("Arial",12));
    nameserverPingButton->setText("Ping Test");
    nameserverPingButton->setStyleSheet("background-color:yellow;");

    
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

    QPushButton *userSwitchButton = new QPushButton(tab3);
    userSwitchButton->move(470,40);
    userSwitchButton->resize(100,30);
    userSwitchButton->setFont(QFont("Arial",12));
    userSwitchButton->setText("Switch");
    userSwitchButton->setStyleSheet("background-color:lime;");
    
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
    
    QPushButton *personalButton3 = new QPushButton(tab3);
    personalButton3->move(10,340);
    personalButton3->resize(120,30);
    personalButton3->setFont(QFont("Arial",12));
    personalButton3->setText("Edit");
    personalButton3->setStyleSheet("background-color:cyan;");



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
    
    QPushButton *profileButton3 = new QPushButton(tab3);
    profileButton3->move(260,340);
    profileButton3->resize(120,30);
    profileButton3->setFont(QFont("Arial",12));
    profileButton3->setText("Edit");
    profileButton3->setStyleSheet("background-color:cyan;");

    //

    QLabel *productLabel = new QLabel(tab5);
    productLabel->move(10,10);
    productLabel->setFont(QFont("Arial",12));
    productLabel->setText("Product's:");
    productLabel->setStyleSheet("border: 0px;");
    
    QListWidget *stockList = new QListWidget(tab5);
    stockList->move(10,40);
    stockList->resize(200,400);
    stockList->setStyleSheet("background-color:white;");
    
    
    QLabel *productNameLabel = new QLabel(tab5);
    productNameLabel->move(230,43);
    productNameLabel->setFont(QFont("Arial",12));
    productNameLabel->setText("Name:");
    productNameLabel->setStyleSheet("border: 0px;");
    
    QLabel *productPriceLabel = new QLabel(tab5);
    productPriceLabel->move(230,83);
    productPriceLabel->setFont(QFont("Arial",12));
    productPriceLabel->setText("Price:");
    productPriceLabel->setStyleSheet("border: 0px;");
    
    QLabel *productCountLabel = new QLabel(tab5);
    productCountLabel->move(230,123);
    productCountLabel->setFont(QFont("Arial",12));
    productCountLabel->setText("Quantity:");
    productCountLabel->setStyleSheet("border: 0px;");
    
    
    QLineEdit *productNameEdit = new QLineEdit(tab5);
    productNameEdit->move(290,40);
    productNameEdit->resize(170,30);
    productNameEdit->setFont(QFont("Arial",12));
    productNameEdit->setStyleSheet("background-color:white;");

    QLineEdit *productPriceEdit = new QLineEdit(tab5);
    productPriceEdit->move(290,80);
    productPriceEdit->resize(170,30);
    productPriceEdit->setFont(QFont("Arial",12));
    productPriceEdit->setStyleSheet("background-color:white;");

    QLineEdit *productCountEdit = new QLineEdit(tab5);
    productCountEdit->move(360,120);
    productCountEdit->resize(100,30);
    productCountEdit->setFont(QFont("Arial",12));
    productCountEdit->setStyleSheet("background-color:white;");


    QPushButton *productAddButton = new QPushButton(tab5);
    productAddButton->move(230,200);
    productAddButton->resize(100,25);
    productAddButton->setFont(QFont("Arial",12));
    productAddButton->setText("Add New ...");
    productAddButton->setStyleSheet("background-color:lime;");

    QPushButton *productDeleteButton = new QPushButton(tab5);
    productDeleteButton->move(230,240);
    productDeleteButton->resize(100,25);
    productDeleteButton->setFont(QFont("Arial",12));
    productDeleteButton->setText("Delete");
    productDeleteButton->setStyleSheet("background-color:rgb(255,100,0);");
    
    QPushButton *productOrderButton = new QPushButton(tab5);
    productOrderButton->move(230,320);
    productOrderButton->resize(140,35);
    productOrderButton->setFont(QFont("Arial",12));
    productOrderButton->setText("Order Product Qty.");
    productOrderButton->setStyleSheet("background-color:cyan;");
    
    QLineEdit *productOrderEdit = new QLineEdit(tab5);
    productOrderEdit->move(400,320);
    productOrderEdit->resize(140,35);
    productOrderEdit->setFont(QFont("Arial",12));
    productOrderEdit->setStyleSheet("background-color:white;");
    
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
