#ifndef VIEW_DRONEDEPLOYVIEW_H
#define VIEW_DRONEDEPLOYVIEW_H

#include <QLabel>
#include <QWidget>

#include "../model/Drone.h"

namespace View {

class DroneDeployView : public QWidget {
    Q_OBJECT
   private:
    QLabel* image;
    QLabel* batteryLevel;
    QLabel* cpuTemperature;
    QLabel* location;
    QLabel* altitude;

   public:
    DroneDeployView(QWidget* = nullptr);

   public slots:
    void back();
};

}  // namespace View
#endif