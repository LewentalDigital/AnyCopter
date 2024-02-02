#include "DroneManager.h"

DroneManager::DroneManager() {
}

void DroneManager::deployDrone(Drone* deployedDrone) {
    drones.push_back(deployedDrone);
}