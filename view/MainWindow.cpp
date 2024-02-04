#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "../model/Drone.h"
#include "DroneList.h"

namespace View {

MainWindow::MainWindow(DroneManager* dm) {
    QAction* create = new QAction(
        "New");
    create->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));

    QAction* open = new QAction(
        "Open");
    open->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));

    QAction* save = new QAction(
        "Save");
    save->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    QAction* save_as = new QAction(
        "Save As");
    save_as->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));

    QAction* close = new QAction(
        "Close");
    close->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    QAction* refresh = new QAction(
        "Refresh");
    refresh->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    // refresh->setShortcut(QKeyEvent(Qt::Key_F5));

    QAction* deploy = new QAction(
        "Deploy new drone");
    deploy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));

    // Sets menu bar
    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(create);
    file->addAction(open);
    file->addAction(save);
    file->addAction(save_as);
    file->addSeparator();
    file->addAction(close);
    QMenu* view = menuBar()->addMenu("&View");
    view->addAction(refresh);
    QMenu* droneMenu = menuBar()->addMenu("&Drones");
    droneMenu->addAction(deploy);

    connect(close, &QAction::triggered, this, &MainWindow::close);

    // QSTACKEDLAYOUT

    DroneList* droneList = new DroneList(dm, this);
    setCentralWidget(droneList);
}

void MainWindow::close() {
    QApplication::quit();
}

}  // namespace View