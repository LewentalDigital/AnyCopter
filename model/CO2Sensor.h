#ifndef CO2SENSOR_H
#define CO2SENSOR_H

#include "AbstractSensor.h"

class CO2Sensor : public AbstractSensor {
   private:
    int time;

   public:
    CO2Sensor(unsigned int bufferSize = 100);
    virtual ~CO2Sensor() = default;

    void read() override;
    std::string getId() const override;

    void accept(SensorVisitorInterface& visitor) override;
};
#endif