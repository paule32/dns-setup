#ifndef MODELMENU_H
#define MODELMENU_H

#include <QtWidgets/QMenu>
#include <QtCore/QAbstractItemModel>

// A QMenu that is dynamically populated from a QAbstractItemModel
class ModelMenu : public QMenu
{
    Q_OBJECT

signals:
    void activated(const QModelIndex &index);
    void hovered(const QString &text);

public:
    ModelMenu(QWidget *parent = 0);

    void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

    void setMaxRows(int max);
    int maxRows() const;

    void setFirstSeparator(int offset);
    int firstSeparator() const;

    void setRootIndex(const QModelIndex &index);
    QModelIndex rootIndex() const;

    void setHoverRole(int role);
    int hoverRole() const;

    void setSeparatorRole(int role);
    int separatorRole() const;

    QAction *makeAction(const QIcon &icon, const QString &text, QObject *parent);

protected:
    // add any actions before the tree, return true if any actions are added.
    virtual bool prePopulated();
    // add any actions after the tree
    virtual void postPopulated();
    // put all of the children of parent into menu up to max
    void createMenu(const QModelIndex &parent, int max, QMenu *parentMenu = 0, QMenu *menu = 0);

private slots:
    void aboutToShow();
    void triggered(QAction *action);
    void hovered(QAction *action);

private:
    QAction *makeAction(const QModelIndex &index);
    int m_maxRows;
    int m_firstSeparator;
    int m_maxWidth;
    int m_hoverRole;
    int m_separatorRole;
    QAbstractItemModel *m_model;
    QPersistentModelIndex m_root;
};

#endif // MODELMENU_H
