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
#include "DroneList.h"
#include "DroneView.h"

namespace View {

MainWindow::MainWindow(DroneManager* dm) {
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

    // Sets menu bar
    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(actionCreate);
    file->addAction(actionOpen);
    file->addAction(actionSave);
    file->addAction(actionSaveAs);
    file->addSeparator();
    file->addAction(actionClose);
    QMenu* view = menuBar()->addMenu("&View");
    view->addAction(actionRefresh);
    view->addAction(actionVewList);
    QMenu* droneMenu = menuBar()->addMenu("&Drones");
    droneMenu->addAction(actionDeploy);

    connect(actionDeploy, &QAction::triggered, this, &MainWindow::deployNewDrone);
    connect(actionClose, &QAction::triggered, this, &MainWindow::close);
    connect(actionRefresh, &QAction::triggered, this, &MainWindow::close);  // test

    DroneList* droneList = new DroneList(dm, this);
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

void MainWindow::deployNewDrone() {
    DroneDeployView* ddv = new DroneDeployView();
    stackedWidget->addWidget(ddv);
    stackedWidget->setCurrentIndex(2);
}

}  // namespace View