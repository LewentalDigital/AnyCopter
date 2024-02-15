#ifndef HYGROMETER_H
#define HYGROMETER_H

#include "AbstractSensor.h"

class Hygrometer : public AbstractSensor {
   private:
    int time;

   public:
    Hygrometer(int bufferSize = 24);
    virtual ~Hygrometer() = default;

    void read() override;
    std::string getId() const override;

    void accept(SensorVisitorInterface& visitor) override;
};
#endif
