#include "Drone.h"

const int Drone::sensorSockets = 2;

Drone::Drone(std::string n) : name(n) {
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
void Drone::unmountSensor(std::vector<AbstractSensor*>::iterator it) {
    externalSensors.erase(it);
}

double Drone::getBatteryLevel() {
    battery.read();
    return battery.getCharge();
}

int Drone::getNumEquippedSensors() const {
    return externalSensors.size();
}