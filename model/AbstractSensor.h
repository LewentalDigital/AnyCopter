#ifndef ABSTRACT_SENSOR_H
#define ABSTRACT_SENSOR_H

#include <random>

class AbstractSensor {
   protected:
    double random() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dist(25);
        return dist(gen);
    }

   public:
    virtual ~AbstractSensor() = default;
    virtual void read() = 0;
    class Reading {
    };
};

#endif