#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include "urllineedit.h"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QAbstractButton>

class QMenu;

class SearchButton;

/*
    Clear button on the right hand side of the search widget.
    Hidden by default
    "A circle with an X in it"
 */
class ClearButton : public QAbstractButton
{
    Q_OBJECT

public:
    ClearButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

public slots:
    void textChanged(const QString &text);
};

class SearchLineEdit : public ExLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString inactiveText READ inactiveText WRITE setInactiveText)

signals:
    void textChanged(const QString &text);

public:
    SearchLineEdit(QWidget *parent = 0);

    QString inactiveText() const;
    void setInactiveText(const QString &text);

    QMenu *menu() const;
    void setMenu(QMenu *menu);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void updateGeometries();

    SearchButton *m_searchButton;
    QString m_inactiveText;
};

#endif // SEARCHLINEEDIT_H
