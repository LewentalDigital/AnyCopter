#include "DroneWidget.h"

#include <QHBoxLayout>
#include <QPushButton>

DroneWidget::DroneWidget(QWidget* parent) : QWidget(parent) {
    image = new QLabel();
    image->setPixmap(QPixmap(":/images/drone.png").scaledToHeight(100));
    name = new QLabel("Drone");
    batteryLevel = new QLabel("69%");
    QPushButton* info = new QPushButton("Info");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    layout->addWidget(name);
    layout->addWidget(image);
    layout->addWidget(batteryLevel);
    layout->addWidget(info);
    // setLayout(layout);
}
