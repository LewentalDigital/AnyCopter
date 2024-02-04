#include "DroneManager.h"

DroneManager::DroneManager() {
}

void DroneManager::deployDrone(Drone* deployedDrone) {
    drones.push_back(deployedDrone);
}

const std::vector<Drone*>& DroneManager::getDrones() const {
    return drones;
}
