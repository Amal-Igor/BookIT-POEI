/*
 * File: ticket.cpp
 * Project:  Ticket Generator | BookIT
 * File Created: Thursday, 7th July 2022 4:32:37 PM
 * Author: nknab
 * Email: adverb_rushed_09@icloud.com
 * Version: 1.0
 * Brief: 
 * -----
 * Last Modified: Thursday, 7th July 2022 4:38:33 PM
 * Modified By: nknab
 * -----
 * Copyright ©2022 nknab
 */

#include "ticket.h"
#include <QDir>

/**
 * @brief It creates a new Ticket object, loads the ticket template, and creates a new barcode object.
 *
 * @param _templateFilePath The path to the directory where the ticket template is located.
 * @param _parent           The parent object of the ticket.
 */
Ticket::Ticket(QString _templateFilePath, QObject *_parent) : QObject{_parent} {
    mTicketTemplate.load(_templateFilePath + "ticket-twnb.png");
    filePathRoot = _templateFilePath;

    mBarcode = new Code128Item();
}

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
void Ticket::writeData(int _reserveID, QString _name, QString _seatNum, QString _departure, QString _arrival, int _flightID, QDateTime _timestamp) {
    QPainter p(&mTicketTemplate);

    QString flightID = "BK " + QString::number(_flightID);
    QString date = _timestamp.date().toString("MMM dd").toUpper();
    QString timeDepart = _timestamp.time().toString("hh:mm");

    p.drawText(QRect(91, 66, 260, 24), Qt::AlignLeft, _name.toUpper());
    p.drawText(QRect(138, 145, 210, 24), Qt::AlignLeft, _departure.toUpper());
    p.drawText(QRect(138, 178, 210, 24), Qt::AlignLeft, _arrival.toUpper());

    p.drawText(QRect(346, 62, 63, 24), Qt::AlignCenter, flightID);
    p.drawText(QRect(428, 62, 63, 24), Qt::AlignCenter, _seatNum.toUpper());

    p.drawText(QRect(346, 203, 63, 24), Qt::AlignCenter, "B");
    p.drawText(QRect(428, 203, 63, 24), Qt::AlignCenter, "C23");

    p.drawText(QRect(428, 133, 63, 24), Qt::AlignCenter, timeDepart);
    p.drawText(QRect(346, 133, 63, 24), Qt::AlignCenter, date);

    p.drawText(QRect(533, 52, 180, 16), Qt::AlignLeft, _name.toUpper());
    p.drawText(QRect(567, 75, 150, 16), Qt::AlignLeft, _departure.toUpper());
    p.drawText(QRect(552, 91, 170, 16), Qt::AlignLeft, _arrival.toUpper());

    p.drawText(QRect(528, 146, 40, 16), Qt::AlignCenter, flightID);
    p.drawText(QRect(684, 146, 40, 16), Qt::AlignCenter, _seatNum.toUpper());
    p.drawText(QRect(605, 146, 40, 16), Qt::AlignCenter, "B");

    p.drawText(QRect(528, 184, 40, 16), Qt::AlignCenter, "C23");
    p.drawText(QRect(684, 184, 40, 16), Qt::AlignCenter, timeDepart);
    p.drawText(QRect(605, 184, 40, 16), Qt::AlignCenter, date);

    mBarcode->setText("BookIT-" + QString::number(_reserveID));
    mBarcode->setTextVisible(false);
    mBarcode->setHighDPI(true);

    mBarcode->setWidth(180);
    mBarcode->setHeight(50);
    mBarcode->setPosition(536, 210);

    mBarcode->paint(&p, nullptr, nullptr);

    mBarcode->setPosition(53, 27);
    mBarcode->setRotate(true);
    mBarcode->paint(&p, nullptr, nullptr);

    p.end();
    QString saveFilePath = filePathRoot + _name + "-" + flightID + ".png";
    mTicketTemplate.save(saveFilePath);
}

/**
 * @brief Function returns the ticket image.
 * 
 * @return The ticket template.
 */
QImage Ticket::getTicket() {
    return mTicketTemplate;
}

/**
 * @brief The destructor for the Ticket class.
 */
Ticket::~Ticket() {
    delete mBarcode;
}
