#include "controller.h"

Controller::Controller(DbUtil* db)
{
    mDb = db->db();
}

QJsonObject Controller::getAllReservations()
{
    resetJsonDocArr();
   // QSqlQuery query("SELECT Reservations.date_of_reservation, Reservations.reservation_id,  Reservations.seat_num, Users.user_id, Routes.route_id, Users.lastname, Users.firstname, Users.email, Routes.departure_airport, Routes.arrival_airport, Routes.departure_time FROM Reservations INNER JOIN Users ON Reservations.user_id = Users.user_id INNER JOIN Routes ON Reservations.route_id = Routes.route_id; ", mDb);

    QSqlQuery query("SELECT Reservations.date_of_reservation, Reservations.reservation_id,  Reservations.seat_num, Users.user_id, Routes.route_id, Users.lastname, Users.firstname, Users.email, Routes.departure_airport, Routes.arrival_airport, Routes.departure_time FROM Reservations INNER JOIN Users ON Reservations.user_id = Users.user_id INNER JOIN Routes ON Reservations.route_id = Routes.route_id", mDb);


    //QSqlQuery query("SELECT * FROM Reservations", mDb);
    QJsonObject recordObjects;
    while (query.next())
    {
       int nbCols = query.record().count();
       QJsonObject recordObject;
       for(int i=0; i< nbCols;i++)
       {
           recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
       }
       recordObjects.insert(QString::number(recordObject["reservation_id"].toInt()), recordObject);
    }
    qDebug() << recordObjects;
    return recordObjects;
}

QJsonObject Controller::getAllReservationsFromUserX(int user_id)
{
   resetJsonDocArr();
   QString buildQuery = "SELECT * FROM Reservations WHERE user_id=";

   buildQuery.append(QString::number(user_id));
   QSqlQuery query(buildQuery, mDb);
   QJsonObject recordObjects;
   while (query.next())
   {
      int nbCols = query.record().count();
      QJsonObject recordObject;
      for(int i=0; i< nbCols;i++)
      {
          recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
      }
      recordObjects.insert(QString::number(recordObject["reservation_id"].toInt()), recordObject);
   }
    qDebug() << query.exec();
   return recordObjects;
}

QJsonObject Controller::getReservationX(int reservation_id)
{
    QString buildQuery = "SELECT * FROM Reservations WHERE reservation_id=";
    buildQuery.append(QString::number(reservation_id));
    QSqlQuery query(buildQuery, mDb);
    QJsonObject recordObject;
    while (query.next())
    {
       int nbCols = query.record().count();
       for(int i=0; i< nbCols;i++)
       {
           recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
       }
    }
    return recordObject;
}

QJsonObject Controller::getAllRoutes()
{
    resetJsonDocArr();
    QSqlQuery query("SELECT * FROM Routes", mDb);
    QJsonObject recordObjects;
    while (query.next())
    {
       int nbCols = query.record().count();
       QJsonObject recordObject;
       for(int i=0; i< nbCols;i++)
       {
           recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
       }
       recordObjects.insert(QString("routes_%1").arg(recordObject["route_id"].toInt()), recordObject);
    }

    return recordObjects;
}

QJsonObject Controller::getAllCurrentRoutes()
{

    // Il faut penser à rajouter des vols qui seront >= à la date actuelle
    QString buildQuery = "SELECT * FROM Routes WHERE departure_time>=CURRENT_TIMESTAMP";
    QSqlQuery query(buildQuery, mDb);
    QJsonObject recordObjects;
    qDebug() << query.lastQuery();
    while (query.next())
    {
       int nbCols = query.record().count();
       QJsonObject recordObject;
       for(int i=0; i< nbCols;i++)
       {
           recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
       }
       recordObjects.insert(QString::number(recordObject["route_id"].toInt()), recordObject);
    }
    return recordObjects;
}


