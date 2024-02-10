#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H

class BatteryChargeSensor;
class CO2Sensor;
class Hygrometer;
class Thermometer;

class SensorVisitorInterface {
   public:
    virtual ~SensorVisitorInterface() = default;
    virtual void visitBatteryChargeSensor(BatteryChargeSensor&) = 0;
    virtual void visitCO2Sensor(CO2Sensor&) = 0;
    virtual void visitHygrometer(Hygrometer&) = 0;
    virtual void visitThermometer(Thermometer&) = 0;
};

#endif