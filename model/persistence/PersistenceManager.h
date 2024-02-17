#include <string>

#include "../AbstractSensor.h"
#include "../Drone.h"
#include "../DroneManager.h"
#include "../DroneObserverInterface.h"
#include "../SensorObserverInterface.h"

class PersistenceManager : public SensorObserverInterface, public DroneObserverInterface {  // so it will be notified when changes occur and can save them
   private:
    static const char SEPARATOR;
    DroneManager &droneManager;

   public:
    PersistenceManager(DroneManager &);
    virtual ~PersistenceManager();
    static const std::string DEFAUL_SAVE_FILE;
    
    void save(const std::string &);
    void load(const std::string &);
    void registerToDrone(Drone &);
    void registerToSensor(AbstractSensor &);

    void notify(Drone &) override;
    void notify(AbstractSensor &) override;
};