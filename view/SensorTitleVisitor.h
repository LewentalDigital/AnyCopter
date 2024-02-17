#ifndef VIEW_SENSORTITLEVISITOR_H
#define VIEW_SENSORTITLEVISITOR_H

#include <QWidget>
#include <QHBoxLayout>

#include "../model/SensorVisitorInterface.h"

namespace View {

class SensorTitleVisitor : public SensorVisitorInterface {
   private:
    QWidget* widget;

    QWidget* title;
    QHBoxLayout* titleContent;

   public:
    QWidget* getTitle();
    void setupTitle();
    void visit(BatteryChargeSensor&) override;
    void visit(CO2Sensor&) override;
    void visit(Hygrometer&) override;
    void visit(Thermometer&) override;
};

}  // namespace View

#endif