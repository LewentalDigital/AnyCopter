#include "SensorSaveVisitor.h"

#include "../BatteryChargeSensor.h"
#include "../CO2Sensor.h"
#include "../Hygrometer.h"
#include "../Thermometer.h"

#include <typeinfo>

std::string SensorSaveVisitor::getId() const {
    return id;
}

void SensorSaveVisitor::visitBatteryChargeSensor(BatteryChargeSensor& bcs) {
    id = "BatteryChargeSensor";
    id = typeid(bcs).name();
}

void SensorSaveVisitor::visitCO2Sensor(CO2Sensor& co2s) {
    id = "CO2Sensor";
    id = typeid(co2s).name();
}

void SensorSaveVisitor::visitHygrometer(Hygrometer& h) {
    id = "Hygrometer";
    id = typeid(h).name();
}

void SensorSaveVisitor::visitThermometer(Thermometer& t) {
    id = "Thermometer";
    id = typeid(t).name();
}
