#include <string>

#include "../AbstractSensor.h"
#include "../Drone.h"
#include "../DroneManager.h"
#include "../SensorObserverInterface.h"
#include "../DroneObserverInterface.h"

class PersistenceManager : public SensorObserverInterface, public DroneObserverInterface { //so it will be notified when changes occur and can save them
   private:
    static const char SEPARATOR;
    DroneManager& droneManager;

    void notify(Drone&) override;
    void notify(AbstractSensor&) override;

   public:
    PersistenceManager(DroneManager&);
    virtual ~PersistenceManager();
    static const std::string defaultSaveFile;
    void save(const std::string &);
    void load(const std::string &);
};