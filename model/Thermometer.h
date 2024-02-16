#ifndef THERMOMETER_H
#define THERMOMETER_H

#include "AbstractSensor.h"

class Thermometer : public AbstractSensor {
   private:
    int time;

   public:
    Thermometer(unsigned int bufferSize = 24);
    virtual ~Thermometer() = default;

    void read() override;
    std::string getId() const override;

    void accept(SensorVisitorInterface& visitor) override;
};
#endif