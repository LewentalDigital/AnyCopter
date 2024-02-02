#include "Drone.h"

Drone::Drone(std::string n) : name(n) {
}
std::string Drone::getName() const {
    return name;
}

const int Drone::sensorSockets = 2;