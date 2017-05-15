#ifndef FEATUREPERMISSIONBAR_H
#define FEATUREPERMISSIONBAR_H

#include <QWidget>
#include <QWebEnginePage>

class QLabel;
class QPushButton;

class FeaturePermissionBar : public QWidget {
Q_OBJECT

public:
    FeaturePermissionBar(QWidget*);
    void requestPermission(const QUrl &, QWebEnginePage::Feature feature);

signals:
    void featurePermissionProvided(const QUrl &securityOrigin, QWebEnginePage::Feature, QWebEnginePage::PermissionPolicy);

private slots:
    void permissionDenied();
    void permissionGranted();
    void permissionUnknown();

private:
    QWebEnginePage::Feature m_feature;
    QLabel *m_messageLabel;
    QUrl m_securityOrigin;
};

#endif // FEATUREPERMISSIONBAR_H
