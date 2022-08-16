#ifndef TOOLS_H
#define TOOLS_H

#include <QDateTime>



class Tools
{
public:
    Tools();
    QDateTime generateRandomDateTime(int _year, int _month, int _day, int _hour, int _minutes);
    bool verifyDateTimeValidity(QDateTime _departure, QDateTime _arrival);

};

#endif // TOOLS_H
