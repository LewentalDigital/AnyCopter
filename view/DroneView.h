#ifndef VIEW_DRONEVIEW_H
#define VIEW_DRONEVIEW_H

#include <QLabel>
#include <QVector>
#include <QWidget>

#include "../model/AbstractSensor.h"
#include "../model/Drone.h"

namespace View {

class DroneView : public QWidget {
    Q_OBJECT
   private:
    Drone* drone;

    // oggetti solo per cose che cambiano
    QLabel* image;
    QLabel* name;
    QLabel* batteryLevel;
    QLabel* cpuTemperature;
    QLabel* location;
    QLabel* altitude;

    // Chart per posizione e altezza
    // grafici per sensori

   public:
    DroneView(Drone*, QWidget* = nullptr);

   public slots:
    void mountSensor(AbstractSensor*);
    void back();
};

}  // namespace View
#endif