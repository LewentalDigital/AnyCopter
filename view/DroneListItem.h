#ifndef VIEW_DRONELISTITEM_H
#define VIEW_DRONELISTITEM_H

#include <QLabel>
#include <QWidget>

#include "../model/Drone.h"

namespace View {
class DroneListItem : public QWidget {
    Q_OBJECT
   private:
    Drone* drone;
    QLabel* image;
    QLabel* name;
    QLabel* batteryLevel;
    QLabel* numSensors;

   public:
    DroneListItem(Drone*, QWidget* = nullptr);

   signals:
    void manageDrone(Drone*);
};

}  // namespace View
#endif