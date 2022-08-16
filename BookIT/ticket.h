/*
 * File: ticket.h
 * Project: Ticket Generator | BookIT
 * File Created: Thursday, 7th July 2022 4:30:27 PM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: 
 * -----
 * Last Modified: Thursday, 7th July 2022 4:38:15 PM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#ifndef TICKET_H
#define TICKET_H

#include <QDateTime>
#include <QImage>
#include <QObject>
#include <QPainter>

#include "code128item.h"

class Ticket : public QObject {
    Q_OBJECT

   private:
    QImage mTicketTemplate;
    Code128Item *mBarcode;
    QString filePathRoot;

   public:
    /**
     * @brief It creates a new Ticket object, loads the ticket template, and creates a new barcode object.
     *
     * @param _templateFilePath The path to the directory where the ticket template is located.
     * @param _parent           The parent object of the ticket.
     */
    explicit Ticket(QString _templateFilePath = "../../../../tickets/", QObject *_parent = nullptr);

    /**
     * @brief Function returns the ticket image.
     *
     * @return The ticket template.
     */
    QImage getTicket();

    /**
     * @brief It takes in a bunch of data, writes it to the ticket template, and saves it to a file.
     *
     * @param _reserveID    The reservation ID of the ticket.
     * @param _name         The name of the passenger.
     * @param _seatNum      The seat number of the passenger.
     * @param _departure    Departure airport.
     * @param _arrival      The arrival airport.
     * @param _flightID      The flight ID of the flight the ticket is for.
     * @param _timestamp    The timestamp of the flight.
     */
    void writeData(int _reserveID, QString _name, QString _seatNum, QString _departure, QString _arrival, int _flightID, QDateTime _timestamp);

    /**
     * @brief The destructor for the Ticket class.
     */
    ~Ticket();
};

#endif  // TICKET_H
