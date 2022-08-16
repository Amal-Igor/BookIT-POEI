#include "dbutil.h"

DbUtil::DbUtil()
{


}

DbUtil::DbUtil(QString dbPath, QString mDbName)
{
    if (QFile::exists(dbPath))
    {
        mDb = QSqlDatabase::addDatabase("QSQLITE", mDbName);
        mDb.setDatabaseName(dbPath);
        if (mDb.open() == false)
            cout << "Prolbème survenu lors de la connection à la base de donnée";
    }
}

const QSqlDatabase &DbUtil::db() const
{
    return mDb;
}

void DbUtil::setDb(const QSqlDatabase &newDb)
{
    mDb = newDb;
}

const QString &DbUtil::file() const
{
    return mFile;
}

void DbUtil::setFile(const QString &newFile)
{
    mFile = newFile;
}

const QString &DbUtil::dbName() const
{
    return mDbName;
}

void DbUtil::setDbName(const QString &newDbName)
{
    mDbName = newDbName;
}



