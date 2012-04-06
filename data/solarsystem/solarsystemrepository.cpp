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
