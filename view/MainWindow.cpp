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

MainWindow::MainWindow(DroneManager* dm) : droneManager(dm), persistenceManager(dm->getDrones()) {
    QAction* actionCreate = new QAction("New");
    actionCreate->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    QAction* actionOpen = new QAction("Open Configuration");
    actionOpen->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    QAction* actionSave = new QAction("Save Configuration");
    actionSave->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    QAction* actionSaveAs = new QAction("Save Configuration As");
    actionSaveAs->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

    QAction* actionQuit = new QAction("Quit");
    actionQuit->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    QAction* actionRefresh = new QAction("Refresh");
    actionRefresh->setShortcuts(QList<QKeySequence>{QKeySequence(Qt::Key_F5), QKeySequence(Qt::CTRL | Qt::Key_R)});

    QAction* actionDeploy = new QAction("Deploy new drone");
    actionDeploy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

    QAction* actionVewList = new QAction("List of drones");
    actionVewList->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));

    QAction* actionGithub = new QAction("Visit LewentalDigital GitHub page");

    // Set menu bar
    QMenu* menuFile = menuBar()->addMenu("&File");
    menuFile->addAction(actionCreate);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    QMenu* menuView = menuBar()->addMenu("&View");
    menuView->addAction(actionRefresh);
    menuView->addAction(actionVewList);
    QMenu* menuDrone = menuBar()->addMenu("&Drones");
    menuDrone->addAction(actionDeploy);
    QMenu* menuInfo = menuBar()->addMenu("&Info");
    menuInfo->addAction(actionGithub);

    connect(actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(actionRefresh, &QAction::triggered, this, &MainWindow::refresh);
    connect(actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(actionSaveAs, &QAction::triggered, this, &MainWindow::saveAs);
    connect(actionQuit, &QAction::triggered, this, &MainWindow::quit);
    connect(actionDeploy, &QAction::triggered, this, &MainWindow::openDeployDroneView);
    connect(actionGithub, &QAction::triggered, this, &MainWindow::visitGithub);

    droneList = new DroneList(dm, this);
    connect(droneList, &DroneList::manageDrone, this, &MainWindow::manageDrone);

    loadConfig("savefile.csv");

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(droneList);

    setCentralWidget(stackedWidget);
}

void MainWindow::loadConfig(const QString& configFile) {
    try {
        persistenceManager.load(configFile.toStdString(), *droneManager);
        for (Drone* drone : droneManager->getDrones())
            droneList->addDrone(drone);
    } catch (std::string errorMsg) {
        QErrorMessage* error = new QErrorMessage(this);
        error->showMessage("Error in configuration file " + configFile + ": \n" + QString::fromStdString(errorMsg));
    }
}

void MainWindow::open() {
    QString filename = QFileDialog::getOpenFileName(this, "Open Configuration", "", "CSV files (*.csv)");
    // if (filename != "") {
    persistenceManager.load(filename.toStdString(), *droneManager);
    // droneList->refresh();
    // }
}

void MainWindow::save() {
    persistenceManager.save("savefile.csv");
}

void MainWindow::saveAs() {
    QString filename = QFileDialog::getSaveFileName(this, "Save Configuration As", "", "CSV files (*.csv)");
    // if (filename != "") {
    persistenceManager.save(filename.toStdString());
    // }
}

void MainWindow::refresh() {  // make every observer update
    const std::vector<Drone*>& drones = droneManager->getDrones();
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
}

void MainWindow::visitGithub() {
    QDesktopServices::openUrl(QUrl("https://github.com/LewentalDigital/AnyCopter"));
}

void MainWindow::manageDrone(Drone* drone) {
    DroneView* dv = new DroneView(drone);
    if (stackedWidget->currentIndex() > 0) {
        QWidget* prevWidget = stackedWidget->currentWidget();
        stackedWidget->removeWidget(prevWidget);
        delete prevWidget;
    }
    stackedWidget->addWidget(dv);
    stackedWidget->setCurrentIndex(1);
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
        droneManager->deployDrone(drone);
        droneList->addDrone(drone);
    } catch (std::string errorMsg) {
        QMessageBox::warning(this, "Error", QString::fromStdString(errorMsg));
    }
}

}  // namespace View