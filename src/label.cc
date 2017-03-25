#include <QWidget>

#include "mainwindow.h"
#include "label.h"

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

void MyLabel::mousePressEvent (QMouseEvent *evt) { emit clicked(); }
void MyWidget::mousePressEvent(QMouseEvent *evt) { emit clicked(); }

