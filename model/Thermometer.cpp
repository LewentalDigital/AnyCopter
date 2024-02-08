#include "Thermometer.h"

#include <cmath>


Thermometer::Thermometer(int bs) : AbstractSensor(bs, 16, 32), prevReadingTime(0) {
}

void Thermometer::read() {
    temperature = random((max + min) / 2, 1);
    temperature -= std::sin((++prevReadingTime)/6) * 8;  // oscillation of temperature with sine
    pushReading(temperature);
}
double Thermometer::getTemperature() const {
    return temperature;
}