#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H

class BatteryChargeSensor;
class CO2Sensor;
class Hygrometer;
class Thermometer;

class SensorVisitorInterface {
   public:
    virtual ~SensorVisitorInterface() = default;
    virtual void visit(BatteryChargeSensor&) = 0;
    virtual void visit(CO2Sensor&) = 0;
    virtual void visit(Hygrometer&) = 0;
    virtual void visit(Thermometer&) = 0;
};

#endif