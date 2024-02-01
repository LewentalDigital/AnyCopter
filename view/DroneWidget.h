#ifndef VIEW_DRONEWIDGET_H
#define VIEW_DRONEWIDGET_H
#include <QWidget>
#include <QLabel>

class DroneWidget: public QWidget, public CharacterObserverInterface {
    Q_OBJECT
  private:
    Character& character;
    QLabel* ;
    QLabel* hit_points_label;
    QLabel* strength_label;

  public:
    Info(Character& character, QWidget* parent = 0);
    void show();
    virtual void notify(Character& character);
};





#endif