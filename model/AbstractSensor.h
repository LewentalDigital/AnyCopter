#ifndef ABSTRACT_SENSOR_H
#define ABSTRACT_SENSOR_H

#include <list>
#include <random>

class AbstractSensor {
   private:
    double reading;
    unsigned int bufferSize; // number of readings the sensor can memorize
    std::list<double> readingsBuffer;

   protected:
    double min, max; // min and max values the sensor can read, but in this simulation they are used as an interval for reasonable readings
    // double powerDrawPerReading; // bigger buffer => higher buttery consumption
    // methods for generating plausible simulation of readings
    double random(double, double) const;
    double randRange(double, double) const;

   public:
    AbstractSensor(int bufferSize = 24, double min = 0, double max = 30);
    virtual ~AbstractSensor() = default;
    virtual void read() = 0;
    virtual void setBufferSize(int);
    virtual unsigned int getBufferSize() const;
    virtual void pushReading(double);
    virtual const std::list<double>& getReadings() const;
};

#endif