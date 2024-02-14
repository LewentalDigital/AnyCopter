#ifndef VIEW_DRONELIST_H
#define VIEW_DRONELIST_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>
#include <vector>

#include "../model/Drone.h"
#include "../model/DroneManager.h"
#include "DroneListItem.h"

namespace View {

class DroneList : public QWidget {
    Q_OBJECT
   private:
    DroneManager* droneManager;
    QVector<DroneListItem*> droneItems;

    QScrollArea* scrollArea;
    QVBoxLayout* content;

   public:
    DroneList(const std::vector<Drone*>&, QWidget* = nullptr);
    ~DroneList();

   signals:
    void manageDrone(Drone*);
   public slots:
    void addDrone(Drone*);
    void reload(const std::vector<Drone*>&);
};

}  // namespace View
#endif