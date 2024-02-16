#include "DroneView.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QMessageBox>
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
    // titleBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* titleBar = new QHBoxLayout();
    titleBar->setContentsMargins(0, 0, 0, 0);
    QPushButton* btnBack = new QPushButton(QIcon(QPixmap(":/assets/icons/arrow-back.svg")), "Back");
    btnBack->setShortcut(QKeySequence::Back);
    name = new QLabel("<strong>" + QString::fromStdString(drone->getName()) + "</strong>");
    QPushButton* btnEdit = new QPushButton(QIcon(QPixmap(":/assets/icons/edit.svg")), "Edit drone name");
    QPushButton* btnDel = new QPushButton(QIcon(QPixmap(":/assets/icons/remove.svg")), "Delete drone");
    titleBar->addWidget(btnBack);
    titleBar->addStretch();
    titleBar->addWidget(name);
    titleBar->addStretch();
    titleBar->addWidget(btnEdit);
    titleBar->addWidget(btnDel);

    connect(btnBack, &QPushButton::clicked, this, &DroneView::back);
    connect(btnEdit, &QPushButton::clicked, this, &DroneView::editDrone);
    connect(btnDel, &QPushButton::clicked, this, &DroneView::handleDeleteDrone);

    // Panel content
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* contentContainer = new QWidget(scrollArea);
    QVBoxLayout* content = new QVBoxLayout(contentContainer);
    contentContainer->setLayout(content);
    scrollArea->setWidget(contentContainer);


    // Drone information
    QHBoxLayout* droneInfo = new QHBoxLayout();
    content->addLayout(droneInfo);

    QLabel* image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(250, Qt::SmoothTransformation));
    droneInfo->addWidget(image);

    // Text info of drone
    QVBoxLayout* droneInfoText = new QVBoxLayout();
    droneInfo->addLayout(droneInfoText);
    QLabel* batteryLabel = new QLabel("Battery level:");
    droneInfoText->addWidget(batteryLabel);
    pbBattery = new QProgressBar();
    drone->readHardware();
    pbBattery->setValue(drone->getBatteryLevel());
    droneInfoText->addWidget(pbBattery);
    if (drone->getBatteryLevel() <= 20)
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 3px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123; width: 1px;}");
    cpuTemperature = new QLabel("CPU Temperature: " + QString::number(drone->getCpuTemperature()) + "°C");
    droneInfoText->addWidget(cpuTemperature);
    btnRead = new QPushButton("Read new sensor data");
    // if (drone->getMountedSensors().size() > 0)
    droneInfoText->addWidget(btnRead);

    connect(btnRead, &QPushButton::clicked, this, &DroneView::readNewData);

    QLabel* sensorsLabel = new QLabel("Mounted sensors:");
    content->addWidget(sensorsLabel);

    // Sensors
    droneSensors = new QGridLayout();
    content->addLayout(droneSensors);
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

    main->addLayout(titleBar);
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

void DroneView::editDrone() {
    bool ok;
    QString text = QInputDialog::getText(this, "Edit drone name", "Enter new drone name:", QLineEdit::Normal, QString::fromStdString(drone->getName()), &ok);
    if (ok && !text.isEmpty()) {
        drone->setName(text.toStdString());
    }
}

void DroneView::handleDeleteDrone() {
    int result = QMessageBox::question(this, "Delete drone", "Are you sure you want to delete this drone?", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        emit deleteDrone(drone);
        back();
    }
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

    emit sensorMounted();
}

void DroneView::removeSensor(int i) {
    drone->unmountSensor(sensorPos[i]);
    EmptySensorSocket* ess = new EmptySensorSocket();
    connect(ess, &EmptySensorSocket::mountSensor, [this, i](AbstractSensor* sensor) {
        mountSensor(sensor, i);
    });
    delete droneSensors->itemAtPosition(i / 2, i % 2)->widget();
    droneSensors->addWidget(ess, i / 2, i % 2);

    for (unsigned int j = i; j < sensorPos.size(); ++j)  // it works, but why ?
        sensorPos[j]--;
    sensorPos[i] = -1;

    emit sensorRemoved();
}

void DroneView::editSensor(int i) {
    bool ok;
    int value = QInputDialog::getInt(this, "Edit Sensor buffer size", "Enter new sensor buffer size:", drone->getMountedSensors()[sensorPos[i]]->getBufferSize(), 1, 256, 1, &ok);
    if (ok)
        drone->getMountedSensors()[sensorPos[i]]->setBufferSize(value);

    emit sensorEdited();
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