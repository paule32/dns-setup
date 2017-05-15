#include "printtopdfdialog.h"
#include "ui_printtopdfdialog.h"

#include <QtCore/QDir>
#ifndef QT_NO_PRINTER
#include <QtPrintSupport/QPageSetupDialog>
#include <QtPrintSupport/QPrinter>
#endif // QT_NO_PRINTER
#include <QtWidgets/QFileDialog>

PrintToPdfDialog::PrintToPdfDialog(const QString &filePath, QWidget *parent) :
    QDialog(parent),
    currentPageLayout(QPageLayout(QPageSize(QPageSize::A4), QPageLayout::Portrait, QMarginsF(0.0, 0.0, 0.0, 0.0))),
    ui(new Ui::PrintToPdfDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(ui->chooseFilePathButton, &QToolButton::clicked, this, &PrintToPdfDialog::onChooseFilePathButtonClicked);
#ifndef QT_NO_PRINTER
    connect(ui->choosePageLayoutButton, &QToolButton::clicked, this, &PrintToPdfDialog::onChoosePageLayoutButtonClicked);
#else
    ui->choosePageLayoutButton->hide();
#endif // QT_NO_PRINTER
    updatePageLayoutLabel();
    setFilePath(filePath);
}

PrintToPdfDialog::~PrintToPdfDialog()
{
    delete ui;
}

void PrintToPdfDialog::onChoosePageLayoutButtonClicked()
{
#ifndef QT_NO_PRINTER
    QPrinter printer;
    printer.setPageLayout(currentPageLayout);

    QPageSetupDialog dlg(&printer, this);
    if (dlg.exec() != QDialog::Accepted)
        return;
    currentPageLayout.setPageSize(printer.pageLayout().pageSize());
    currentPageLayout.setOrientation(printer.pageLayout().orientation());
    updatePageLayoutLabel();
#endif // QT_NO_PRINTER
}

void PrintToPdfDialog::onChooseFilePathButtonClicked()
{
    QFileInfo fi(filePath());
    QFileDialog dlg(this, tr("Save PDF as"), fi.absolutePath());
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDefaultSuffix(QStringLiteral(".pdf"));
    dlg.selectFile(fi.absoluteFilePath());
    if (dlg.exec() != QDialog::Accepted)
        return;
    setFilePath(dlg.selectedFiles().first());
}

QString PrintToPdfDialog::filePath() const
{
    return QDir::fromNativeSeparators(ui->filePathLineEdit->text());
}

void PrintToPdfDialog::setFilePath(const QString &filePath)
{
    ui->filePathLineEdit->setText(QDir::toNativeSeparators(filePath));
}

QPageLayout PrintToPdfDialog::pageLayout() const
{
    return currentPageLayout;
}

void PrintToPdfDialog::updatePageLayoutLabel()
{
    ui->pageLayoutLabel->setText(QString("%1, %2").arg(
                                   currentPageLayout.pageSize().name()).arg(
                                   currentPageLayout.orientation() == QPageLayout::Portrait
                                   ? tr("Portrait") : tr("Landscape")
                                   ));
}
