#ifndef CAFEMESSAGE_H_
#define CAFEMESSAGE_H_

#include <QLabel>
#include <QWidget>
#include <QThread>
#include <QString>

class Worker: public QObject {
    Q_OBJECT
public:
    Worker();
    ~Worker();
    
public slots:
    void process();
signals:
    void finished();
    void error(QString err);
private:
};

class MyCafeMessage: public QLabel {
    Q_OBJECT
public:
    explicit MyCafeMessage(QWidget *parent = 0);

private:
    QThread *runner;
};

#endif
