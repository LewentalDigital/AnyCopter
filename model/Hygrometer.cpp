#include "Hygrometer.h"

#include <cmath>

Hygrometer::Hygrometer(int bs) : AbstractSensor(bs, 50, 75), prevReadingTime(0) {
}

void Hygrometer::read() {
    humidity = random((min + max) / 2, (min + max) / 5);
    humidity += std::cos((++prevReadingTime) / 2);  // oscillation of humidity with cosine
    pushReading(humidity);
}