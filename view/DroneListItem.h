#ifndef VIEW_DRONELISTITEM_H
#define VIEW_DRONELISTITEM_H

#include <QLabel>
#include <QProgressBar>
#include <QWidget>

#include "../model/Drone.h"
#include "../model/DroneObserverInterface.h"

namespace View {
class DroneListItem : public QWidget, public DroneObserverInterface {
    Q_OBJECT
   private:
    Drone* drone;

    QLabel* image;
    QLabel* name;
    QProgressBar* pbBattery;
    QLabel* numSensors;

   public:
    DroneListItem(Drone*, QWidget* = nullptr);
    ~DroneListItem();
    void notify(Drone&) override;

   signals:
    void manageDrone(Drone*);
};

}  // namespace View
#endif