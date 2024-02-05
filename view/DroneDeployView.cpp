#include "DroneDeployView.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QLineEdit>

namespace View {

DroneDeployView::DroneDeployView(QWidget* parent) : QWidget(parent) {
    // DeployDroneView Forse????

    QVBoxLayout* main = new QVBoxLayout(this);

    // Title bar del panello
    QWidget* titleBarContainer = new QWidget();
    QHBoxLayout* titleBar = new QHBoxLayout(titleBarContainer);
    titleBarContainer->setLayout(titleBar);
    QPushButton* back = new QPushButton(QIcon(QPixmap(":/assets/icons/arrow-back.svg")), "");
    back->setShortcut(QKeySequence::Back);
    QLabel* title = new QLabel(QString::fromStdString("Deploy new Drone"));
    titleBar->addWidget(back);
    titleBar->addStretch();
    titleBar->addWidget(title);
    titleBar->addStretch();

    connect(back, &QPushButton::clicked, this, &DroneDeployView::back);

    // // Contenuto del panello
    // QWidget* centralWidget = new QWidget();
    // QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    // centralWidget->setLayout(layout);

    // QWidget* droneInsertContainer = new QWidget();
    // layout->addWidget(droneInsertContainer);
    // QHBoxLayout* droneInsert = new QHBoxLayout(droneInsertContainer);
    // droneInsertContainer->setLayout(droneInsert);
    // image = new QLabel();
    // image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // droneInsert->addWidget(image);

    // // Informazioni testuali del drone disposte verticalmente
    // QWidget* droneInsertTextContainer = new QWidget();
    // droneInsert->addWidget(droneInsertTextContainer);
    // QVBoxLayout* droneInsertText = new QVBoxLayout(droneInsertTextContainer);
    // droneInsertTextContainer->setLayout(droneInsertText);

    // QLabel* nameLabel = new QLabel("&Name", this);
    // QLineEdit* nameInput = new QLineEdit(this);
    // nameLabel->setBuddy(nameInput);
    // QLabel* integratedSensors = new QLabel(QString::fromStdString("Integrated sensors: Thermometer for CPU, Battery charge sensor, Altimeter, GPS"));

    // droneInsertText->addWidget(nameLabel);
    // droneInsertText->addWidget(nameInput);
    // droneInsertText->addWidget(integratedSensors);

    // QLabel* sensorsLabel = new QLabel("External sensors:");
    // layout->addWidget(sensorsLabel);

    main->addWidget(titleBarContainer);
    // main->addWidget(centralWidget);
}

void DroneDeployView::back() {
    delete this;
}

}  // namespace View