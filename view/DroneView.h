#ifndef VIEW_DRONEVIEW_H
#define VIEW_DRONEVIEW_H

#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVector>
#include <QWidget>
#include <vector>

#include "../model/AbstractSensor.h"
#include "../model/Drone.h"
#include "../model/DroneObserverInterface.h"

namespace View {

class DroneView : public QWidget, public DroneObserverInterface {
    Q_OBJECT
   private:
    Drone* drone;
    std::vector<int> sensorPos;  // sensorPos[n] < 0 => free socket, sensorPos[n] >= 0 => position of sensor in the vector

    QLabel* name;
    QProgressBar* pbBattery;
    QLabel* cpuTemperature;
    QGridLayout* droneSensors;
    QPushButton* btnRead;

   public:
    DroneView(Drone*, QWidget* = nullptr);
    ~DroneView();

    void notify(Drone&) override;

   signals:
    void sensorMounted();
    void sensorRemoved();
    void sensorEdited();

   public slots:
    void mountSensor(AbstractSensor*, int);
    void removeSensor(int);
    void editSensor(int);
    void readNewData();
    void back();
};

}  // namespace View
#endif