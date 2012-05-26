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

#include "solarsystemrepository.h"

/*!
 \brief Constructor: Repository of the solar systems and their data.

*/
SolarSystemRepository::SolarSystemRepository()
{
    database = PostgreSQLDatabase::getInstance();
}

/*!
 \brief Create a list of all solar systems stored in the database.

 \return QList<HeavenlyBody *> List of all stored solar systems including all data.
*/
QList<SolarSystem *> SolarSystemRepository::fetchAllSolarSystemEntities()
{
    QSqlQuery solarSystemQuery;
    solarSystemQuery.prepare("SELECT"
                             "     solarsystemid, "
                             "     solarsystem.name, "
                             "     heavenlybodyid, "
                             "     heavenlybody.name, "
                             "     diameter, "
                             "     color, "
                             "     type "
                             "FROM "
                             "     solarsystem "
                             "INNER JOIN "
                             "     heavenlybody "
                             "ON "
                             "     centralstarid = heavenlybodyid "
                             "ORDER BY "
                             "     solarsystem.name, "
                             "     solarsystemid");

    if (!solarSystemQuery.exec())
    {
        throw SqlQueryException("The solar system entities could not be retrieved!",
                                solarSystemQuery.lastError().text());
    }

    QList<SolarSystem *> entities;

    QSqlQuery innerQuery;
    innerQuery.prepare("SELECT"
                  "     excentricity, "
                  "     semimajoraxis, "
                  "     angle, "
                  "     orbitalplaneangle, "
                  "     heavenlybody.heavenlybodyid, "
                  "     heavenlybody.name, "
                  "     diameter, "
                  "     color, "
                  "     type "
                  "FROM "
                  "     solarsystemtoheavenlybody "
                  "INNER JOIN "
                  "     heavenlybody "
                  "ON "
                  "     solarsystemtoheavenlybody.heavenlybodyid = heavenlybody.heavenlybodyid "
                  "WHERE "
                  "     solarsystemid = :solarsystemid "
                  "ORDER BY "
                  "     semimajoraxis");

    while (solarSystemQuery.next())
    {
        // The solar system data.
        qint64 solarSystemId = solarSystemQuery.value(0).toLongLong();
        QString solarSystemName = solarSystemQuery.value(1).toString();

        // The central star data.
        qint64 id = solarSystemQuery.value(2).toLongLong();
        QString name = solarSystemQuery.value(3).toString();
        int diameter = solarSystemQuery.value(4).toInt();
        QString color = solarSystemQuery.value(5).toString();
        QString type = solarSystemQuery.value(6).toString();

        SolarSystem *solarSystem = new SolarSystem(solarSystemId,
                                                   solarSystemName,
                                                   new HeavenlyBody(id, name, diameter, color, type));

        innerQuery.bindValue(":solarsystemid", solarSystemId);

        // If there was an error in the inner query the _complete_ execution is canceled here!
        if (!innerQuery.exec())
        {
            throw SqlQueryException("The solar system heavenly bodies could not be retrieved!",
                                    innerQuery.lastError().text());
        }

        while (innerQuery.next())
        {
            // The planet within the solar system.
            SolarSystemHeavenlyBody *solarSystemHeavenlyBody = new SolarSystemHeavenlyBody(
                        new HeavenlyBody(innerQuery.value(4).toLongLong(),
                                         innerQuery.value(5).toString(),
                                         innerQuery.value(6).toInt(),
                                         innerQuery.value(7).toString(),
                                         innerQuery.value(8).toString()),
                        innerQuery.value(0).toDouble(),
                        innerQuery.value(1).toDouble(),
                        innerQuery.value(2).toDouble(),
                        innerQuery.value(3).toDouble());

            solarSystem->addHeavenlyBody(solarSystemHeavenlyBody);
        }

        entities.append(solarSystem);
    }

    return entities;
}

