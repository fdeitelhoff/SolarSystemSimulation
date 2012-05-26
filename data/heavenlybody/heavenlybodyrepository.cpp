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

#include "heavenlybodyrepository.h"

/*!
 \brief Constructor: Repository of the heavenly bodies with an instance of the complete database.

*/
HeavenlyBodyRepository::HeavenlyBodyRepository()
{
    database = PostgreSQLDatabase::getInstance();
}

/*!
 \brief Create a list of all heavenly bodies stored in the database.

 \return QList<HeavenlyBody *> List of all stored heavenly bodies.
*/
QList<HeavenlyBody *> HeavenlyBodyRepository::fetchAllHeavenlyBodyEntities()
{
    QSqlQuery heavenlyBodyEntityQuery;
    heavenlyBodyEntityQuery.prepare("SELECT "
                                    "     heavenlybodyid, "
                                    "     name, "
                                    "     diameter, "
                                    "     color, "
                                    "     type "
                                    "FROM "
                                    "     heavenlybody "
                                    "ORDER BY "
                                    "     type, "
                                    "     name");

    if (!heavenlyBodyEntityQuery.exec())
    {
        throw SqlQueryException("The heavenly body entities could not be fetched!",
                                heavenlyBodyEntityQuery.lastError().text());
    }

    QList<HeavenlyBody *> entities;

    while (heavenlyBodyEntityQuery.next())
    {
        qint64 id = heavenlyBodyEntityQuery.value(0).toLongLong();
        QString name = heavenlyBodyEntityQuery.value(1).toString();
        int diameter = heavenlyBodyEntityQuery.value(2).toInt();
        QString color = heavenlyBodyEntityQuery.value(3).toString();
        QString type = heavenlyBodyEntityQuery.value(4).toString();

        entities.append(new HeavenlyBody(id, name, diameter, color, type));
    }

    return entities;
}

/*!
 \brief Update the data of the given heavenly body.

 \param heavenlyBody Heavely body to be updated.
*/
void HeavenlyBodyRepository::updateEntity(HeavenlyBody *heavenlyBody)
{
    // Check if the heavenly body is unique (the name until now).
    if (!isEntityUnique(heavenlyBody))
    {
        throw EntityNotUniqueException("The name of the heavenly body is not unique! Please choose another one.");
    }

    // Check if the heavenlybody is used as a star, when it should be a planet!
    if (heavenlyBody->getType() == "P")
    {
        QSqlQuery isHeavenlyBodyStarQuery;
        isHeavenlyBodyStarQuery.prepare("SELECT "
                                        "       COUNT(*) As count "
                                        "FROM "
                                        "       solarsystem "
                                        "WHERE "
                                        "       centralstarid = :centralstarid");

        isHeavenlyBodyStarQuery.bindValue(":centralstarid", heavenlyBody->getId());

        if (!isHeavenlyBodyStarQuery.exec())
        {
            throw SqlQueryException("The heavenly body could not be checked!",
                                    isHeavenlyBodyStarQuery.lastError().text());
        }

        if (!isHeavenlyBodyStarQuery.next())
        {
            throw SqlQueryException("The heavenly body could not be checked!",
                                    isHeavenlyBodyStarQuery.lastError().text());
        }

        if (isHeavenlyBodyStarQuery.record().value("count").toInt() != 0)
        {
            throw HeavenlyBodyTypeException(QString("The Heavenly Body '%1' could not changed to a planet!\n\nIt is used as a star in at least one solar system.").arg(heavenlyBody->getName()));
        }
    }
    // Check if the heavenlybody is used as a planet, when it should be a star!
    else if (heavenlyBody->getType() == "S")
    {
        QSqlQuery isHeavenlyBodyPlanetQuery;
        isHeavenlyBodyPlanetQuery.prepare("SELECT "
                                          "       COUNT(*) As count "
                                          "FROM "
                                          "       solarsystemtoheavenlybody "
                                          "WHERE "
                                          "       heavenlybodyid = :heavenlybodyid");

        isHeavenlyBodyPlanetQuery.bindValue(":heavenlybodyid", heavenlyBody->getId());

        if (!isHeavenlyBodyPlanetQuery.exec())
        {
            throw SqlQueryException("The heavenly body could not be checked!",
                                    isHeavenlyBodyPlanetQuery.lastError().text());
        }

        if (!isHeavenlyBodyPlanetQuery.next())
        {
            throw SqlQueryException("The heavenly body could not be checked!",
                                    isHeavenlyBodyPlanetQuery.lastError().text());
        }

        if (isHeavenlyBodyPlanetQuery.record().value("count").toInt() != 0)
        {
            throw HeavenlyBodyTypeException(QString("The Heavenly Body '%1' could not changed to a star!\n\nIt is used as a planet in at least one solar system.").arg(heavenlyBody->getName()));
        }
    }

    QSqlQuery updateHeavenlyBodyQuery;
    updateHeavenlyBodyQuery.prepare("UPDATE "
                                    "     heavenlybody "
                                    "SET "
                                    "     name = :name, "
                                    "     diameter = :diameter, "
                                    "     color = :color, "
                                    "     type = :type "
                                    "WHERE "
                                    "     heavenlybodyid = :heavenlybodyid");

    updateHeavenlyBodyQuery.bindValue(":name", heavenlyBody->getName());
    updateHeavenlyBodyQuery.bindValue(":diameter", heavenlyBody->getDiameter());
    updateHeavenlyBodyQuery.bindValue(":color", colorToString(heavenlyBody->getColor()));
    updateHeavenlyBodyQuery.bindValue(":type", heavenlyBody->getType());
    updateHeavenlyBodyQuery.bindValue(":heavenlybodyid", heavenlyBody->getId());

    if (!updateHeavenlyBodyQuery.exec())
    {
        throw SqlQueryException("The heavenly body could not be updated!",
                                updateHeavenlyBodyQuery.lastError().text());
    }
}

