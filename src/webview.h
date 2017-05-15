#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QIcon>
#include <QWebEngineView>

class QAuthenticator;
class QMouseEvent;
class QNetworkProxy;
class QNetworkReply;
class QSslError;

class BrowserMainWindow;
class WebPage : public QWebEnginePage {
    Q_OBJECT
public:
    WebPage(QWebEngineProfile *profile, QObject *parent = 0);
    BrowserMainWindow *mainWindow();

protected:
    QWebEnginePage *createWindow(QWebEnginePage::WebWindowType type) Q_DECL_OVERRIDE;
#if !defined(QT_NO_UITOOLS)
    QObject *createPlugin(const QString &classId, const QUrl &url, const QStringList &paramNames, const QStringList &paramValues);
#endif
    virtual bool certificateError(const QWebEngineCertificateError &error) Q_DECL_OVERRIDE;

private slots:
#if defined(QWEBENGINEPAGE_UNSUPPORTEDCONTENT)
    void handleUnsupportedContent(QNetworkReply *reply);
#endif
    void authenticationRequired(const QUrl &requestUrl, QAuthenticator *auth);
    void proxyAuthenticationRequired(const QUrl &requestUrl, QAuthenticator *auth, const QString &proxyHost);

private:
    friend class WebView;

    // set the webview mousepressedevent
    Qt::KeyboardModifiers m_keyboardModifiers;
    Qt::MouseButtons m_pressedButtons;
};

class WebView : public QWebEngineView {
    Q_OBJECT

public:
    WebView(QWidget *parent = 0);
    WebPage *webPage() const { return m_page; }
    void setPage(WebPage *page);

    void loadUrl(const QUrl &url);
    QUrl url() const;

    QString lastStatusBarText() const;
    inline int progress() const { return m_progress; }

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void setProgress(int progress);
    void loadFinished(bool success);
    void setStatusBarText(const QString &string);
    void onFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature);
    void onIconChanged(const QIcon &icon);

private:
    QString m_statusBarText;
    QUrl m_initialUrl;
    int m_progress;
    WebPage *m_page;
};

#endif
