#include "solarsystemrepository.h"

SolarSystemRepository::SolarSystemRepository()
{
    database = PostgreSQLDatabase::getInstance();
}

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
                        new HeavenlyBody(innerQuery.value(3).toLongLong(),
                                         innerQuery.value(4).toString(),
                                         innerQuery.value(5).toInt(),
                                         innerQuery.value(6).toString(),
                                         innerQuery.value(7).toString()),
                        innerQuery.value(0).toDouble(),
                        innerQuery.value(1).toDouble(),
                        innerQuery.value(2).toInt());

            solarSystem->addHeavenlyBody(solarSystemHeavenlyBody);
        }

        entities.append(solarSystem);
    }

    return entities;
}

void SolarSystemRepository::insertEntity(SolarSystem *solarSystem)
{
    // Check if the solar system is unique (only the name until now).
    if (!isEntityUnique(solarSystem))
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

void SolarSystemRepository::updateEntity(SolarSystem *solarSystem)
{
    // Check if the solar system is unique (only the name until now).
    if (!isEntityUnique(solarSystem))
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

void SolarSystemRepository::insertPlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    QSqlQuery insertPlanetQuery;
    insertPlanetQuery.prepare("INSERT INTO solarsystemtoheavenlybody"
                              "     (solarsystemid, "
                              "      heavenlybodyid, "
                              "      excentricity, "
                              "      semimajoraxis, "
                              "      angle) "
                              "VALUES "
                              "     (:solarsystemid, "
                              "      :heavenlybodyid, "
                              "      :excentricity, "
                              "      :semimajoraxis, "
                              "      :angle)");

    insertPlanetQuery.bindValue(":solarsystemid", solarSystem->getId());
    insertPlanetQuery.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());
    insertPlanetQuery.bindValue(":excentricity", solarSystemHeavenlyBody->getNumericExcentricity());
    insertPlanetQuery.bindValue(":semimajoraxis", solarSystemHeavenlyBody->getSemimajorAxis());
    insertPlanetQuery.bindValue(":angle", solarSystemHeavenlyBody->getAngle());

    if (!insertPlanetQuery.exec())
    {
        throw SqlQueryException("The planet could not inserted to the solar system!",
                                insertPlanetQuery.lastError().text());
    }
}

void SolarSystemRepository::deletePlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    QSqlQuery deletePlanetQuery;
    deletePlanetQuery.prepare("DELETE FROM "
                              "     solarsystemtoheavenlybody "
                              "WHERE "
                              "     solarsystemid = :solarsystemid "
                              "AND "
                              "     heavenlybodyid = :heavenlybodyid");

    deletePlanetQuery.bindValue(":solarsystemid", solarSystem->getId());
    deletePlanetQuery.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());

    if (!deletePlanetQuery.exec())
    {
        throw SqlQueryException("The planet could not be deleted from the solar system!",
                                deletePlanetQuery.lastError().text());
    }
}

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

bool SolarSystemRepository::isEntityUnique(SolarSystem *solarSystem)
{
    QSqlQuery solarSystemQuery;
    solarSystemQuery.prepare("SELECT"
                             "     COUNT(*) AS count "
                             "FROM "
                             "     solarsystem "
                             "WHERE "
                             "     name = :name "
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

