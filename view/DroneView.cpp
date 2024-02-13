#include "DroneView.h"

#include <QMessageBox>
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

DroneView::DroneView(Drone* d, QWidget* parent) : QWidget(parent), drone(d) {
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
    drone->readHardware();
    pbBattery->setValue(drone->getBatteryLevel());
    droneInfoText->addWidget(pbBattery);
    if (drone->getBatteryLevel() > 20)
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #06b025; width: 1px;}");
    else
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123; width: 1px;}");
    cpuTemperature = new QLabel("CPU Temperature: " + QString::number(drone->getCpuTemperature()) + "°C");
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

    int gridIndex = 0;  // grid has 2 columns and whatever rows, so this index is used to calculate the row and column where to place sensors
    // gridIndex / 2 is the row, gridIndex % 2 is the column
    // so the gridLayout can be considered a normal array indexed by gridIndex, this inedx will match the vector of sensors mounted on the drone
    const std::vector<AbstractSensor*>& mountedSensors = drone->getMountedSensors();
    for (auto it = mountedSensors.begin(); it != mountedSensors.end(); ++it) {
        SensorView* sv = new SensorView(*it);
        connect(sv, &SensorView::remove, [this, gridIndex]() {
            removeSensor(gridIndex);
        });
        connect(sv, &SensorView::edit, [this, gridIndex]() {
            editSensor(gridIndex);
        });
        droneSensors->addWidget(sv, gridIndex / 2, gridIndex % 2);
        sensorPos.push_back(gridIndex);
        gridIndex++;
    }

    for (unsigned int i = drone->getNumMountedSensors(); i < Drone::sensorSockets; ++i) {
        EmptySensorSocket* ess = new EmptySensorSocket();
        connect(ess, &EmptySensorSocket::mountSensor, [this, gridIndex](AbstractSensor* sensor) {
            mountSensor(sensor, gridIndex);
        });
        droneSensors->addWidget(ess, gridIndex / 2, gridIndex % 2);
        sensorPos.push_back(-1);
        gridIndex++;
    }

    main->addWidget(titleBarContainer);
    main->addWidget(scrollArea);

    drone->registerObserver(this);
}

DroneView::~DroneView() {
    drone->unregisterObserver(this);
}

void DroneView::notify(Drone& d) {
    name->setText("<strong>" + QString::fromStdString(d.getName()) + "</strong>");
    pbBattery->setValue(d.getBatteryLevel());
    cpuTemperature->setText("CPU Temperature: " + QString::number(d.getCpuTemperature()) + "°C");
}

void DroneView::mountSensor(AbstractSensor* sensor, int i) {
    try {
        if (BatteryChargeSensor* bcs = dynamic_cast<BatteryChargeSensor*>(sensor))
            bcs->setCharge(drone->getBatteryLevel());
        sensor->read();
        drone->mountSensor(sensor);

        SensorView* sv = new SensorView(sensor);
        connect(sv, &SensorView::remove, [this, i]() {
            removeSensor(i);
        });
        connect(sv, &SensorView::edit, [this, i]() {
            editSensor(i);
        });
        delete droneSensors->itemAtPosition(i / 2, i % 2)->widget();
        droneSensors->addWidget(sv, i / 2, i % 2);
        sensorPos[i] = drone->getNumMountedSensors() - 1;
    } catch (std::string errorMsg) {
        QMessageBox::warning(this, "Error", QString::fromStdString(errorMsg));
        back();
    }
}

void DroneView::removeSensor(int i) {
    drone->unmountSensor(sensorPos[i]);
    EmptySensorSocket* ess = new EmptySensorSocket();
    connect(ess, &EmptySensorSocket::mountSensor, [this, i](AbstractSensor* sensor) {
        mountSensor(sensor, i);
    });
    delete droneSensors->itemAtPosition(i / 2, i % 2)->widget();
    droneSensors->addWidget(ess, i / 2, i % 2);

    for (unsigned int j = 0; j < sensorPos.size(); ++j)  // should not work but it does ;)
        sensorPos[j]--;
    sensorPos[i] = -1;
}

void DroneView::editSensor(int i) {  // attenzione con gli indici!!!
    bool ok;
    int value = QInputDialog::getInt(this, "Edit Sensor buffer size", "Enter new sensor buffer size:", drone->getMountedSensors()[sensorPos[i]]->getBufferSize(), 0, 256, 1, &ok);
    if (ok)
        drone->getMountedSensors()[sensorPos[i]]->setBufferSize(value);
}

void DroneView::readNewData() {
    drone->readHardware();

    const std::vector<AbstractSensor*>& mountedSensors = drone->getMountedSensors();
    for (auto it = mountedSensors.begin(); it != mountedSensors.end(); ++it) {
        (*it)->read();
    }
}

void DroneView::back() {
    delete this;
}

}  // namespace View