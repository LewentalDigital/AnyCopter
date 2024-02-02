#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <vector>

#include "Drone.h"

class DroneManager {
   private:
    std::vector<Drone*> drones;

   public:
    DroneManager();
    void deployDrone(Drone* );
};
#endif