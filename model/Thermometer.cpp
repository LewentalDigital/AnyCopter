#include "Thermometer.h"

#include <cmath>

Thermometer::Thermometer(int bs) : AbstractSensor(bs, 16, 32), time(0) {
}

void Thermometer::read() {
    reading = random((max + min) / 2, 1);
    reading -= std::sin((++time) / 6) * 8;  // oscillation of temperature with sine
    pushReading(reading);
    AbstractSensor::read();
}

void Thermometer::accept(SensorVisitorInterface& visitor) {
    visitor.visitThermometer(*this);
}