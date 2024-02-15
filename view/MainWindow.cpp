#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDesktopServices>
#include <QErrorMessage>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "../model/Drone.h"
#include "DroneDeployView.h"
#include "DroneView.h"

namespace View {

MainWindow::MainWindow(DroneManager& dm) : droneManager(dm), persistenceManager(dm) {
    QAction* actionOpen = new QAction("Load Config");
    actionOpen->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    QAction* actionSaveAs = new QAction("Save Config As");
    actionSaveAs->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

    QAction* actionQuit = new QAction("Quit");
    actionQuit->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    QAction* actionRefresh = new QAction("Refresh");
    actionRefresh->setShortcuts(QList<QKeySequence>{QKeySequence(Qt::Key_F5), QKeySequence(Qt::CTRL | Qt::Key_R)});

    QAction* actionSearch = new QAction("Search");
    actionSearch->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_F));

    QAction* actionDeploy = new QAction("New drone");
    actionDeploy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    QAction* actionDroneList = new QAction("List of drones");
    actionDroneList->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));

    QAction* actionGithub = new QAction("Visit LewentalDigital GitHub page");

    // Set menu bar
    QMenu* menuFile = menuBar()->addMenu("&File");
    menuFile->addAction(actionDeploy);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSaveAs);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    QMenu* menuView = menuBar()->addMenu("&View");
    menuView->addAction(actionDroneList);
    menuView->addAction(actionSearch);
    menuView->addSeparator();
    menuView->addAction(actionRefresh);

    QMenu* menuInfo = menuBar()->addMenu("&Info");
    menuInfo->addAction(actionGithub);

    connect(actionDeploy, &QAction::triggered, this, &MainWindow::openDeployDroneView);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(actionSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(actionQuit, &QAction::triggered, this, &MainWindow::quit);
    connect(actionSearch, &QAction::triggered, this, &MainWindow::openSearch);
    connect(actionRefresh, &QAction::triggered, this, &MainWindow::refresh);
    connect(actionGithub, &QAction::triggered, this, &MainWindow::visitGithub);

    droneList = new DroneList(dm.getDrones(), this);
    connect(droneList, &DroneList::manageDrone, this, &MainWindow::manageDrone);

    loadConfig(QString::fromStdString(PersistenceManager::defaultSaveFile));

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(droneList);

    setCentralWidget(stackedWidget);
}

void MainWindow::loadConfig(const QString& configFile) {
    try {
        persistenceManager.load(configFile.toStdString());
        for (Drone* drone : droneManager.getDrones())
            droneList->addDrone(drone);
        droneList->reload(droneManager.getDrones());
    } catch (std::string errorMsg) {
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage("Error in configuration file " + configFile + ": \n" + QString::fromStdString(errorMsg));
    }
}

void MainWindow::open() {
    QString filename = QFileDialog::getOpenFileName(this, "Open Configuration", "", "CSV files (*.csv)");
    if (filename != "") {
        int result = QMessageBox::question(this, "Confirm config overwrite", "Loading new configuration will overwirte the current. Load configuration from " + filename + "?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (result == QMessageBox::Yes) {
            loadConfig(filename);
        }
    }
}

void MainWindow::save() {
    persistenceManager.save(PersistenceManager::defaultSaveFile);
}

void MainWindow::saveAs() {
    QString filename = QFileDialog::getSaveFileName(this, "Save Configuration As", "", "CSV files (*.csv)");
    if (filename != "")
        persistenceManager.save(filename.toStdString());
}

void MainWindow::refresh() {  // make every observer update
    const std::vector<Drone*>& drones = droneManager.getDrones();
    for (auto drone = drones.begin(); drone != drones.end(); ++drone) {
        (*drone)->readHardware();
        const std::vector<AbstractSensor*>& sensors = (*drone)->getMountedSensors();
        for (auto sensor = sensors.begin(); sensor != sensors.end(); ++sensor) {
            (*sensor)->read();
        }
    }
}

void MainWindow::quit() {
    QApplication::quit();
    save();
}

void MainWindow::visitGithub() {
    QDesktopServices::openUrl(QUrl("https://github.com/LewentalDigital/AnyCopter"));
}

void MainWindow::openSearch() {
    droneList->searchFocus();
}

void MainWindow::manageDrone(Drone* drone) {
    if (stackedWidget->currentIndex() > 0) {
        QWidget* prevWidget = stackedWidget->currentWidget();
        stackedWidget->removeWidget(prevWidget);
        delete prevWidget;
    }
    DroneView* dv = new DroneView(drone);
    stackedWidget->addWidget(dv);
    stackedWidget->setCurrentIndex(1);
    connect(dv, &DroneView::sensorRemoved, this, &MainWindow::save);
    connect(dv, &DroneView::sensorMounted, this, &MainWindow::save);
    connect(dv, &DroneView::sensorEdited, this, &MainWindow::save);
    connect(dv, &DroneView::deleteDrone, this, &MainWindow::deleteDrone);
}

void MainWindow::openDeployDroneView() {
    DroneDeployView* ddv = new DroneDeployView();
    if (stackedWidget->currentIndex() > 0) {
        QWidget* prevWidget = stackedWidget->currentWidget();
        stackedWidget->removeWidget(prevWidget);
        delete prevWidget;
    }
    stackedWidget->addWidget(ddv);
    connect(ddv, &DroneDeployView::deploy, this, &MainWindow::deployNewDrone);
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::deployNewDrone(Drone* drone) {
    try {
        droneManager.deployDrone(drone);
        droneList->addDrone(drone);
        save();
        droneList->loadSearchList(droneManager.getDrones());
        droneList->resetSearch();
    } catch (std::string errorMsg) {
        QMessageBox::warning(this, "Error", QString::fromStdString(errorMsg));
    }
}

void MainWindow::deleteDrone(Drone* drone) {
    for (std::vector<Drone*>::const_iterator it = droneManager.getDrones().begin(); it != droneManager.getDrones().end(); ++it) {
        if ((*it) == drone) {
            droneManager.removeDrone(it);
            break;
        }
    }
    droneList->removeDrone(drone);
    save();
    droneList->loadSearchList(droneManager.getDrones());
}

}  // namespace View