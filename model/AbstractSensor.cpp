#include "AbstractSensor.h"

AbstractSensor::AbstractSensor(int bs, double m, double M) : bufferSize(bs), min(m), max(M) {}

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

void AbstractSensor::setBufferSize(int size) {
    bufferSize = size;
}

unsigned int AbstractSensor::getBufferSize() const {
    return bufferSize;
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