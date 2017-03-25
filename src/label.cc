#include "mainwindow.h"
#include "label.h"

MyLabel::MyLabel(QWidget *parent, QString txt)
    : QLabel(parent)
{
    setFont(QFont("Arial",12));
    setText(txt);
}

void MyLabel::mousePressEvent(QMouseEvent *evt)
{
    emit clicked();
}
