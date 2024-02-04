#include "AbstractSensor.h"

double AbstractSensor::random(double mean, double variation) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(mean, variation);
    return dist(gen);
}