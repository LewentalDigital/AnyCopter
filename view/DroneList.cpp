#include "DroneList.h"

#include <QBoxLayout>
#include <QScrollArea>
#include <vector>

#include "../model/Drone.h"
#include "../model/DroneManager.h"

namespace View {

DroneList::DroneList(DroneManager* dm, QWidget* parent) : QWidget(parent) {
    // mettere titleBar

    QBoxLayout* main = new QVBoxLayout(this);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* centralWidget = new QWidget(scrollArea);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    const std::vector<Drone*>& drones = dm->getDrones();
    for (std::vector<Drone*>::const_iterator it = drones.begin(); it != drones.end(); it++) {
        droneItems.push_back(new DroneListItem(*it));
        connect(droneItems[droneItems.size() - 1], &DroneListItem::manageDrone, this, &DroneList::manageDrone);
        layout->addWidget(droneItems[droneItems.size() - 1]);
    }

    centralWidget->setLayout(layout);
    scrollArea->setWidget(centralWidget);
    main->addWidget(scrollArea);
}

}  // namespace View