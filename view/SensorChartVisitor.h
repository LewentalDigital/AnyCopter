#ifndef VIEW_SENSORCHARTVISITOR_H
#define VIEW_SENSORCHARTVISITOR_H

#include <QWidget>

#include "../model/SensorVisitorInterface.h"

namespace View {

class SensorChartVisitor : public SensorVisitorInterface {
   private:
    QWidget* widget;

   public:
    QWidget* getWidget();
    void visitBatteryChargeSensor(BatteryChargeSensor&) override;
    void visitCO2Sensor(CO2Sensor&) override;
    void visitHygrometer(Hygrometer&) override;
    void visitThermometer(Thermometer&) override;
};

}  // namespace View

#endif