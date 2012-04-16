#include "postgresqldatabase.h"
#include <QDebug>
#include <QSqlError>

PostgreSQLDatabase* PostgreSQLDatabase::instance = 0;

PostgreSQLDatabase::PostgreSQLDatabase()
{
    // Connection over ODBC!. "SolarSystem" is the name of the ODBC data source.
//    database = QSqlDatabase::addDatabase("QODBC");
//    database.setDatabaseName("SolarSystemSimulation");
//    bool ok = database.open();

    // Connection through the native PostgreSQL driver.
     database = QSqlDatabase::addDatabase("QPSQL");
     database.setHostName("localhost");
     database.setDatabaseName("SolarSystemSimulation");
     database.setUserName("postgres");
     database.setPassword("postgres");
     bool ok = database.open();

    qDebug() << "DB-Connection: " << ok;
    qDebug() << "Last-error: " << database.lastError();
}

PostgreSQLDatabase* PostgreSQLDatabase::getInstance()
{
    if (!instance)
    {
        instance = new PostgreSQLDatabase();
    }

    return instance;
}

void PostgreSQLDatabase::transaction()
{
    qDebug() << database.transaction();
}

void PostgreSQLDatabase::commit()
{
    qDebug() << database.commit();
}

void PostgreSQLDatabase::rollback()
{
    qDebug() << database.rollback();
}
