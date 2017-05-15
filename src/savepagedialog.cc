#include "savepagedialog.h"
#include "ui_savepagedialog.h"

#include <QtCore/QDir>
#include <QtWidgets/QFileDialog>

const QWebEngineDownloadItem::SavePageFormat SavePageDialog::m_indexToFormatTable[] = {
    QWebEngineDownloadItem::SingleHtmlSaveFormat,
    QWebEngineDownloadItem::CompleteHtmlSaveFormat,
    QWebEngineDownloadItem::MimeHtmlSaveFormat
};

SavePageDialog::SavePageDialog(QWidget *parent, QWebEngineDownloadItem::SavePageFormat format,
                               const QString &filePath)
    : QDialog(parent)
    , ui(new Ui::SavePageDialog)
{
    ui->setupUi(this);
    ui->formatComboBox->setCurrentIndex(formatToIndex(format));
    setFilePath(filePath);
}

SavePageDialog::~SavePageDialog()
{
    delete ui;
}

QWebEngineDownloadItem::SavePageFormat SavePageDialog::pageFormat() const
{
    return indexToFormat(ui->formatComboBox->currentIndex());
}

QString SavePageDialog::filePath() const
{
    return QDir::fromNativeSeparators(ui->filePathLineEdit->text());
}

void SavePageDialog::on_chooseFilePathButton_clicked()
{
    QFileInfo fi(filePath());
    QFileDialog dlg(this, tr("Save Page As"), fi.absolutePath());
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDefaultSuffix(suffixOfFormat(pageFormat()));
    dlg.selectFile(fi.absoluteFilePath());
    if (dlg.exec() != QDialog::Accepted)
        return;
    setFilePath(dlg.selectedFiles().first());
    ensureFileSuffix(pageFormat());
}

void SavePageDialog::on_formatComboBox_currentIndexChanged(int idx)
{
    ensureFileSuffix(indexToFormat(idx));
}

int SavePageDialog::formatToIndex(QWebEngineDownloadItem::SavePageFormat format)
{
    for (auto i : m_indexToFormatTable) {
        if (m_indexToFormatTable[i] == format)
            return i;
    }
    Q_UNREACHABLE();
}

QWebEngineDownloadItem::SavePageFormat SavePageDialog::indexToFormat(int idx)
{
    Q_ASSERT(idx >= 0 && size_t(idx) < (sizeof(m_indexToFormatTable)
                                        / sizeof(QWebEngineDownloadItem::SavePageFormat)));
    return m_indexToFormatTable[idx];
}

QString SavePageDialog::suffixOfFormat(QWebEngineDownloadItem::SavePageFormat format)
{
    if (format == QWebEngineDownloadItem::MimeHtmlSaveFormat)
        return QStringLiteral(".mhtml");
    return QStringLiteral(".html");
}

void SavePageDialog::setFilePath(const QString &filePath)
{
    ui->filePathLineEdit->setText(QDir::toNativeSeparators(filePath));
}

void SavePageDialog::ensureFileSuffix(QWebEngineDownloadItem::SavePageFormat format)
{
    QFileInfo fi(filePath());
    setFilePath(fi.absolutePath() + QLatin1Char('/') + fi.completeBaseName()
                + suffixOfFormat(format));
}
