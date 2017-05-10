#include <QMessageBox>
#include "label.h"
#include "menu.h"
#include "mainwindow.h"

MyMenu::MyMenu(QWidget *parent, int mode)
    : QMenu(parent)
    {

}

void MyMenu::showMenu(const QPoint &pos)
{
    QPoint p = pos;
    p.setX(app_window->pos().x());
    p.setY(parentWidget()->pos().y());
    exec(p);
    QMessageBox::information(0,"Tti",parentWidget()->objectName());
}
