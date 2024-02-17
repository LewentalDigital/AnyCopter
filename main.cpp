#include <QApplication>
#include <QFile>
#include <QSplashScreen>

#include "model/DroneManager.h"
#include "view/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":assets/icons/icon.svg"));

    QFile style(":/assets/style.qss");
    style.open(QFile::ReadOnly);
    app.setStyleSheet(QLatin1String(style.readAll()));

    QPixmap pixmap(":assets/icons/icon.svg");
    QSplashScreen splash(pixmap);
    splash.show();
    
    DroneManager droneManager;

    View::MainWindow window(droneManager);
    window.resize(1024, 576);
    window.show();
    splash.finish(&window);

    return app.exec();
}
