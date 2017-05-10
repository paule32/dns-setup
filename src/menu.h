#ifndef MYMENU_H_
#define MYMENU_H_

#include <QWidget>
#include <QPoint>
#include <QMenu>

#include "label.h"

class MyMenu: public QMenu
{
    Q_OBJECT
public:
    explicit MyMenu(QWidget *parent=0, int mode=0);
    explicit MyMenu(QString);
public slots:
    void showMenu(const QPoint &pos);
};

#endif
