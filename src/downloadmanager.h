#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include "ui_downloads.h"
#include "ui_downloaditem.h"

#include <QtCore/QFileInfo>
#include <QtCore/QTime>
#include <QtCore/QUrl>

#include <QWebEngineDownloadItem>

class DownloadManager;
class DownloadWidget : public QWidget, public Ui_DownloadItem
{
    Q_OBJECT

signals:
    void statusChanged();

public:
    DownloadWidget(QWebEngineDownloadItem *download, QWidget *parent = 0);
    bool downloading() const;
    bool downloadedSuccessfully() const;

    void init();
    bool getFileName(bool promptForFileName = false);

private slots:
    void stop();
    void open();

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void finished();

private:
    friend class DownloadManager;
    void updateInfoLabel();
    QString dataString(int size) const;

    QUrl m_url;
    QFileInfo m_file;
    qint64 m_bytesReceived;
    QTime m_downloadTime;
    bool m_stopped;

    QScopedPointer<QWebEngineDownloadItem> m_download;
};

class AutoSaver;
class DownloadModel;
class QFileIconProvider;

class DownloadManager : public QDialog, public Ui_DownloadDialog
{
    Q_OBJECT
    Q_PROPERTY(RemovePolicy removePolicy READ removePolicy WRITE setRemovePolicy)

public:
    enum RemovePolicy {
        Never,
        Exit,
        SuccessFullDownload
    };
    Q_ENUM(RemovePolicy)

    DownloadManager(QWidget *parent = 0);
    ~DownloadManager();
    int activeDownloads() const;

    RemovePolicy removePolicy() const;
    void setRemovePolicy(RemovePolicy policy);

public slots:
    void download(QWebEngineDownloadItem *download);
    void cleanup();

private slots:
    void save() const;
    void updateRow();

private:
    void addItem(DownloadWidget *item);
    void updateItemCount();
    void load();

    AutoSaver *m_autoSaver;
    DownloadModel *m_model;
    QFileIconProvider *m_iconProvider;
    QList<DownloadWidget*> m_downloads;
    RemovePolicy m_removePolicy;
    friend class DownloadModel;
};

class DownloadModel : public QAbstractListModel
{
    friend class DownloadManager;
    Q_OBJECT

public:
    DownloadModel(DownloadManager *downloadManager, QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    DownloadManager *m_downloadManager;

};

#endif // DOWNLOADMANAGER_H
