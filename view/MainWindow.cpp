#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "../model/Drone.h"
#include "DroneDeployView.h"
#include "DroneView.h"

namespace View {

MainWindow::MainWindow(DroneManager* dm) : droneManager(dm) {
    QAction* actionCreate = new QAction(
        "New");
    actionCreate->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    QAction* actionOpen = new QAction(
        "Open");
    actionOpen->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    QAction* actionSave = new QAction(
        "Save");
    actionSave->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    QAction* actionSaveAs = new QAction(
        "Save As");
    actionSaveAs->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

    QAction* actionClose = new QAction(
        "Close");
    actionClose->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    QAction* actionRefresh = new QAction(
        "Refresh");
    actionRefresh->setShortcuts(QList<QKeySequence>{QKeySequence(Qt::Key_F5), QKeySequence(Qt::CTRL | Qt::Key_R)});

    QAction* actionDeploy = new QAction(
        "Deploy new drone");
    actionDeploy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

    QAction* actionVewList = new QAction(
        "List of drones");
    actionVewList->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));

    QAction* actionGithub = new QAction(
        "Go to LewentalDigital GitHub page");
    //TODO

    // Sets menu bar
    QMenu* menuFile = menuBar()->addMenu("&File");
    menuFile->addAction(actionCreate);
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
    menuFile->addSeparator();
    menuFile->addAction(actionClose);
    QMenu* menuView = menuBar()->addMenu("&View");
    menuView->addAction(actionRefresh);
    menuView->addAction(actionVewList);
    QMenu* menuDrone = menuBar()->addMenu("&Drones");
    menuDrone->addAction(actionDeploy);
    QMenu* menuInfo = menuBar()->addMenu("&Info");
    menuInfo->addAction(actionGithub);

    connect(actionDeploy, &QAction::triggered, this, &MainWindow::openDeployDroneView);
    connect(actionClose, &QAction::triggered, this, &MainWindow::close);
    connect(actionRefresh, &QAction::triggered, this, &MainWindow::close);  // test

    droneList = new DroneList(dm, this);
    connect(droneList, &DroneList::manageDrone, this, &MainWindow::manageDrone);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(droneList);

    setCentralWidget(stackedWidget);
}

void MainWindow::close() {
    QApplication::quit();
}

void MainWindow::manageDrone(Drone* drone) {
    DroneView* dv = new DroneView(drone);
    stackedWidget->addWidget(dv);
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::openDeployDroneView() {
    DroneDeployView* ddv = new DroneDeployView();
    stackedWidget->addWidget(ddv);
    stackedWidget->setCurrentIndex(1);
    connect(ddv, &DroneDeployView::deploy, this, &MainWindow::deployNewDrone);
}

void MainWindow::deployNewDrone(Drone* drone) {
    droneManager->deployDrone(drone);
    droneList->addDrone(drone);
}

}  // namespace View