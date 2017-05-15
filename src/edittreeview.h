#ifndef EDITTREEVIEW_H
#define EDITTREEVIEW_H

#include <QtWidgets/QTreeView>

class EditTreeView : public QTreeView
{
    Q_OBJECT

public:
    EditTreeView(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void removeOne();
    void removeAll();
};

#endif // EDITTREEVIEW_H
