#include "MainWindow.h"


MainWindow::MainWindow(DroneManager& dm) {

    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(create);
    file->addAction(open);
    file->addAction(save);
    file->addAction(save_as);
    file->addSeparator();
    file->addAction(close);
    QMenu* item_menu = menuBar()->addMenu("&Item");
    item_menu->addAction(create_item);
    QMenu* view = menuBar()->addMenu("&View");
    view->addAction(togge_toolbar);
}
