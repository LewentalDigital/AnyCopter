#include "DroneListItem.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

namespace View {

DroneListItem::DroneListItem(Drone* d, QWidget* parent) : QWidget(parent), drone(d) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* main = new QHBoxLayout(this);

    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(100, Qt::SmoothTransformation));

    QWidget* infoContainer = new QWidget();
    infoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QVBoxLayout* info = new QVBoxLayout(infoContainer);
    infoContainer->setLayout(info);

    name = new QLabel("<strong>" + QString::fromStdString(drone->getName()) + "</strong>");
    pbBattery = new QProgressBar();
    drone->readHardware();
    pbBattery->setValue(drone->getBatteryLevel());
    if (drone->getBatteryLevel() > 20)
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #06b025; width: 1px;}");
    else
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123; width: 1px;}");

    numSensors = new QLabel("Mounted sensors: " + QString::number(drone->getNumMountedSensors()) + "/" + QString::number(Drone::sensorSockets));
    info->addWidget(name);
    info->addWidget(pbBattery);
    info->addWidget(numSensors);

    QPushButton* btnManage = new QPushButton("Manage");
    btnManage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    connect(btnManage, &QPushButton::clicked, std::bind(&DroneListItem::manageDrone, this, drone));

    main->addWidget(image);
    main->addWidget(infoContainer);
    main->addStretch();
    main->addWidget(btnManage);

    drone->registerObserver(this);
}

DroneListItem::~DroneListItem() {
    drone->unregisterObserver(this);
}

void DroneListItem::notify(Drone& d) {
    pbBattery->setValue(d.getBatteryLevel());
    numSensors->setText("Mounted sensors: " + QString::number(d.getNumMountedSensors()) + "/" + QString::number(Drone::sensorSockets));
}

}  // namespace View
