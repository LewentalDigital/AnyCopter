#ifndef BATTERYCHARGESENSOR_H
#define BATTERYCHARGESENSOR_H

#include "AbstractSensor.h"

class BatteryChargeSensor : public AbstractSensor {
   private:
    double time;

   public:
    BatteryChargeSensor(unsigned int bufferSize = 60);
    virtual ~BatteryChargeSensor() = default;

    void read() override;
    void setCharge(double);
    std::string getId() const override;

    void accept(SensorVisitorInterface& visitor) override;
};

#endif