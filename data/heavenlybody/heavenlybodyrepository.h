#ifndef HEAVENLYBODYREPOSITORY_H
#define HEAVENLYBODYREPOSITORY_H

#include <QList>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include "heavenlybody.h"
#include "database/postgresqldatabase.h"

class HeavenlyBodyRepository
{

public:
    HeavenlyBodyRepository();

    QList<HeavenlyBody *> fetchAllHeavenlyBodyEntities();

    void updateEntity(HeavenlyBody *heavenlyBody);
    void addEntity(HeavenlyBody *heavenlyBody);
    void deleteEntity(HeavenlyBody *heavenlyBody);

private:
    PostgreSQLDatabase *database;

    QString colorToString(QColor color);
};

#endif // HEAVENLYBODYREPOSITORY_H
