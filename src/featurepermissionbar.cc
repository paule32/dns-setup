#include "featurepermissionbar.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QUrl>
#include <QPropertyAnimation>

static const int defaultHeight = 30;

static QString textForPermissionType(QWebEnginePage::Feature type)
{
    switch (type) {
    case QWebEnginePage::Notifications:
        return QObject::tr("use desktop notifications");
    case QWebEnginePage::Geolocation:
        return QObject::tr("use your position");
    case QWebEnginePage::MediaAudioCapture:
        return QObject::tr("use your microphone");
    case QWebEnginePage::MediaVideoCapture:
        return QObject::tr("use your camera");
    case QWebEnginePage::MediaAudioVideoCapture:
        return QObject::tr("use your camera and microphone");
    case QWebEnginePage::MouseLock:
        return QObject::tr("lock your mouse");
    default:
        Q_UNREACHABLE();
    }
    return QString();
}

FeaturePermissionBar::FeaturePermissionBar(QWidget *view)
    : QWidget(view)
    , m_messageLabel(new QLabel(this))
{
    setAutoFillBackground(true);
    QHBoxLayout *l = new QHBoxLayout;
    setLayout(l);
    l->setContentsMargins(defaultHeight, 0, 0, 0);
    l->addWidget(m_messageLabel);
    l->addStretch();
    QPushButton *allowButton = new QPushButton(tr("Allow"), this);
    QPushButton *denyButton = new QPushButton(tr("Deny"), this);
    QPushButton *discardButton = new QPushButton(QIcon(QStringLiteral(":closetab.png")), QString(), this);
    connect(allowButton, &QPushButton::clicked, this, &FeaturePermissionBar::permissionGranted);
    connect(denyButton, &QPushButton::clicked, this, &FeaturePermissionBar::permissionDenied);
    connect(discardButton, &QPushButton::clicked, this, &FeaturePermissionBar::permissionUnknown);
    connect(allowButton, &QPushButton::clicked, this, &QObject::deleteLater);
    connect(denyButton, &QPushButton::clicked, this, &QObject::deleteLater);
    connect(discardButton, &QPushButton::clicked, this, &QObject::deleteLater);
    l->addWidget(denyButton);
    l->addWidget(allowButton);
    l->addWidget(discardButton);
    setGeometry(0, -defaultHeight, view->width(), defaultHeight);
}

void FeaturePermissionBar::requestPermission(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
    m_securityOrigin = securityOrigin;
    m_feature = feature;
    m_messageLabel->setText(tr("%1 wants to %2.").arg(securityOrigin.host()).arg(textForPermissionType(feature)));
    show();
    // Ease in
    QPropertyAnimation *animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);
    animation->setPropertyName(QByteArrayLiteral("pos"));
    animation->setDuration(300);
    animation->setStartValue(QVariant::fromValue(pos()));
    animation->setEndValue(QVariant::fromValue(QPoint(0,0)));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void FeaturePermissionBar::permissionDenied()
{
    emit featurePermissionProvided(m_securityOrigin, m_feature, QWebEnginePage::PermissionDeniedByUser);
}

void FeaturePermissionBar::permissionGranted()
{
    emit featurePermissionProvided(m_securityOrigin, m_feature, QWebEnginePage::PermissionGrantedByUser);
}

void FeaturePermissionBar::permissionUnknown()
{
    emit featurePermissionProvided(m_securityOrigin, m_feature, QWebEnginePage::PermissionUnknown);
}
