#include "edittableview.h"
#include <QtGui/QKeyEvent>

EditTableView::EditTableView(QWidget *parent)
    : QTableView(parent)
{
}

void EditTableView::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Delete
        || event->key() == Qt::Key_Backspace)
        && model()) {
        removeOne();
    } else {
        QAbstractItemView::keyPressEvent(event);
    }
}

void EditTableView::removeOne()
{
    if (!model() || !selectionModel())
        return;
    int row = currentIndex().row();
    model()->removeRow(row, rootIndex());
    QModelIndex idx = model()->index(row, 0, rootIndex());
    if (!idx.isValid())
        idx = model()->index(row - 1, 0, rootIndex());
    selectionModel()->select(idx, QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows);
}

void EditTableView::removeAll()
{
    if (model())
        model()->removeRows(0, model()->rowCount(rootIndex()), rootIndex());
}
