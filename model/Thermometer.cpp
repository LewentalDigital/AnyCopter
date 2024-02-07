#include "Thermometer.h"

#include <cmath>

Thermometer::Thermometer(int bs) : AbstractSensor(bs, 10, 32), prevReadingTime(0) {
}

void Thermometer::read() {
    temperature = random((max + min) / 2, (max + min) / 5);
    temperature -= std::sin((++prevReadingTime) / 2);  // oscillation of temperature with sine
    pushReading(temperature);
}
double Thermometer::getTemperature() const {
    return temperature;
}