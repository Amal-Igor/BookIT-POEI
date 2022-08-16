/*
 * File: client.cpp
 * Project: HTTP Client | BookIT
 * File Created: Thursday, 30th June 2022 4:28:40 PM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: HTTP Client class for the various API request for airline seat
 *        reservation platform
 * -----
 * Last Modified: Wednesday, 6th July 2022 9:53:56 AM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#include "client.h"

/**
 * @brief Takes a URL as a parameter, makes a request to that URL,
 *        and returns the JSON response as a QJsonObject
 *
 * @param _url  URL to send the request to.
 *
 * @return QJsonObject
 */
QJsonObject Client::processRequest(QString _url) {
    QNetworkRequest request((QUrl(_url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = (mManager->get(request));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QJsonObject data{};

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        data = jsonDoc.object();
    } else {
        qDebug() << "Error:" << reply->errorString();
    }

    delete reply;
    return data;
}

/**
 * @brief Takes a URL, an HTTP method, and a JSON object, and returns a
 *        boolean indicating whether the request was statusful.
 *
 * @param _url      URL of the request.
 * @param _opt      HTTP method to use.
 * @param _data     Data to be sent to the server.
 *
 * @return Boolean
 */
bool Client::processRequest(QString _url, QString _opt, QJsonObject _data) {
    QNetworkRequest request((QUrl(_url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply;
    if (_opt != "DELETE") {
        QJsonDocument jsonDoc(_data);
        QByteArray b = jsonDoc.toJson();

        if (_opt == "PUT")
            reply = mManager->put(request, b);
        else
            reply = mManager->post(request, b);
    } else
        reply = mManager->deleteResource(request);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    bool status = false;
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        status = jsonDoc.object()["status"].toBool();
    }
    delete reply;

    return status;
}

/**
 * @brief The constructor, it creates a new QNetworkAccessManager object and assigns it to the mManager member
 *        as well as set the mServerURL variable.
 *
 * @param _configFilePath   Path to the JSON file that contains the URLs, server's IP and port.
 * @param _parent           Parent object of the client.
 */
Client::Client(QString _configFilePath, QObject *_parent) : QObject{_parent} {
    mManager = new QNetworkAccessManager(this);

    QFile jsonFile(_configFilePath);
    if (jsonFile.open(QFile::ReadOnly | QFile::Text)) {
        QString data = jsonFile.readAll();

        QJsonDocument documentJSON = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject config = documentJSON.object();

        mServerURL = "http://" + config["IP"].toString() + ":" + QString::number(config["PORT"].toInt());

        mResURLs = config["URLS"].toObject()["RESERVATIONS"].toObject();
        mRouteURLs = config["URLS"].toObject()["ROUTES"].toObject();
        mAirURLs = config["URLS"].toObject()["AIRPORTS"].toObject();
        mUserURLs = config["URLS"].toObject()["USERS"].toObject();

        qDebug() << "Config Set: " << mServerURL;

        jsonFile.close();
    }
}

//---------------Reservations--------------

/**
 * @brief Sends a POST request to the server with the data of the reservation to be added.
 *
 * @param _status   Status of the reservation (e.g. "0-Booked", "1-Cancelled", "2-Modified").
 * @param _price    Price of the ticket.
 * @param _seat     Seat number.
 * @param _routeID  ID of the route that the user wants to reserve.
 * @param _userID   User's ID.
 * @param _tor      Timestamp of reservation.
 *
 * @return Boolean
 */
bool Client::addReservation(int _status, double _price, QString _seat, int _routeID, int _userID, QDateTime _tor) {
    QJsonObject data;

    data["status"] = _status;
    data["price"] = _price;
    data["seat_num"] = _seat;
    data["route_id"] = _routeID;
    data["phone_number"] = _userID; //changed to phone number
    data["date_of_reservation"] = _tor.toString("yyyy-MM-dd hh:mm:ss");

    QString url = mServerURL + mResURLs["ADD"].toString();

    return processRequest(url, "POST", data);
}

/**
 * @brief Sends a DELETE request to the server to delete a reservation with the given ID.
 *
 * @param _reserveID    ID of the reservation to delete.
 *
 * @return Boolean
 */
bool Client::deleteReservation(int _reserveID) {
    QString url = mServerURL + mResURLs["DELETE"].toString() + QString::number(_reserveID);

    return processRequest(url, "DELETE", {});
}

/**
 * @brief Sends a GET request to the server to get all the reservations.
 *
 * @return QJsonObject
 */
QJsonObject Client::getAllReservations() {
    QString url = mServerURL + mResURLs["GET_ALL"].toString();

    return processRequest(url);
}

/**
 * @brief Sends a GET request to the server to get a specific reservation.
 *
 * @param _reserveID    ID of the reservation you want to get.
 *
 * @return QJsonObject
 */
QJsonObject Client::getReservation(int _reserveID) {
    QString url = mServerURL + mResURLs["GET"].toString() + QString::number(_reserveID);

    return processRequest(url);
}

/**
 * @brief Sends a GET request to the server to get all reservations of a user.
 *
 * @param _userID   ID of the user whose reservations you want to get.
 *
 * @return QJsonObject
 */
QJsonObject Client::getUserReservations(int _userID) {
    QString url = mServerURL + mResURLs["GET_USER_RES"].toString() + QString::number(_userID);

    return processRequest(url);
}

/**
 * @brief Sends a PUT request to the server to modify an existing reservation.
 *
 * @param _reserveID    ID of the reservation to be modified.
 * @param _status       Status of the reservation (e.g. "0-Booked", "1-Cancelled", "2-Modified").
 * @param _price        Price of the reservation.
 * @param _seat         Seat number.
 * @param _routeID      ID of the route that the reservation is for.
 * @param _userID       ID of the user who made the reservation.
 * @param _tor          Date of reservation.
 *
 * @return Boolean
 */
bool Client::modifyReservation(int _reserveID, int _status, double _price, QString _seat, int _routeID, int _userID, QDateTime _tor) {
    QJsonObject data;
    data["reservation_id"] = _reserveID;
    data["status"] = _status;
    data["price"] = _price;
    data["seat_num"] = _seat;
    data["route_id"] = _routeID;
    data["user_id"] = _userID;
    data["date_of_reservation"] = _tor.toString("yyyy-MM-dd hh:mm:ss");

    QString url = mServerURL + mResURLs["MODIFY"].toString();

    return processRequest(url, "PUT", data);
}

//------------------Routes-----------------

/**
 * @brief Takes in the parameters and then it sends a POST request to the server to add a route.
 *
 * @param _flightID             ID of the aircraft that will be used for this route.
 * @param _departTime           Time the plane departs in the format YYYY-MM-DD HH:MM:00.
 * @param _arrivalTime          Arrival time of the flight in the format YYYY-MM-DD HH:MM:00.
 * @param _departAirport        Airport code where the flight is departing from.
 * @param _arrivalAirport       Airport code where the flight will arrive at.
 *
 * @return Boolean
 */
bool Client::addRoute(int _flightID, QDateTime _departTime, QDateTime _arrivalTime, QString _departAirport, QString _arrivalAirport) {
    QJsonObject data;
    data["departure_time"] = _departTime.toString("yyyy-MM-dd hh:mm:ss");
    data["arrival_time"] = _arrivalTime.toString("yyyy-MM-dd hh:mm:ss");
    data["flight_id"] = _flightID;
    data["departure_airport"] = _departAirport;
    data["arrival_airport"] = _arrivalAirport;

    QString url = mServerURL + mRouteURLs["ADD"].toString();

    return processRequest(url, "POST", data);
}

/**
 * @brief Get all the information about a route.
 *
 * @param _routeID Route ID you want to get the infos on.
 *
 * @return QJsonObject
 */
QJsonObject Client::getAllInfosOnRoute(int _routeID) {
    QString url = mServerURL + mRouteURLs["GET_ALL_INFOS"].toString() + QString::number(_routeID);

    return processRequest(url);
}

/**
 * @brief Sends a GET request to the server to get all the routes.
 *
 * @return QJsonObject
 */
QJsonObject Client::getAllRoutes() {
    QString url = mServerURL + mRouteURLs["GET_ALL"].toString();

    return processRequest(url);
}

/**
 * @brief Sends a GET request to the server to get a specific route.
 *
 * @param _routeID  ID of the route you want to get.
 *
 * @return QJsonObject
 */
QJsonObject Client::getRoute(int _routeID) {
    QString url = mServerURL + mRouteURLs["GET"].toString() + QString::number(_routeID);

    return processRequest(url);
}

/**
 * @brief Sends a GET request to the server to get the routes at a given departure time.
 *
 * @param _timestamp    Timestamp of the departure time of the route.
 *
 * @return QJsonObject
 */
QJsonObject Client::getRoutesAtDepartTime(QDateTime _timestamp) {
    QString url = mServerURL + mRouteURLs["GET_DEPART_TIME"].toString() + _timestamp.toString("yyyy-MM-dd hh:mm:ss");

    return processRequest(url);
}

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

QJsonObject Client::getRoutesBetweenAirports(QString _departAirport, QString _arrivalAirport, QDateTime _departTime)
{

    QString url = mServerURL + mRouteURLs["GET_BETWEEN_AIRPORT"].toString() + _departAirport + "/" + _arrivalAirport + "/" + _departTime.toString(Qt::ISODate);


    return processRequest(url);
}

/**
 * @brief Sends a GET request to the server to get all the routes for today.
 *
 * @return QJsonObject
 */
QJsonObject Client::getRoutesForToday() {
    QString url = mServerURL + mRouteURLs["GET_FOR_DAY"].toString();

    return processRequest(url);
}

/**
 * @brief Sends a GET request to the server to get the routes to a specific airport.
 *
 * @param _arrivalAirport     Airport code you want to get the routes to.
 *
 * @return QJsonObject
 */
QJsonObject Client::getRoutesToAirport(QString _arrivalAirport) {
    QString url = mServerURL + mRouteURLs["GET_TO_AIRPORT"].toString() + _arrivalAirport;

    return processRequest(url);
}

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
bool Client::modifyRoute(int _routeID, int _flightID, QDateTime _departTime, QDateTime _arrivalTime, QString _departAirport, QString _arrivalAirport) {
    QJsonObject data;
    data["route_id"] = _routeID;
    data["departure_time"] = _departTime.toString("yyyy-MM-dd hh:mm:ss");
    data["arrival_time"] = _arrivalTime.toString("yyyy-MM-dd hh:mm:ss");
    data["flight_id"] = _flightID;
    data["departure_airport"] = _departAirport;
    data["arrival_airport"] = _arrivalAirport;

    QString url = mServerURL + mRouteURLs["MODIFY"].toString();

    return processRequest(url, "PUT", data);
}

//-----------------Airport-----------------

/**
 * @brief Sends a GET request to the server to get all the airports.
 *
 * @return QJsonObject
 */
QJsonObject Client::getAllAirports() {
    QString url = mServerURL + mAirURLs["GET_ALL"].toString();

    return processRequest(url);
}

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
bool Client::addUser(QString _fName, QString _lName, QString _email, QString _number, QDate _dob) {
    QJsonObject data;
    data["firstname"] = _fName;
    data["lastname"] = _lName;
    data["email"] = _email;
    data["phone_number"] = _number;
    data["date_of_birth"] = _dob.toString("yyyyMMdd");

    QString url = mServerURL + mUserURLs["ADD"].toString();

    return processRequest(url, "POST", data);
}

/**
 * @brief Destructor for the Client class, Deletes the mManager Variable.
 */
Client::~Client() {
    delete mManager;
}
