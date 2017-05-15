#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtWidgets/QDialog>
#include "ui_settings.h"

class SettingsDialog : public QDialog, public Ui_Settings
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = 0);
    void accept();

private slots:
    void loadDefaults();
    void loadFromSettings();
    void saveToSettings();

    void setHomeToCurrentPage();
    void showCookies();
    void showExceptions();

    void chooseFont();
    void chooseFixedFont();

    void on_httpUserAgent_editingFinished();
    void on_httpAcceptLanguage_editingFinished();

private:
    QFont standardFont;
    QFont fixedFont;
};

#endif // SETTINGS_H
