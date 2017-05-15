#include <QApplication>
#include "mainwindow.h"

#include "browserapplication.h"
#include <qtwebenginewidgetsglobal.h>

class MainWindow *app_window = nullptr;
class BrowserMainWindow *my_browser_window = nullptr;

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    Q_INIT_RESOURCE(data);
    BrowserApplication app(argc, argv);

    app_window = new MainWindow(1024,728);
    app_window->show ();
    my_browser_window = app.newMainWindow();
    
    return app.exec();
}
