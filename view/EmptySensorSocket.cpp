#include "EmptySensorSocket.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QIntValidator>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>

#include "../model/BatteryChargeSensor.h"
#include "../model/CO2Sensor.h"
#include "../model/Hygrometer.h"
#include "../model/Thermometer.h"

namespace View {

EmptySensorSocket::EmptySensorSocket(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* main = new QVBoxLayout(this);

    // Title 
    QWidget* titleContainer = new QWidget();
    QHBoxLayout* title = new QHBoxLayout(titleContainer);
    titleContainer->setLayout(title);
    QLabel* titleIcon = new QLabel();
    titleIcon->setPixmap(QPixmap(":assets/icons/hardware-chip.svg").scaledToHeight(28, Qt::SmoothTransformation));
    QLabel* titleLabel = new QLabel("Empty Sensor Socket");
    title->addWidget(titleIcon);
    title->addWidget(titleLabel);
    title->addStretch();

    // Form to input data for the new sensor
    QLabel* mountLabel = new QLabel("Mount new sensor:");
    QWidget* formContainer = new QWidget();
    QFormLayout* formLayout = new QFormLayout;
    formContainer->setLayout(formLayout);
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

    main->addWidget(titleContainer);
    main->addWidget(formContainer);
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