#include "DroneList.h"

#include <QBoxLayout>
#include <QScrollArea>
#include <QStringList>
#include <QStringListModel>
#include <vector>

#include "../model/Drone.h"
#include "../model/DroneManager.h"

namespace View {

DroneList::DroneList(const std::vector<Drone*>& drones, QWidget* parent) : QWidget(parent) {
    QBoxLayout* main = new QVBoxLayout(this);

    // Title bar
    QHBoxLayout* titleBar = new QHBoxLayout();
    titleBar->setContentsMargins(0, 0, 0, 0);

    QPushButton* back = new QPushButton(QIcon(QPixmap(":/assets/icons/arrow-back.svg")), "Back");
    back->setShortcut(QKeySequence::Back);
    QLabel* title = new QLabel("Drones");
    title->setObjectName("title");

    titleBar->addWidget(back);
    titleBar->addStretch();
    titleBar->addWidget(title);
    titleBar->addStretch();

    // completer for drone names and sensors so it will suggest searches
    completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);

    // Search bar
    QHBoxLayout* searchBar = new QHBoxLayout();
    searchBar->setContentsMargins(0, 0, 0, 0);
    
    searchInput = new QLineEdit();
    searchInput->setCompleter(completer);
    searchInput->setPlaceholderText("Search for drones or sensors");
    searchInput->setMaxLength(32);
    QPushButton* btnSearch = new QPushButton(QIcon(QPixmap(":/assets/icons/search.svg")), "Search");
    QPushButton* btnReset = new QPushButton("Reset");

    searchBar->addWidget(searchInput);
    searchBar->addWidget(btnSearch);
    searchBar->addWidget(btnReset);

    connect(searchInput, &QLineEdit::returnPressed, this, &DroneList::search);
    connect(btnSearch, &QPushButton::clicked, this, &DroneList::search);
    connect(btnReset, &QPushButton::clicked, this, &DroneList::resetSearch);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* contentContainer = new QWidget(scrollArea);
    scrollArea->setWidget(contentContainer);
    content = new QVBoxLayout(contentContainer);
    contentContainer->setLayout(content);
    content->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    loadDroneItems(drones);
    loadSearchList(drones);

    main->addLayout(titleBar);
    main->addLayout(searchBar);
    main->addWidget(scrollArea);
}

DroneList::~DroneList() {
    for (DroneListItem* item : droneItems)
        delete item;
}

void DroneList::loadDroneItems(const std::vector<Drone*>& drones) {
    for (std::vector<Drone*>::const_iterator it = drones.begin(); it != drones.end(); ++it)
        addDrone(*it);
}

void DroneList::loadSearchList(const std::vector<Drone*>& drones) {
    QStringList searchList;
    for (std::vector<Drone*>::const_iterator drone = drones.begin(); drone != drones.end(); ++drone) {
        searchList << QString::fromStdString((*drone)->getName());
        std::vector<AbstractSensor*> sensors = (*drone)->getMountedSensors();
        for (std::vector<AbstractSensor*>::const_iterator sensor = sensors.begin(); sensor != sensors.end(); ++sensor) {
            if (!searchList.contains(QString::fromStdString((*sensor)->getId()))) {
                searchList << QString::fromStdString((*sensor)->getId());
            }
        }
    }
    completer->setModel(new QStringListModel(searchList));
}

void DroneList::addDrone(Drone* d) {
    DroneListItem* item = new DroneListItem(d);
    item->setObjectName("DroneListItem");
    droneItems.push_back(item);
    connect(droneItems.back(), &DroneListItem::manageDrone, this, &DroneList::manageDrone);
    content->addWidget(droneItems.back());
}

void DroneList::removeDrone(Drone* d) {
    for (auto it = droneItems.begin(); it != droneItems.end(); ++it) {
        if (&(*it)->getDrone() == d) {
            content->removeWidget(*it);
            delete *it;
            droneItems.erase(it);
            break;
        }
    }
}

void DroneList::searchFocus() {
    searchInput->setFocus();
}

void DroneList::search() {
    QString query = searchInput->text().simplified().replace( " ", "" );

    for (DroneListItem* item : droneItems) {
        bool matchSensor = false;
        for (AbstractSensor* sensor : item->getDrone().getMountedSensors()) {
            if (QString::fromStdString(sensor->getId()).contains(query, Qt::CaseInsensitive)) {
                matchSensor = true;
                break;
            }
        }
        if (QString::fromStdString((item->getDrone()).getName()).contains(query, Qt::CaseInsensitive) || matchSensor)
            item->show();
        else
            item->hide();
    }
}

void DroneList::resetSearch() {
    searchInput->clear();
    search();
}

void DroneList::reload(const std::vector<Drone*>& drones) {
    for (DroneListItem* item : droneItems) {
        content->removeWidget(item);
        delete item;
    }
    droneItems.clear();
    loadDroneItems(drones);
    loadSearchList(drones);
}

}  // namespace View