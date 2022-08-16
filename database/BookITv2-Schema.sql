BEGIN TRANSACTION;
DROP TABLE IF EXISTS "Users";
CREATE TABLE IF NOT EXISTS "Users" (
	"user_id"	INTEGER NOT NULL,
	"firstname"	VARCHAR(30) NOT NULL,
	"lastname"	VARCHAR(50) NOT NULL,
	"email"	VARCHAR(100) NOT NULL UNIQUE,
	"phone_number"	INTEGER(15) NOT NULL UNIQUE,
	"date_of_birth"	INTEGER(8) NOT NULL,
	"password"	VARCHAR(255),
	"auth_level"	INTEGER(1) DEFAULT 1,
	PRIMARY KEY("user_id" AUTOINCREMENT)
);
DROP TABLE IF EXISTS "Airports";
CREATE TABLE IF NOT EXISTS "Airports" (
	"airport_id"	INTEGER NOT NULL,
	"airport_name"	VARCHAR(50) NOT NULL,
	"airport_code"	VARCHAR(3) NOT NULL UNIQUE,
	"country"	VARCHAR(100) NOT NULL,
	"country_code"	VARCHAR(3) NOT NULL,
	"city"	VARCHAR(100) NOT NULL,
	PRIMARY KEY("airport_id" AUTOINCREMENT)
);
DROP TABLE IF EXISTS "Flights";
CREATE TABLE IF NOT EXISTS "Flights" (
	"flight_id"	INTEGER NOT NULL,
	"manufacturer"	VARCHAR(100) NOT NULL,
	"model"	VARCHAR(100) NOT NULL,
	"total_seats"	INTEGER(10) NOT NULL,
	"nb_rows"	INTEGER(3),
	"nb_cols"	INTEGER(3),
	PRIMARY KEY("flight_id" AUTOINCREMENT)
);
DROP TABLE IF EXISTS "Routes";
CREATE TABLE IF NOT EXISTS "Routes" (
	"route_id"	INTEGER NOT NULL,
	"departure_time"	TIMESTAMP NOT NULL,
	"arrival_time"	TIMESTAMP NOT NULL,
	"flight_id"	INTEGER(10) NOT NULL,
	"departure_airport"	VARCHAR(3) NOT NULL,
	"arrival_airport"	VARCHAR(3) NOT NULL,
	PRIMARY KEY("route_id" AUTOINCREMENT),
	FOREIGN KEY("flight_id") REFERENCES "Flights"("flight_id"),
	FOREIGN KEY("arrival_airport") REFERENCES "Airports"("airport_code"),
	FOREIGN KEY("departure_airport") REFERENCES "Airports"("airport_code")
);
DROP TABLE IF EXISTS "Reservations";
CREATE TABLE IF NOT EXISTS "Reservations" (
	"reservation_id"	INTEGER NOT NULL,
	"status"	integer(1) NOT NULL DEFAULT 0,
	"price"	DECIMAL(10, 5) NOT NULL,
	"seat_num"	varchar(3) NOT NULL,
	"route_id"	INTEGER(10) NOT NULL,
	"user_id"	INTEGER(10) NOT NULL,
	"date_of_reservation"	TIMESTAMP NOT NULL,
	PRIMARY KEY("reservation_id" AUTOINCREMENT),
	FOREIGN KEY("user_id") REFERENCES "Users"("user_id"),
	FOREIGN KEY("route_id") REFERENCES "Routes"("route_id")
);
COMMIT;
