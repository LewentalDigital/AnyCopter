#include "DroneWidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QString>

DroneWidget::DroneWidget(Drone* d, QWidget* parent) : drone(d), QWidget(parent) {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(100));

    name = new QLabel(QString::fromStdString(drone->getName()));
    batteryLevel = new QLabel("69%");
    QPushButton* info = new QPushButton("Info");

    layout->addWidget(name);
    layout->addWidget(image);
    layout->addWidget(batteryLevel);
    layout->addStretch();
    layout->addWidget(info);
}
