#include "DroneList.h"

#include <QBoxLayout>
#include <vector>

#include "../model/Drone.h"
#include "../model/DroneManager.h"

namespace View {

DroneList::DroneList(DroneManager* dm, QWidget* parent) : QWidget(parent) {
    // mettere titleBar

    QBoxLayout* main = new QVBoxLayout(this);
    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* centralWidget = new QWidget(scrollArea);
    content = new QVBoxLayout(centralWidget);
    content->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    const std::vector<Drone*>& drones = dm->getDrones();
    for (std::vector<Drone*>::const_iterator it = drones.begin(); it != drones.end(); it++) {
        droneItems.push_back(new DroneListItem(*it));
        connect(droneItems[droneItems.size() - 1], &DroneListItem::manageDrone, this, &DroneList::manageDrone);
        content->addWidget(droneItems[droneItems.size() - 1]);
    }

    centralWidget->setLayout(content);
    scrollArea->setWidget(centralWidget);
    main->addWidget(scrollArea);
}

void DroneList::addDrone(Drone* d) {
    droneItems.push_back(new DroneListItem(d));
    connect(droneItems.back(), &DroneListItem::manageDrone, this, &DroneList::manageDrone);
    content->addWidget(droneItems.back());
    // scrollArea->ensureWidgetVisible(droneItems.back()); // non funziona :(
}

DroneList::~DroneList() {
    for (DroneListItem* item : droneItems) {
        delete item;
    }
}

}  // namespace View