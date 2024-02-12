#include <QApplication>
#include <QFile>

#include "model/DroneManager.h"
#include "view/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":assets/icons/icon.svg"));

    // QFile style(":/assets/style.qss");
    // style.open(QFile::ReadOnly);
    // app.setStyleSheet(QLatin1String(style.readAll()));
    
    DroneManager droneManager;

    Drone *d1 = new Drone("Drone 1");
    d1->mountSensor(new BatteryChargeSensor());
    droneManager.deployDrone(d1);
    droneManager.deployDrone(new Drone("Drone 2"));
    droneManager.deployDrone(new Drone("Drone 3"));
    droneManager.deployDrone(new Drone("Drone 4"));
    droneManager.deployDrone(new Drone("Drone 5"));

    View::MainWindow window(&droneManager);
    window.resize(1024, 576);
    window.show();

    return app.exec();
}
