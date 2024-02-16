#ifndef VIEW_DASHBOARD_H
#define VIEW_DASHBOARD_H

#include <QWidget>
#include <QLabel>

#include "../model/DroneManager.h"
#include "../model/DroneObserverInterface.h"
#include "../model/SensorObserverInterface.h"

namespace View {

class Dashboard : public QWidget, SensorObserverInterface {
    Q_OBJECT
   private:
    const DroneManager& droneManager;

    QLabel* labelNumDrones;
    QLabel* labelNumSensors;
    QLabel* labelAvgCo2;
    QLabel* labelAvgHumidity;
    QLabel* labelAvgTemp;

   public:
    Dashboard(const DroneManager&, QWidget* = nullptr);

    void notify(AbstractSensor&) override;


   signals:
   public slots:
};

}  // namespace View
#endif