QJsonObject Controller::getAllRoutesDerpartTime(QJsonObject routes_to_search, QString departure_time)
{

    // Time format:: = "2015-05-17T05:16:22";
    QDateTime dateTimeFrom = QDateTime::fromString(departure_time, "yyyy-MM-ddThh:mm:ss");
    QString newStr = dateTimeFrom.toString("yyyy-mm-dd hh:mm:ss");
    QJsonObject results;
    QJsonObject tmp;
    QStringList keys = routes_to_search.keys();
    QJsonArray arr;
    foreach(QString key, keys)
    {
        arr.push_back(routes_to_search[key].toObject());

    }
    for(int i=0; i < arr.size(); i++)
    {

        QJsonObject obj2 = arr[i].toObject();
        QStringList keys2 = obj2.keys();

        foreach(QString key, keys2)
        {
            if(key == "departure_time")
            {
            QDateTime dateTimeFromJSON = QDateTime::fromString(obj2[key].toString(), "yyyy-MM-ddThh:mm:ss");
            qDebug() << dateTimeFromJSON;
                if(dateTimeFromJSON > dateTimeFrom)
                {

                    foreach(QString key, keys2)
                    {
                        tmp.insert(key, obj2[key]);
                    }
                    results.insert(QString::number(tmp["route_id"].toInt()), tmp);
                }
            }
        }
    }
    return results;
}

bool Controller::addRandomRoutes(int _nb_routes)
{
    QString buildQuery = "SELECT DISTINCT airport_code FROM Airports";
    QSqlQuery query(buildQuery, mDb);
    QJsonObject airport_Code;
    QJsonArray airport_arr;
    while (query.next())
    {
       int nbCols = query.record().count();

       for(int i=0; i< nbCols;i++)
           airport_Code.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));

       airport_arr.push_back(airport_Code);
    }
    QString departure_airport;
    QString arrival_airport;
     ;
    QDateTime _arrival_time, _randomdeparture;
    int randomDeparture =0, randomArrival=0, randomFlightid=0, randomDay=0, randomYear=0, randomMonth=0, randomHour=0, randomMinutes=0, randomTravelTime=0;
    for(int i =0; i < _nb_routes; i++)
    {

        randomDeparture= genRandom.bounded(0, airport_arr.size());
        randomArrival = genRandom.bounded(0, airport_arr.size());
        randomFlightid = genRandom.bounded(0, 44);

        randomYear = genRandom.bounded(2022, 2030);
        randomMonth = genRandom.bounded(0, 11);
        randomDay = genRandom.bounded(0, 28);

        randomHour = genRandom.bounded(0, 23);
        randomMinutes = genRandom.bounded(0, 59);

        randomTravelTime = genRandom.bounded(3600, 36000);

        departure_airport = airport_arr[randomDeparture].toObject()["airport_code"].toString();
        arrival_airport = airport_arr[randomArrival].toObject()["airport_code"].toString();

        if(randomDeparture != randomArrival)
        {
           _randomdeparture = t.generateRandomDateTime(randomYear, randomMonth, randomDay, randomHour, randomMinutes);
          _arrival_time = t.generateRandomDateTime(randomYear, randomMonth, randomDay, randomHour, randomMinutes);
          _arrival_time =_arrival_time.addSecs(randomTravelTime);

            if(t.verifyDateTimeValidity(_randomdeparture, _arrival_time))
            {
                buildQuery = QString("INSERT INTO Routes (departure_time, arrival_time, flight_id, departure_airport, arrival_airport) VALUES ('%1', '%2', %3, '%4', '%5')").arg(_randomdeparture.toString(Qt::ISODate)).arg(_arrival_time.toString(Qt::ISODate)).arg(randomFlightid).arg(departure_airport).arg(arrival_airport);
                query.prepare(buildQuery);
                query.exec();
            }
            else{
                i--;
            }
        }

    }
    return true;
}


QJsonObject Controller::getInfosOnRoutesX(int route_id)
{

    QString buildQuery = "SELECT * FROM Routes WHERE route_id = ";
    buildQuery.append(QString::number(route_id));
    QSqlQuery query(buildQuery, mDb);
    QJsonObject recordObject;
    while (query.next())
    {
       int nbCols = query.record().count();

       for(int i=0; i< nbCols;i++)
           recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
    }
    return recordObject;
}

