#include "PersistenceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>

#include "../AbstractSensor.h"
#include "../BatteryChargeSensor.h"
#include "../CO2Sensor.h"
#include "../DroneManager.h"
#include "../Hygrometer.h"
#include "../Thermometer.h"
#include "SensorSaveVisitor.h"

const std::string PersistenceManager::defaultSaveFile = "savefile.csv";
const char PersistenceManager::SEPARATOR = ',';

PersistenceManager::PersistenceManager(DroneManager &dm) : droneManager(dm) {
    for (Drone *drone : droneManager.getDrones()) {
        drone->registerObserver(this);
        for (AbstractSensor *sensor : drone->getMountedSensors()) {
            sensor->registerObserver(this);
        }
    }
}

PersistenceManager::~PersistenceManager() {
    for (Drone *drone : droneManager.getDrones()) {
        drone->unregisterObserver(this);
        for (AbstractSensor *sensor : drone->getMountedSensors()) {
            sensor->unregisterObserver(this);
        }
    }
}

void PersistenceManager::notify(Drone &drone) {
    save(PersistenceManager::defaultSaveFile);
    std::string noWarning = drone.getName();
}
void PersistenceManager::notify(AbstractSensor &sensor) {
    save(PersistenceManager::defaultSaveFile);
    unsigned int noWarning = sensor.getBufferSize();
    noWarning++;  // to avoid compiler warning
}

void PersistenceManager::save(const std::string &fn) {
    std::string filename = fn;
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    if (extension.compare("csv") != 0)
        filename += ".csv";

    std::ofstream file(filename, std::ios_base::trunc);  // it will overwrite the file with new changes

    if (file.is_open()) {
        const std::vector<Drone *> drones = droneManager.getDrones();
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

void PersistenceManager::load(const std::string &filename) {
    std::ifstream file(filename, std::ios_base::in);
    // std::ifstream file(filename, std::ios_base::app);
    std::string line;

    droneManager.clear();  // clear all drones and sensors to load new ones

    if (file.is_open()) {
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

                if (sensorId.compare(typeid(BatteryChargeSensor).name()) == 0)
                    sensor = new BatteryChargeSensor();
                else if (sensorId.compare(typeid(CO2Sensor).name()) == 0)
                    sensor = new CO2Sensor();
                else if (sensorId.compare(typeid(Hygrometer).name()) == 0)
                    sensor = new Hygrometer();
                else if (sensorId.compare(typeid(Thermometer).name()) == 0)
                    sensor = new Thermometer();
                else
                    sensor = new BatteryChargeSensor();
                // There must be a better way to do this

                sensor->setBufferSize(buffer);
                for (unsigned int i = 0; i < readings; i++)
                    sensor->read();
                drone->mountSensor(sensor);
                sensor->registerObserver(this);
            }
            drone->registerObserver(this);
            droneManager.deployDrone(drone);
        }
        file.close();
    } else {
        throw std::string("Error managing load file; maybe it's already open in another program?");
    }
}