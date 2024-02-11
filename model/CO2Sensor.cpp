#include "CO2Sensor.h"

#include <cmath>

CO2Sensor::CO2Sensor(int bs) : AbstractSensor(bs, 0, 650), time(0) {}

void CO2Sensor::read() {
    reading = max * cos(time / 12) + max;
    reading += random(25, 10);
    pushReading(reading);
    time++;
}

void CO2Sensor::accept(SensorVisitorInterface& visitor) {
    visitor.visitCO2Sensor(*this);
}