QJsonObject Controller::getAllInfosOnRoutesX(int route_id)
{

    int avaible_seats = 0, total_seats = 0, reservations = 0;

    QString buildQuery = "SELECT * FROM Routes WHERE route_id = ";
    buildQuery.append(QString::number(route_id));
    QSqlQuery query(buildQuery, mDb);
    QJsonObject routeObject;
    QJsonObject recordObjects;

    while (query.next())
    {
       int nbCols = query.record().count();

       for(int i=0; i< nbCols;i++)
           routeObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
    }

    QJsonObject flightObject;
    buildQuery = "SELECT total_seats, nb_rows, nb_cols FROM Flights WHERE flight_id = "; //, nb_rows, nb_cols
    buildQuery.append(QString::number(routeObject["flight_id"].toInt()));
    query.exec(buildQuery);
    while (query.next())
    {
       int nbCols = query.record().count();

       for(int i=0; i< nbCols;i++)
           flightObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
    }
    total_seats = flightObject["total_seats"].toInt();
    recordObjects.insert("flight_infos", flightObject);

    //QJsonObject reservationsObject;
    QJsonObject reservationsObject2;
    buildQuery = "SELECT reservation_id, user_id, seat_num FROM Reservations WHERE route_id = ";
    buildQuery.append(QString::number(routeObject["route_id"].toInt()));
    query.exec(buildQuery);
    qDebug() << query.lastQuery();
    //int i = 0;
    while (query.next())
    {
       int nbCols = query.record().count();
       QJsonObject reservationObject;
       for(int i=0; i< nbCols;i++)
       {
           reservationObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));

        }
       reservationsObject2.insert(QString("reservation_%1").arg(reservationObject["reservation_id"].toInt()), reservationObject);
       recordObjects.insert("reservations", reservationsObject2);
    }
    qDebug() << reservationsObject2.size();
    routeObject.insert("avaible_seats", total_seats - reservationsObject2.size());
    recordObjects.insert("route_infos", routeObject);
    return recordObjects;
}

QJsonObject Controller::getAllAirports()
{
    QSqlQuery query("SELECT * FROM Airports", mDb);
    QJsonObject recordObjects;

    while (query.next())
    {
       int nbCols = query.record().count();
       QJsonObject recordObject;
       for(int i=0; i< nbCols;i++)
       {
           recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)) );
       }

       recordObjects.insert(QString::number(recordObject["airport_id"].toInt()), recordObject);

    }
    return recordObjects;
}

QJsonObject Controller::getFlightsBetweenAirports(QString departure_time, QString departure_airport, QString arrival_airport)
{
    qDebug() << "Request dep" << departure_airport;
    qDebug() << "Request arrv" << arrival_airport;
    QString buildQuery = QString("SELECT * FROM Routes WHERE departure_airport='%1' AND arrival_airport='%2'").arg(departure_airport).arg(arrival_airport);
    QSqlQuery query(buildQuery, mDb);
    QJsonObject recordObjects;
    qDebug()<< query.lastQuery();
    qDebug() << query.exec();
    while (query.next())
    {
       int nbCols = query.record().count();
       QJsonObject recordObject;
       for(int i=0; i< nbCols;i++)
       {
           recordObject.insert(query.record().fieldName(i), QJsonValue::fromVariant(query.value(i)));
       }
       recordObjects.insert(QString::number(recordObject["route_id"].toInt()), recordObject);
    }

    QJsonObject res = getAllRoutesDerpartTime(recordObjects,departure_time);

    return res;
}