/*!
 \brief Add a new heavenly body to the to the database.

 \param heavenlyBody Heavenly body to add.
*/
void HeavenlyBodyRepository::insertEntity(HeavenlyBody *heavenlyBody)
{
    // Check if the heavenly body is unique (the name until now).
    if (!isEntityUnique(heavenlyBody))
    {
        throw EntityNotUniqueException("The name of the heavenly body is not unique! Please choose another one.");
    }

    QSqlQuery addHeavenlyBodyQuery;
    addHeavenlyBodyQuery.prepare("INSERT INTO heavenlybody "
                                 "      ( "
                                 "       name, "
                                 "       diameter, "
                                 "       color, "
                                 "       type "
                                 "      ) "
                                 "VALUES "
                                 "      ( "
                                 "       :name, "
                                 "       :diameter, "
                                 "       :color, "
                                 "       :type "
                                 "      ) "
                                 "RETURNING "
                                 "      heavenlybodyid");

    addHeavenlyBodyQuery.bindValue(":name", heavenlyBody->getName());
    addHeavenlyBodyQuery.bindValue(":diameter", heavenlyBody->getDiameter());
    addHeavenlyBodyQuery.bindValue(":color", colorToString(heavenlyBody->getColor()));
    addHeavenlyBodyQuery.bindValue(":type", heavenlyBody->getType());

    if (!addHeavenlyBodyQuery.exec())
    {
        throw SqlQueryException("The heavenly body could not be inserted!",
                                addHeavenlyBodyQuery.lastError().text());
    }

    // Get the last inserted id.
    if (!addHeavenlyBodyQuery.next())
    {
        throw new SqlQueryException("The last inserted heavenly body id could not be retrieved!",
                                    addHeavenlyBodyQuery.lastError().text());
    }

    qint64 id = addHeavenlyBodyQuery.record().value("heavenlybodyid").toLongLong();

    if (id <= 0)
    {
        throw new SqlQueryException("The last inserted heavenly body id could not be retrieved!",
                                    addHeavenlyBodyQuery.lastError().text());
    }

    heavenlyBody->setId(id);
}

/*!
 \brief Delete heavenly body from the database.

 \param heavenlyBody Heavenly body to delete.
*/
void HeavenlyBodyRepository::deleteEntity(HeavenlyBody *heavenlyBody)
{
    int count = isHeavenlyBodyUsedAsPlanet(heavenlyBody);

    if (count > 0)
    {
        throw DeleteEntityFailedException(QString("The heavenly body could not be deleted because it is used in %1 solar system(s) as a planet!").arg(count));
    }

    count = isHeavenlyBodyUsedAsStar(heavenlyBody);

    if (count > 0)
    {
        throw DeleteEntityFailedException(QString("The heavenly body could not be deleted because it is used in %1 solar system(s) as a star!").arg(count));
    }

    QSqlQuery deleteHeavenlyBodyQuery;
    deleteHeavenlyBodyQuery.prepare("DELETE FROM "
                                    "       heavenlybody "
                                    "WHERE "
                                    "       heavenlybodyid = :heavenlybodyid");

    deleteHeavenlyBodyQuery.bindValue(":heavenlybodyid", heavenlyBody->getId());

    if (!deleteHeavenlyBodyQuery.exec())
    {
        throw DeleteEntityFailedException("The heavenly body could not be deleted!",
                                          deleteHeavenlyBodyQuery.lastError().text());
    }
}

/*!
 \brief Convert a Qt-color to a string to store in database.

 \param color Color to store in the database
 \return QString Color in database format
*/
QString HeavenlyBodyRepository::colorToString(QColor color)
{
    QString colorString("%1:%2:%3:%4");
    colorString = colorString.arg(color.red());
    colorString = colorString.arg(color.green());
    colorString = colorString.arg(color.blue());
    colorString = colorString.arg(color.alpha());

    return colorString;
}

