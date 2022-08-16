/*
 * File: client.h
 * Project: HTTP Client | BookIT
 * File Created: Thursday, 30th June 2022 4:31:05 PM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: HTTP Client header file for the various API request for airline
 *        seat reservation platform
 * -----
 * Last Modified:  Wednesday, 6th July 2022 9:53:43 AM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QEventLoop>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>

class Client : public QObject {
    Q_OBJECT

   private:
    QNetworkAccessManager *mManager;
    QString mServerURL;
    QJsonObject mResURLs, mRouteURLs, mAirURLs, mUserURLs;

   private:
    /**
     * @brief Takes a URL as a parameter, makes a GET request to that URL,
     *        and returns the JSON response as a QJsonObject
     *
     * @param _url  URL to send the request to.
     *
     * @return QJsonObject
     */
    QJsonObject processRequest(QString _url);

    /**
     * @brief Takes a URL, an HTTP method, and a JSON object, and returns a
     *        boolean indicating whether the request was successful.
     *
     * @param _url      URL of the request.
     * @param _opt      HTTP method to use.
     * @param _data     Data to be sent to the server.
     *
     * @return Boolean
     */
    bool processRequest(QString _url, QString _opt, QJsonObject _data);

   public:
    /**
     * @brief The constructor, it creates a new QNetworkAccessManager object and assigns it to the mManager member
     *        as well as set the mServerURL variable.
     *
     * @param _configFilePath   Path to the JSON file that contains the URLs, server's IP and port.
     * @param _parent           Parent object of the client.
     */
    explicit Client(QString _configFilePath = "../configs/config.json", QObject *_parent = nullptr);

    //---------------Reservations--------------

    /**
     * @brief Sends a POST request to the server with the data of the reservation to be added.
     *
     * @param _status   Status of the reservation (e.g. "0-Booked", "1-Cancelled", "2-Modified").
     * @param _price    Price of the ticket.
     * @param _seat     Seat number.
     * @param _routeID  ID of the route that the user wants to reserve.
     * @param _userID   User's ID.
     * @param _tor      Date of reservation.
     *
     * @return Boolean
     */
    bool addReservation(int _status, double _price, QString _seat, int _routeID, int _userID, QDateTime _tor);

    /**
     * @brief Sends a DELETE request to the server to delete a reservation with the given ID.
     *
     * @param _reserveID    ID of the reservation to delete.
     *
     * @return Boolean
     */
    bool deleteReservation(int _reserveID);

    /**
     * @brief Sends a GET request to the server to get all the reservations.
     *
     * @return QJsonObject
     */
    QJsonObject getAllReservations();

    /**
     * @brief Sends a GET request to the server to get a specific reservation.
     *
     * @param _reserveID    ID of the reservation you want to get.
     *
     * @return QJsonObject
     */
    QJsonObject getReservation(int _reserveID);

    /**
     * @brief Sends a GET request to the server to get all reservations of a user.
     *
     * @param _userID   ID of the user whose reservations you want to get.
     *
     * @return QJsonObject
     */
    QJsonObject getUserReservations(int _userID);

    /**
     * @brief Sends a PUT request to the server to modify an existing reservation.
     *
     * @param _reserveID    ID of the reservation to be modified.
     * @param _status       Status of the reservation (e.g. "0-Booked", "1-Cancelled", "2-Modified").
     * @param _price        Price of the reservation.
     * @param _seat         Seat number.
     * @param _routeID      ID of the route that the reservation is for.
     * @param _userID       ID of the user who made the reservation.
     * @param _tor          Timestamp of reservation.
     *
     * @return Boolean
     */
    bool modifyReservation(int _reserveID, int _status, double _price, QString _seat, int _routeID, int _userID, QDateTime _tor);

    //------------------Routes-----------------

    /**
     * @brief Takes in the parameters and then it sends a POST request to the server to add a route.
     *
     * @param _flightID             ID of the aircraft that will be used for this route.
     * @param _departTime           Time the plane departs.
     * @param _arrivalTime          Arrival time of the flight.
     * @param _departAirport        Airport code where the flight is departing from.
     * @param _arrivalAirport       Airport code where the flight will arrive at.
     *
     * @return Boolean
     */
    bool addRoute(int _flightID, QDateTime _departTime, QDateTime _arrivalTime, QString _departAirport, QString _arrivalAirport);

    /**
     * @brief Get all the information about a route.
     *
     * @param _routeID Route ID you want to get the infos on.
     *
     * @return QJsonObject
     */
    QJsonObject getAllInfosOnRoute(int _routeID);

    /**
     * @brief Sends a GET request to the server to get all the routes.
     *
     * @return QJsonObject
     */
    QJsonObject getAllRoutes();

    /**
     * @brief Sends a GET request to the server to get a specific route.
     *
     * @param _routeID  ID of the route you want to get.
     *
     * @return QJsonObject
     */
    QJsonObject getRoute(int _routeID);

    /**
     * @brief Sends a GET request to the server to get the routes at a given departure time.
     *
     * @param _timestamp    Timestamp of the departure time of the route.
     *
     * @return QJsonObject
     */
    QJsonObject getRoutesAtDepartTime(QDateTime _timestamp);

    /**
     * @brief Takes two airport codes as parameters, and returns a JSON object
     *        containing all the routes between those two airports
     *
     * @param _departAirport    ICAO code of the departure airport.
     * @param _arrivalAirport   IATA code of the arrival airport.
     * @param _departTime       Time the plane departs.
     *
     * @return QJsonObject
     */

    QJsonObject getRoutesBetweenAirports(QString _departAirport, QString _arrivalAirport, QDateTime _departTime);


    /**
     * @brief Sends a GET request to the server to get all the routes for today.
     *
     * @return QJsonObject
     */
    QJsonObject getRoutesForToday();

    /**
     * @brief Sends a GET request to the server to get the routes to a specific airport.
     *
     * @param _arrivalAirport     Airport code you want to get the routes to.
     *
     * @return QJsonObject
     */
    QJsonObject getRoutesToAirport(QString _arrivalAirport);

    /**
     * @brief Takes in a bunch of parameters and sends a PUT request to the server to modify a route.
     *
     * @param _routeID              ID of the route to modify.
     * @param _flightID             ID of the aircraft that will be used for the route.
     * @param _departTime           Time the plane departs.
     * @param _arrivalTime          Arrival time of the flight.
     * @param _departAirport        Airport code where the flight is departing from.
     * @param _arrivalAirport       Airport code where the flight will arrive at.
     *
     * @return Boolean
     */
    bool modifyRoute(int _routeID, int _flightID, QDateTime _departTime, QDateTime _arrivalTime, QString _departAirport, QString _arrivalAirport);

    //-----------------Airport-----------------

    /**
     * @brief Sends a GET request to the server to get all the airports.
     *
     * @return QJsonObject
     */
    QJsonObject getAllAirports();

    //------------------Users------------------

    /**
     * @brief It takes in a bunch of user information, converts it to a JSON object, and
     *        sends a POST request to the server.
     *
     * @param _fName    First name of the user.
     * @param _lName    Last name of the user.
     * @param _email    Email of the user to be added.
     * @param _number   Phone number.
     * @param _dob      Date of birth.
     *
     * @return Boolean
     */
    bool addUser(QString _fName, QString _lName, QString _email, QString _number, QDate _dob);

    /**
     * @brief Destructor for the Client class, Deletes the mManager Variable.
     */
    ~Client();
};

#endif  // CLIENT_H
