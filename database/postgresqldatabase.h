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

#ifndef POSTGRESQLDATABASE_H
#define POSTGRESQLDATABASE_H

#include <QSqlDatabase>

#include "database/exceptions/databaseconnectionfailedexception.h"

/**
    Class for connect to database.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class PostgreSQLDatabase
{
protected:
    PostgreSQLDatabase();

private:
    static PostgreSQLDatabase *instance;

    QSqlDatabase database;

public:
    static PostgreSQLDatabase* getInstance();

    void transaction();
    void commit();
    void rollback();
};

#endif // POSTGRESQLDATABASE_H