/*!
 \brief Returns a list of heavely bodies of the given type

 \param type Type of the heavenly body
 \return QList<HeavenlyBody *> List of the heavenly bodies of type 'type'.
*/
QList<HeavenlyBody *> HeavenlyBodyRepository::fetchExplizitTypedEntities(QString type)
{
    QSqlQuery fetchTypedEntitiesQuery;
    fetchTypedEntitiesQuery.prepare("SELECT "
                                    "     heavenlybodyid, "
                                    "     name, "
                                    "     diameter, "
                                    "     color, "
                                    "     type "
                                    "FROM "
                                    "     heavenlybody "
                                    "WHERE "
                                    "     type = :type "
                                    "ORDER BY "
                                    "     name");

    fetchTypedEntitiesQuery.bindValue(":type", type);

    if (!fetchTypedEntitiesQuery.exec())
    {
        throw SqlQueryException("The explizit typed heavenly bodies could not be retrieved!",
                                fetchTypedEntitiesQuery.lastError().text());
    }

    QList<HeavenlyBody *> entities;

    while (fetchTypedEntitiesQuery.next())
    {
        qint64 id = fetchTypedEntitiesQuery.value(0).toLongLong();
        QString name = fetchTypedEntitiesQuery.value(1).toString();
        int diameter = fetchTypedEntitiesQuery.value(2).toInt();
        QString color = fetchTypedEntitiesQuery.value(3).toString();
        QString type = fetchTypedEntitiesQuery.value(4).toString();

        entities.append(new HeavenlyBody(id, name, diameter, color, type));
    }

    return entities;
}

/*!
 \brief Check if the database contains a heavenly body with the same name as the given heavenly body.

 \param heavenlyBody Heavenly body with the Name to be checked.
 \return bool TRUE when the name of the given heavenly body is not in the database.
*/
bool HeavenlyBodyRepository::isEntityUnique(HeavenlyBody *heavenlyBody)
{
    QSqlQuery heavenlyBodyQuery;
    heavenlyBodyQuery.prepare("SELECT"
                              "     COUNT(*) AS count "
                              "FROM "
                              "     heavenlybody "
                              "WHERE "
                              "     lower(name) = lower(:name) "
                              "AND "
                              "     heavenlybodyid <> :heavenlybodyid");

    heavenlyBodyQuery.bindValue(":name", heavenlyBody->getName());
    heavenlyBodyQuery.bindValue(":heavenlybodyid", heavenlyBody->getId());

    if (!heavenlyBodyQuery.exec())
    {
        throw SqlQueryException("The heavenly body entity could not checked if it is unique!",
                                heavenlyBodyQuery.lastError().text());
    }

    if (!heavenlyBodyQuery.next())
    {
        throw SqlQueryException("The heavenly body entity could not checked if it is unique!",
                                heavenlyBodyQuery.lastError().text());
    }

    return heavenlyBodyQuery.record().value("count").toInt() == 0;
}

/*!
 \brief Check if the given heavenly body is used as 'planet'.

 \param heavenlyBody Heavenly body to be checked.
 \return int How often the heavenly body is used as a planet.
*/
int HeavenlyBodyRepository::isHeavenlyBodyUsedAsPlanet(HeavenlyBody *heavenlyBody)
{
    QSqlQuery isHeavenlyBodyUsedQuery;
    isHeavenlyBodyUsedQuery.prepare("SELECT"
                                    "     COUNT(*) AS count "
                                    "FROM "
                                    "     solarsystemtoheavenlybody "
                                    "WHERE "
                                    "     heavenlybodyid = :heavenlybodyid");

    isHeavenlyBodyUsedQuery.bindValue(":heavenlybodyid", heavenlyBody->getId());

    if (!isHeavenlyBodyUsedQuery.exec())
    {
        throw SqlQueryException("It could not be checked if the heavenly body is used in a solar system!",
                                isHeavenlyBodyUsedQuery.lastError().text());
    }

    if (!isHeavenlyBodyUsedQuery.next())
    {
        throw SqlQueryException("It could not be checked if the heavenly body is used in a solar system!",
                                isHeavenlyBodyUsedQuery.lastError().text());
    }

    return isHeavenlyBodyUsedQuery.record().value("count").toInt();
}

/*!
 \brief Check if the given heavenly body is used as a 'star'.

 \param heavenlyBody Heavenly body to be checked.
 \return int How often the heavenly body is used as a star.
*/
int HeavenlyBodyRepository::isHeavenlyBodyUsedAsStar(HeavenlyBody *heavenlyBody)
{
    QSqlQuery isHeavenlyBodyUsedQuery;
    isHeavenlyBodyUsedQuery.prepare("SELECT"
                                    "     COUNT(*) AS count "
                                    "FROM "
                                    "     solarsystem "
                                    "WHERE "
                                    "     centralstarid = :heavenlybodyid");

    isHeavenlyBodyUsedQuery.bindValue(":heavenlybodyid", heavenlyBody->getId());

    if (!isHeavenlyBodyUsedQuery.exec())
    {
        throw SqlQueryException("It could not be checked it the heavenly body is used in a solar system!",
                                isHeavenlyBodyUsedQuery.lastError().text());
    }

    if (!isHeavenlyBodyUsedQuery.next())
    {
        throw SqlQueryException("It could not be checked it the heavenly body is used in a solar system!",
                                isHeavenlyBodyUsedQuery.lastError().text());
    }

    return isHeavenlyBodyUsedQuery.record().value("count").toInt();
}
