#ifndef MYLABEL_H_
#define MYLABEL_H_

#include <QString>
#include <QLabel>
#include <QMouseEvent>

class MyLabel: public QLabel {
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent, QString txt);

signals:
    void clicked();
    
protected:
    virtual void mousePressEvent(QMouseEvent *evt) override;
};

class MyWidget: public QWidget {
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

signals:
    void clicked();
    
protected:
    virtual void mousePressEvent(QMouseEvent *evt) override;
};

#endif
