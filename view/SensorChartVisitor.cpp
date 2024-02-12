#include "SensorChartVisitor.h"

#include <QtCharts>

#include "../model/BatteryChargeSensor.h"
#include "../model/CO2Sensor.h"
#include "../model/Hygrometer.h"
#include "../model/Thermometer.h"

namespace View {

void SensorChartVisitor::setupChart() {
    chart->legend()->hide();
    chart->setMargins(QMargins(6, 6, 6, 6));
    chart->createDefaultAxes();
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void SensorChartVisitor::setupTitle() {
    title = new QWidget();
    titleContent = new QHBoxLayout();
    titleContent->setContentsMargins(10, 0, 10, 0);
    title->setLayout(titleContent);
}

QWidget* SensorChartVisitor::getWidget() {
    return widget;
}

QWidget* SensorChartVisitor::getTitle() {
    return title;
}

QChart* SensorChartVisitor::getChart() {
    return chart;
}

void SensorChartVisitor::visitBatteryChargeSensor(BatteryChargeSensor& bcs) {
    setupTitle();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/battery-half.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    titleContent->addWidget(new QLabel("<strong>Battery charge sensor</strong>"));

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
    chart = new QChart();
    chart->addSeries(series);
    chartView = new QChartView(chart);
    setupChart();
    // QValueAxis* axisY = new QValueAxis();
    // axisY->setRange(0, 100);
    // chart->addAxis(axisY, Qt::AlignLeft);
    chart->axes(Qt::Vertical).back()->setRange(0, 100);

    content->addWidget(chartView);
    content->addWidget(pbBattery);
}

void SensorChartVisitor::visitCO2Sensor(CO2Sensor& co2s) {
    setupTitle();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/leaf.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    titleContent->addWidget(new QLabel("<strong>CO2 Sensor</strong>"));

    QLineSeries* series = new QLineSeries();
    const std::list<double>& data = co2s.getReadings();
    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);
    chart = new QChart();
    chart->addSeries(series);
    chartView = new QChartView(chart);
    setupChart();
    widget = chartView;
}

void SensorChartVisitor::visitHygrometer(Hygrometer& h) {
    setupTitle();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/water.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    titleContent->addWidget(new QLabel("<strong>Hygrometer</strong>"));

    QLineSeries* series = new QLineSeries();
    const std::list<double>& data = h.getReadings();
    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);
    chart = new QChart;
    chart->addSeries(series);
    chartView = new QChartView(chart);
    setupChart();
    widget = chartView;
}

void SensorChartVisitor::visitThermometer(Thermometer& t) {
    setupTitle();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/thermometer.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    titleContent->addWidget(new QLabel("<strong>Thermometer</strong>"));

    QSplineSeries* series = new QSplineSeries();
    const std::list<double>& data = t.getReadings();
    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);
    chart = new QChart;
    chart->addSeries(series);
    chartView = new QChartView(chart);
    setupChart();
    widget = chartView;
}

}  // namespace View