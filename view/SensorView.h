#ifndef VIEW_SENSORVIEW_H
#define VIEW_SENSORVIEW_H

#include <QChart>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include "../model/AbstractSensor.h"
#include "../model/SensorObserverInterface.h"

namespace View {

class SensorView : public QWidget, public SensorObserverInterface {
    Q_OBJECT
   private:
    AbstractSensor* sensor;

    QLabel* bufferSize;
    QPushButton* btnEdit;
    QPushButton* btnRemove;
    QWidget* content;
    QChart* chart;

   public:
    SensorView(AbstractSensor*, QWidget* = nullptr);
    ~SensorView();

    void notify(AbstractSensor&) override;

   signals:
    void edit();
    void remove();
};

}  // namespace View
#endif