/*!
 \brief Insert a new solar system.

 \param solarSystem Object of the new solar system.
*/
void SolarSystemRepository::insertEntity(SolarSystem *solarSystem)
{
    // Check if the solar system is unique (only the name until now).
    if (!isSolarSystemUnique(solarSystem))
    {
        throw EntityNotUniqueException("The name of the solar system is not unique! Please choose another one.");
    }

    QSqlQuery insertSolarSystemQuery;
    insertSolarSystemQuery.prepare("INSERT INTO solarsystem "
                                   "     (name, "
                                   "      centralstarid) "
                                   "VALUES "
                                   "     (:name, "
                                   "      :centralstarid) "
                                   "RETURNING "
                                   "     solarsystemid");

    insertSolarSystemQuery.bindValue(":name", solarSystem->getName());
    insertSolarSystemQuery.bindValue(":centralstarid", solarSystem->getCentralStar()->getId());

    if (!insertSolarSystemQuery.exec())
    {
        throw SqlQueryException("The solar system could not be inserted!",
                                insertSolarSystemQuery.lastError().text());
    }

    if (!insertSolarSystemQuery.next())
    {
        throw SqlQueryException("The last inserted solar system id could not be retrieved!",
                                insertSolarSystemQuery.lastError().text());
    }

    qint64 id = insertSolarSystemQuery.record().value("solarsystemid").toLongLong();

    if (id <= 0)
    {
        throw SqlQueryException("The last inserted solar system id could not be retrieved!",
                                insertSolarSystemQuery.lastError().text());
    }

    solarSystem->setId(id);
}

/*!
 \brief Update the data of an existing solar system.

 \param solarSystem Name of the solar system to be updated.
 \param solarSystemHeavenlyBody New parameters of the solar system.
 \param oldSolarSystemHeavenlyBody Old parameter of the solar system.
*/
void SolarSystemRepository::updatePlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody,
                                               SolarSystemHeavenlyBody *oldSolarSystemHeavenlyBody)
{
    if (!isSolarSystemHeavenlyBodyUnique(solarSystem, solarSystemHeavenlyBody))
    {
        throw EntityNotUniqueException("The solar system heavenly body is not unique!");
    }

    QSqlQuery editPlanetQuery;
    editPlanetQuery.prepare("UPDATE "
                            "       solarsystemtoheavenlybody "
                            "SET "
                            "       heavenlybodyid = :heavenlybodyid, "
                            "       excentricity = :excentricity, "
                            "       semimajoraxis = :semimajoraxis, "
                            "       angle = :angle, "
                            "       orbitalplaneangle = :orbitalplaneangle "
                            "WHERE "
                            "       solarsystemid = :solarsystemid "
                            "AND "
                            "       heavenlybodyid = :oldHeavenlybodyid "
                            "AND "
                            "       excentricity = :oldExcentricity "
                            "AND "
                            "       semimajoraxis = :oldSemimajoraxis "
                            "AND "
                            "       angle = :oldAngle "
                            "AND "
                            "       orbitalplaneangle = :oldOrbitalplaneangle");

    editPlanetQuery.bindValue(":solarsystemid", solarSystem->getId());
    editPlanetQuery.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());
    editPlanetQuery.bindValue(":excentricity", solarSystemHeavenlyBody->getNumericExcentricity());
    editPlanetQuery.bindValue(":semimajoraxis", solarSystemHeavenlyBody->getSemimajorAxis());
    editPlanetQuery.bindValue(":angle", solarSystemHeavenlyBody->getAngle());
    editPlanetQuery.bindValue(":orbitalplaneangle", solarSystemHeavenlyBody->getOrbitalPlaneAngle());

    editPlanetQuery.bindValue(":oldHeavenlybodyid", oldSolarSystemHeavenlyBody->getHeavenlyBody()->getId());
    editPlanetQuery.bindValue(":oldExcentricity", oldSolarSystemHeavenlyBody->getNumericExcentricity());
    editPlanetQuery.bindValue(":oldSemimajoraxis", oldSolarSystemHeavenlyBody->getSemimajorAxis());
    editPlanetQuery.bindValue(":oldAngle", oldSolarSystemHeavenlyBody->getAngle());
    editPlanetQuery.bindValue(":oldOrbitalplaneangle", oldSolarSystemHeavenlyBody->getOrbitalPlaneAngle());

    if (!editPlanetQuery.exec())
    {
        throw SqlQueryException("The planet could not updated in the database!",
                                editPlanetQuery.lastError().text());
    }
}

