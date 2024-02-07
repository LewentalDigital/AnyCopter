#ifndef HYGROMETER_H
#define HYGROMETER_H

#include "AbstractSensor.h"

class Hygrometer : public AbstractSensor {
   private:
    int prevReadingTime;
    double humidity;

   public:
    Hygrometer(int bufferSize = 24);

    void read() override;
};
#endif
