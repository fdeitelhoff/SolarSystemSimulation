#include "solarsystemrepository.h"

SolarSystemRepository::SolarSystemRepository()
{
    database = PostgreSQLDatabase::getInstance();
}

QList<SolarSystem *> SolarSystemRepository::fetchAllSolarSystemEntities()
{
    QSqlQuery query;
    query.prepare("SELECT"
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
                  "     centralstarid = heavenlybodyid");
    query.exec();

    qDebug() << query.lastError();

    QList<SolarSystem *> entities;

    QSqlQuery innerQuery;
    innerQuery.prepare("SELECT"
                  "     excentricity, "
                  "     semimajoraxis, "
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
                  "     solarsystemid = :solarsystemid");

    while (query.next())
    {
        // The solar system data.
        qint64 solarSystemId = query.value(0).toLongLong();
        QString solarSystemName = query.value(1).toString();

        // The central star data.
        qint64 id = query.value(2).toLongLong();
        QString name = query.value(3).toString();
        int diameter = query.value(4).toInt();
        QString color = query.value(5).toString();
        QString type = query.value(6).toString();

        SolarSystem *solarSystem = new SolarSystem(solarSystemId,
                                                   solarSystemName,
                                                   new HeavenlyBody(id, name, diameter, color, type));

        innerQuery.bindValue(":solarsystemid", solarSystemId);

        innerQuery.exec();

        qDebug() << innerQuery.lastError();

        while (innerQuery.next())
        {
            // The planet within the solar system.
            SolarSystemHeavenlyBody *solarSystemHeavenlyBody = new SolarSystemHeavenlyBody(
                        new HeavenlyBody(innerQuery.value(2).toLongLong(),
                                         innerQuery.value(3).toString(),
                                         innerQuery.value(4).toInt(),
                                         innerQuery.value(5).toString(),
                                         innerQuery.value(6).toString()),
                        innerQuery.value(0).toDouble(),
                        innerQuery.value(1).toDouble());

            solarSystem->addHeavenlyBody(solarSystemHeavenlyBody);
        }

        entities.append(solarSystem);
    }

    return entities;
}

void SolarSystemRepository::addEntity(SolarSystem *solarSystem)
{
    QSqlQuery query;
    query.prepare("INSERT INTO solarsystem "
                  "     (name, "
                  "      centralstarid) "
                  "VALUES "
                  "     (:name, "
                  "      :centralstarid) "
                  "RETURNING "
                  "     solarsystemid");
    query.bindValue(":name", solarSystem->getName());
    query.bindValue(":centralstarid", solarSystem->getCentralStar()->getId());
    query.exec();

    qDebug() << query.lastError();

    query.next();
    qint64 id = query.record().value("solarsystemid").toLongLong();

    solarSystem->setId(id);
}

void SolarSystemRepository::updateEntity(SolarSystem *solarSystem)
{
    QSqlQuery query;
    query.prepare("UPDATE "
                  "     solarsystem "
                  "SET "
                  "     name = :name, "
                  "     centralstarid = :centralstarid) "
                  "WHERE "
                  "     solarsystemid = :solarsystemid");
    query.bindValue(":name", solarSystem->getName());
    query.bindValue(":centralstarid", solarSystem->getCentralStar()->getId());
    query.bindValue(":solarsystemid", solarSystem->getId());
    query.exec();

    qDebug() << query.lastError();
}

void SolarSystemRepository::addPlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    QSqlQuery query;
    query.prepare("INSERT INTO solarsystemtoheavenlybody"
                  "     (solarsystemid, "
                  "      heavenlybodyid, "
                  "      excentricity, "
                  "      semimajoraxis) "
                  "VALUES "
                  "     (:solarsystemid, "
                  "      :heavenlybodyid, "
                  "      :excentricity, "
                  "      :semimajoraxis)");
    query.bindValue(":solarsystemid", solarSystem->getId());
    query.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());
    query.bindValue(":excentricity", solarSystemHeavenlyBody->getNumericExcentricity());
    query.bindValue(":semimajoraxis", solarSystemHeavenlyBody->getSemimajorAxis());
    query.exec();

    qDebug() << query.lastError();
}

void SolarSystemRepository::deletePlanetEntity(SolarSystem *solarSystem, SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    QSqlQuery query;
    query.prepare("DELETE FROM "
                  "     solarsystemtoheavenlybody "
                  "WHERE "
                  "     solarsystemid = :solarsystemid "
                  "AND "
                  "     heavenlybodyid = :heavenlybodyid");
    query.bindValue(":solarsystemid", solarSystem->getId());
    query.bindValue(":heavenlybodyid", solarSystemHeavenlyBody->getHeavenlyBody()->getId());
    query.exec();

    qDebug() << query.lastError();
}

void SolarSystemRepository::deleteEntity(SolarSystem *solarSystem)
{
    database->getInstance()->transaction();

    QSqlQuery deleteSolarSystemPlanetsQuery;
    deleteSolarSystemPlanetsQuery.prepare("DELETE FROM "
                  "     solarsystemtoheavenlybody "
                  "WHERE "
                  "     solarsystemid = :solarsystemid");
    deleteSolarSystemPlanetsQuery.bindValue(":solarsystemid", solarSystem->getId());
    deleteSolarSystemPlanetsQuery.exec();

    qDebug() << deleteSolarSystemPlanetsQuery.lastError();

    QSqlQuery deleteSolarSystemQuery;
    deleteSolarSystemQuery.prepare("DELETE FROM "
                  "     solarsystem "
                  "WHERE "
                  "     solarsystemid = :solarsystemid");
    deleteSolarSystemQuery.bindValue(":solarsystemid", solarSystem->getId());
    deleteSolarSystemQuery.exec();

    qDebug() << deleteSolarSystemQuery.lastError();

    database->getInstance()->commit();
}