/*!
 \brief Update the main components of the database. Name and central star.

 \param solarSystem
*/
void SolarSystemRepository::updateEntity(SolarSystem *solarSystem)
{
    // Check if the solar system is unique (only the name until now).
    if (!isSolarSystemUnique(solarSystem))
    {
        throw EntityNotUniqueException("The name of the solar system is not unique! Please choose another one.");
    }

    QSqlQuery updateSolarSystemQuery;
    updateSolarSystemQuery.prepare("UPDATE "
                                   "     solarsystem "
                                   "SET "
                                   "     name = :name, "
                                   "     centralstarid = :centralstarid "
                                   "WHERE "
                                   "     solarsystemid = :solarsystemid");

    updateSolarSystemQuery.bindValue(":name", solarSystem->getName());
    updateSolarSystemQuery.bindValue(":centralstarid", solarSystem->getCentralStar()->getId());
    updateSolarSystemQuery.bindValue(":solarsystemid", solarSystem->getId());

    if (!updateSolarSystemQuery.exec())
    {
        throw SqlQueryException("The solar system could not be updated!",
                                updateSolarSystemQuery.lastError().text());
    }
}

/*!
 \brief Add a new heavenly body to an existing solar system.

 \param solarSystem Solar system which is to expand.
 \param solarSystemHeavenlyBody The new heavenly body in the solar system.
*/
void SolarSystemRepository::insertPlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (!isSolarSystemHeavenlyBodyUnique(solarSystem, solarSystemHeavenlyBody))
    {
        throw EntityNotUniqueException("The solar system heavenly body is not unique!");
    }

    QSqlQuery insertPlanetQuery;
    insertPlanetQuery.prepare("INSERT INTO solarsystemtoheavenlybody"
                              "     (solarsystemid, "
                              "      heavenlybodyid, "
                              "      excentricity, "
                              "      semimajoraxis, "
                              "      angle, "
                              "      orbitalplaneangle) "
                              "VALUES "
                              "     (:solarsystemid, "
                              "      :heavenlybodyid, "
                              "      :excentricity, "
                              "      :semimajoraxis, "
                              "      :angle, "
                              "      :orbitalplaneangle)");

    insertPlanetQuery.bindValue(":solarsystemid", solarSystem->getId());
    insertPlanetQuery.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());
    insertPlanetQuery.bindValue(":excentricity", solarSystemHeavenlyBody->getNumericExcentricity());
    insertPlanetQuery.bindValue(":semimajoraxis", solarSystemHeavenlyBody->getSemimajorAxis());
    insertPlanetQuery.bindValue(":angle", solarSystemHeavenlyBody->getAngle());
    insertPlanetQuery.bindValue(":orbitalplaneangle", solarSystemHeavenlyBody->getOrbitalPlaneAngle());

    if (!insertPlanetQuery.exec())
    {
        throw SqlQueryException("The planet could not inserted to the solar system!",
                                insertPlanetQuery.lastError().text());
    }
}

/*!
 \brief Delete an existing heavenly body from a solar system.

 \param solarSystem Solar system to change.
 \param solarSystemHeavenlyBody Heavenly body to be deleted.
*/
void SolarSystemRepository::deletePlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    QSqlQuery deletePlanetQuery;
    deletePlanetQuery.prepare("DELETE FROM "
                              "     solarsystemtoheavenlybody "
                              "WHERE "
                              "     solarsystemid = :solarsystemid "
                              "AND "
                              "     heavenlybodyid = :heavenlybodyid "
                              "AND "
                              "     excentricity = :excentricity "
                              "AND "
                              "     semimajoraxis = :semimajoraxis "
                              "AND "
                              "     angle = :angle "
                              "AND "
                              "     orbitalplaneangle = :orbitalplaneangle");

    deletePlanetQuery.bindValue(":solarsystemid", solarSystem->getId());
    deletePlanetQuery.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());
    deletePlanetQuery.bindValue(":excentricity", solarSystemHeavenlyBody->getNumericExcentricity());
    deletePlanetQuery.bindValue(":semimajoraxis", solarSystemHeavenlyBody->getSemimajorAxis());
    deletePlanetQuery.bindValue(":angle", solarSystemHeavenlyBody->getAngle());
    deletePlanetQuery.bindValue(":orbitalplaneangle", solarSystemHeavenlyBody->getOrbitalPlaneAngle());

    if (!deletePlanetQuery.exec())
    {
        throw SqlQueryException("The planet could not be deleted from the solar system!",
                                deletePlanetQuery.lastError().text());
    }
}

