#ifndef VIEW_DRONEWIDGET_H
#define VIEW_DRONEWIDGET_H
#include <QLabel>
#include <QWidget>

class DroneWidget : public QWidget {
    Q_OBJECT
   private:
    QLabel* hit_points_label;
    QLabel* strength_label;

   public:
};

#endif