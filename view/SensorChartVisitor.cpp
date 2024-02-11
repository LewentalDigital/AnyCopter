#include "SensorChartVisitor.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QtCharts>

#include "../model/BatteryChargeSensor.h"
#include "../model/CO2Sensor.h"
#include "../model/Hygrometer.h"
#include "../model/Thermometer.h"

namespace View {

QWidget* SensorChartVisitor::getWidget() {
    return widget;
}

void SensorChartVisitor::visitBatteryChargeSensor(BatteryChargeSensor& bcs) {
    widget = new QWidget();
    QHBoxLayout* content = new QHBoxLayout();
    content->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(content);

    QProgressBar* pbBattery = new QProgressBar();
    pbBattery->setOrientation(Qt::Vertical);
    pbBattery->setValue(bcs.getReadings().back());
    if (bcs.getReadings().back())
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px;  background-color: #e6e6e6; } QProgressBar::chunk {background-color: #06b025;}");
    else
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 0px;  background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123;}");

    QLineSeries* series = new QLineSeries();
    const std::list<double>& data = bcs.getReadings();

    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);

    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Battery Charge Sensor readings");
    chart->setMargins(QMargins(6, 6, 6, 6));
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    content->addWidget(chartView);
    content->addWidget(pbBattery);
}

void SensorChartVisitor::visitCO2Sensor(CO2Sensor& co2s) {
    widget = new QWidget();
    QVBoxLayout* content = new QVBoxLayout();
    content->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(content);

    QWidget* titleBarContainer = new QWidget();
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBar->setContentsMargins(0, 0, 0, 0);
    titleBarContainer->setLayout(titleBar);
    QLabel* title = new QLabel("CO2 Sensor, buffer size:" + QString::number(co2s.getBufferSize()));
    QPushButton* btnEdit = new QPushButton(QIcon(QPixmap(":/assets/icons/edit.svg")), "Edit");
    QPushButton* btnRemove = new QPushButton(QIcon(QPixmap(":/assets/icons/remove.svg")), "Remove");
    titleBar->addWidget(title);
    titleBar->addStretch();
    titleBar->addWidget(btnEdit);
    titleBar->addWidget(btnRemove);

    QSplineSeries* series = new QSplineSeries();
    const std::list<double>& data = co2s.getReadings();

    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);

    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    // chart->setTitle("CO2 Sensor readings");
    chart->setMargins(QMargins(6, 6, 6, 6));
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    content->addWidget(titleBarContainer);
    content->addWidget(chartView);
}

void SensorChartVisitor::visitHygrometer(Hygrometer& h) {
    QLineSeries* series = new QLineSeries();
    const std::list<double>& data = h.getReadings();

    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);

    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Hygrometer readings");
    chart->setMargins(QMargins(6, 6, 6, 6));
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    widget = chartView;
}

void SensorChartVisitor::visitThermometer(Thermometer& t) {
    QLineSeries* series = new QLineSeries();
    const std::list<double>& data = t.getReadings();

    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);

    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Thermometer readings");
    chart->setMargins(QMargins(6, 6, 6, 6));
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    widget = chartView;
}

}  // namespace View