#include "tools.h"

Tools::Tools()
{

}

QDateTime Tools::generateRandomDateTime(int _year, int _month, int _day, int _hour, int _minutes)
{
    QDateTime dt;
    dt.setDate(QDate(_year,_month, _day));
        dt.setTime(QTime(_hour,_minutes));

        return dt;
}

bool Tools::verifyDateTimeValidity(QDateTime _departure, QDateTime _arrival)
{
        QString departure =_departure.toString(Qt::ISODate);
        QString arrival =_arrival.toString(Qt::ISODate);
        if(departure.isEmpty() || arrival.isEmpty())
        {
            return false;
        }

        return true;
}
