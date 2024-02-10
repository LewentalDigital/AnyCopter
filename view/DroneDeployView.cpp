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

    // Panel content
    QWidget* contenContainer = new QWidget();
    QVBoxLayout* content = new QVBoxLayout(contenContainer);
    contenContainer->setLayout(content);

    QWidget* droneInsertContainer = new QWidget();
    content->addWidget(droneInsertContainer);
    QHBoxLayout* droneInsert = new QHBoxLayout(droneInsertContainer);
    droneInsertContainer->setLayout(droneInsert);
    image = new QLabel();
    image->setPixmap(QPixmap(":assets/images/droneModels/3.png").scaledToHeight(200, Qt::SmoothTransformation));
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

    QLabel* integratedSensors = new QLabel(QString::fromStdString("Integrated sensors: Thermometer for CPU, Battery charge sensor"));
    integratedSensors->setWordWrap(true);

    droneInsertText->addWidget(nameLabel);
    droneInsertText->addWidget(nameInput);
    droneInsertText->addWidget(integratedSensors);

    QLabel* sensorsLabel = new QLabel("External sensors:");
    content->addWidget(sensorsLabel);

    QPushButton* btnDeploy = new QPushButton(QIcon(QPixmap(":/assets/icons/deploy.svg")), "Deploy");
    btnDeploy->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Return));

    connect(btnDeploy, &QPushButton::clicked, this, &DroneDeployView::handleDeploy);


    main->addWidget(titleBarContainer);
    main->addWidget(contenContainer);
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