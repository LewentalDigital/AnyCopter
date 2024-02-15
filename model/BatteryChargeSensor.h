#ifndef BATTERYCHARGESENSOR_H
#define BATTERYCHARGESENSOR_H

#include "AbstractSensor.h"

class BatteryChargeSensor : public AbstractSensor {
   private:
    double time;

   public:
    BatteryChargeSensor(int bufferSize = 60);
    virtual ~BatteryChargeSensor() = default;

    void read() override;
    void setCharge(double charge);
    std::string getId() const override;

    void accept(SensorVisitorInterface& visitor) override;
};

#endif