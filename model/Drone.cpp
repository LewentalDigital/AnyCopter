#include "Drone.h"

const unsigned int Drone::sensorSockets = 2;

Drone::Drone(std::string n) : name(n) {
}

Drone::~Drone() {
    for (AbstractSensor* sensor : externalSensors)
        delete sensor;
}

std::string Drone::getName() const {
    return name;
}

void Drone::setName(std::string n) {
    name = n;
    
    for (auto observer = observers.begin(); observer != observers.end(); ++observer)
        (*observer)->notify(*this);
}

void Drone::mountSensor(AbstractSensor* sensor) {
    if (externalSensors.size() < sensorSockets) {
        externalSensors.push_back(sensor);
    } else
        throw std::string("No more sensor sockets available");

    for (auto observer = observers.begin(); observer != observers.end(); ++observer)
        (*observer)->notify(*this);
}

void Drone::unmountSensor(int index) {
    externalSensors.erase(externalSensors.begin() + index);

    for (auto observer = observers.begin(); observer != observers.end(); ++observer)
        (*observer)->notify(*this);
}

void Drone::readHardware() {
    battery.read();
    tempCpu.read();

    for (auto observer = observers.begin(); observer != observers.end(); ++observer)
        (*observer)->notify(*this);
}

double Drone::getBatteryLevel() const {
    return battery.getCurrentReading();
}

double Drone::getCpuTemperature() const {
    return tempCpu.getCurrentReading();
}

int Drone::getNumMountedSensors() const {
    return externalSensors.size();
}

const std::vector<AbstractSensor*>& Drone::getMountedSensors() const {
    return externalSensors;
}

void Drone::registerObserver(DroneObserverInterface* observer) {
    observers.push_back(observer);
}

void Drone::unregisterObserver(DroneObserverInterface* observer) {
    observers.remove(observer);
}
