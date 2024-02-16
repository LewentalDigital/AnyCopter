#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "../model/Drone.h"
#include "../model/DroneManager.h"
#include "../model/persistence/PersistenceManager.h"
#include "Dashboard.h"
#include "DroneList.h"

namespace View {

class MainWindow : public QMainWindow {
    Q_OBJECT
   private:
    DroneManager& droneManager;
    PersistenceManager persistenceManager;
    QStackedWidget* stackedWidget;
    Dashboard* dashboard;
    DroneList* droneList;

    void loadConfig(const QString&);

   public:
    MainWindow(DroneManager&);

   public slots:
    void open();
    void save();
    void saveAs();
    void quit();
    void refresh();
    void visitGithub();
    // void openDroneList();
    void openSearch();
    void deployNewDrone(Drone*);
    void deleteDrone(Drone*);
    void manageDrone(Drone*);
    void openDeployDroneView();
};

}  // namespace View
#endif