/*!
 \brief Delete complete solarsystem.

 \param solarSystem Solar system to delete.
*/
void SolarSystemRepository::deleteEntity(SolarSystem *solarSystem)
{
    database->getInstance()->transaction();

    // Delete all planets of the solar system first!
    QSqlQuery deleteSolarSystemPlanetsQuery;
    deleteSolarSystemPlanetsQuery.prepare("DELETE FROM "
                                          "     solarsystemtoheavenlybody "
                                          "WHERE "
                                          "     solarsystemid = :solarsystemid");

    deleteSolarSystemPlanetsQuery.bindValue(":solarsystemid", solarSystem->getId());

    if (!deleteSolarSystemPlanetsQuery.exec())
    {
        database->getInstance()->rollback();

        throw SqlQueryException("No planet of the solar system could be deleted!",
                                deleteSolarSystemPlanetsQuery.lastError().text());
    }

    // Now delete the solar system!
    QSqlQuery deleteSolarSystemQuery;
    deleteSolarSystemQuery.prepare("DELETE FROM "
                                   "     solarsystem "
                                   "WHERE "
                                   "     solarsystemid = :solarsystemid");

    deleteSolarSystemQuery.bindValue(":solarsystemid", solarSystem->getId());

    if (!deleteSolarSystemQuery.exec())
    {
        database->getInstance()->rollback();

        throw SqlQueryException("The solar system could not be deleted!",
                                deleteSolarSystemQuery.lastError().text());
    }

    database->getInstance()->commit();
}

/*!
 \brief Check if the solar system exists.

 \param solarSystem The solar system to check.
 \return bool Return TRUE if the solar system does not exists.
*/
bool SolarSystemRepository::isSolarSystemUnique(SolarSystem *solarSystem)
{
    QSqlQuery solarSystemQuery;
    solarSystemQuery.prepare("SELECT"
                             "     COUNT(*) AS count "
                             "FROM "
                             "     solarsystem "
                             "WHERE "
                             "     lower(name) = lower(:name) "
                             "AND "
                             "     solarsystemid <> :solarsystemid");

    solarSystemQuery.bindValue(":name", solarSystem->getName());
    solarSystemQuery.bindValue(":solarsystemid", solarSystem->getId());

    if (!solarSystemQuery.exec())
    {
        throw SqlQueryException("The solar system entity could not checked if it is unique!",
                                solarSystemQuery.lastError().text());
    }

    if (!solarSystemQuery.next())
    {
        throw SqlQueryException("The solar system entity could not checked if it is unique!",
                                solarSystemQuery.lastError().text());
    }

    return solarSystemQuery.record().value("count").toInt() == 0;
}

/*!
 \brief Check if the heavenly body of a solar system exists

 \param solarSystem Solar system to check.
 \param solarSystemHeavenlyBody Check for this heavenly body.
 \return bool Return TRUE if heavenly bode does not exists in the solar system.
*/
bool SolarSystemRepository::isSolarSystemHeavenlyBodyUnique(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    QSqlQuery heavenlyBodyQuery;
    heavenlyBodyQuery.prepare("SELECT"
                              "     COUNT(*) AS count "
                              "FROM "
                              "     solarsystemtoheavenlybody "
                              "WHERE "
                              "     heavenlybodyid = :heavenlybodyid "
                              "AND "
                              "     excentricity = :excentricity "
                              "AND "
                              "     semimajoraxis = :semimajoraxis "
                              "AND "
                              "     angle = :angle "
                              "AND "
                              "     orbitalplaneangle = :orbitalplaneangle "
                              "AND "
                              "     solarsystemid = :solarsystemid");

    heavenlyBodyQuery.bindValue(":solarsystemid", solarSystem->getId());
    heavenlyBodyQuery.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());
    heavenlyBodyQuery.bindValue(":excentricity", solarSystemHeavenlyBody->getNumericExcentricity());
    heavenlyBodyQuery.bindValue(":semimajoraxis", solarSystemHeavenlyBody->getSemimajorAxis());
    heavenlyBodyQuery.bindValue(":angle", solarSystemHeavenlyBody->getAngle());
    heavenlyBodyQuery.bindValue(":orbitalplaneangle", solarSystemHeavenlyBody->getOrbitalPlaneAngle());

    if (!heavenlyBodyQuery.exec())
    {
        throw SqlQueryException("It could not be checked if the heavenly body is unique!",
                                heavenlyBodyQuery.lastError().text());
    }

    if (!heavenlyBodyQuery.next())
    {
        throw SqlQueryException("It could not be checked if the heavenly body is unique!",
                                heavenlyBodyQuery.lastError().text());
    }

    return heavenlyBodyQuery.record().value("count").toInt() == 0;
}
