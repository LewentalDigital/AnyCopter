#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include <vector>

#include "Drone.h"

class DroneManager {
   private:
    std::vector<Drone&> drones;

   public:
    DrooneManager() {}
    void deployDrone(Drone& drone) {
        drones.push_back(drone);
    }
};
#endif