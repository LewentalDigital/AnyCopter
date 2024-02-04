#ifndef VIEW_DRONELIST_H
#define VIEW_DRONELIST_H

#include <QWidget>
#include <QVector>

#include "../model/DroneManager.h"
#include "../model/Drone.h"
#include "DroneListItem.h"

namespace View {

class DroneList : public QWidget {
    Q_OBJECT
   private:
    DroneManager* droneManager;
    QVector<DroneListItem*> droneItems;

   public:
    DroneList(DroneManager*, QWidget* = nullptr);

   signals:
    void manageDrone(Drone*);
};

}  // namespace View
#endif