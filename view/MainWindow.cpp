#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include "../model/Drone.h"
#include "DroneWidget.h"
#include "DroneView.h"

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

    QScrollArea* scrollArea = new QScrollArea(this);
    QWidget* centralWidget = new QWidget(scrollArea);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    scrollArea->setWidgetResizable(true);
    // scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    layout->addWidget(new DroneWidget(new Drone("Drone 1")));
    layout->addWidget(new DroneWidget(new Drone("Drone 2")));
    layout->addWidget(new DroneWidget(new Drone("Drone 3")));
    layout->addWidget(new DroneWidget(new Drone("Drone 4")));
    layout->addWidget(new DroneWidget(new Drone("Drone 5")));
    layout->addWidget(new DroneWidget(new Drone("Drone 6")));
    layout->addWidget(new DroneWidget(new Drone("Drone 7")));
    layout->addWidget(new DroneWidget(new Drone("Drone 8")));
    layout->addWidget(new DroneView(new Drone("Drone 8")));

    //QSTACKEDLAYOUT

    centralWidget->setLayout(layout);
    scrollArea->setWidget(centralWidget);
    setCentralWidget(scrollArea);
}

void MainWindow::close() {
    QApplication::quit();
}

}  // namespace View