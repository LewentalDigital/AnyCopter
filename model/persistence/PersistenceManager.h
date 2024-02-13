#include <vector>
#include <string>

#include "../Drone.h"
#include "../DroneManager.h"

class PersistenceManager {
   private:
    static const char SEPARATOR;
    const std::vector<Drone *> &drones;

   public:
    PersistenceManager(const std::vector<Drone *> &drones);
    void save(const std::string &);
    void load(const std::string &, DroneManager &);
};