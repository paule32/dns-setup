#include <QWidget>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QString>

#include "mainwindow.h"
#include "label.h"
#include "menu.h"

MyLabel::MyLabel(QWidget *parent, QString txt)
    : QLabel(parent)
{
    setFont(QFont("Arial",12));
    setText(txt);
}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
}

void MyLabel::mousePressEvent (QMouseEvent *evt) { }
void MyWidget::mouseReleaseEvent(QMouseEvent *evt)
{
    emit clicked();
    MyMenu *m_Menu = new MyMenu;
    
    QPoint globalCursorPos = QCursor::pos();
    int mouseScreen = qApp->desktop()->screenNumber(globalCursorPos);
    QRect mouseScreenGeometry = qApp->desktop()->screen(mouseScreen)->geometry();
    QPoint localCursorPos = globalCursorPos - mouseScreenGeometry.topLeft();
    

    QString ars;
    QRegExp rx("^pc(\\d+)click$");
    int pos = rx.indexIn(objectName());
    if (pos > -1) {
        ars = rx.cap(1);      
        QString pcstr = QString("CafePC %1:").arg(ars);
        
        MyMenu  *s_Menu = dynamic_cast<QMenu*>(m_Menu->addMenu(QString("%1 New Session").arg(pcstr)));
        QAction *s_Menu_Action02 = new QAction(QString("DVE-Members"));
        QAction *s_Menu_Action03 = new QAction(QString("Non-Members"));
        s_Menu->addAction(s_Menu_Action02);
        s_Menu->addAction(s_Menu_Action03);
        m_Menu->addMenu(s_Menu);
        
        QAction * m_Menu_Action2 = new QAction(QString("%1 Pause").arg(pcstr),this);
        QAction * m_Menu_Action3 = new QAction(QString("%1 GoTo Session").arg(pcstr),this);

        QAction * m_Menu_Action5 = new QAction(QString("%1 Statistic's").arg(pcstr),this);
        QAction * m_Menu_Action6 = new QAction(QString("%1 Reset").arg(pcstr),this);
        
        QAction * m_Menu_Action7 = new QAction(QString("%1 Monitor Session").arg(pcstr),this);
        QAction * m_Menu_Action8 = new QAction(QString("%1 Help User").arg(pcstr),this);
        
        m_Menu->addAction(m_Menu_Action2);
        m_Menu->addAction(m_Menu_Action3);
        m_Menu->addSeparator();
        m_Menu->addAction(m_Menu_Action5);
        m_Menu->addAction(m_Menu_Action6);
        m_Menu->addSeparator();
        m_Menu->addAction(m_Menu_Action7);
        m_Menu->addAction(m_Menu_Action8);

        connect(s_Menu_Action02, &QAction::triggered, this, &MyWidget::newPCSessionMembers);
        connect(s_Menu_Action03, &QAction::triggered, this, &MyWidget::newPCSessionNonMembers);
        
        m_Menu->exec(localCursorPos);
        return;
    }   else {
    QRegExp rx("^table(\\d+)click$");
    int pos = rx.indexIn(objectName());
    if (pos > -1) {
        ars = rx.cap(1);      
        QString pcstr = QString("CafeTable %1:").arg(ars);

        QAction * m_Menu_Action1 = new QAction(QString("%1 Serve New Guest").arg(pcstr),this);
        QAction * m_Menu_Action2 = new QAction(QString("%1 Order product").arg(pcstr),this);
        
        QAction * m_Menu_Action4 = new QAction(QString("%1 Show products").arg(pcstr),this);
        QAction * m_Menu_Action5 = new QAction(QString("%1 Make billing").arg(pcstr),this);
        
        QAction * m_Menu_Action7 = new QAction(QString("%1 Statistic's").arg(pcstr),this);
        QAction * m_Menu_Action8 = new QAction(QString("%1 Make free").arg(pcstr),this);
        
        m_Menu->addAction(m_Menu_Action1);
        m_Menu->addAction(m_Menu_Action2); m_Menu->addSeparator();
        
        m_Menu->addAction(m_Menu_Action4);
        m_Menu->addAction(m_Menu_Action5); m_Menu->addSeparator();
        
        m_Menu->addAction(m_Menu_Action7);
        m_Menu->addAction(m_Menu_Action8);
        
        m_Menu->exec(localCursorPos);
        return;
    }   }
}

void MyWidget::newPCSession(int m)
{
}

void MyWidget::newPCSessionMembers   () { newPCSession(1); }
void MyWidget::newPCSessionNonMembers() { newPCSession(0); }

