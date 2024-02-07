#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "AbstractSensor.h"

class Thermometer : public AbstractSensor {
   private:
    double temperature;
    int prevReadingTime;

   public:
    Thermometer(int bufferSize = 24);

    void read() override;

    double getTemperature() const;
};
#endif