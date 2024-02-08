#include "DroneList.h"

#include <QBoxLayout>
#include <vector>

#include "../model/Drone.h"
#include "../model/DroneManager.h"

namespace View {

DroneList::DroneList(DroneManager* dm, QWidget* parent) : QWidget(parent) {
    QBoxLayout* main = new QVBoxLayout(this);

    // Panel title bar
    QWidget* titleBarContainer = new QWidget();
    titleBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBarContainer->setLayout(titleBar);
    // QPushButton* back = new QPushButton(QIcon(QPixmap(":/assets/icons/arrow-back.svg")), "Back");
    // back->setShortcut(QKeySequence::Back);
    QLabel* title = new QLabel("Drones");
    // titleBar->addWidget(back);
    titleBar->addStretch();
    titleBar->addWidget(title);
    titleBar->addStretch();

    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* contentContainer = new QWidget(scrollArea);
    scrollArea->setWidget(contentContainer);
    content = new QVBoxLayout(contentContainer);
    contentContainer->setLayout(content);
    content->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    const std::vector<Drone*>& drones = dm->getDrones();
    for (std::vector<Drone*>::const_iterator it = drones.begin(); it != drones.end(); it++) {
        droneItems.push_back(new DroneListItem(*it));
        connect(droneItems[droneItems.size() - 1], &DroneListItem::manageDrone, this, &DroneList::manageDrone);
        content->addWidget(droneItems[droneItems.size() - 1]);
    }

    main->addWidget(titleBarContainer);
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