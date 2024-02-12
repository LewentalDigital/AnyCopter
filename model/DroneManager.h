#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <list>
#include <vector>

#include "Drone.h"

class DroneManager {
   private:
    std::vector<Drone*> drones;

   public:
    DroneManager();
    ~DroneManager();

    void deployDrone(Drone*);
    void removeDrone(const std::vector<Drone*>::iterator);

    const std::vector<Drone*>& getDrones() const;
    std::list<double> getAllReadings() const;
};
#endif