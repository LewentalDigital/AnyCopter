#ifndef ABSTRACT_SENSOR_H
#define ABSTRACT_SENSOR_H

#include <list>
#include <random>

#include "SensorObserverInterface.h"
#include "SensorVisitorInterface.h"

class AbstractSensor {
   private:
    unsigned int bufferSize;  // number of readings the sensor can memorize
    std::list<double> readingsBuffer;
    std::list<SensorObserverInterface*> observers;

   protected:
    double reading; // Value of the last reading
    // min and max values the sensor can read, but in this simulation they are used as an interval for reasonable readings
    double min, max;
    // methods for generating plausible simulation of readings
    double random(double, double) const;
    double randRange(double, double) const;
    virtual void pushReading(double);

   public:
    AbstractSensor(int bufferSize = 24, double min = 0, double max = 30);
    virtual ~AbstractSensor() = 0;

    virtual void read();

    virtual double getCurrentReading() const;
    virtual const std::list<double>& getReadings() const;
    virtual unsigned int getBufferSize() const;

    virtual void setBufferSize(int);

    void registerObserver(SensorObserverInterface*);
    void unregisterObserver(SensorObserverInterface*);
    virtual void accept(SensorVisitorInterface& visitor) = 0;
};

#endif