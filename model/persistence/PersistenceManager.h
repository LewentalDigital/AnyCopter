#include <vector>

#include "../Drone.h"

class PersistenceManager {
   private:
    const std::vector<Drone *> &drones;

   public:
    PersistenceManager(const std::vector<Drone *> &drones);
    void save(const std::string &);
};