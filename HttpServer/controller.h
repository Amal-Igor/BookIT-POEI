#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QHttpServer>
#include "dbutil.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QRandomGenerator>
#include "tools.h"


class Controller
{
public:
    Controller(DbUtil* db);


    /**
     * @brief getAllReservations
     * @return QJsonDocument containing QJsonArray corresponding to registration made on the app stored in DB.
     */
    QJsonObject getAllReservations();

    /**
     * @brief getReservationsFromUserX
     * @param user_id ID of user X
     * @return QJsonDocument containing QJsonArray corresponding to registration made by user X.
     */
    QJsonObject getAllReservationsFromUserX(int user_id);

    /**
     * @brief getReservationX
     * @param reservation_id ID of reservation X
     * @return Return a QJsonObject containing all data from a specific reservations
     */
    QJsonObject getReservationX(int reservation_id);

    /**
     * @brief getAllRoutes
     * @return QJsonDocument containing QJsonArray corresponding to every flights every made by the agency.
     */
    QJsonObject getAllRoutes();

    /**
     * @brief getAllCurrentRoutes
     * @return QJsonDocument containing QJsonArray corresponding to every flights from the current day.
     */
    QJsonObject getAllCurrentRoutes();

    /**
     * @brief getInfosOnRoutesX Retrieve infos from a specified reservation
     * @param route_id
     * @return Return a QJsonObject containing all data from a specific reservations
     */
    QJsonObject getInfosOnRoutesX(int route_id);


    /**
     * @brief getAllInfosOnRoutesX This method allow a user to get all data from a specified route, such as info on travel, number of seats, number of reservations
     * @param route_id  The id from the route we want to know
     * @return  a QJson Object contains every informations with keys flights_infos containing "total_seats" per plane, "reservations", "routes_infos"
     */
    QJsonObject getAllInfosOnRoutesX(int route_id);

    /**
     * @brief getAllAirports Retrieve every airports registred in the database
     * @return Return QJsonDocument containing QJsonArray corresponding to every flights from the current day
     */
    QJsonObject getAllAirports();


    /**
     * @brief getFlightsBetweenAirports Allow to search for flights between two airport given a certain date
     * @param departure_time Time desired to traval, should be to ISO8601 standard = "2015-05-17T05:16:22"
     * @param departure_airport
     * @param arrival_airport
     * @return  Return QJsonObject containing every data that comply to specified criterias
     */
    QJsonObject getFlightsBetweenAirports(QString departure_time, QString departure_airport, QString arrival_airport);


    /**
     * @brief addReservation Allow the client to add a reservation to database
     * @param body Contains the body request
     */
    QJsonObject addReservation(QByteArray body);


    /**
     * @brief addRoute Allow a company to add a new flight
     * @param body
     */
    QJsonObject addRoute(QByteArray body);


    /**
     * @brief addUser This function permit to add a customer to database
     * @param body Contains the body of the request
     */
    QJsonObject addUser(QByteArray body);


    /**
     * @brief deleteReservation This function permit to delete a reservation in database
     * @param body Contains the body of the request ie reservation_id
     */
    QJsonObject deleteReservation(int reservation_id);



    /**
     * @brief modifyRoute Allow a user to modify data about a specified route
     * @param body  Should contain every informations that a user want to update in DB
     * @return  QJsonObject containing the data["status"] with value true if the SQL query has been executed
     */
    QJsonObject modifyRoute(QByteArray body);

    /**
     * @brief modifyReservation Allow a user to modify data about a specified reservation
     * @param body  Should contain every informations that a user want to update in DB
     * @param reservation_id Correspond to a specific route ID
     * @return  QJsonObject containing the data["status"] with value true if the SQL query has been executed
     */
    QJsonObject modifyReservation(QByteArray body);


    /**
     * @brief modifyUserInfos Allow a user to modify data about a specified user
     * @param body  Should contain every informations that a user want to update in DB
     * @param user_id Correspond to a specific route ID
     * @return  QJsonObject containing the data["status"] with value true if the SQL query has been executed
     */
    QJsonObject modifyUserInfos(QByteArray body);

    /**
     * @brief getAllRoutesDerpartTime Permit to get flight given a specific datetime format ISO86
     * @param routes_to_search QJsonObject with departure_airport and arrival airport
     * @param departure_time    Date to check
     * @return QJsonObject containg every flights complying to specified date
     */
    QJsonObject getAllRoutesDerpartTime(QJsonObject routes_to_search, QString departure_time);


    /**
     * @brief addRandomRoutes Allow a manager to add random routes in databse for testing
     * @param _nb_routes    The number of routes you want to add
     * @return true if Query is welle executed
     */
    bool addRandomRoutes(int _nb_routes);





    void resetJsonDocArr();
    const QSqlDatabase &db() const;
    void setDb(const QSqlDatabase &newDb);

private:
   int request_params;
   DbUtil* mDbInfo;
   QSqlDatabase mDb;
   QJsonDocument mResponse;
   QJsonArray mArrResponse;
   QRandomGenerator genRandom;
   Tools t;


};

#endif // CONTROLLER_H
