#include "heavenlybodyrepository.h"

HeavenlyBodyRepository::HeavenlyBodyRepository()
{
    database = PostgreSQLDatabase::getInstance();
}

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

void HeavenlyBodyRepository::deleteEntity(HeavenlyBody *heavenlyBody)
{
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

QString HeavenlyBodyRepository::colorToString(QColor color)
{
    QString colorString("%1:%2:%3:%4");
    colorString = colorString.arg(color.red());
    colorString = colorString.arg(color.green());
    colorString = colorString.arg(color.blue());
    colorString = colorString.arg(color.alpha());

    return colorString;
}

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

bool HeavenlyBodyRepository::isEntityUnique(HeavenlyBody *heavenlyBody)
{
    QSqlQuery heavenlyBodyQuery;
    heavenlyBodyQuery.prepare("SELECT"
                              "     COUNT(*) AS count "
                              "FROM "
                              "     heavenlybody "
                              "WHERE "
                              "     name = :name "
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
