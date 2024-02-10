#ifndef CO2SENSOR_H
#define CO2SENSOR_H

#include "AbstractSensor.h"

class CO2Sensor : public AbstractSensor {
   private:
    int time;

   public:
    CO2Sensor(int bufferSize = 100);
    void read() override;

    void accept(SensorVisitorInterface& visitor) override;
};
#endif