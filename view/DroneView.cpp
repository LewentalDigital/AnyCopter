#include "DroneView.h"

#include <QErrorMessage>
#include <QHBoxLayout>
#include <QIcon>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>
#include <QtCharts>

#include "../model/BatteryChargeSensor.h"
#include "EmptySensorSocket.h"
#include "SensorView.h"

namespace View {

DroneView::DroneView(Drone* d, QWidget* parent) : QWidget(parent), drone(d), gridRowPosition(0), gridColPosition(0) {
    QVBoxLayout* main = new QVBoxLayout(this);

    // Panel title bar
    QWidget* titleBarContainer = new QWidget();
    titleBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBar->setContentsMargins(0, 0, 0, 0);
    titleBarContainer->setLayout(titleBar);
    QPushButton* back = new QPushButton(QIcon(QPixmap(":/assets/icons/arrow-back.svg")), "Back");
    back->setShortcut(QKeySequence::Back);
    name = new QLabel("<strong>" + QString::fromStdString(drone->getName()) + "</strong>");

    titleBar->addWidget(back);
    titleBar->addStretch();
    titleBar->addWidget(name);
    titleBar->addStretch();

    connect(back, &QPushButton::clicked, this, &DroneView::back);

    // Panel content
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* contentContainer = new QWidget(scrollArea);
    QVBoxLayout* content = new QVBoxLayout(contentContainer);
    contentContainer->setLayout(content);
    scrollArea->setWidget(contentContainer);

    // Drone information
    QWidget* droneInfoContainer = new QWidget();
    content->addWidget(droneInfoContainer);
    QHBoxLayout* droneInfo = new QHBoxLayout(droneInfoContainer);
    droneInfoContainer->setLayout(droneInfo);
    QLabel* image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(250, Qt::SmoothTransformation));
    droneInfo->addWidget(image);

    // Text info of drone
    QWidget* droneInfoTextContainer = new QWidget();
    droneInfoTextContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    droneInfo->addWidget(droneInfoTextContainer);
    QVBoxLayout* droneInfoText = new QVBoxLayout(droneInfoTextContainer);
    droneInfoTextContainer->setLayout(droneInfoText);
    QLabel* batteryLabel = new QLabel("Battery level:");
    droneInfoText->addWidget(batteryLabel);
    pbBattery = new QProgressBar();
    pbBattery->setValue(drone->getBatteryLevel());
    droneInfoText->addWidget(pbBattery);
    if (drone->getBatteryLevel() > 20)
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #06b025; width: 1px;}");
    else
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123; width: 1px;}");
    cpuTemperature = new QLabel("CPU Temperature: " + QString::number(57.4) + "°C");
    droneInfoText->addWidget(cpuTemperature);
    btnRead = new QPushButton("Read new sensor data");
    // if (drone->getMountedSensors().size() > 0)
    droneInfoText->addWidget(btnRead);

    connect(btnRead, &QPushButton::clicked, this, &DroneView::readNewData);

    QLabel* sensorsLabel = new QLabel("Mounted sensors:");
    content->addWidget(sensorsLabel);

    // Sensors
    QWidget* droneSensorsContainer = new QWidget();
    content->addWidget(droneSensorsContainer);
    droneSensors = new QGridLayout();
    droneSensorsContainer->setLayout(droneSensors);
    droneSensors->setContentsMargins(0, 0, 0, 0);

    const std::vector<AbstractSensor*>& mountedSensors = drone->getMountedSensors();
    for (auto it = mountedSensors.begin(); it != mountedSensors.end(); ++it) {
        SensorView* sv = new SensorView(*it);
        droneSensors->addWidget(sv, gridRowPosition++ / 2, gridColPosition++ % 2);
    }

    for (unsigned int i = drone->getNumMountedSensors(); i < Drone::sensorSockets; ++i) {
        EmptySensorSocket* ess = new EmptySensorSocket();
        int row = gridRowPosition++;
        int col = gridColPosition++;  // beacause capture list allows only local variables
        connect(ess, &EmptySensorSocket::mountSensor, [this, row, col](AbstractSensor* sensor) {
            mountSensor(sensor, row / 2, col % 2);
        });
        droneSensors->addWidget(ess, row / 2, col % 2);
    }

    main->addWidget(titleBarContainer);
    main->addWidget(scrollArea);
}

void DroneView::notify(AbstractSensor& sensor) {
}

void DroneView::mountSensor(AbstractSensor* sensor, int row, int col) {
    try {
        if (BatteryChargeSensor* bcs = dynamic_cast<BatteryChargeSensor*>(sensor))
            bcs->setCharge(drone->getBatteryLevel());
        sensor->read();
        drone->mountSensor(sensor);
        SensorView* sv = new SensorView(sensor);
        delete droneSensors->itemAtPosition(row, col)->widget();
        droneSensors->addWidget(sv, row, col);

    } catch (std::string e) {
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage(QString::fromStdString(e));
        connect(error, &QErrorMessage::finished, this, &DroneView::back);
    }
}

void DroneView::readNewData() {
    pbBattery->setValue(drone->getBatteryLevel());
    if (drone->getBatteryLevel() > 20)
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #06b025;}");
    else
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123;}");
    cpuTemperature = new QLabel("CPU Temperature: " + QString::number(57.4) + "°C");

    // orribile da fare bene

    int row = 0;
    int col = 0;

    const std::vector<AbstractSensor*>& mountedSensors = drone->getMountedSensors();
    for (auto it = mountedSensors.begin(); it != mountedSensors.end(); ++it) {
        (*it)->read();
        SensorView* sv = new SensorView(*it);
        droneSensors->addWidget(sv, row++ / 2, col++ % 2);
    }
}

void DroneView::back() {
    delete this;
}

}  // namespace View