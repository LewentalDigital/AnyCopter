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
    std::ofstream f(filename, std::ios_base::app);

    if (f.is_open()) {
        for (auto d = drones.begin(); d != drones.end(); ++d) {
            f << (*d)->getName() << PersistenceManager::SEPARATOR;
            for (auto s = (*d)->getMountedSensors().begin(); s != (*d)->getMountedSensors().end(); ++s) {
                SensorSaveVisitor visitor;
                (*s)->accept(visitor);
                f << visitor.getId() << PersistenceManager::SEPARATOR
                  << (*s)->getBufferSize() << PersistenceManager::SEPARATOR
                  << (*s)->getReadings().size() << PersistenceManager::SEPARATOR;
            }
            f << std::endl;
        }
    } else {
        throw std::runtime_error("Error managing save file; maybe it's already open in another program?");
    }
}

std::vector<Drone *> PersistenceManager::load(const std::string &filename) const {
    std::vector<Drone *> retDrones;
    Drone* gino = new Drone("gino");
    retDrones.push_back(gino);

    std::ifstream f(filename, std::ios_base::app);
    std::string line;

    if (f.is_open()) {
        if (f.peek() == std::ifstream::traits_type::eof()) {
            f.close();
            return retDrones;
        }

        while (getline(f, line)) {
            std::string droneName, sensorId, sensorBufferSize, sensorReadings;
            std::istringstream iss(line);

            getline(iss, droneName, PersistenceManager::SEPARATOR);
            // Drone *drone = new Drone(droneName);

            // while (getline(iss, sensorId, PersistenceManager::SEPARATOR)) {
            //         getline(iss, sensorBufferSize, PersistenceManager::SEPARATOR);
            //         getline(iss, sensorReadings, PersistenceManager::SEPARATOR);

            //         unsigned int buffer = stoul(sensorBufferSize);
            //         unsigned int readings = stoul(sensorReadings);
            //         AbstractSensor *sensor;

            //         if (sensorId == "BatteryChargeSensor") {
            //             sensor = new BatteryChargeSensor(buffer);
            //         } else {
            //             sensor = new Thermometer(buffer);
            //         }

            //         for (int i = 0; i < readings; i++)
            //             sensor->read();
            //         drone->mountSensor(sensor);
            // }
            // retDrones.push_back(new Drone("gino"));
        }
        f.close();
        return retDrones;
    } else {
        throw std::runtime_error("Error managing load file; maybe it's already open in another program?");
    }
}