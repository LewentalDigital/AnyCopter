#ifndef DRONE_H
#define DRONE_H

#include <string>
#include <vector>

#include "AbstractSensor.h"
#include "BatteryChargeSensor.h"
#include "Hygrometer.h"
#include "Thermometer.h"
#include "DroneObserverInterface.h"

class Drone {
   private:
    std::string name;
    Thermometer tempCpu;
    BatteryChargeSensor battery;

    std::vector<AbstractSensor*> externalSensors;

    std::list<DroneObserverInterface*> observers;

   public:
    static const unsigned int sensorSockets;  // sarebbe da chiamare numSocets?
    Drone(std::string);
    virtual ~Drone();

    std::string getName() const;
    void mountSensor(AbstractSensor*);
    void unmountSensor(int);
    void readHardware();

    double getBatteryLevel() const;
    double getCpuTemperature() const;
    int getNumMountedSensors() const;
    const std::vector<AbstractSensor*>& getMountedSensors() const;

    void registerObserver(DroneObserverInterface*);
    void unregisterObserver(DroneObserverInterface*);
};
#endif