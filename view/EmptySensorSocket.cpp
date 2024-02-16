#include "EmptySensorSocket.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QIntValidator>
#include <QLabel>
#include <QVBoxLayout>

#include "../model/BatteryChargeSensor.h"
#include "../model/CO2Sensor.h"
#include "../model/Hygrometer.h"
#include "../model/Thermometer.h"

namespace View {

EmptySensorSocket::EmptySensorSocket(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* main = new QVBoxLayout(this);

    // Title
    QHBoxLayout* titleBar = new QHBoxLayout();
    titleBar->setContentsMargins(10, 0, 10, 0);
    QLabel* titleIcon = new QLabel();
    titleIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    titleIcon->setPixmap(QPixmap(":assets/icons/hardware-chip.svg").scaledToHeight(28, Qt::SmoothTransformation));
    QLabel* title = new QLabel("Empty Sensor Socket");
    title->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    titleBar->addWidget(titleIcon);
    titleBar->addWidget(title);
    titleBar->addStretch();

    // Form to input data for the new sensor
    QLabel* mountLabel = new QLabel("Mount new sensor:");
    QFormLayout* formLayout = new QFormLayout();
    sensorType = new QComboBox();
    sensorType->insertItem(0, QIcon(":assets/icons/thermometer.svg"), "Thermometer");
    sensorType->insertItem(1, QIcon(":assets/icons/water.svg"), "Hygrometer");
    sensorType->insertItem(2, QIcon(":assets/icons/leaf.svg"), "CO2 Sensor");
    sensorType->insertItem(3, QIcon(":assets/icons/battery-half.svg"), "Battery Charge Sensor");
    btnMountSensor = new QPushButton("Mount");
    bufferSizeInput = new QLineEdit();
    QValidator* validator = new QIntValidator(1, 256);  // to prevent huge buffer sizes
    bufferSizeInput->setValidator(validator);
    bufferSizeInput->setPlaceholderText("Buffer size");
    formLayout->addRow(mountLabel);
    formLayout->addRow("&Sensor type:", sensorType);
    formLayout->addRow("&Buffer size (optional):", bufferSizeInput);
    formLayout->addRow(btnMountSensor);

    connect(btnMountSensor, &QPushButton::clicked, this, &EmptySensorSocket::handleMount);

    main->addLayout(titleBar);
    main->addLayout(formLayout);
}

void EmptySensorSocket::handleMount() {
    AbstractSensor* mountedSensor;
    switch (sensorType->currentIndex()) {
        case 0:
            mountedSensor = new Thermometer();
            break;
        case 1:
            mountedSensor = new Hygrometer();
            break;
        case 2:
            mountedSensor = new CO2Sensor();
            break;
        case 3:
            mountedSensor = new BatteryChargeSensor();
            break;
        default:
            mountedSensor = new Thermometer();
            break;
    }
    if (!bufferSizeInput->text().isEmpty()) {
        int bufferSize = bufferSizeInput->text().toInt();
        mountedSensor->setBufferSize(bufferSize);
    }
    emit mountSensor(mountedSensor);
}

void EmptySensorSocket::remove() {
    delete this;
}

}  // namespace View