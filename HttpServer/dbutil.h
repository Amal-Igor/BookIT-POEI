#ifndef DBUTIL_H
#define DBUTIL_H
#include <QFile>
#include <QSqlDatabase>
#include <iostream>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>


using namespace std;

class DbUtil
{
public:
    DbUtil();
    DbUtil(QString dbPath, QString mDbName);



    const QSqlDatabase &db() const;
    void setDb(const QSqlDatabase &newDb);
    const QString &file() const;
    void setFile(const QString &newFile);
    const QString &dbName() const;
    void setDbName(const QString &newDbName);




private:
    QSqlDatabase mDb;
    QString mFile;
    QString mDbName;

};

#endif // DBUTIL_H
