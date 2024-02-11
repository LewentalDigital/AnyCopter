#include "Drone.h"

const unsigned int Drone::sensorSockets = 2;

Drone::Drone(std::string n) : name(n) {
}

Drone::~Drone() {
    for (auto it = externalSensors.begin(); it != externalSensors.end(); ++it) {
        delete *it;
    }
}

std::string Drone::getName() const {
    return name;
}

void Drone::mountSensor(AbstractSensor* sensor) {
    if (externalSensors.size() < sensorSockets) {
        externalSensors.push_back(sensor);
    } else
        throw std::string("No more sensor sockets available");
}

void Drone::unmountSensor(int index) {
    externalSensors.erase(externalSensors.begin() + index);
}

double Drone::getBatteryLevel() {
    battery.read();
    return battery.getCurrentReading();
}

double Drone::getCpuTemperature() {
    tempCpu.read();
    return tempCpu.getCurrentReading();
}

int Drone::getNumMountedSensors() const {
    return externalSensors.size();
}

const std::vector<AbstractSensor*>& Drone::getMountedSensors() const {
    return externalSensors;
}