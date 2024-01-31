#include "Thermometer.h"
#include "BatteryChargeSensor.h"
#include "GPS.h"
#include "Altimeter.h"


class Drone
{
private:
    Thermometer tempCpu;
    BatteryChargeSensor battery;
    GPS gps;
    Altimeter altimeter;

public:
    Drone();
    ~Drone();
};

Drone::Drone()
{
}

Drone::~Drone()
{
}
