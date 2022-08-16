#include <QCoreApplication>
#include <QFile>
#include <QHttpServer>
#include <QJsonObject>
#include <QJsonDocument>
#include "controller.h"
#include "dbutil.h"

QString jsonToQString(QJsonObject jsonOb)
{
    QJsonDocument doc(jsonOb);
   ;
    return  QString(doc.toJson(QJsonDocument::Compact));
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QJsonObject resURLs, routeURLs, airURLs, userURLs;

    int serverPort = 0;
    QString dbFilePath;

    QFile jsonFile("../configs/config.json");
    if (jsonFile.open(QFile::ReadOnly | QFile::Text))
    {
        QByteArray data = jsonFile.readAll();
        QJsonDocument documentJSON = QJsonDocument::fromJson(data);
        QJsonObject config = documentJSON.object();

        serverPort = config["PORT"].toInt();
        dbFilePath = config["DATABASE"].toString();
        resURLs = config["URLS"].toObject()["RESERVATIONS"].toObject();
        routeURLs = config["URLS"].toObject()["ROUTES"].toObject();
        airURLs = config["URLS"].toObject()["AIRPORTS"].toObject();
        userURLs = config["URLS"].toObject()["USERS"].toObject();

        jsonFile.close();
    }

    QHttpServer server;
    DbUtil db(dbFilePath, "BookIT");
    Controller *ctrl = new Controller(&db);


    //Function to add random routes in db
    //ctrl->addRandomRoutes(1000);
    /**
     * All routes about user and reservations
     **/
    server.route(resURLs["GET_ALL"].toString(), [&] (const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return ctrl->getAllReservations();
        }

    });

    server.route(resURLs["ADD"].toString(), [&] (const QHttpServerRequest &request){

        if(request.method() == QHttpServerRequest::Method::POST)
        {
            return ctrl->addReservation(request.body());
        }
    });

    server.route(userURLs["ADD"].toString(), [&] (const QHttpServerRequest &request){

        if(request.method() == QHttpServerRequest::Method::POST)
        {
            return ctrl->addUser(request.body());
        }
    });

    server.route(userURLs["MODIFY"].toString(), [&] (const QHttpServerRequest &request){

        if(request.method() == QHttpServerRequest::Method::PUT)
        {
            return ctrl->modifyUserInfos(request.body());
        }
    });


    server.route(resURLs["GET_USER_RES"].toString()+"<arg>", [&] (const int user_id, const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return ctrl->getAllReservationsFromUserX(user_id);
        }

    });


    // Route to get a specific reservation
    server.route(resURLs["GET"].toString()+"<arg>", [&] (const int reservation_id, const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
             // &request to get infos about a specific reservation.
            return ctrl->getReservationX(reservation_id);
        }
    });



    // Route to get a specific reservation
    server.route(resURLs["DELETE"].toString()+"<arg>", [&] (const int reservation_id, const QHttpServerRequest &request) {
        if(request.method() == QHttpServerRequest::Method::DELETE)
        {
            return ctrl->deleteReservation(reservation_id);
        }
    });
    // Route to get a specific reservation
    server.route(resURLs["MODIFY"].toString(), [&] (const QHttpServerRequest &request){

        if(request.method() == QHttpServerRequest::Method::PUT)
        {
            return ctrl->modifyReservation(request.body());
        }
    });

    /**
     * All routes concerning flights with various criterias
     **/
    // Routes to get all fly from DB and to add new one (for the bonus)
    server.route(routeURLs["GET_ALL"].toString(), [&] (const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return ctrl->getAllRoutes();
        }
    });

    server.route(routeURLs["GET_ALL_INFOS"].toString()+"<arg>", [&] (const int route_id, const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return ctrl->getAllInfosOnRoutesX(route_id);
        }
    });


    server.route(routeURLs["GET_FOR_DAY"].toString(), [&] (const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            // &request to get infos about a specific reservation.
            return ctrl->getAllCurrentRoutes();
        }
    });

    server.route(routeURLs["ADD"].toString(), [&] (const QHttpServerRequest &request){

        if(request.method() == QHttpServerRequest::Method::POST)
        {
            return ctrl->addRoute(request.body());
        }
    });

    server.route(routeURLs["MODIFY"].toString(), [&] (const QHttpServerRequest &request){

        if(request.method() == QHttpServerRequest::Method::PUT)
        {
            return ctrl->modifyRoute(request.body());
        }
    });

    //TODO faire une seule méthode pour récupérer les vols vers une destination avec le temps
//    server.route(routeURLs["GET_DEPART_TIME"].toString()+"<arg>", [&] (const QString departure_time, const QHttpServerRequest &request) {
//        if (request.method() == QHttpServerRequest::Method::GET)
//        {
//            return ctrl->getAllRoutesDerpartTime(departure_time);
//        }
//    });

    server.route(routeURLs["GET_BETWEEN_AIRPORT"].toString()+"<arg>/<arg>/<arg>", [&] (const QString departure_airport, const QString arrival_airport, const QString departure_time, const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return ctrl->getFlightsBetweenAirports(departure_time, departure_airport, arrival_airport);
        }
    });

    server.route(routeURLs["GET"].toString()+"<arg>", [&] (const int route_id, const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return ctrl->getInfosOnRoutesX(route_id);
        }
    });

    /**
     * Routes about aiport
     * */
    server.route(airURLs["GET_ALL"].toString(), [&] (const QHttpServerRequest &request) {
        if (request.method() == QHttpServerRequest::Method::GET)
        {
            return ctrl->getAllAirports();
        }
    });
    qDebug() << "Server is listening on port: " << server.listen(QHostAddress::Any,serverPort);

    return a.exec();
}
