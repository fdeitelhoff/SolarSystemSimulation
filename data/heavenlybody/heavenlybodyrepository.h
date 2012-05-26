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

#ifndef HEAVENLYBODYREPOSITORY_H
#define HEAVENLYBODYREPOSITORY_H

#include <QList>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include "database/postgresqldatabase.h"
#include "model/heavenlybody/heavenlybody.h"
#include "data/exceptions/deleteentityfailedexception.h"
#include "data/exceptions/sqlqueryexception.h"
#include "data/exceptions/entitynotuniqueexception.h"
#include "data/exceptions/heavenlybodytypeexception.h"

/**
    Class for heavenly body repository.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBodyRepository
{

public:
    HeavenlyBodyRepository();

    QList<HeavenlyBody *> fetchAllHeavenlyBodyEntities();

    QList<HeavenlyBody *> fetchExplizitTypedEntities(QString type);

    void updateEntity(HeavenlyBody *heavenlyBody);
    void insertEntity(HeavenlyBody *heavenlyBody);
    void deleteEntity(HeavenlyBody *heavenlyBody);

private:
    PostgreSQLDatabase *database;

    QString colorToString(QColor color);

    bool isEntityUnique(HeavenlyBody *heavenlyBody);
    int isHeavenlyBodyUsedAsPlanet(HeavenlyBody *heavenlyBody);
    int isHeavenlyBodyUsedAsStar(HeavenlyBody *heavenlyBody);
};

#endif // HEAVENLYBODYREPOSITORY_H
