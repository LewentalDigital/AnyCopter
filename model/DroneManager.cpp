#include "DroneManager.h"

DroneManager::DroneManager() {
}
DroneManager::~DroneManager() {
    for (Drone* drone : drones) {
        delete drone;
    }
}

void DroneManager::deployDrone(Drone* deployedDrone) {
    drones.push_back(deployedDrone);
}

const std::vector<Drone*>& DroneManager::getDrones() const {
    return drones;
}
