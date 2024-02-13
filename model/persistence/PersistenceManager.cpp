#include "PersistenceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../AbstractSensor.h"
#include "../BatteryChargeSensor.h"
#include "../CO2Sensor.h"
#include "../Hygrometer.h"
#include "../Thermometer.h"
#include "SensorSaveVisitor.h"

PersistenceManager::PersistenceManager(const std::vector<Drone *> &drones) : drones(drones) {
}

const char PersistenceManager::SEPARATOR = ',';

void PersistenceManager::save(const std::string &filename) {
    // std::ofstream file(filename, std::ios_base::app);
    std::ofstream file(filename, std::ios_base::trunc);

    if (file.is_open()) {
        for (auto d = drones.begin(); d != drones.end(); ++d) {
            file << (*d)->getName() << PersistenceManager::SEPARATOR;
            for (auto s = (*d)->getMountedSensors().begin(); s != (*d)->getMountedSensors().end(); ++s) {
                SensorSaveVisitor visitor;
                (*s)->accept(visitor);
                file << visitor.getId() << PersistenceManager::SEPARATOR
                  << (*s)->getBufferSize() << PersistenceManager::SEPARATOR
                  << (*s)->getReadings().size() << PersistenceManager::SEPARATOR;
            }
            file << std::endl;
        }
    } else {
        throw std::string("Error managing save file; maybe it's already open in another program?");
    }
}

void PersistenceManager::load(const std::string &filename, DroneManager &droneManager) {
    std::ifstream file(filename, std::ios_base::app);
    std::string line;

    if (file.is_open()) {
        // if (file.peek() == std::ifstream::traits_type::eof()) {
        //     file.close();
        //     return;
        // }

        while (getline(file, line)) {
            std::string droneName, sensorId, sensorBufferSize, sensorReadings;
            std::istringstream stream(line);

            getline(stream, droneName, PersistenceManager::SEPARATOR);
            Drone *drone = new Drone(droneName);

            while (getline(stream, sensorId, PersistenceManager::SEPARATOR)) {
                getline(stream, sensorBufferSize, PersistenceManager::SEPARATOR);
                getline(stream, sensorReadings, PersistenceManager::SEPARATOR);

                unsigned int buffer = stoul(sensorBufferSize);
                unsigned int readings = stoul(sensorReadings);
                AbstractSensor *sensor;

                if (sensorId == "BatteryChargeSensor") {
                    sensor = new BatteryChargeSensor(buffer);
                } else {
                    sensor = new Thermometer(buffer);
                }

                for (unsigned int i = 0; i < readings; i++)
                    sensor->read();
                drone->mountSensor(sensor);
            }
            droneManager.deployDrone(drone);
        }
        file.close();
    } else {
        throw std::string("Error managing load file; maybe it's already open in another program?");
    }
}