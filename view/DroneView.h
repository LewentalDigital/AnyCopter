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
#include "../model/SensorObserverInterface.h"

namespace View {

class DroneView : public QWidget, public SensorObserverInterface{
    Q_OBJECT
   private:
    Drone* drone;
    int removedSensors;

    QLabel* name;
    QProgressBar* pbBattery;
    QLabel* cpuTemperature;
    QGridLayout* droneSensors;
    QPushButton* btnRead;
    
    // QVector<QWidget*> sensorSockets;

   public:
    DroneView(Drone*, QWidget* = nullptr);

    void notify(AbstractSensor&) override;

   public slots:
    void mountSensor(AbstractSensor*, int);
    void removeSensor(int);
    void readNewData();
    void back();
};

}  // namespace View
#endif