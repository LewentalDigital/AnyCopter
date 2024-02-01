#include <QApplication>
#include <QFile>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    // app.setWindowIcon(QIcon(":assets/icon.svg"));

    // QFile style(":/assets/style.qss");
    // style.open(QFile::ReadOnly);
    // app.setStyleSheet(QLatin1String(style.readAll()));

    // View::MainWindow window();
    // window.resize(1024, 576);
    // window.show();

    QLabel hello(" Hello world !");
    hello.show();

    return app.exec();
}
