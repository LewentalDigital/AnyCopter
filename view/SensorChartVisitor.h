#ifndef VIEW_SENSORCHARTVISITOR_H
#define VIEW_SENSORCHARTVISITOR_H

#include <QVBoxLayout>
#include <QWidget>
#include <QtCharts>

#include "../model/SensorVisitorInterface.h"

namespace View {

class SensorChartVisitor : public SensorVisitorInterface {
   private:
    QWidget* widget;
    
    QChart* chart;
    QChartView* chartView;

    QWidget* title;
    QHBoxLayout* titleContent;

   public:
    QWidget* getWidget();
    QWidget* getTitle();
    void setupChart();
    void setupTitle();
    void visitBatteryChargeSensor(BatteryChargeSensor&) override;
    void visitCO2Sensor(CO2Sensor&) override;
    void visitHygrometer(Hygrometer&) override;
    void visitThermometer(Thermometer&) override;
};

}  // namespace View

#endif