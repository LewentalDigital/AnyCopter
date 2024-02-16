#include "Hygrometer.h"

#include <cmath>

Hygrometer::Hygrometer(unsigned int bs) : AbstractSensor(bs, 50, 75), time(0) {
}

void Hygrometer::read() {
    reading = random((min + max) / 2, 5);
    reading += std::cos((++time) / 5) * 12;  // oscillation of humidity with cosine
    pushReading(reading);
    AbstractSensor::read();
}

std::string Hygrometer::getId() const {
    return "Hygrometer";
}

void Hygrometer::accept(SensorVisitorInterface& visitor) {
    visitor.visitHygrometer(*this);
}