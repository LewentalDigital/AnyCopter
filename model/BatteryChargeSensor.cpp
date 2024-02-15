#include "BatteryChargeSensor.h"

#include <cmath>

BatteryChargeSensor::BatteryChargeSensor(int bs) : AbstractSensor(bs, 1, 100) {
    setCharge(randRange(min, max));
}

double dischargeFunction(double x) {
    return -56 * log(x + 15) + 265;  // simulate battery discharge with tweaked log function
}

double inverseDischargeFunction(double y) {
    return exp((265 - y) / 56) - 15;
}

void BatteryChargeSensor::read() {
    if (reading > 0) {
        time += random(0, 0.5);  // a bit of randomness
        double newValue = dischargeFunction(time++);
        reading = (newValue > 0) ? newValue : 0;
    }
    pushReading(reading);
    AbstractSensor::read();
}

void BatteryChargeSensor::setCharge(double c) {
    reading = c;
    time = inverseDischargeFunction(c);
}

std::string BatteryChargeSensor::getId() const {
    return "BatteryChargeSensor";
}

void BatteryChargeSensor::accept(SensorVisitorInterface& visitor) {
    visitor.visitBatteryChargeSensor(*this);
}