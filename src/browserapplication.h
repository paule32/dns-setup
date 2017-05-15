#ifndef BROWSERAPPLICATION_H
#define BROWSERAPPLICATION_H

#include <QtWidgets/QApplication>

#include <QtCore/QUrl>
#include <QtCore/QPointer>

#include <QtGui/QIcon>
#include <QHideEvent>

#include <QtNetwork/QAuthenticator>

class QLocalServer;
class QNetworkAccessManager;
class QWebEngineProfile;

class BookmarksManager;
class BrowserMainWindow;
class CookieJar;
class DownloadManager;
class HistoryManager;
class BrowserApplication : public QApplication
{
    Q_OBJECT

public:
    BrowserApplication(int &argc, char **argv);
    ~BrowserApplication();
    static BrowserApplication *instance();
    void loadSettings();

    bool isTheOnlyBrowser() const;
    BrowserMainWindow *mainWindow();
    QList<BrowserMainWindow*> mainWindows();
    QIcon icon(const QUrl &url) const;
    QIcon defaultIcon() const;

    void saveSession();
    bool canRestoreSession() const;
    bool privateBrowsing() const { return m_privateBrowsing; }

    static HistoryManager *historyManager();
    static CookieJar *cookieJar();
    static DownloadManager *downloadManager();
    static QNetworkAccessManager *networkAccessManager();
    static BookmarksManager *bookmarksManager();

#if defined(Q_OS_OSX)
    bool event(QEvent *event);
#endif

public slots:
    BrowserMainWindow *newMainWindow();
    void restoreLastSession();
    void lastWindowClosed();
    void quitBrowser();
    void setPrivateBrowsing(bool);
    void my_exit();

signals:
    void privateBrowsingChanged(bool);

private slots:
    void postLaunch();
    void openUrl(const QUrl &url);
    void newLocalSocketConnection();

private:
    void clean();
    void installTranslator(const QString &name);
    QString getCommandLineUrlArgument() const;

    static HistoryManager *s_historyManager;
    static DownloadManager *s_downloadManager;
    static QNetworkAccessManager *s_networkAccessManager;
    static BookmarksManager *s_bookmarksManager;

    QList<QPointer<BrowserMainWindow> > m_mainWindows;
    QLocalServer *m_localServer;
    QByteArray m_lastSession;
    QWebEngineProfile *m_privateProfile;
    bool m_privateBrowsing;
    mutable QIcon m_defaultIcon;

    QAuthenticator m_lastAuthenticator;
    QAuthenticator m_lastProxyAuthenticator;
    
protected:
    virtual void hideEvent(QHideEvent *ev);
};

#endif // BROWSERAPPLICATION_H
