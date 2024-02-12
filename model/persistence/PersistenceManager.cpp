#include "PersistenceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../Drone.h"
#include "SensorSaveVisitor.h"

PersistenceManager::PersistenceManager(const std::vector<Drone *> &drones) : drones(drones) {
}

void PersistenceManager::save(const std::string &filename) {
    const std::string separator = ",";
    std::ofstream f(filename, std::ios_base::app);

    if (f.is_open()) {
        for (auto d = drones.begin(); d != drones.end(); ++d) {
            f << (*d)->getName() << separator;
            for (auto s = (*d)->getMountedSensors().begin(); s != (*d)->getMountedSensors().end(); ++s) {
                SensorSaveVisitor visitor;
                (*s)->accept(visitor);
                f << visitor.getId() << separator
                  << (*s)->getBufferSize() << separator
                  << (*s)->getReadings().size();
            }
            f << std::endl;
        }
    } else {
        throw std::runtime_error("Error opening the file");
    }
}

// void ReservationList::createResLayout() {
//     ReservationManagement rm = readFromFile("reservations.txt", p);
//     std::vector<Reservation> reservations = rm.getReservations();

//     int row = 0;

//     for (const auto &reservation : reservations) {
//         QLabel *filmLabel = new QLabel(this);
//         QString filmTitle = QString::fromStdString(reservation.getFilmTitle());
//         QFontMetrics fontMetrics(filmLabel->font());
//         QString elidedFilmTitle = fontMetrics.elidedText(filmTitle, Qt::ElideRight, 150);
//         filmLabel->setText(elidedFilmTitle);

//         QLabel *dataLabel = new QLabel(QString::fromStdString(Programming::createStringFromTm(reservation.getDateTime(), "%d/%m/%Y %H:%M")));
//         QLabel *hallIdLabel = new QLabel(QString("Hall %1").arg(reservation.getHallId()));
//         QLabel *priceLabel = new QLabel(QString("Price: %1").arg(reservation.getTotalPrice()));
//         QPushButton *infoSeats = new QPushButton("Info");
//         infoSeats->setStyleSheet("background-color: transparent; color: black; border: none; text-decoration: underline;");
//         infoSeats->setCursor(Qt::PointingHandCursor);
//         QPushButton *deleteRes = new QPushButton("Delete");
//         deleteRes->setFixedSize(90, 25);

//         Reservation reservationCopy = reservation;

//         QObject::connect(deleteRes, &QPushButton::clicked, [this, reservationCopy]() { deleteAndRefresh(reservationCopy); });
//         QObject::connect(infoSeats, &QPushButton::clicked, [this, reservationCopy]() { openSeatsInfo(reservationCopy.getReservedSeats()); });

//         resLayout->addWidget(filmLabel, row, 0);
//         resLayout->addWidget(dataLabel, row, 1);
//         resLayout->addWidget(hallIdLabel, row, 2);
//         resLayout->addWidget(priceLabel, row, 3);
//         resLayout->addWidget(infoSeats, row, 4);
//         resLayout->addWidget(deleteRes, row, 5);

//         QFrame *separator = new QFrame();
//         separator->setFrameShape(QFrame::HLine);
//         separator->setFrameShadow(QFrame::Sunken);
//         separator->setLineWidth(1);
//         separator->setMidLineWidth(0);
//         separator->setStyleSheet("background-color: #D0D0D0;");
//         resLayout->addWidget(separator, row + 1, 0, 1, 6);

//         row += 2;
//     }
// }
// void ReservationList::deleteAndRefresh(const Reservation &reservation) {
//     deleteResFromFile("reservations.txt", reservation, p);
//     refresh();
// }
// void ReservationList::refresh() {
//     QLayoutItem *item;
//     while ((item = resLayout->takeAt(0)) != nullptr) {
//         QWidget *widget = item->widget();
//         resLayout->removeWidget(widget);
//         delete widget;
//         delete item;
//     }
//     createResLayout();
// }
// void ReservationList::openSeatsInfo(const std::vector<const FullPriceSeat *> &seats) {
//     QDialog dialog(this);
//     dialog.setWindowTitle("Seats Info");
//     dialog.setFixedSize(340, 250);

//     QScrollArea *scrollArea = new QScrollArea(&dialog);
//     scrollArea->setWidgetResizable(true);

//     QWidget *contentWidget = new QWidget(scrollArea);
//     QVBoxLayout *layout = new QVBoxLayout(contentWidget);

//     SeatsInfoWidget *seatsInfoWidget = new SeatsInfoWidget(seats, contentWidget);
//     layout->addWidget(seatsInfoWidget);

//     scrollArea->setWidget(contentWidget);

//     QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
//     mainLayout->addWidget(scrollArea);
//     QPushButton *closeButton = new QPushButton("Close");
//     QObject::connect(closeButton, &QPushButton::clicked, &dialog, &QDialog::close);
//     mainLayout->addWidget(closeButton);
//     dialog.setLayout(mainLayout);
//     dialog.resize(300, 200);
//     dialog.exec();
// }
// ReservationManagement ReservationList::readFromFile(const std::string &fn, const Programming &p) {
//     ReservationManagement rm;
//     char DEL = '|';
//     std::ifstream f(fn, std::ios_base::app);
//     std::string line;

//     if (!f.is_open()) {
//         throw std::runtime_error("Error opening the file");
//     }

//     if (f.peek() == std::ifstream::traits_type::eof()) {
//         f.close();
//         return rm;
//     }

//     while (getline(f, line)) {
//         std::string reservationIdString, hallIdString, totalPriceString, filmTitle, dateString;
//         std::istringstream iss(line);
//         getline(iss, reservationIdString, DEL);
//         getline(iss, filmTitle, DEL);
//         getline(iss, hallIdString, DEL);
//         getline(iss, dateString, DEL);
//         int reservationId = stoi(reservationIdString);
//         unsigned int hallId = stoul(hallIdString);
//         tm dateTm = Programming::createTmFromString(dateString, "%d/%m/%Y %H:%M");

//         std::string rowString, columnString;
//         std::vector<const FullPriceSeat *> reservedSeats;
//         std::vector<Hall> halls = p.getHalls();
//         while (getline(iss, rowString, DEL) && getline(iss, columnString, DEL)) {
//             int row = stoi(rowString), column = stoi(columnString);

//             for (const auto &hall : halls) {
//                 if (hall.getId() == hallId) {
//                     const FullPriceSeat *fps = dynamic_cast<const FullPriceSeat *>(hall.getSeat(row, column));
//                     if (fps) {
//                         reservedSeats.push_back(fps);
//                     }
//                 }
//             }
//         }
//         Reservation reservation(reservationId, hallId, reservedSeats, dateTm, filmTitle);
//         rm.addReservation(reservation);
//     }
//     f.close();
//     return rm;
// }

// void ReservationList::deleteResFromFile(const std::string &fn, const Reservation &r, const Programming &p) {
//     ReservationManagement rm = readFromFile(fn, p);
//     rm.removeReservation(r);
//     std::vector<Reservation> reservations = rm.getReservations();

//     std::ofstream file(fn);
//     if (file) {
//         for (const Reservation &res : reservations) {
//             saveResToFile(fn, res);
//         }
//         file.close();
//     } else {
//         throw std::runtime_error("Error opening the file");
//     }
// }
