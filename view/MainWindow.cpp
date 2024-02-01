#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

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
    QMenu* view = menuBar()->addMenu("&View");

    connect(close, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::close() {
    QApplication::quit();
}