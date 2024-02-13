#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "../model/Drone.h"
#include "../model/DroneManager.h"
#include "../model/persistence/PersistenceManager.h"
#include "DroneList.h"

namespace View {

class MainWindow : public QMainWindow {
    Q_OBJECT
   private:
    DroneManager* droneManager;
    PersistenceManager persistenceManager;
    QStackedWidget* stackedWidget;
    DroneList* droneList;

   public:
    MainWindow(DroneManager* = nullptr);

   public slots:
    void save();
    void quit();
    void refresh();
    void visitGithub();
    // void viewDroneList();
    void manageDrone(Drone*);
    void openDeployDroneView();
    void deployNewDrone(Drone*);
};

}  // namespace View
#endif