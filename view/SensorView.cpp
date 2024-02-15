#include "SensorView.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "SensorChartVisitor.h"

namespace View {

SensorView::SensorView(AbstractSensor* sensor, QWidget* parent) : QWidget(parent), sensor(sensor) {
    SensorChartVisitor visitor;
    sensor->accept(visitor);
    content = visitor.getWidget();  // get custom chart from visitor of sensor chart
    chart = visitor.getChart();     // get chart from visitor so i can update it later

    main = new QVBoxLayout();
    main->setContentsMargins(0, 0, 0, 0);
    setLayout(main);

    QWidget* titleBarContainer = new QWidget();
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBar->setContentsMargins(0, 0, 0, 0);
    titleBarContainer->setLayout(titleBar);
    bufferSize = new QLabel("Buffer size: " + QString::number(sensor->getBufferSize()));
    btnEdit = new QPushButton(QIcon(QPixmap(":/assets/icons/edit.svg")), "Edit");
    btnRemove = new QPushButton(QIcon(QPixmap(":/assets/icons/remove.svg")), "Remove");
    titleBar->addWidget(visitor.getTitle());
    titleBar->addStretch();
    titleBar->addWidget(bufferSize);
    titleBar->addWidget(btnEdit);
    titleBar->addWidget(btnRemove);

    connect(btnEdit, &QPushButton::clicked, this, &SensorView::edit);
    connect(btnRemove, &QPushButton::clicked, this, &SensorView::remove);

    main->addWidget(titleBarContainer);
    main->addWidget(content);

    sensor->registerObserver(this);
}

SensorView::~SensorView() {
    sensor->unregisterObserver(this);  // if this view gets deleted it should unregister from the observer list
}

void SensorView::notify(AbstractSensor& sensor) {
    bufferSize->setText("Buffer size: " + QString::number(sensor.getBufferSize()));
    SensorChartVisitor visitor;
    sensor.accept(visitor);
    chart = visitor.getChart();

    delete content;
    content = visitor.getWidget();
    main->addWidget(content);
}

}  // namespace View