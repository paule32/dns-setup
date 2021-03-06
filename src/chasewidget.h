
#ifndef CHASEWIDGET_H
#define CHASEWIDGET_H

#include <QtWidgets/QWidget>

#include <QtCore/QSize>
#include <QtGui/QColor>
#include <QtGui/QPixmap>

class QHideEvent;
class QShowEvent;
class QPaintEvent;
class QTimerEvent;

class ChaseWidget : public QWidget
{
    Q_OBJECT
public:
    ChaseWidget(QWidget *parent = 0, QPixmap pixmap = QPixmap(), bool pixmapEnabled = false);

    void setAnimated(bool value);
    void setPixmapEnabled(bool enable);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    int segmentCount() const;
    QColor colorForSegment(int segment) const;

    int m_segment;
    int m_delay;
    int m_step;
    int m_timerId;
    bool m_animated;
    QPixmap m_pixmap;
    bool m_pixmapEnabled;
};

#endif
