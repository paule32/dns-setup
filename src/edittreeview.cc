#include "edittreeview.h"
#include "browserapplication.h"
#include "history.h"

#include <QtGui/QKeyEvent>

EditTreeView::EditTreeView(QWidget *parent)
    : QTreeView(parent)
{
}

void EditTreeView::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Delete
        || event->key() == Qt::Key_Backspace)
        && model()) {
        removeOne();
    } else {
        QAbstractItemView::keyPressEvent(event);
    }
}

void EditTreeView::removeOne()
{
    if (!model())
        return;
    QModelIndex ci = currentIndex();
    BrowserApplication::historyManager()->removeHistoryEntry(model()->data(ci,HistoryModel::UrlStringRole).toString());
}

void EditTreeView::removeAll()
{
    if (!model())
        return;
    BrowserApplication::historyManager()->clear();
}
