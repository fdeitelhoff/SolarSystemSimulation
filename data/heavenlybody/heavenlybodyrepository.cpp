#include "heavenlybodyrepository.h"

HeavenlyBodyRepository::HeavenlyBodyRepository()
{
    database = PostgreSQLDatabase::getInstance();
}

QList<HeavenlyBody *> HeavenlyBodyRepository::fetchAllHeavenlyBodyEntities()
{
    QSqlQuery query;
    query.prepare("SELECT heavenlybodyid, name, diameter, color, type FROM heavenlybody");
    query.exec();

    qDebug() << query.lastError();

    QList<HeavenlyBody *> entities;

    while (query.next())
    {
        qint64 id = query.value(0).toLongLong();
        QString name = query.value(1).toString();
        int diameter = query.value(2).toInt();
        QString color = query.value(3).toString();
        QString type = query.value(4).toString();

        entities.append(new HeavenlyBody(id, name, diameter, color, type));
    }

    return entities;
}

void HeavenlyBodyRepository::updateEntity(HeavenlyBody *heavenlyBody)
{
    QSqlQuery query;
    query.prepare("UPDATE heavenlybody SET name = :name, diameter = :diameter, color = :color, type = :type WHERE heavenlybodyid = :heavenlybodyid");
    query.bindValue(":name", heavenlyBody->getName());
    query.bindValue(":diameter", heavenlyBody->getDiameter());
    query.bindValue(":color", colorToString(heavenlyBody->getColor()));
    query.bindValue(":type", heavenlyBody->getType());
    query.bindValue(":heavenlybodyid", heavenlyBody->getId());
    query.exec();

    qDebug() << query.lastError();
}

void HeavenlyBodyRepository::addEntity(HeavenlyBody *heavenlyBody)
{
    QSqlQuery query;
    query.prepare("INSERT INTO heavenlybody(heavenlybodyid, name, diameter, color, type) VALUES (DEFAULT, :name, :diameter, :color, :type) RETURNING heavenlybodyid");
    query.bindValue(":name", heavenlyBody->getName());
    query.bindValue(":diameter", heavenlyBody->getDiameter());
    query.bindValue(":color", colorToString(heavenlyBody->getColor()));
    query.bindValue(":type", heavenlyBody->getType());
    query.exec();

    qDebug() << query.lastError();

    query.next();
    qint64 id = query.record().value("heavenlybodyid").toLongLong();

    heavenlyBody->setId(id);
}

void HeavenlyBodyRepository::deleteEntity(HeavenlyBody *heavenlyBody)
{
    QSqlQuery query;
    query.prepare("DELETE FROM heavenlybody WHERE heavenlybodyid = :heavenlybodyid");
    query.bindValue(":heavenlybodyid", heavenlyBody->getId());

    if (!query.exec())
    {
        throw DeleteEntityFailedException("The Heavenly Body entity could not be deleted!",
                                          query.lastError().text());
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
    QSqlQuery query;
    query.prepare("SELECT "
                  "     heavenlybodyid, "
                  "     name, "
                  "     diameter, "
                  "     color, "
                  "     type "
                  "FROM "
                  "     heavenlybody "
                  "WHERE "
                  "     type = :type");
    query.bindValue(":type", type);

    query.exec();

    qDebug() << query.lastError();

    QList<HeavenlyBody *> entities;

    while (query.next())
    {
        qint64 id = query.value(0).toLongLong();
        QString name = query.value(1).toString();
        int diameter = query.value(2).toInt();
        QString color = query.value(3).toString();
        QString type = query.value(4).toString();

        entities.append(new HeavenlyBody(id, name, diameter, color, type));
    }

    return entities;
}
