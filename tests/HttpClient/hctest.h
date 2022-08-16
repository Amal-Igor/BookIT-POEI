/*
 * File: hctest.h
 * Project: HTTP Client Test | BookIT
 * File Created: Monday, 4th July 2022 9:03:11 AM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: HTTP Client Test header file for the testing the HTTP Client.
 * -----
 * Last Modified: Wednesday, 6th July 2022 10:36:20 AM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#ifndef HCTEST_H
#define HCTEST_H

#include <QJsonObject>
#include <QObject>
#include <QtTest>

#include "../../HttpClient/client.h"

class HCTest : public QObject {
    Q_OBJECT

   private:
    Client *mClient;

   private slots:
    
    //---------------Reservations--------------

    /**
     * @brief Tests the addReservation() function.
     */
    void addReservation();
    /**
     * @brief Tests the deleteReservation() function.
     */
    void deleteReservation();

    /**
     * @brief Tests the getAllReservations() function.
     */
    void getAllReservations();

    /**
     * @brief Tests the getReservation() function.
     */
    void getReservation();
    
    /**
     * @brief Tests the getUserReservations() function.
     */
    void getUserReservations();

    /**
     * @brief Tests the modifyReservation() function.
     */
    void modifyReservation();

    //------------------Routes-----------------

    /**
     * @brief Tests the addRoute() function.
     */
    void addRoute();

    /**
     * @brief Tests the getAllInfosOnRoute() function.
     */
    void getAllInfosOnRoute();

    /**
     * @brief Tests the getAllRoutes() function.
     */
    void getAllRoutes();

    /**
     * @brief Tests the getRoute() function.
     */
    void getRoute();

    /**
     * @brief Tests the getRoutesAtDepartTime() function.
     */
    void getRoutesAtDepartTime();

    /**
     * @brief Tests that the getRoutesBetweenAirports() function.
     */
    void getRoutesBetweenAirports();

    /**
     * @brief Tests the getRoutesForToday() function.
     */
    void getRoutesForToday();

    /**
     * @brief Tests the modifyRoute() function.
     */
    void modifyRoute();

    //-----------------Airport-----------------

    /**
     * @brief Tests getAllAirports() function with the expected results.
     */
    void getAllAirports();

    //------------------Users------------------

    /**
     * @brief Tests the addUser() function.
     */
    void addUser();

   public:
    /**
     * @brief Constructor, Creates a new Client object and stores it in the mClient member variable.
     *
     * @param parent The parent object of the client.
     */
    explicit HCTest(QObject *parent = nullptr);

    /**
     * @brief Destructor for the HCTest class.
     */
    ~HCTest();
};

#endif  // HCTEST_H
