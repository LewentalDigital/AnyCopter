#include "DroneDeployView.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QString>
#include <QtCharts>
#include <QVBoxLayout>

namespace View {

DroneDeployView::DroneDeployView(QWidget* parent) : QWidget(parent) {
    // DeployDroneView Forse????

    QVBoxLayout* main = new QVBoxLayout(this);

    // Title bar del panello
    QWidget* titleBarContainer = new QWidget();
    titleBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBarContainer->setLayout(titleBar);
    QPushButton* btnClose = new QPushButton(QIcon(QPixmap(":/assets/icons/close.svg")), "Cancel");
    btnClose->setShortcut(QKeySequence::Back);
    QLabel* title = new QLabel(QString::fromStdString("Deploy new Drone"));
    titleBar->addWidget(btnClose);
    titleBar->addStretch();
    titleBar->addWidget(title);
    titleBar->addStretch();

    connect(btnClose, &QPushButton::clicked, this, &DroneDeployView::close);

    // Contenuto del panello
    QWidget* centralWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);

    QWidget* droneInsertContainer = new QWidget();
    layout->addWidget(droneInsertContainer);
    QHBoxLayout* droneInsert = new QHBoxLayout(droneInsertContainer);
    droneInsertContainer->setLayout(droneInsert);
    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    droneInsert->addWidget(image);

    // Input testuali del drone disposte verticalmente
    QWidget* droneInsertTextContainer = new QWidget();
    droneInsertTextContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    droneInsert->addWidget(droneInsertTextContainer);
    QVBoxLayout* droneInsertText = new QVBoxLayout(droneInsertTextContainer);
    droneInsertTextContainer->setLayout(droneInsertText);

    QLabel* nameLabel = new QLabel("&Name", this);
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Insert name");
    nameInput->setMaxLength(32);

    nameLabel->setBuddy(nameInput);
    QLabel* integratedSensors = new QLabel(QString::fromStdString("Integrated sensors: Thermometer for CPU, Battery charge sensor, Altimeter, GPS"));

    droneInsertText->addWidget(nameLabel);
    droneInsertText->addWidget(nameInput);
    droneInsertText->addWidget(integratedSensors);

    QLabel* sensorsLabel = new QLabel("External sensors:");
    layout->addWidget(sensorsLabel);

    QPushButton* btnDeploy = new QPushButton(QIcon(QPixmap(":/assets/icons/deploy.png")), "Deploy");
    btnDeploy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Return));

    connect(btnDeploy, &QPushButton::clicked, this, &DroneDeployView::handleDeploy);

    QLineSeries* series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    auto chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple Line Chart");
    auto chartView = new QChartView(chart);

    main->addWidget(titleBarContainer);
    main->addWidget(centralWidget);
    main->addWidget(btnDeploy);
    main->addWidget(chartView);
}
void DroneDeployView::handleDeploy() {
    Drone* d = new Drone(nameInput->text().toStdString());
    emit deploy(d);
    close();
}

void DroneDeployView::close() {
    delete this;
}

}  // namespace View