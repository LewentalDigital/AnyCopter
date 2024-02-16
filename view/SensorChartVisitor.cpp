#include "SensorChartVisitor.h"

#include <QAreaSeries>
#include <QPen>
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
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleContent = new QHBoxLayout();
    titleContent->setAlignment(Qt::AlignLeft);
    titleContent->setContentsMargins(10, 0, 10, 0);
    title->setLayout(titleContent);
}

QWidget* SensorChartVisitor::getWidget() {
    return widget;
}

QWidget* SensorChartVisitor::getTitle() {
    return title;
}

QLineSeries* SensorChartVisitor::getSeries() {
    return series;
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
    
    if (bcs.getReadings().back() <= 20)
        pbBattery->setStyleSheet(" QProgressBar { border: 1px solid grey; border-radius: 3px; text-align: center; background-color: #e6e6e6; } QProgressBar::chunk {background-color: #e81123; width: 1px;}");

    QLineSeries* series = new QLineSeries();

    const std::list<double>& data = bcs.getReadings();
    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);

    QAreaSeries* areaSeries = new QAreaSeries(series);  // Area below line
    QColor areaColor("#41cc64e3");
    QBrush brush(areaColor);
    areaSeries->setBrush(brush);
    QColor lineColor("#41cc64");
    QPen pen(lineColor);  //  green line
    pen.setWidth(2);      // width of the line
    areaSeries->setPen(pen);

    chart = new QChart();
    chart->addSeries(areaSeries);
    chartView = new QChartView(chart);
    setupChart();
    chart->axes(Qt::Vertical).back()->setRange(0, 100);
    chart->axes(Qt::Horizontal).back()->setRange(0, bcs.getBufferSize());

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
    QColor color("#f7ac44");
    QPen pen(color);
    pen.setWidth(2);
    series->setPen(pen);

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

    QAreaSeries* areaSeries = new QAreaSeries(series);  // Area below line
    QColor areaColor("#4bb2bfcc");
    QBrush brush(areaColor);
    areaSeries->setBrush(brush);
    QColor lineColor("#028b9f");
    QPen pen(lineColor);
    pen.setWidth(2);
    areaSeries->setPen(pen);

    chart = new QChart();
    chart->addSeries(areaSeries);
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
    QColor color("#ff6961");
    QPen pen(color);
    pen.setWidth(2);
    series->setPen(pen);

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