#ifndef VIEW_DRONELIST_H
#define VIEW_DRONELIST_H

#include <QWidget>

#include "../model/DroneManager.h"

namespace View {

class DroneList : public QWidget {
    Q_OBJECT
   private:
    DroneManager* droneManager;

   public:
    DroneList(DroneManager*, QWidget* = nullptr);
};

}  // namespace View
#endif