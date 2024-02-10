#ifndef SENSOROBSERVERINTERFACE_H
#define SENSOROBSERVERINTERFACE_H

#include "AbstractSensor.h"
class AbstractSensor;

class SensorObserverInterface {
   public:
    virtual ~SensorObserverInterface() = default;
    virtual void notify(AbstractSensor&) = 0;
};

#endif