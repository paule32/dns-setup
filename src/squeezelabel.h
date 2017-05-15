#ifndef SQUEEZELABEL_H
#define SQUEEZELABEL_H

#include <QtWidgets/QLabel>

class SqueezeLabel : public QLabel
{
    Q_OBJECT

public:
    SqueezeLabel(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // SQUEEZELABEL_H
