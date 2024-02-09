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

namespace View {

class DroneView : public QWidget {
    Q_OBJECT
   private:
    Drone* drone;
    int gridRowPosition;
    int gridColPosition;
    // row = [0...int(number of sockets/2)], col = [0,1]
    // 2 sensors in a row
    // => grid->addWidget(widget, gridRowPosition/2, gridColPosition % 2);

    // oggetti solo per cose che cambiano
    QLabel* name;
    QProgressBar* pbBattery;
    QLabel* cpuTemperature;
    QGridLayout* droneSensors;
    QPushButton* btnRead;

   public:
    DroneView(Drone*, QWidget* = nullptr);

   public slots:
    void mountSensor(const AbstractSensor&, int, int);
    void readNewData();
    void back();
};

}  // namespace View
#endif