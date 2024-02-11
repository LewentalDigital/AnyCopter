#ifndef BATTERYCHARGESENSOR_H
#define BATTERYCHARGESENSOR_H

#include "AbstractSensor.h"

class BatteryChargeSensor : public AbstractSensor {
   private:
    double time;

   public:
    BatteryChargeSensor(int bufferSize = 60);

    void read() override;
    void setCharge(double charge);

    void accept(SensorVisitorInterface& visitor) override;
};

#endif