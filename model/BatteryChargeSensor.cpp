#include   "BatteryChargeSensor.h"

BatteryChargeSensor::BatteryChargeSensor() : charge(25) {
}

void BatteryChargeSensor::read() {
    charge -= random(1, 0.8);
}
double BatteryChargeSensor::getCharge() const {
    return charge;
}