#include <vector>
#include <string>

#include "../Drone.h"

class PersistenceManager {
   private:
    static const char SEPARATOR;
    const std::vector<Drone *> &drones;

   public:
    PersistenceManager(const std::vector<Drone *> &drones);
    void save(const std::string &);
    std::vector<Drone *> load(const std::string &) const;
};