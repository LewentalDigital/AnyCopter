#include <random>

#include "AbstractSensor.h"

class Thermometer : public AbstractSensor {
   private:
    double temperature;

   public:

    Thermometer() : temperature(0) {}
    
    void read() override {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 2);  // distribution in range [1, 6]

        // do complex measurements
        temperature = dist6(rng);
    }

    double getTemperature() const {
        return temperature;
    }
};