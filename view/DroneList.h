#ifndef VIEW_DRONELIST_H
#define VIEW_DRONELIST_H

#include <QVector>
#include <QWidget>
#include <QVBoxLayout>

#include "../model/Drone.h"
#include "../model/DroneManager.h"
#include "DroneListItem.h"

namespace View {

class DroneList : public QWidget {
    Q_OBJECT
   private:
    DroneManager* droneManager;
    QVector<DroneListItem*> droneItems;

    QVBoxLayout* content;

   public:
    DroneList(DroneManager*, QWidget* = nullptr);

   signals:
    void manageDrone(Drone*);
   public slots:
    void addDrone(Drone*);
};

}  // namespace View
#endif