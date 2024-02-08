#include "DroneListItem.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
namespace View {

DroneListItem::DroneListItem(Drone* d, QWidget* parent) : QWidget(parent), drone(d) {
    QHBoxLayout* main = new QHBoxLayout(this);

    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(100, Qt::SmoothTransformation));
    
    QWidget* infoContainer = new QWidget();
    infoContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QVBoxLayout* info = new QVBoxLayout(infoContainer);
    infoContainer->setLayout(info);
    
    name = new QLabel(QString::fromStdString(drone->getName()));
    batteryLevel = new QLabel(QString::number(drone->getBatteryLevel()) + "%");
    numSensors = new QLabel(QString::number(drone->getNumEquippedSensors()) + " Sensors equipped");
    info->addWidget(name);
    info->addWidget(batteryLevel);
    info->addWidget(numSensors);

    QPushButton* btnManage = new QPushButton("Manage");
    btnManage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    connect(btnManage, &QPushButton::clicked, std::bind(&DroneListItem::manageDrone, this, drone));

    main->addWidget(image);
    main->addWidget(infoContainer);
    main->addStretch();
    main->addWidget(btnManage);
}

}  // namespace View
