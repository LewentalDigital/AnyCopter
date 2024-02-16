#include "DroneManager.h"
#include "Thermometer.h"
#include "Hygrometer.h"
#include "CO2Sensor.h"

DroneManager::~DroneManager() {
    for (Drone* drone : drones) {
        delete drone;
    }
}

void DroneManager::deployDrone(Drone* deployedDrone) {
    for (auto drone = drones.begin(); drone != drones.end(); ++drone)
        if ((*drone)->getName() == deployedDrone->getName())
            throw std::string("Drone with name \"" + deployedDrone->getName() + "\" already exists, Drones must have unique names.");

    drones.push_back(deployedDrone);
}

void DroneManager::removeDrone(std::vector<Drone*>::const_iterator it) {
    drones.erase(it);
}

void DroneManager::clear() {
    drones.clear();
}

unsigned int DroneManager::getNumDrones() const {
    return drones.size();
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

std::list<double> DroneManager::getThermometerReadings() const {
    std::list<double> readings;
    for (auto drone = drones.begin(); drone != drones.end(); ++drone) {
        const std::vector<AbstractSensor*>& sensors = (*drone)->getMountedSensors();
        for (auto sensor = sensors.begin(); sensor != sensors.end(); ++sensor) {
            if (dynamic_cast<Thermometer*>(*sensor)) {
                (*sensor)->read();
                for (auto reading = (*sensor)->getReadings().begin(); reading != (*sensor)->getReadings().end(); ++reading) {
                    readings.push_back(*reading);
                }
            }
        }
    }
    return readings;
}

std::list<double> DroneManager::getHygrometerReadings() const {
    std::list<double> readings;
    for (auto drone = drones.begin(); drone != drones.end(); ++drone) {
        const std::vector<AbstractSensor*>& sensors = (*drone)->getMountedSensors();
        for (auto sensor = sensors.begin(); sensor != sensors.end(); ++sensor) {
            if (dynamic_cast<Hygrometer*>(*sensor)) {
                (*sensor)->read();
                for (auto reading = (*sensor)->getReadings().begin(); reading != (*sensor)->getReadings().end(); ++reading) {
                    readings.push_back(*reading);
                }
            }
        }
    }
    return readings;
}

std::list<double> DroneManager::getCO2SensorReadings() const {
    std::list<double> readings;
    for (auto drone = drones.begin(); drone != drones.end(); ++drone) {
        const std::vector<AbstractSensor*>& sensors = (*drone)->getMountedSensors();
        for (auto sensor = sensors.begin(); sensor != sensors.end(); ++sensor) {
            if (dynamic_cast<CO2Sensor*>(*sensor)) {
                (*sensor)->read();
                for (auto reading = (*sensor)->getReadings().begin(); reading != (*sensor)->getReadings().end(); ++reading) {
                    readings.push_back(*reading);
                }
            }
        }
    }
    return readings;
}
