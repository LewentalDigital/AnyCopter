#include "SensorTitleVisitor.h"

#include <QLabel>

#include "../model/BatteryChargeSensor.h"
#include "../model/CO2Sensor.h"
#include "../model/Hygrometer.h"
#include "../model/Thermometer.h"

namespace View {

void SensorTitleVisitor::setupTitle() {
    title = new QWidget();
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleContent = new QHBoxLayout();
    titleContent->setAlignment(Qt::AlignLeft);
    titleContent->setContentsMargins(10, 0, 10, 0);
    title->setLayout(titleContent);
}

QWidget* SensorTitleVisitor::getTitle() {
    return title;
}

void SensorTitleVisitor::visit(BatteryChargeSensor& bcs) {
    setupTitle();

    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/battery-half.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    QLabel* labelTitle = new QLabel("Battery charge sensor");
    labelTitle->setObjectName("title");
    // titleContent->addWidget(new QLabel("<strong>Battery charge sensor</strong>"));
    titleContent->addWidget(labelTitle);

}

void SensorTitleVisitor::visit(CO2Sensor& co2s) {
    setupTitle();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/leaf.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    titleContent->addWidget(new QLabel("<strong>CO2 Sensor</strong>"));

}

void SensorTitleVisitor::visit(Hygrometer& h) {
    setupTitle();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/water.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    titleContent->addWidget(new QLabel("<strong>Hygrometer</strong>"));

}

void SensorTitleVisitor::visit(Thermometer& t) {
    setupTitle();
    QLabel* icon = new QLabel();
    icon->setPixmap(QPixmap(":assets/icons/thermometer.svg").scaledToHeight(28, Qt::SmoothTransformation));
    titleContent->addWidget(icon);
    titleContent->addWidget(new QLabel("<strong>Thermometer</strong>"));
}

}  // namespace View