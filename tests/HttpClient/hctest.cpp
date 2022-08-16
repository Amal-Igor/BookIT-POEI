/*
 * File: hctest.cpp
 * Project: HTTP Client Test | BookIT
 * File Created: Monday, 4th July 2022 9:05:15 AM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: HTTP Client Test class for the testing the HTTP Client.
 * -----
 * Last Modified: Wednesday, 6th July 2022 10:29:47 AM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#include "hctest.h"

/**
 * @brief Constructor, Creates a new Client object and stores it in the mClient member variable.
 *
 * @param parent The parent object of the client.
 */
HCTest::HCTest(QObject *parent) : QObject{parent} {
    mClient = new Client("../../configs/config.json");
}

//---------------Reservations--------------

/**
 * @brief Tests the addReservation() function.
 */
void HCTest::addReservation() {
    bool result = mClient->addReservation(0, 2502.5, "23A", 1, 2, QDateTime::currentDateTime());
    QCOMPARE(result, true);
}

/**
 * @brief Tests the deleteReservation() function.
 */
void HCTest::deleteReservation() {
    bool result = mClient->deleteReservation(4);
    QCOMPARE(result, true);
}

/**
 * @brief Tests the getAllReservations() function.
 */
void HCTest::getAllReservations() {
    QJsonObject expectedData, result;
    expectedData["reservation_id"] = 9;
    expectedData["status"] = 0;
    expectedData["price"] = 200;
    expectedData["seat_num"] = "06C";
    expectedData["route_id"] = 3;
    expectedData["user_id"] = 5;
    expectedData["date_of_reservation"] = "2022-07-09 12:45:11";

    result = mClient->getAllReservations()["9"].toObject();
    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the getReservation() function.
 */
void HCTest::getReservation() {
    QJsonObject expectedData, result;
    expectedData["reservation_id"] = 2;
    expectedData["status"] = 0;
    expectedData["price"] = 500.92;
    expectedData["seat_num"] = "30E";
    expectedData["route_id"] = 1;
    expectedData["user_id"] = 4;
    expectedData["date_of_reservation"] = "2022-07-13 23:05:14";

    result = mClient->getReservation(2);
    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the getUserReservations() function.
 */
void HCTest::getUserReservations() {
    QJsonObject expectedData, result;
    expectedData["reservation_id"] = 6;
    expectedData["status"] = 0;
    expectedData["price"] = 1300;
    expectedData["seat_num"] = "04D";
    expectedData["route_id"] = 2;
    expectedData["user_id"] = 2;
    expectedData["date_of_reservation"] = "2022-07-06 12:45:11";

    result = mClient->getUserReservations(2)["6"].toObject();
    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the modifyReservation() function.
 */
void HCTest::modifyReservation() {
    bool result = mClient->modifyReservation(2, 0, 2502.5, "23A", 1, 2, QDateTime::currentDateTime());
    QCOMPARE(result, true);
}

//------------------Routes-----------------

/**
 * @brief Tests the addRoute() function.
 */
void HCTest::addRoute() {
    bool result = mClient->addRoute(21, QDateTime::fromString("20220711070500", "yyyyMMddhhmmss"), QDateTime::fromString("20220712044500", "yyyyMMddhhmmss"), "AAL", "BRE");
    QCOMPARE(result, true);
}

/**
 * @brief Tests the getAllInfosOnRoute() function.
 */
void HCTest::getAllInfosOnRoute() {
    QJsonObject expectedData, result;
    expectedData["route_id"] = 2;
    expectedData["departure_time"] = "2022-07-09 07:35:00";
    expectedData["arrival_time"] = "2022-07-09 08:00:00";
    expectedData["avaible_seats"] = 421;
    expectedData["flight_id"] = 30;
    expectedData["departure_airport"] = "ZMH";
    expectedData["arrival_airport"] = "LAD";

    result = mClient->getAllInfosOnRoute(2)["route_infos"].toObject();
    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the getAllRoutes() function.
 */
void HCTest::getAllRoutes() {
    QJsonObject expectedData, result;
    expectedData["route_id"] = 3;
    expectedData["departure_time"] = "2022-07-09 18:35:00";
    expectedData["arrival_time"] = "2022-07-09 18:50:00";
    expectedData["flight_id"] = 2;
    expectedData["departure_airport"] = "ZMH";
    expectedData["arrival_airport"] = "LAD";

    result = mClient->getAllRoutes()["routes_3"].toObject();
    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the getRoute() function.
 */
void HCTest::getRoute() {
    QJsonObject expectedData, result;
    expectedData["route_id"] = 6;
    expectedData["departure_time"] = "2022-07-11 07:05:00";
    expectedData["arrival_time"] = "2022-07-12 04:45:00";
    expectedData["flight_id"] = 21;
    expectedData["departure_airport"] = "AAL";
    expectedData["arrival_airport"] = "BRE";

    result = mClient->getRoute(6);
    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the getRoutesAtDepartTime() function.
 */
void HCTest::getRoutesAtDepartTime() {
    QJsonObject expectedData, result;
    expectedData["route_id"] = 6;
    expectedData["departure_time"] = "2022-07-11 07:05:00";
    expectedData["arrival_time"] = "2022-07-12 04:45:00";
    expectedData["flight_id"] = 21;
    expectedData["departure_airport"] = "AAL";
    expectedData["arrival_airport"] = "BRE";

//    result = mClient->getRoutesAtDepartTime(QDateTime::fromString("20220709073500", "yyyyMMddhhmmss"))["6"].toObject();
//    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests that the getRoutesBetweenAirports() function.
 */
void HCTest::getRoutesBetweenAirports() {
    QJsonObject expectedData, result;
    expectedData["route_id"] = 3;
    expectedData["departure_time"] = "2022-07-09 18:35:00";
    expectedData["arrival_time"] = "2022-07-09 18:50:00";
    expectedData["flight_id"] = 2;
    expectedData["departure_airport"] = "ZMH";
    expectedData["arrival_airport"] = "LAD";

    result = mClient->getRoutesBetweenAirports("ZMH", "LAD", QDateTime::fromString("2022-07-09 18:15:00", "yyyy-MM-dd hh:mm:ss"))["3"].toObject();
    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the getRoutesForToday() function.
 */
void HCTest::getRoutesForToday() {
    //    QJsonObject expectedData, result;

    //    result = mClient->getRoutesForToday();
    //    QCOMPARE(result, expectedData);
}

/**
 * @brief Tests the modifyRoute() function.
 */
void HCTest::modifyRoute() {
    bool result = mClient->modifyRoute(2, 40, QDateTime::fromString("20220709073500", "yyyyMMddhhmmss"), QDateTime::fromString("20220709080000", "yyyyMMddhhmmss"), "ZMH", "NCE");
    QCOMPARE(result, true);
}

//-----------------Airport-----------------

/**
 * @brief Tests getAllAirports() function with the expected results.
 */
void HCTest::getAllAirports() {
    QJsonObject expectedData, result;
    expectedData["airport_id"] = 16;
    expectedData["airport_name"] = "Abau";
    expectedData["airport_code"] = "ABW";
    expectedData["country"] = "Papua New Guinea";
    expectedData["country_code"] = "PG";
    expectedData["city"] = "Abau";

    result = mClient->getAllAirports()["16"].toObject();
    QCOMPARE(result, expectedData);
}

//------------------Users------------------

/**
 * @brief Tests the addUser() function.
 */
void HCTest::addUser() {
    bool result = mClient->addUser("Lexis", "Cooke", "lex123@gmail.com", "0429876543", QDate::fromString("19920406", "yyyyMMdd"));
    QCOMPARE(result, true);
}

/**
 * @brief Destructor for the HCTest class.
 */
HCTest::~HCTest() {
    delete mClient;
}
