#include "BatteryChargeSensor.h"

// #include <cmath>

BatteryChargeSensor::BatteryChargeSensor(int bs) : AbstractSensor(bs, 1, 100), charge(randRange(min, max)) {
}

void BatteryChargeSensor::read() {
    if (charge > 0) {
        double variation = sqrt(random(0.008, 0.002) * getBufferSize()); // simulate higher consumption with bigger buffer
        charge = ((charge - variation) > 0) ? charge - variation : 0;
    }
    pushReading(charge);
}
double BatteryChargeSensor::getCharge() const {
    return charge;
}