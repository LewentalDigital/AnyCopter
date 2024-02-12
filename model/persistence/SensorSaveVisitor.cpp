#include "SensorSaveVisitor.h"

#include "../BatteryChargeSensor.h"
#include "../CO2Sensor.h"
#include "../Hygrometer.h"
#include "../Thermometer.h"

std::string SensorSaveVisitor::getId() const {
    return id;
}

void SensorSaveVisitor::visitBatteryChargeSensor(BatteryChargeSensor& bcs) {
    id = "BatteryChargeSensor";
}

void SensorSaveVisitor::visitCO2Sensor(CO2Sensor& co2s) {
    id = "CO2Sensor";
}

void SensorSaveVisitor::visitHygrometer(Hygrometer& h) {
    id = "Hygrometer";
}

void SensorSaveVisitor::visitThermometer(Thermometer& t) {
    id = "Thermometer";
}
