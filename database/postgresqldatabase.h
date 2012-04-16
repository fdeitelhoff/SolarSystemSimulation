#ifndef POSTGRESQLDATABASE_H
#define POSTGRESQLDATABASE_H

#include <QSqlDatabase>

#include "database/exceptions/databaseconnectionfailedexception.h"

class PostgreSQLDatabase
{
protected:
    PostgreSQLDatabase();

private:
    static PostgreSQLDatabase *instance;

    QSqlDatabase database;

public:
    static PostgreSQLDatabase* getInstance();

    void transaction();
    void commit();
    void rollback();
};

#endif // POSTGRESQLDATABASE_H
