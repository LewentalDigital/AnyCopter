#ifndef VIEW_EMPTYSENSORSOCKET_H
#define VIEW_EMPTYSENSORSOCKET_H

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "../model/AbstractSensor.h"

namespace View {

class EmptySensorSocket : public QWidget {
    Q_OBJECT
   private:
    QComboBox* sensorType;
    QLineEdit* bufferSizeInput;
    QPushButton* btnMountSensor;

   public:
    EmptySensorSocket(QWidget* = nullptr);

   signals:
    void mountSensor(AbstractSensor*);
   public slots:
    void handleMount();
    void remove();
};

}  // namespace View
#endif