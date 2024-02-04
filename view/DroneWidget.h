#ifndef VIEW_DRONEWIDGET_H
#define VIEW_DRONEWIDGET_H

#include <QLabel>
#include <QWidget>

#include "../model/Drone.h"

namespace View {
class DroneWidget : public QWidget {
    Q_OBJECT
   private:
    Drone* drone;
    QLabel* image;
    QLabel* name;
    QLabel* batteryLevel;
    QLabel* numSensors;

   public:
    DroneWidget(Drone*, QWidget* = nullptr);
};

}  // namespace View
#endif