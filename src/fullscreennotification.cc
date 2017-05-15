#include "fullscreennotification.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

FullScreenNotification::FullScreenNotification(QWidget *parent)
    : QWidget(parent)
    , width(400)
    , height(80)
    , x((parent->geometry().width() - width) / 2)
    , y(80)
{
    setVisible(false);
    setWindowFlags(Qt::ToolTip | Qt::WindowDoesNotAcceptFocus);

    QGridLayout *layout = new QGridLayout(this);

    m_label = new QLabel(tr("You are now in fullscreen mode. Press ESC to quit!"), this);
    layout->addWidget(m_label, 0, 0, 0, 0, Qt::AlignHCenter | Qt::AlignVCenter);

    setGeometry(x, y, width, height);

    setStyleSheet("background-color: white;\
        color: black;");

    m_animation = new QPropertyAnimation(this, "windowOpacity");
    connect(m_animation, SIGNAL(finished()), this, SLOT(fadeOutFinished()));
}

FullScreenNotification::~FullScreenNotification()
{
}

void FullScreenNotification::show()
{
    setWindowOpacity(1.0);
    QTimer::singleShot(300, [&] {
        QWidget *parent = parentWidget();
        x = (parent->geometry().width() - width) / 2;
        QPoint topLeft = parent->mapToGlobal(QPoint(x, y));
        QWidget::move(topLeft.x(), topLeft.y());
        QWidget::show();
        QWidget::raise();
    });
    QTimer::singleShot(5000, this, SLOT(fadeOut()));
}

void FullScreenNotification::hide()
{
    QWidget::hide();
    m_animation->stop();
}

void FullScreenNotification::fadeOut()
{
    m_animation->setDuration(800);
    m_animation->setStartValue(1.0);
    m_animation->setEndValue(0.0);
    m_animation->setEasingCurve(QEasingCurve::OutQuad);
    m_animation->start();
}

void FullScreenNotification::fadeOutFinished()
{
    hide();
    setWindowOpacity(1.0);
}
