#ifndef DRONE_H
#define DRONE_H

#include <string>
#include <vector>

#include "AbstractSensor.h"
#include "BatteryChargeSensor.h"
#include "Hygrometer.h"
#include "Thermometer.h"

class Drone {
   private:
    std::string name;
    Thermometer tempCpu;
    BatteryChargeSensor battery;

    std::vector<AbstractSensor*> externalSensors;

   public:
    static const unsigned int sensorSockets;  // sarebbe da chiamare numSocets?
    Drone(std::string);
    virtual ~Drone();

    std::string getName() const;
    void mountSensor(AbstractSensor*);
    void unmountSensor(std::vector<AbstractSensor*>::iterator);

    double getBatteryLevel();
    double getCpuTemperature();
    int getNumMountedSensors() const;
    const std::vector<AbstractSensor*>& getMountedSensors() const;
};
#endif