#ifndef PRINTTOPDFDIALOG_H
#define PRINTTOPDFDIALOG_H

#include <QDialog>
#include <QPageLayout>

namespace Ui {
class PrintToPdfDialog;
}

class PrintToPdfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintToPdfDialog(const QString &filePath, QWidget *parent = 0);
    ~PrintToPdfDialog();

    QString filePath() const;
    QPageLayout pageLayout() const;

private slots:
    void onChoosePageLayoutButtonClicked();
    void onChooseFilePathButtonClicked();

private:
    void setFilePath(const QString &);
    void updatePageLayoutLabel();

    QPageLayout currentPageLayout;
    Ui::PrintToPdfDialog *ui;
};

#endif // PRINTTOPDFDIALOG_H
