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
};

#endif // HEAVENLYBODYREPOSITORY_H
