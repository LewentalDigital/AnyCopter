#ifndef VIEW_DRONEDEPLOYVIEW_H
#define VIEW_DRONEDEPLOYVIEW_H

#include <QLabel>
#include <QLineEdit>
#include <QWidget>

#include "../model/Drone.h"

namespace View {

class DroneDeployView : public QWidget {
    Q_OBJECT
   private:
    QLabel* image;
    QLineEdit* nameInput;

   public:
    DroneDeployView(QWidget* = nullptr);

   signals:
    void deploy(Drone*);
   public slots:
    // void checkInput();
    void handleDeploy();
    void close();
};

}  // namespace View
#endif