#include "DroneView.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>

namespace View {

DroneView::DroneView(Drone* d, QWidget* parent) : QWidget(parent), drone(d) {
    //____________________
    //|<     titleBar    |
    //|_______   Info1   |
    //|| IMG |   Info2   |
    //||_____|   InfoN   |
    //| Sensor1  Sensor2 |
    //| Sensor3  SensorN |
    //|__________________|
    QVBoxLayout* main = new QVBoxLayout(this);

    // Title bar del panello (forse da creare classe a parte)
    QWidget* titleBarContainer = new QWidget();
    titleBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBarContainer->setLayout(titleBar);
    QPushButton* back = new QPushButton(QIcon(QPixmap(":/assets/icons/arrow-back.svg")), "Back");
    back->setShortcut(QKeySequence::Back);
    name = new QLabel(QString::fromStdString(drone->getName()));
    titleBar->addWidget(back);
    titleBar->addStretch();
    titleBar->addWidget(name);
    titleBar->addStretch();

    connect(back, &QPushButton::clicked, this, &DroneView::back);

    // Contenuto del panello
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* centralWidget = new QWidget(scrollArea);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    // layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    centralWidget->setLayout(layout);
    scrollArea->setWidget(centralWidget);

    // Informazioni del drone
    QWidget* droneInfoContainer = new QWidget();
    layout->addWidget(droneInfoContainer);
    QHBoxLayout* droneInfo = new QHBoxLayout(droneInfoContainer);
    droneInfoContainer->setLayout(droneInfo);
    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    droneInfo->addWidget(image);
    // Informazioni testuali del drone disposte verticalmente
    QWidget* droneInfoTextContainer = new QWidget();
    droneInfo->addWidget(droneInfoTextContainer);
    QVBoxLayout* droneInfoText = new QVBoxLayout(droneInfoTextContainer);
    droneInfoTextContainer->setLayout(droneInfoText);
    QLabel* batteryLabel = new QLabel("Battery level:");
    droneInfoText->addWidget(batteryLabel);
    QProgressBar* pBBattery = new QProgressBar();
    pBBattery->setValue(drone->getBatteryLevel());
    droneInfoText->addWidget(pBBattery);
    if (drone->getBatteryLevel() > 20)
        pBBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #06b025; width: 1px;}");
    else
        pBBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123; width: 1px;}");
    cpuTemperature = new QLabel("CPU Temperature: " + QString::number(57.4) + "°C");
    droneInfoText->addWidget(cpuTemperature);
    location = new QLabel("GPS Loaction: " + QString::number(45) + "N " + QString::number(57) + "E");
    droneInfoText->addWidget(location);
    altitude = new QLabel("Altitude: " + QString::number(23) + "m");
    droneInfoText->addWidget(altitude);

    QLabel* sensorsLabel = new QLabel("External sensors:");
    layout->addWidget(sensorsLabel);
    // droneSensors layout...

    main->addWidget(titleBarContainer);
    main->addWidget(scrollArea);
}

void DroneView::back() {
    delete this;
}

}  // namespace View