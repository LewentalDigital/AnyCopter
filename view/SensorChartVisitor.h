#ifndef VIEW_SENSORCHARTVISITOR_H
#define VIEW_SENSORCHARTVISITOR_H

#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts>
#include <QLineSeries>

#include "../model/SensorVisitorInterface.h"

namespace View {

class SensorChartVisitor : public SensorVisitorInterface {
   private:
    QWidget* widget;

    QLineSeries* series;
    QChart* chart;
    QChartView* chartView;

   public:
    QWidget* getWidget();
    void setupChart();
    void visit(BatteryChargeSensor&) override;
    void visit(CO2Sensor&) override;
    void visit(Hygrometer&) override;
    void visit(Thermometer&) override;
};

}  // namespace View

#endif