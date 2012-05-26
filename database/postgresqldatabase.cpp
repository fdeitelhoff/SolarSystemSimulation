/*
    Copyright (C) 2012 by
    Fabian Deitelhoff (FH@FabianDeitelhoff.de) and
    Christof Geisler (christof.geisler@stud.fh-swf.de)

    This file is part of the project SolarSystemSimulation.

    SolarSystemSimulation is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SolarSystemSimulation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SolarSystemSimulation.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "postgresqldatabase.h"
#include <QDebug>
#include <QSqlError>

PostgreSQLDatabase* PostgreSQLDatabase::instance = 0; /*Database to modify */

/*!
 \brief Establish database connection. On windows systems use ODBC, on other systems the native PostgreSQL driver.

*/
PostgreSQLDatabase::PostgreSQLDatabase()
{
    #ifdef WIN32
    // Connection over ODBC!. "SolarSystemSimulation" is the name of the ODBC data source.
    database = QSqlDatabase::addDatabase("QODBC");
    database.setDatabaseName("SolarSystemSimulation");

    #else
    // Connection through the native PostgreSQL driver.
    database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("localhost");
    database.setDatabaseName("SolarSystemSimulation");
    database.setUserName("postgres");
    database.setPassword("postgres");
    #endif

    if (!database.open())
    {
        throw DatabaseConnectionFailedException("The database connection could not be opened!",
                                                database.lastError().text());
    }
}

/*!
 \brief Make PostgreSQLDatabase Object if none exists.

 \return PostgreSQLDatabase * Return the PostgreSQLDatabase Object.
*/
PostgreSQLDatabase* PostgreSQLDatabase::getInstance()
{
    if (!instance)
    {
        instance = new PostgreSQLDatabase();
    }

    return instance;
}

/*!
 \brief Start database transaction.

*/
void PostgreSQLDatabase::transaction()
{
    database.transaction();
}

/*!
 \brief Commit database operations.

*/
void PostgreSQLDatabase::commit()
{
    database.commit();
}

/*!
 \brief Rollback the database operations.

*/
void PostgreSQLDatabase::rollback()
{
    database.rollback();
}
