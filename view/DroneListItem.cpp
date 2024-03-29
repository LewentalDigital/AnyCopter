#include "DroneListItem.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

#include "../model/AbstractSensor.h"
#include "SensorTitleVisitor.h"

namespace View {

DroneListItem::DroneListItem(Drone* d, QWidget* parent) : QWidget(parent), drone(d) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* main = new QHBoxLayout(this);

    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(100, Qt::SmoothTransformation));

    QVBoxLayout* infoDrone = new QVBoxLayout();

    name = new QLabel(QString::fromStdString(drone->getName()));
    name->setObjectName("title");
    pbBattery = new QProgressBar();
    drone->readHardware();
    pbBattery->setValue(drone->getBatteryLevel());
    if (drone->getBatteryLevel() <= 20)
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 3px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123; width: 1px;}");
    cpuTemperature = new QLabel("CPU temperature: " + QString::number(drone->getCpuTemperature()) + "°C");

    infoDrone->addWidget(name);
    infoDrone->addWidget(pbBattery);
    infoDrone->addWidget(cpuTemperature);

    infoSensors = new QVBoxLayout();

    numSensors = new QLabel("Mounted sensors: " + QString::number(drone->getNumMountedSensors()) + "/" + QString::number(Drone::SENSOR_SOKETS));
    numSensors->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    infoSensors->addWidget(numSensors);

    for (AbstractSensor* sensor : drone->getMountedSensors()) {
        SensorTitleVisitor visitor;
        sensor->accept(visitor);
        infoSensors->addWidget(visitor.getTitle());
    }

    QPushButton* btnManage = new QPushButton("Manage");
    btnManage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    connect(btnManage, &QPushButton::clicked, std::bind(&DroneListItem::manageDrone, this, drone));

    main->addWidget(image);
    main->addLayout(infoDrone);
    main->addLayout(infoSensors);
    main->addStretch();
    main->addWidget(btnManage);

    drone->registerObserver(this);
}

DroneListItem::~DroneListItem() {
    drone->unregisterObserver(this);
}

const Drone& DroneListItem::getDrone() const {
    return *drone;
}

void DroneListItem::notify(Drone& d) {
    name->setText(QString::fromStdString(d.getName()));
    pbBattery->setValue(d.getBatteryLevel());
    if (drone->getBatteryLevel() <= 20)
        pbBattery->setStyleSheet("QProgressBar { border: 1px solid grey; border-radius: 3px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123}");
    cpuTemperature->setText("CPU temperature: " + QString::number(drone->getCpuTemperature()) + "°C");
    numSensors->setText("Mounted sensors: " + QString::number(drone->getNumMountedSensors()) + "/" + QString::number(Drone::SENSOR_SOKETS));

    QLayoutItem* child;
    while ((child = infoSensors->takeAt(1)) != nullptr) {
        delete child->widget();  // delete the widget
        delete child;            // delete the layout item
    }

    for (AbstractSensor* sensor : drone->getMountedSensors()) {
        SensorTitleVisitor visitor;
        sensor->accept(visitor);
        infoSensors->addWidget(visitor.getTitle());
    }
}

}  // namespace View