QJsonObject Controller::addReservation(QByteArray body)
{
    QJsonObject data;

    if(body.isEmpty())
    {
      data["status"] = false;
    }
    QJsonDocument itemDoc = QJsonDocument::fromJson(body);
    QJsonObject rootObject = itemDoc.object();
    int user_id_from_DB;



    QString queryForID = "SELECT * FROM Users WHERE phone_number = ";
    queryForID.append(QString::number(rootObject["phone_number"].toInt()));
    QSqlQuery query2(queryForID, mDb);
    QJsonObject recordObject;
    while (query2.next())
    {
       int nbCols = query2.record().count();

       for(int i=0; i< nbCols;i++)
           recordObject.insert(query2.record().fieldName(i), QJsonValue::fromVariant(query2.value(i)));
    }

//    qDebug() << recordObject["user_id"].toInt();
    user_id_from_DB = recordObject["user_id"].toInt();
//    qDebug() << recordObject;
//    qDebug() << user_id_from_DB;
//    qDebug() << rootObject["phone_number"].toInt();

    QSqlQuery query(mDb);
    query.prepare("INSERT INTO Reservations (status, price, seat_num, route_id, user_id, date_of_reservation) VALUES (:status, :price, :seat_num, :route_id, :user_id, :date_of_reservation)");

    query.bindValue(":status",QString::number(rootObject["status"].toInt()));
    query.bindValue(":price",QString::number(rootObject["price"].toDouble()));
    query.bindValue(":seat_num",rootObject["seat_num"].toString());
    query.bindValue(":route_id",QString::number(rootObject["route_id"].toInt()));
    query.bindValue(":user_id", user_id_from_DB);
    query.bindValue(":date_of_reservation",rootObject["date_of_reservation"].toString());

    query.exec();
    data["status"] = (query.lastError().type() == QSqlError::NoError) ? true : false;

    qDebug() << "Add Reservation: " << data["status"];

    return data;
}

QJsonObject Controller::modifyRoute(QByteArray body)
{
    QJsonObject data;
    data["status"] = false;
    if(body.isEmpty())
    {
        return data;
    }


    QJsonDocument itemDoc = QJsonDocument::fromJson(body);
    QJsonObject rootObject = itemDoc.object();
    QStringList keys = rootObject.keys();
    QSqlQuery query(mDb);
    QString buildQuery;

    query.prepare("UPDATE Routes SET departure_time = :departure_time, arrival_time = :arrival_time, flight_id = :flight_id, departure_airport = :departure_airport, arrival_airport = :arrival_airport WHERE route_id = :route_id");

    query.bindValue(":departure_time",rootObject["departure_time"].toString());
    query.bindValue(":arrival_time",rootObject["arrival_time"].toString());
    query.bindValue(":flight_id",QString::number(rootObject["flight_id"].toInt()));
    query.bindValue(":departure_airport",rootObject["departure_airport"].toString());
    query.bindValue(":arrival_airport",rootObject["arrival_airport"].toString());
    query.bindValue(":route_id",QString::number(rootObject["route_id"].toInt()));

    query.exec();
    data["status"] = (query.lastError().type() == QSqlError::NoError) ? true : false;

    qDebug() << "Modify Route: " << data["status"];
    return data;
}

QJsonObject Controller::modifyReservation(QByteArray body)
{
    QJsonObject data;
    data["status"] = false;
    if(body.isEmpty())
    {
        return data;
    }


    QJsonDocument itemDoc = QJsonDocument::fromJson(body);
    QJsonObject rootObject = itemDoc.object();
    QStringList keys = rootObject.keys();
    QSqlQuery query(mDb);
    QString buildQuery;

    query.prepare("UPDATE Reservations SET status = :status, price = :price, seat_num = :seat_num, route_id = :route_id, user_id = :user_id, date_of_reservation = :date_of_reservation WHERE reservation_id = :reservation_id");

    query.bindValue(":status",QString::number(rootObject["status"].toInt()));
    query.bindValue(":price",QString::number(rootObject["price"].toDouble()));
    query.bindValue(":seat_num",rootObject["seat_num"].toString());
    query.bindValue(":route_id",QString::number(rootObject["route_id"].toInt()));
    query.bindValue(":user_id",QString::number(rootObject["user_id"].toInt()));
    query.bindValue(":date_of_reservation",rootObject["date_of_reservation"].toString());
    query.bindValue(":reservation_id",QString::number(rootObject["reservation_id"].toInt()));

    query.exec();
    data["status"] = (query.lastError().type() == QSqlError::NoError) ? true : false;

    qDebug() << "Modify Reservation: " << data["status"];
    return data;
}

