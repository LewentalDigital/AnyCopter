#ifndef VIEW_SENSORSAVEVISITOR_H
#define VIEW_SENSORSAVEVISITOR_H

#include <string>

#include "../SensorVisitorInterface.h"

class SensorSaveVisitor : public SensorVisitorInterface {
   private:
    std::string id;

   public:
    std::string getId() const;
    void visitBatteryChargeSensor(BatteryChargeSensor&) override;
    void visitCO2Sensor(CO2Sensor&) override;
    void visitHygrometer(Hygrometer&) override;
    void visitThermometer(Thermometer&) override;
};

#endif