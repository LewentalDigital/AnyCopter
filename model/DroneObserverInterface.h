#ifndef DRONEOBSERVERINTERFACE_H
#define DRONEOBSERVERINTERFACE_H

class Character;

class DroneObserverInterface {
   public:
    virtual ~DroneObserverInterface() = default;
    virtual void notify(Drone& character) = 0;
};

#endif