#ifndef DRONE_H
#define DRONE_H

#include <string>
#include <vector>

#include "AbstractSensor.h"
#include "Altimeter.h"
#include "BatteryChargeSensor.h"
#include "GPS.h"
#include "Thermometer.h"

class Drone {
   private:
    std::string name;
    Thermometer tempCpu;
    BatteryChargeSensor battery;
    GPS gps;
    Altimeter altimeter;

    // std::vector<AbstractSensor&> externalSensors;

   public:
    static const int sensorSockets;
    Drone(std::string);
    virtual ~Drone() = default;
    std::string getName() const;
    // void mountSensor(const AbstractSensor& sensor) {
    //     if (externalSensors.size() < sensorSockets) {
    //         externalSensors.push_back(sensor);
    //     } else
    //         throw std::runtime_error("No more sensor sockets available");
    // }
    // void unmountSensor(std::vector<AbstractSensor&>::iterator it) {
    //     externalSensors.erase(it);
    // }
    // double getCurrentCpuTemperature() const {
    //     return tempCpu.getTemperature();
    // }
    // double getCurrentBatteryCharge() const {
    //     return battery.getCharge();
    // }
    // double getCurrentLatitude() const {
    //     return gps.getLat();
    // }
    // double getCurrentLongitude() const {
    //     return gps.getLon();
    // }
    // double getCurrentAltitude() const {
    //     return altimeter.getAltitude();
    // }
};
#endif