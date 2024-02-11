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
    int gridRowPosition;
    int gridColPosition;
    // row = [0...int(number of sockets/2)], col = [0,1]
    // 2 sensors in a row
    // => grid->addWidget(widget, gridRowPosition/2, gridColPosition % 2);

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
    void mountSensor(AbstractSensor*, int, int);
    void readNewData();
    void back();
};

}  // namespace View
#endif