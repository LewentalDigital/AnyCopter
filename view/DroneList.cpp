#include "DroneList.h"

#include <QScrollArea>
#include <QBoxLayout>

#include "../model/Drone.h"
#include "DroneListItem.h"

namespace View {

DroneList::DroneList(DroneManager* dm, QWidget* parent) : QWidget(parent) {
    QBoxLayout* main = new QVBoxLayout(this);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* centralWidget = new QWidget(scrollArea);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);


    layout->addWidget(new DroneListItem(new Drone("Drone 8")));
    layout->addWidget(new DroneListItem(new Drone("Drone 8")));
    layout->addWidget(new DroneListItem(new Drone("Drone 8")));
    layout->addWidget(new DroneListItem(new Drone("Drone 8")));
    layout->addWidget(new DroneListItem(new Drone("Drone 8")));
    layout->addWidget(new DroneListItem(new Drone("Drone 8")));

    centralWidget->setLayout(layout);
    scrollArea->setWidget(centralWidget);
    main->addWidget(scrollArea);
}

}  // namespace View