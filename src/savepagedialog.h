#ifndef SAVEPAGEDIALOG_H
#define SAVEPAGEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWebEngineWidgets/QWebEngineDownloadItem>

namespace Ui {
class SavePageDialog;
}

class SavePageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SavePageDialog(QWidget *parent, QWebEngineDownloadItem::SavePageFormat format,
                            const QString &filePath);
    ~SavePageDialog();

    QWebEngineDownloadItem::SavePageFormat pageFormat() const;
    QString filePath() const;

private slots:
    void on_chooseFilePathButton_clicked();
    void on_formatComboBox_currentIndexChanged(int idx);

private:
    static int formatToIndex(QWebEngineDownloadItem::SavePageFormat format);
    static QWebEngineDownloadItem::SavePageFormat indexToFormat(int idx);
    static QString suffixOfFormat(QWebEngineDownloadItem::SavePageFormat format);
    void setFilePath(const QString &filePath);
    void ensureFileSuffix(QWebEngineDownloadItem::SavePageFormat format);

    static const QWebEngineDownloadItem::SavePageFormat m_indexToFormatTable[];
    Ui::SavePageDialog *ui;
};

#endif // SAVEPAGEDIALOG_H
