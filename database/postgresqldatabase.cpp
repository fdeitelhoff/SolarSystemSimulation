#include "postgresqldatabase.h"
#include <QDebug>
#include <QSqlError>

PostgreSQLDatabase* PostgreSQLDatabase::instance = 0;

PostgreSQLDatabase::PostgreSQLDatabase()
{
    // Connection over ODBC!. "SolarSystem" is the name of the ODBC data source.
    database = QSqlDatabase::addDatabase("QODBC");
    database.setDatabaseName("SolarSystemSimulation");

    // Connection through the native PostgreSQL driver.
     /*database = QSqlDatabase::addDatabase("QPSQL");
     database.setHostName("localhost");
     database.setDatabaseName("SolarSystemSimulation");
     database.setUserName("postgres");
     database.setPassword("postgres");*/

    if (!database.open())
    {
        throw DatabaseConnectionFailedException("The database connection could not be opened!",
                                                database.lastError().text());
    }
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