QJsonObject Controller::modifyUserInfos(QByteArray body)
{

    QJsonObject data;
    data["status"] = false;
    if(body.isEmpty())
    {
        return data;
    }


    QJsonDocument itemDoc = QJsonDocument::fromJson(body);
    QJsonObject rootObject = itemDoc.object();
    QStringList keys = rootObject.keys();
    int user_id = rootObject["user_id"].toInt();
    QSqlQuery query(mDb);
    QString buildQuery;

    foreach(QString key, keys)
    {

        if(key == "user_id")
        {
            break;
        }

        if(rootObject[key].isString())
        {
            buildQuery = QString("UPDATE Users SET %1='%2' WHERE user_id=%3").arg(key).arg(rootObject.value(key).toString()).arg(user_id);;
            query.exec(buildQuery);
         }
        else if(!rootObject[key].isString())
        {
            if(key != "user_id")
            {
                buildQuery = QString("UPDATE Users SET %1=%2 WHERE user_id=%3").arg(key).arg(rootObject.value(key).toInt()).arg(user_id);;
                query.exec(buildQuery);
            }
        }

        qDebug() << query.lastQuery();
    }

    data["status"] = (query.lastError().type() == QSqlError::NoError) ? true : false;

    qDebug() << "Modify user Infos: " << data["status"];
    return data;

}

QJsonObject Controller::addRoute(QByteArray body)
{

    QJsonObject data;
    data["status"] = false;
    if(body.isEmpty())
    {
        return data;
    }

    QJsonDocument itemDoc = QJsonDocument::fromJson(body);
    QJsonObject rootObject = itemDoc.object();
    QSqlQuery query(mDb);
    query.prepare("INSERT INTO Routes (departure_time, arrival_time, flight_id, departure_airport, arrival_airport) VALUES (:departure_time, :arrival_time, :flight_id, :departure_airport, :arrival_airport)");

    query.bindValue(":departure_time",rootObject["departure_time"].toString());
    query.bindValue(":arrival_time",rootObject["arrival_time"].toString());
    query.bindValue(":flight_id",QString::number(rootObject["flight_id"].toInt()));
    query.bindValue(":departure_airport",rootObject["departure_airport"].toString());
    query.bindValue(":arrival_airport",rootObject["arrival_airport"].toString());

    query.exec();
    data["status"] = (query.lastError().type() == QSqlError::NoError) ? true : false;

    qDebug() << "Add Route: " << data["status"];

    return data;
}

QJsonObject Controller::addUser(QByteArray body)
{

    QJsonObject data;
    data["status"] = false;
    if(body.isEmpty())
    {
        return data;
    }
    QJsonDocument itemDoc = QJsonDocument::fromJson(body);
    QJsonObject rootObject = itemDoc.object();
    QSqlQuery query(mDb);
    query.prepare("INSERT INTO Users (firstname, lastname, email, phone_number, date_of_birth) VALUES (:firstname, :lastname, :email, :phone_number, :date_of_birth)");


    query.bindValue(":firstname",rootObject["firstname"].toString());
    query.bindValue(":lastname",rootObject["lastname"].toString());
    query.bindValue(":email",rootObject["email"].toString());
    query.bindValue(":phone_number",rootObject["phone_number"].toString());
    query.bindValue(":date_of_birth",rootObject["date_of_birth"].toString());

    query.exec();
    data["status"] = (query.lastError().type() == QSqlError::NoError) ? true : false;

    qDebug() << "Add User: " << data["status"];

    return data;
}

QJsonObject Controller::deleteReservation(int reservation_id)
{
    QJsonObject data;
    data["status"] = false;

    QString buildQuery = "DELETE FROM Reservations WHERE reservation_id = ";
    buildQuery.append(QString::number(reservation_id));
    QSqlQuery query(buildQuery, mDb);
    query.exec();
    data["status"] = (query.lastError().type() == QSqlError::NoError) ? true : false;

    qDebug() << "Delete User: " << data["status"];

    return data;
}

void Controller::resetJsonDocArr()
{
    mArrResponse = QJsonArray();
    mResponse = QJsonDocument();
}

const QSqlDatabase &Controller::db() const
{
    return mDb;
}

void Controller::setDb(const QSqlDatabase &newDb)
{
    mDb = newDb;
}
