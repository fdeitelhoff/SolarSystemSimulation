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

class HeavenlyBodyRepository
{

public:
    HeavenlyBodyRepository();

    QList<HeavenlyBody *> fetchAllHeavenlyBodyEntities();

    QList<HeavenlyBody *> fetchExplizitTypedEntities(QString type);

    void updateEntity(HeavenlyBody *heavenlyBody);
    void addEntity(HeavenlyBody *heavenlyBody);
    void deleteEntity(HeavenlyBody *heavenlyBody);

private:
    PostgreSQLDatabase *database;

    QString colorToString(QColor color);
};

#endif // HEAVENLYBODYREPOSITORY_H
