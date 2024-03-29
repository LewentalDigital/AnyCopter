#include "SensorView.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "SensorChartVisitor.h"
#include "SensorTitleVisitor.h"

namespace View {

SensorView::SensorView(AbstractSensor* sensor, QWidget* parent) : QWidget(parent), sensor(sensor) {
    setMinimumHeight(220);

    SensorChartVisitor chartVisitor;
    sensor->accept(chartVisitor);
    content = chartVisitor.getWidget();  // get custom chart from visitor of sensor chart

    SensorTitleVisitor titleVisitor;
    sensor->accept(titleVisitor);

    main = new QVBoxLayout(this);
    main->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* titleBar = new QHBoxLayout();
    titleBar->setContentsMargins(0, 0, 0, 0);

    bufferSize = new QLabel("Buffer size: " + QString::number(sensor->getBufferSize()));
    btnEdit = new QPushButton(QIcon(QPixmap(":/assets/icons/edit.svg")), "Edit");
    btnRemove = new QPushButton(QIcon(QPixmap(":/assets/icons/remove.svg")), "Remove");
    btnRemove->setObjectName("btnDel");

    connect(btnEdit, &QPushButton::clicked, this, &SensorView::edit);
    connect(btnRemove, &QPushButton::clicked, this, &SensorView::remove);

    titleBar->addWidget(titleVisitor.getTitle());
    titleBar->addStretch();
    titleBar->addWidget(bufferSize);
    titleBar->addWidget(btnEdit);
    titleBar->addWidget(btnRemove);

    main->addLayout(titleBar);
    main->addWidget(content);

    sensor->registerObserver(this);
}

SensorView::~SensorView() {
    sensor->unregisterObserver(this);  // if this view gets deleted it should unregister from the observer list
}

void SensorView::notify(AbstractSensor& sensor) {
    bufferSize->setText("Buffer size: " + QString::number(sensor.getBufferSize()));
    SensorChartVisitor chartVisitor;
    sensor.accept(chartVisitor);

    delete content;
    content = chartVisitor.getWidget();
    main->addWidget(content);
}

}  // namespace View