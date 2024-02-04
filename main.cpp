#include <QApplication>
#include <QFile>

#include "view/MainWindow.h"
#include "model/DroneManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // app.setWindowIcon(QIcon(":assets/icon.svg"));

    // QFile style(":/assets/style.qss");
    // style.open(QFile::ReadOnly);
    // app.setStyleSheet(QLatin1String(style.readAll()));

    // DroneManager droneManager;
    // View::MainWindow window(droneManager);
    
    DroneManager droneManager;
    View::MainWindow window(&droneManager);
    // window.resize(1024, 576);
    window.show();


    return app.exec();
}
