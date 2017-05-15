#ifndef TOOLBARSEARCH_H
#define TOOLBARSEARCH_H

#include "searchlineedit.h"

class QUrl;
class QAction;
class QStringListModel;

class AutoSaver;

class ToolbarSearch : public SearchLineEdit
{
    Q_OBJECT

signals:
    void search(const QUrl &url);

public:
    ToolbarSearch(QWidget *parent = 0);
    ~ToolbarSearch();

public slots:
    void clear();
    void searchNow();

private slots:
    void save();
    void aboutToShowMenu();
    void triggeredMenuAction(QAction *action);

private:
    void load();

    AutoSaver *m_autosaver;
    int m_maxSavedSearches;
    QStringListModel *m_stringListModel;
};

#endif // TOOLBARSEARCH_H
