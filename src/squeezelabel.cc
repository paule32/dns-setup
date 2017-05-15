#include "squeezelabel.h"

SqueezeLabel::SqueezeLabel(QWidget *parent) : QLabel(parent)
{
}

void SqueezeLabel::paintEvent(QPaintEvent *event)
{
    QFontMetrics fm = fontMetrics();
    if (fm.width(text()) > contentsRect().width()) {
        QString elided = fm.elidedText(text(), Qt::ElideMiddle, width());
        QString oldText = text();
        setText(elided);
        QLabel::paintEvent(event);
        setText(oldText);
    } else {
        QLabel::paintEvent(event);
    }
}
