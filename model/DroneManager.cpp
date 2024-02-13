#include "DroneManager.h"

DroneManager::DroneManager() {
}

DroneManager::~DroneManager() {
    for (Drone* drone : drones) {
        delete drone;
    }
}

void DroneManager::deployDrone(Drone* deployedDrone) {
    for (Drone* drone : drones)
        if (drone->getName() == deployedDrone->getName())
            throw std::string("Drone with name \"" + deployedDrone->getName() + "\" already exists, Drones must have unique names.");

    drones.push_back(deployedDrone);
}

void DroneManager::removeDrone(const std::vector<Drone*>::iterator it) {
    drones.erase(it);
}

const std::vector<Drone*>& DroneManager::getDrones() const {
    return drones;
}

std::list<double> DroneManager::getAllReadings() const {
    std::list<double> readings;
    for (auto drone = drones.begin(); drone != drones.end(); ++drone) {
        const std::vector<AbstractSensor*>& sensors = (*drone)->getMountedSensors();
        for (auto sensor = sensors.begin(); sensor != sensors.end(); ++sensor) {
            (*sensor)->read();
            for (auto reading = (*sensor)->getReadings().begin(); reading != (*sensor)->getReadings().end(); ++reading) {
                readings.push_back(*reading);
            }
        }
    }
    return readings;
}
