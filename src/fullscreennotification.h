#ifndef FULLSCREENNOTIFICATION_H
#define FULLSCREENNOTIFICATION_H

#include <QWidget>

class QLabel;
class QGridLayout;
class QPropertyAnimation;

class FullScreenNotification : public QWidget
{
    Q_OBJECT
public:
    FullScreenNotification(QWidget *parent = 0);
    ~FullScreenNotification();

    void show();
    void hide();

public slots:
    void fadeOut();
    void fadeOutFinished();

private:
    QLabel *m_label;
    QGridLayout *m_layout;
    QPropertyAnimation *m_animation;
    int width;
    int height;
    int x;
    int y;
};

#endif // FULLSCREENNOTIFICATION_H
