#include "DroneWidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QString>

DroneWidget::DroneWidget(Drone* d, QWidget* parent) : QWidget(parent), drone(d) {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaled(200, 300,Qt::KeepAspectRatio, Qt::SmoothTransformation));
    name = new QLabel(QString::fromStdString(drone->getName()));
    batteryLevel = new QLabel(QString::number(drone->getBatteryLevel()) + "%");
    numSensors = new QLabel(QString::number(drone->getNumEquippedSensors()) + " sensors equipped");

    QPushButton* info = new QPushButton("Info");

    layout->addWidget(name);
    layout->addWidget(image);
    layout->addWidget(batteryLevel);
    layout->addWidget(numSensors);
    layout->addStretch();
    layout->addWidget(info);
}
