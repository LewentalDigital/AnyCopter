#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "AbstractSensor.h"

class Thermometer : public AbstractSensor {
   private:
    double temperature;

   public:
    Thermometer();

    void read() override {
        temperature = 20.0;
    }

    double getTemperature() const {
        return temperature;
    }
};
#endif