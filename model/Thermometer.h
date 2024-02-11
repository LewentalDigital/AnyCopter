#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "AbstractSensor.h"

class Thermometer : public AbstractSensor {
   private:
    int time;

   public:
    Thermometer(int bufferSize = 24);
    virtual ~Thermometer() = default;

    void read() override;

    void accept(SensorVisitorInterface& visitor) override;
};
#endif