#ifndef BATTERYCHARGESENSOR_H
#define BATTERYCHARGESENSOR_H

#include "AbstractSensor.h"

class BatteryChargeSensor : public AbstractSensor {
   private:
    double charge;

   public:
    BatteryChargeSensor(int bufferSize = 60);
    void read() override;
    double getCharge() const;
};

#endif