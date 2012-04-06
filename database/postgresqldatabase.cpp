#include "postgresqldatabase.h"
#include <QDebug>
#include <QSqlError>

PostgreSQLDatabase* PostgreSQLDatabase::instance = 0;

PostgreSQLDatabase::PostgreSQLDatabase()
{
    // Verbindung über ODBC. "SolarSystem" ist der Name der ODBC-Datenquelle!
    // database = QSqlDatabase::addDatabase("QODBC");
    // database.setDatabaseName("SolarSystem");

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
