/*
 * File: main.cpp
 * Project: HTTP Client | BookIT
 * File Created: Thursday, 30th June 2022 4:25:32 PM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: 
 * -----
 * Last Modified: Wednesday, 6th July 2022 10:38:28 AM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#include <QCoreApplication>

#include "client.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

//     Client client;


    // qDebug() << "Get All Reservations\n"
    //          << client.getAllReservations();  // IF

    // qDebug().noquote() << "\nGet User 3 Reservations\n"
    //                    << client.getUserReservations(3);

    // qDebug().noquote() << "\nGet Reservation, ID = 1\n"
    //                    << client.getReservation(1);

    // qDebug().noquote() << "\nGet All Routes\n"
    //                    << client.getAllRoutes();

    // qDebug().noquote() << "\nGet Route, ID = 2\n"
    //                    << client.getAllInfosOnRoute(2);

    // qDebug().noquote() << "\nGet All Airports\n"
    //                    << client.getAllAirports();

    // qDebug().noquote() << "\nAdd User\n"
    //                    << client.addUser("Lexis", "Cooke", "lex123@gmail.com", "0429876543", QDate::fromString("19920406", "yyyyMMdd"));

    // qDebug().noquote() << "\nAdd Reservation\n"
    //                    << client.addReservation(0, 2502.5, "23A", 1, 2, QDateTime::currentDateTime());

    // qDebug().noquote() << "\nAdd Route\n"
    //                    << client.addRoute(35, QDateTime::fromString("20220709070500", "yyyyMMddhhmmss"), QDateTime::fromString("20220710044500", "yyyyMMddhhmmss"), "NTE", "ACC");

    // qDebug().noquote() << "\nGet All Routes to Heathrow Airport\n"
    //                    << client.getRoutesToAirport("LHR");



//     qDebug().noquote() << "\nGet All Routes to Heathrow Airport\n";
  //   qDebug()  <<    client.getRoutesBetweenAirports("ZBF","XXG", QDateTime::fromString("2023-03-26T05:16:22", "yyyy-MM-ddThh:mm:ss"));

    // qDebug().noquote() << "\nDelete Reservation, ID = 16\n"
    //                    << client.deleteReservation(16);

    // qDebug().noquote() << "\nModifty Reservation, ID = 4\n"
    //                    << client.modifyReservation(4, 0, 2.5, "23A", 1, 2, QDateTime::currentDateTime());

    // qDebug().noquote() << "\nModify Route, ID = 2\n"
    //                    << client.modifyRoute(2, 40, QDateTime::fromString("20220709073500", "yyyyMMddhhmmss"), QDateTime::fromString("20220709080000", "yyyyMMddhhmmss"), "CDG", "NCE");

    // qDebug().noquote() << "\nGet All Routes Departing at\n"
    //                    << client.getRoutesAtDepartTime(QDateTime::fromString("20220709073500", "yyyyMMddhhmmss"));

    // qDebug().noquote() << "\nGet All Routes for the Day\n"
    //                    << client.getRoutesForToday();

    return a.exec();
}
