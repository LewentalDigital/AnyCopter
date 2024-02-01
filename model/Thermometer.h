#ifndef THERMOMETER_H
#define THERMOMETER_H

#include <random>

#include "AbstractSensor.h"

class Thermometer : public AbstractSensor {
   private:
    double temperature;

   public:
    Thermometer() : temperature(0) {}

    void read() override {
    }

    double getTemperature() const {
        return temperature;
    }
};
#endif