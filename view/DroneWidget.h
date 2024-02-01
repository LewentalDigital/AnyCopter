#ifndef VIEW_DRONEWIDGET_H
#define VIEW_DRONEWIDGET_H

#include <QLabel>
#include <QWidget>

class DroneWidget : public QWidget {
    Q_OBJECT
   private:
    QLabel* image;
    QLabel* name;
    QLabel* batteryLevel;

   public:
    DroneWidget(QWidget* parent = nullptr);
};

#endif