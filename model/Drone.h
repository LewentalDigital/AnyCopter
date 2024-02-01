#include "AbstractSensor.h"
#include "Thermometer.h"
#include "BatteryChargeSensor.h"
#include "GPS.h"
#include "Altimeter.h"

#include <vector>


class Drone
{
private:
    Thermometer tempCpu;
    BatteryChargeSensor battery;
    GPS gps;
    Altimeter altimeter;

    std::vector<AbstractSensor&> externalSensors;
public:
    Drone();
    virtual ~Drone();
    void mountSensor(const AbstractSensor& sensor) {
        externalSensors.push_back(sensor);
    }
    void unmountSensor(std::vector<AbstractSensor&>::iterator it) {
        externalSensors.erase(it);
    }
    double getCurrentCpuTemperature() const {
        return tempCpu.getTemperature();
    }
    double getCurrentBatteryCharge() const {
        return battery.getCharge();
    }
    double getCurrentLatitude() const {
        return gps.getLat();
    }
    double getCurrentLongitude() const {
        return gps.getLon();
    }
    double getCurrentAltitude() const {
        return altimeter.getAltitude();
    }
    
};