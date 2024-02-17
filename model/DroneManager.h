#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <list>
#include <vector>

#include "Drone.h"

class DroneManager {
   private:
    std::vector<Drone*> drones;

   public:
    ~DroneManager();

    void deployDrone(Drone*);
    void removeDrone(std::vector<Drone*>::const_iterator);
    void clear();

    unsigned int getNumDrones() const;
    const std::vector<Drone*>& getDrones() const;
    std::list<double> getAllReadings() const;

};
#endif