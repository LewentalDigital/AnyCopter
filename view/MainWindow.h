#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>

#include "../model/DroneManager.h"

namespace View {

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(DroneManager* = nullptr);

   public slots:
    void close();
};

}  // namespace View
#endif