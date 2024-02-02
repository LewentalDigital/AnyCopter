#ifndef HYGROMETER_H
#define HYGROMETER_H

#include "AbstractSensor.h"

class Hygrometer : public AbstractSensor {
   private:
    double humidity;

   public:
    Hygrometer();

    void read() override {
        humidity = 0.5;
    }
};
#endif
