#ifndef VIEW_DRONEVIEW_H
#define VIEW_DRONEVIEW_H

#include <QLabel>
#include <QVector>
#include <QWidget>

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
    // QLabel* cpuTemperature;
    // QLabel* position;
    // QLabel* altitude;

    // Chart per posizione e altezza
    // grafici per sensori

   public:
    DroneView(Drone*, QWidget* = nullptr);
};

}  // namespace View
#endif