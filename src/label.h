#ifndef MYLABEL_H_
#define MYLABEL_H_

#include <QString>
#include <QLabel>
#include <QMouseEvent>
#include <QProcess>

class MyLabel: public QLabel {
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent, QString txt);

signals:
    void clicked();
    
protected:
    virtual void mousePressEvent(QMouseEvent *evt) override;
};

class MyWidget: public QWidget {
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

    void newPCSessionMembers();
    void newPCSessionNonMembers();
    void newPCSession(int m);
    void monitorUser();
    void monitorUserIP();
    
signals:
    void clicked();

private:
    QString MonitorIP;
    int     newSessionPC;
    
    QProcess * myprocess;
    
protected:
    virtual void mouseReleaseEvent(QMouseEvent *evt) override;
};

#endif
