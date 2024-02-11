#ifndef VIEW_DRONEVIEW_H
#define VIEW_DRONEVIEW_H

#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVector>
#include <QWidget>

#include "../model/AbstractSensor.h"
#include "../model/Drone.h"
#include "../model/DroneObserverInterface.h"

namespace View {

class DroneView : public QWidget, public DroneObserverInterface {
    Q_OBJECT
   private:
    Drone* drone;
    int removedSensors;

    QLabel* name;
    QProgressBar* pbBattery;
    QLabel* cpuTemperature;
    QGridLayout* droneSensors;
    QPushButton* btnRead;

   public:
    DroneView(Drone*, QWidget* = nullptr);
    ~DroneView();

    void notify(Drone&) override;

   public slots:
    void mountSensor(AbstractSensor*, int);
    void removeSensor(int);
    void readNewData();
    void back();
};

}  // namespace View
#endif