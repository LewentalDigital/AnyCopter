#include "AbstractSensor.h"

class GPS : public AbstractSensor {
   private:
    double latitude, longitude;

   public:
    GPS() : latitude(0), longitude(0) {}

    void read() override {
        // get in contact with the satellites and do complex calculations to get the position
        latitude = 1.0;
        longitude = 2.0;
    }

    double getLat() const {
        return latitude;
    }
    double getLon() const {
        return longitude;
    }
};