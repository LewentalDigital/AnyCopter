#include "DroneView.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>
#include <QtCharts>
#include <QErrorMessage>

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

    QLabel* sensorsLabel = new QLabel("Mounted sensors:");
    layout->addWidget(sensorsLabel);

    QWidget* droneSensorsContainer = new QWidget();
    layout->addWidget(droneSensorsContainer);
    QGridLayout* droneSensors = new QGridLayout();
    droneSensorsContainer->setLayout(droneSensors);

    int gridPosition = 0;
    const std::vector<AbstractSensor*>& mountedSensors = drone->getMountedSensors();
    for (auto it = mountedSensors.begin(); it != mountedSensors.end(); ++it) {
        // QSplineSeries* series = new QSplineSeries();
        QLineSeries* series = new QLineSeries();
        series->append(0, 6);
        series->append(1, 4);
        series->append(2, 2);
        series->append(3, 8);
        series->append(4, 3);
        series->append(5, 5);
        auto chart = new QChart;
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Simple Line Chart");
        chart->setMargins(QMargins(6, 6, 6, 6));
        // chart->setAnimationOptions(QChart::SeriesAnimations);
        // chart->setAnimationDuration(150);
        auto chartView = new QChartView(chart);
        chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        droneSensors->addWidget(chartView, 0, gridPosition++ % 2);
    }

    for (unsigned int i = mountedSensors.size(); i < Drone::sensorSockets; ++i) {
        // droneSensors->addWidget(empty, 0, 1);
        QPushButton* btnMountSensor = new QPushButton("Mount thermometer");
        droneSensors->addWidget(btnMountSensor, 0, gridPosition++ % 2);
        connect(btnMountSensor, &QPushButton::clicked, std::bind(&DroneView::mountSensor, this, new Thermometer()));
    }

    main->addWidget(titleBarContainer);
    main->addWidget(scrollArea);
}

void DroneView::mountSensor(AbstractSensor* sensor) {
    try {
        drone->mountSensor(sensor);
    } catch (std::string e) {
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage(QString::fromStdString(e));
        connect(error, &QErrorMessage::finished, error, &QErrorMessage::close);
    }
}

void DroneView::back() {
    delete this;
}

}  // namespace View