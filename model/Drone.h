#ifndef DRONE_H
#define DRONE_H

#include <string>
#include <vector>

#include "AbstractSensor.h"
#include "Altimeter.h"
#include "BatteryChargeSensor.h"
#include "GPS.h"
#include "Hygrometer.h"
#include "Thermometer.h"

class Drone {
   private:
    std::string name;
    Thermometer tempCpu;
    BatteryChargeSensor battery;
    GPS gps;
    Altimeter altimeter;

    std::vector<AbstractSensor*> externalSensors;

   public:
    static const int sensorSockets;  // sarebbe da chiamare numSocets?
    Drone(std::string);
    virtual ~Drone();
    std::string getName() const;
    void mountSensor(AbstractSensor*);
    void unmountSensor(std::vector<AbstractSensor*>::iterator);
    double getBatteryLevel();
    int getNumEquippedSensors() const;
};
#endif