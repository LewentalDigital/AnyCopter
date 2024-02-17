#include "CO2Sensor.h"

#include <cmath>

CO2Sensor::CO2Sensor(unsigned int bs) : AbstractSensor(bs, 0, 650), time(0) {}

void CO2Sensor::read() {
    reading = max * cos(time / 12) + max;
    reading += random(25, 10);
    pushReading(reading);
    time++;
    AbstractSensor::read();
}

std::string CO2Sensor::getId() const {
    return "CO2Sensor";
}

void CO2Sensor::accept(SensorVisitorInterface& visitor) {
    visitor.visit(*this);
}
