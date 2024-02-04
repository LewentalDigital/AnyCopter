#ifndef ABSTRACT_SENSOR_H
#define ABSTRACT_SENSOR_H

#include <random>

class AbstractSensor {
   protected:
    double min, max;
    double random(double mean, double variation);

   public:
    virtual ~AbstractSensor() = default;
    virtual void read() = 0;
};

#endif