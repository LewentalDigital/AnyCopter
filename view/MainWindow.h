#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow();

   public slots:
    void close();
};

#endif