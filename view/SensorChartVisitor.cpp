#include "SensorChartVisitor.h"

#include "../model/BatteryChargeSensor.h"
#include "../model/CO2Sensor.h"
#include "../model/Hygrometer.h"
#include "../model/Thermometer.h"

#include <QtCharts>

namespace View {

QWidget* SensorChartVisitor::getWidget() {
    return widget;
}

void SensorChartVisitor::visitBatteryChargeSensor(BatteryChargeSensor& bcs) {
    QLineSeries* series = new QLineSeries();
    const std::list<double>& data = bcs.getReadings();

    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);

    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Thermometer readings");
    chart->setMargins(QMargins(6, 6, 6, 6));
    // chart->setAnimationOptions(QChart::SeriesAnimations);
    // chart->setAnimationDuration(150);
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    widget = chartView;
}

void SensorChartVisitor::visitCO2Sensor(CO2Sensor& co2s) {
    QSplineSeries* series = new QSplineSeries();
    const std::list<double>& data = co2s.getReadings();

    int i = 0;
    for (auto reading = data.begin(); reading != data.end(); ++reading)
        series->append(i++, *reading);

    QChart* chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("CO2 Sensor readings");
    chart->setMargins(QMargins(6, 6, 6, 6));
    // chart->setAnimationOptions(QChart::SeriesAnimations);
    // chart->setAnimationDuration(150);
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    widget = chartView;
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
    // chart->setAnimationOptions(QChart::SeriesAnimations);
    // chart->setAnimationDuration(150);
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
    // chart->setAnimationOptions(QChart::SeriesAnimations);
    // chart->setAnimationDuration(150);
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    widget = chartView;
}

}  // namespace View