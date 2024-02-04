#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "../model/DroneManager.h"
#include "../model/Drone.h"

namespace View {

class MainWindow : public QMainWindow {
    Q_OBJECT
    QStackedWidget* stackedWidget;

   public:
    MainWindow(DroneManager* = nullptr);

   public slots:
    void close();
    void manageDrone(Drone*);
};

}  // namespace View
#endif