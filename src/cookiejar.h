#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QtNetwork/QNetworkCookieJar>

#include <QtCore/QAbstractItemModel>
#include <QtCore/QStringList>

#include <QtWidgets/QDialog>
#include <QtWidgets/QTableView>

class QSortFilterProxyModel;
class QKeyEvent;

class AutoSaver;

class CookieJar : public QNetworkCookieJar
{
    friend class CookieModel;
    Q_OBJECT
    Q_PROPERTY(AcceptPolicy acceptPolicy READ acceptPolicy WRITE setAcceptPolicy)
    Q_PROPERTY(KeepPolicy keepPolicy READ keepPolicy WRITE setKeepPolicy)
    Q_PROPERTY(QStringList blockedCookies READ blockedCookies WRITE setBlockedCookies)
    Q_PROPERTY(QStringList allowedCookies READ allowedCookies WRITE setAllowedCookies)
    Q_PROPERTY(QStringList allowForSessionCookies READ allowForSessionCookies WRITE setAllowForSessionCookies)
    Q_ENUMS(KeepPolicy)
    Q_ENUMS(AcceptPolicy)

signals:
    void cookiesChanged();

public:
    enum AcceptPolicy {
        AcceptAlways,
        AcceptNever,
        AcceptOnlyFromSitesNavigatedTo
    };

    enum KeepPolicy {
        KeepUntilExpire,
        KeepUntilExit,
        KeepUntilTimeLimit
    };

    CookieJar(QObject *parent = 0);
    ~CookieJar();

    QList<QNetworkCookie> cookiesForUrl(const QUrl &url) const;
    bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url);

    AcceptPolicy acceptPolicy() const;
    void setAcceptPolicy(AcceptPolicy policy);

    KeepPolicy keepPolicy() const;
    void setKeepPolicy(KeepPolicy policy);

    QStringList blockedCookies() const;
    QStringList allowedCookies() const;
    QStringList allowForSessionCookies() const;

    void setBlockedCookies(const QStringList &list);
    void setAllowedCookies(const QStringList &list);
    void setAllowForSessionCookies(const QStringList &list);

public slots:
    void clear();
    void loadSettings();

private slots:
    void save();

private:
    void purgeOldCookies();
    void load();
    bool m_loaded;
    AutoSaver *m_saveTimer;

    AcceptPolicy m_acceptCookies;
    KeepPolicy m_keepCookies;

    QStringList m_exceptions_block;
    QStringList m_exceptions_allow;
    QStringList m_exceptions_allowForSession;
};

class CookieModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    CookieModel(CookieJar *jar, QObject *parent = 0);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private slots:
    void cookiesChanged();

private:
    CookieJar *m_cookieJar;
};

#include "ui_cookies.h"
#include "ui_cookiesexceptions.h"

class CookiesDialog : public QDialog, public Ui_CookiesDialog
{
    Q_OBJECT

public:
    CookiesDialog(CookieJar *cookieJar, QWidget *parent = 0);

private:
    QSortFilterProxyModel *m_proxyModel;
};

class CookieExceptionsModel : public QAbstractTableModel
{
    Q_OBJECT
    friend class CookiesExceptionsDialog;

public:
    CookieExceptionsModel(CookieJar *cookieJar, QObject *parent = 0);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    CookieJar *m_cookieJar;

    // Domains we allow, Domains we block, Domains we allow for this session
    QStringList m_allowedCookies;
    QStringList m_blockedCookies;
    QStringList m_sessionCookies;
};

class CookiesExceptionsDialog : public QDialog, public Ui_CookiesExceptionsDialog
{
    Q_OBJECT

public:
    CookiesExceptionsDialog(CookieJar *cookieJar, QWidget *parent = 0);

private slots:
    void block();
    void allow();
    void allowForSession();
    void textChanged(const QString &text);

private:
    CookieExceptionsModel *m_exceptionsModel;
    QSortFilterProxyModel *m_proxyModel;
    CookieJar *m_cookieJar;
};

#endif // COOKIEJAR_H
