#include "BatteryChargeSensor.h"

#include <cmath>

BatteryChargeSensor::BatteryChargeSensor(int bs) : AbstractSensor(bs, 1, 100), charge(randRange(min, max)) {
    setCharge(charge);
}

double dischargeFunction(double x) {
    return -56 * log(x + 15) + 265;  // simulate battery discharge with tweaked log function
}

double inverseDischargeFunction(double y) {
    return exp((265 - y) / 56) - 15;
}

void BatteryChargeSensor::read() {
    if (charge > 0) {
        time += random(0, 0.5);  // a bit of randomness
        double newValue = dischargeFunction(time++);
        charge = (newValue > 0) ? newValue : 0;
    }
    pushReading(charge);
}

double BatteryChargeSensor::getCharge() const {
    return charge;
}

void BatteryChargeSensor::setCharge(double c) {
    charge = c;
    time = inverseDischargeFunction(c);
}

void BatteryChargeSensor::accept(SensorVisitorInterface& visitor) {
    visitor.visitBatteryChargeSensor(*this);
}