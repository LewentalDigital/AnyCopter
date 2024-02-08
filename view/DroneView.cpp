#include "DroneView.h"
#include "EmptySensorSocket.h"

#include <QErrorMessage>
#include <QHBoxLayout>
#include <QIcon>
#include <QProgressBar>
#include <QPushButton>
#include <QScrollArea>
#include <QString>
#include <QVBoxLayout>
#include <QtCharts>

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
    QLabel* image = new QLabel();
    // image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(250, Qt::SmoothTransformation));
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

    QLabel* sensorsLabel = new QLabel("Mounted sensors:");
    layout->addWidget(sensorsLabel);

    QWidget* droneSensorsContainer = new QWidget();
    layout->addWidget(droneSensorsContainer);
    QGridLayout* droneSensors = new QGridLayout();
    droneSensorsContainer->setLayout(droneSensors);

    int gridRowPosition = 0;
    int gridColPosition = 0;
    // row = [0...int(number of sockets/2)], col = [0,1]
    // 2 sensors in a row 
    // => grid->addWidget(widget, gridRowPosition/2, gridColPosition % 2);

    const std::vector<AbstractSensor*>& mountedSensors = drone->getMountedSensors();
    for (auto it = mountedSensors.begin(); it != mountedSensors.end(); ++it) {
        (*it)->read();
        // QSplineSeries* series = new QSplineSeries();
        QLineSeries* series = new QLineSeries();
        const std::list<double>& data = (*it)->getReadings();

        int i = 0;
        for (auto reading = data.begin(); reading != data.end(); ++reading) {
            series->append(i++, *reading);
        }
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
        droneSensors->addWidget(chartView, gridRowPosition++/2, gridColPosition++ % 2);
    }

    for (unsigned int i = mountedSensors.size(); i < Drone::sensorSockets; ++i) {
        EmptySensorSocket* ess = new EmptySensorSocket();
        droneSensors->addWidget(ess, gridRowPosition++/2, gridColPosition++ % 2);
        connect(ess, &EmptySensorSocket::mountSensor, this, &DroneView::mountSensor);
    }

    main->addWidget(titleBarContainer);
    main->addWidget(scrollArea);
}

void DroneView::mountSensor(AbstractSensor* sensor) {
    try {
        drone->mountSensor(sensor);
        // monta grafico passando la sua posizione
    } catch (std::string e) {
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage(QString::fromStdString(e));
        connect(error, &QErrorMessage::finished, this, &DroneView::back);
    }
}

void DroneView::back() {
    delete this;
}

}  // namespace View