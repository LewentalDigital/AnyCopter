#ifndef VIEW_SENSORVIEW_H
#define VIEW_SENSORVIEW_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "../model/AbstractSensor.h"
#include "../model/SensorObserverInterface.h"

namespace View {

class SensorView : public QWidget, public SensorObserverInterface {
    Q_OBJECT
   private:
    QLabel* bufferSize;
    QPushButton* btnEdit;
    QPushButton* btnRemove;
    QVBoxLayout* main;
    QWidget* content;

   public:
    SensorView(AbstractSensor*, QWidget* = nullptr);
    // void setContent(QWidget*);

    void notify(AbstractSensor&) override;

   signals:
    void edit();
    void remove();
};

}  // namespace View
#endif