#include <QString>
#include <QMessageBox>

#include "mainwindow.h"
#include "cafemessage.h"

Worker:: Worker() { }
Worker::~Worker() { }

void Worker::process() {
    emit finished();
}

MyCafeMessage::MyCafeMessage(QWidget *parent)
    : QLabel(parent)
{
    runner = new QThread;
    
    Worker *worker = new Worker();
    worker->moveToThread(runner);
    
    connect(runner, SIGNAL (started() ), worker, SLOT (process()));
    connect(worker, SIGNAL (finished()), runner, SLOT (quit()));
    connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
    connect(runner, SIGNAL (finished()), runner, SLOT (deleteLater()));
    
    runner->start();
}

