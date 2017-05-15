#ifndef EDITTABLEVIEW_H
#define EDITTABLEVIEW_H

#include <QtWidgets/QTableView>

class EditTableView : public QTableView
{
    Q_OBJECT

public:
    EditTableView(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void removeOne();
    void removeAll();
};

#endif // EDITTABLEVIEW_H
