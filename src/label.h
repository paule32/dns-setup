#ifndef MYLABEL_H_
#define MYLABEL_H_

#include <QString>
#include <QLabel>
#include <QMouseEvent>

class MyLabel: public QLabel {
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent, QString txt);

protected:
    virtual void mousePressEvent(QMouseEvent *evt) override;
};

#endif
