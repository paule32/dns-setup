#include <QApplication>
#include "mainwindow.h"

class MainWindow *app_window = nullptr;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    
    app_window = new MainWindow();
    app_window->show();
    
    return app.exec();
}
