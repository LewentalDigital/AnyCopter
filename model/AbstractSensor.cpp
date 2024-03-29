#include "AbstractSensor.h"

AbstractSensor::AbstractSensor(unsigned int bs, double m, double M) : bufferSize(bs), min(m), max(M) {}

AbstractSensor::~AbstractSensor() {}

void AbstractSensor::read() {
    for (auto observer = observers.begin(); observer != observers.end(); ++observer)
        (*observer)->notify(*this);
}

double AbstractSensor::random(double mean, double variation) const {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> dist(mean, variation);
    return dist(generator);
}

double AbstractSensor::randRange(double start, double end) const {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> dist(start, end);
    return dist(generator);
}

double AbstractSensor::getCurrentReading() const {
    return reading;
}

void AbstractSensor::pushReading(double reading) {
    // if buffer is full, forget the oldest readingt
    if (readingsBuffer.size() >= bufferSize)
        readingsBuffer.pop_front();
    readingsBuffer.push_back(reading);
}

const std::list<double>& AbstractSensor::getReadings() const {
    return readingsBuffer;
}

unsigned int AbstractSensor::getBufferSize() const {
    return bufferSize;
}

void AbstractSensor::setBufferSize(int size) {
    bufferSize = size;
    
    auto it = readingsBuffer.begin();
    while (readingsBuffer.size() > bufferSize) // forget older readings if buffer size is reduced
        it = readingsBuffer.erase(it);

    for (auto observer = observers.begin(); observer != observers.end(); ++observer)
        (*observer)->notify(*this);
}

void AbstractSensor::registerObserver(SensorObserverInterface* observer) {
    observers.push_back(observer);
}

void AbstractSensor::unregisterObserver(SensorObserverInterface* observer) {
    observers.remove(observer);
}
