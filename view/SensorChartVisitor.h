#ifndef VIEW_SENSORCHARTVISITOR_H
#define VIEW_SENSORCHARTVISITOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts>

#include "../model/SensorVisitorInterface.h"

namespace View {

class SensorChartVisitor : public SensorVisitorInterface {
   private:
    QWidget* widget;
    QLabel* title;
    QChart* chart;
    QChartView* chartView;

   public:
    QWidget* getWidget();
    void init();
    void visitBatteryChargeSensor(BatteryChargeSensor&) override;
    void visitCO2Sensor(CO2Sensor&) override;
    void visitHygrometer(Hygrometer&) override;
    void visitThermometer(Thermometer&) override;
};

}  // namespace View

#endif