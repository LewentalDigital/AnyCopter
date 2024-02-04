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
    QVBoxLayout* main = new QVBoxLayout(this);

    QWidget* titleBarContainer = new QWidget();
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBarContainer->setLayout(titleBar);
    QPushButton* back = new QPushButton(QIcon(QPixmap(":/assets/icons/arrow-back.svg")), "");
    name = new QLabel(QString::fromStdString(drone->getName()));
    titleBar->addWidget(back);
    titleBar->addWidget(name);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* centralWidget = new QWidget(scrollArea);
    QHBoxLayout* layout = new QHBoxLayout(centralWidget);
    // layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    centralWidget->setLayout(layout);
    scrollArea->setWidget(centralWidget);

    QWidget* droneInfoContainer = new QWidget();
    layout->addWidget(droneInfoContainer);
    QHBoxLayout* droneInfo = new QHBoxLayout(droneInfoContainer);
    droneInfoContainer->setLayout(droneInfo);
    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    droneInfo->addWidget(image);
    QProgressBar* pBBattery = new QProgressBar();
    pBBattery->setValue(drone->getBatteryLevel());
    droneInfo->addWidget(batteryLevel);

    // pBBattery->setStyleSheet(" QProgressBar { border: 2px solid grey; border-radius: 0px; text-align: center; } QProgressBar::chunk {background-color: #3add36; width: 1px;}");

    batteryLevel = new QLabel(QString::number(drone->getBatteryLevel()) + "%");

    layout->addWidget(pBBattery);

    main->addWidget(titleBarContainer);
    main->addWidget(scrollArea);
}

}  // namespace View