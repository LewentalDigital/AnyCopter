#include "BatteryChargeSensor.h"

BatteryChargeSensor::BatteryChargeSensor() : charge(25) {
}

void BatteryChargeSensor::read() {
    if (charge > 0) {
        double variazione = random(1, 0.8);
        charge = ((charge - variazione) > 0) ? charge - variazione : 0;
    }
}
double BatteryChargeSensor::getCharge() const {
    return charge;
}