#include "DroneDeployView.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QtCharts>
#include <QVBoxLayout>

namespace View {

DroneDeployView::DroneDeployView(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* main = new QVBoxLayout(this);

    // Panel title bar 
    QHBoxLayout* titleBar = new QHBoxLayout();
    titleBar->setContentsMargins(0, 0, 0, 0);
    QPushButton* btnClose = new QPushButton(QIcon(QPixmap(":/assets/icons/close.svg")), "Cancel");
    btnClose->setShortcut(QKeySequence::Back);
    QLabel* title = new QLabel(QString::fromStdString("<strong>Deploy new Drone</strong>"));
    title->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    title->setObjectName("title");
    titleBar->addWidget(btnClose);
    titleBar->addStretch();
    titleBar->addWidget(title);
    titleBar->addStretch();

    connect(btnClose, &QPushButton::clicked, this, &DroneDeployView::close);

    // Panel content
    QVBoxLayout* content = new QVBoxLayout();


    QHBoxLayout* droneInsert = new QHBoxLayout();
    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/agriDrone.png").scaledToHeight(200, Qt::SmoothTransformation));
    // Input testuali del drone disposte verticalmente
    QVBoxLayout* droneInsertText = new QVBoxLayout();
    droneInsert->addWidget(image);
    droneInsert->addLayout(droneInsertText);

    QLabel* nameLabel = new QLabel("&Name", this);
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Insert name");
    nameInput->setMaxLength(32);
    nameLabel->setBuddy(nameInput);
    QLabel* integratedSensors = new QLabel(QString::fromStdString("Integrated sensors: Thermometer for CPU, Battery charge sensor"));
    integratedSensors->setWordWrap(true);

    droneInsertText->addWidget(nameLabel);
    droneInsertText->addWidget(nameInput);
    droneInsertText->addWidget(integratedSensors);

    QLabel* sensorsLabel = new QLabel("Sensors can be added later from the drone management panel.");

    QPushButton* btnDeploy = new QPushButton(QIcon(QPixmap(":/assets/icons/deploy.svg")), "Deploy");
    btnDeploy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Return));

    connect(btnDeploy, &QPushButton::clicked, this, &DroneDeployView::handleDeploy);

    content->addLayout(droneInsert);
    content->addWidget(sensorsLabel);

    main->addLayout(titleBar);
    main->addLayout(content);
    main->addWidget(btnDeploy);
}

void DroneDeployView::handleDeploy() {
    if (nameInput->text().toStdString().empty()) {
        QMessageBox::warning(this, "Input error", "Drone name cannot be empty!");
    } else {
        Drone* d = new Drone(nameInput->text().toStdString());
        emit deploy(d);
        close();
    }
}

void DroneDeployView::close() {
    delete this;
}

}  // namespace View