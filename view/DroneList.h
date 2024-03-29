#ifndef VIEW_DRONELIST_H
#define VIEW_DRONELIST_H

#include <QCompleter>
#include <QLineEdit>
#include <QPushButton>
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

    QVBoxLayout* content;
    QCompleter* completer;
    QLineEdit* searchInput;

    void loadDroneItems(const std::vector<Drone*>&);

   public:
    DroneList(const std::vector<Drone*>& = std::vector<Drone*>(), QWidget* = nullptr);
    ~DroneList();

    void loadSearchList(const std::vector<Drone*>&);

   signals:
    void manageDrone(Drone*);
   public slots:
    void addDrone(Drone*);
    void removeDrone(Drone*);
    void searchFocus();
    void search();
    void resetSearch();
    void reload(const std::vector<Drone*>&);
};

}  // namespace View
#endif