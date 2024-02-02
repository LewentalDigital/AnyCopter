#include "MainWindow.h"

#include <QWidget>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

#include "DroneWidget.h"
// #include "../model/Drone.h"

MainWindow::MainWindow() {
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

    // Sets menu bar
    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(create);
    file->addAction(open);
    file->addAction(save);
    file->addAction(save_as);
    file->addSeparator();
    file->addAction(close);
    // QMenu* view = menuBar()->addMenu("&View");

    connect(close, &QAction::triggered, this, &MainWindow::close);


    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    layout->addWidget(new DroneWidget(new Drone("Drone 1")));
    layout->addWidget(new DroneWidget(new Drone("Drone 2")));
    layout->addWidget(new DroneWidget(new Drone("Drone 3")));

    // layout->addWidget(new DroneWidget());
    // layout->addWidget(new DroneWidget());
    // layout->addWidget(new DroneWidget());

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainWindow::close() {
    QApplication::quit();
}