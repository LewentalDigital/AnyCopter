#include   "BatteryChargeSensor.h"

BatteryChargeSensor::BatteryChargeSensor() : charge(0) {
}

void BatteryChargeSensor::read() {
    charge = random();
}
double BatteryChargeSensor::getCharge() const {
    return charge;
}