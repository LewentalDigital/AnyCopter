#include "Dashboard.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace View {

Dashboard::Dashboard(const DroneManager& dm, QWidget* parent) : QWidget(parent), droneManager(dm) {
    QVBoxLayout* main = new QVBoxLayout(this);

    QHBoxLayout* titleBar = new QHBoxLayout();
    titleBar->setContentsMargins(0, 0, 0, 0);
    QLabel* title = new QLabel("Dashboard");
    title->setObjectName("title");
    title->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    titleBar->addWidget(title);
    main->addLayout(titleBar);

    QHBoxLayout* anyCopter = new QHBoxLayout();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/icon.svg").scaledToHeight(75, Qt::SmoothTransformation));
    icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    QLabel* labelAnycopter = new QLabel("Anycopter");
    labelAnycopter->setObjectName("title");
    labelAnycopter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    anyCopter->addWidget(icon);
    anyCopter->addWidget(labelAnycopter);
    main->addLayout(anyCopter);

    int numDrones = droneManager.getNumDrones();
    int numSensors = 0;
    std::vector<Drone*> drones = droneManager.getDrones();
    for (auto it = drones.begin(); it != drones.end(); ++it)
        numSensors += (*it)->getNumMountedSensors();

    std::list<double> co2 = droneManager.getCO2SensorReadings();
    double avgCo2 = 0;
    for (auto it = co2.begin(); it != co2.end(); ++it)
        avgCo2 += *it;
    avgCo2 /= co2.size();

    std::list<double> humidity = droneManager.getHygrometerReadings();
    double avgHumidity = 0;
    for (auto it = humidity.begin(); it != humidity.end(); ++it)
        avgHumidity += *it;
    avgHumidity /= humidity.size();

    std::list<double> temp = droneManager.getThermometerReadings();
    double avgTemp = 0;
    for (auto it = temp.begin(); it != temp.end(); ++it)
        avgTemp += *it;
    avgTemp /= temp.size();

    QGridLayout* numbers = new QGridLayout();
    labelNumDrones = new QLabel("Drones deployed:\n" + QString::number(numDrones));
    labelNumSensors = new QLabel("Sensors mounted:\n" + QString::number(numSensors));
    numbers->addWidget(labelNumDrones, 0, 0);
    numbers->addWidget(labelNumSensors, 0, 1);

    QGridLayout* averages = new QGridLayout();
    labelAvgCo2 = new QLabel("Average CO2:\n" + QString::number(avgCo2) + " ppm");
    labelAvgHumidity = new QLabel("Average humidity:\n" + QString::number(avgHumidity) + " %");
    labelAvgTemp = new QLabel("Average temperature:\n" + QString::number(avgTemp) + " °C");
    averages->addWidget(labelAvgTemp, 0, 0);
    averages->addWidget(labelAvgCo2, 0, 1);
    averages->addWidget(labelAvgHumidity, 1, 0);

    main->addLayout(numbers);
    main->addLayout(averages);
}

void Dashboard::notify(AbstractSensor&) {
}

}  // namespace View