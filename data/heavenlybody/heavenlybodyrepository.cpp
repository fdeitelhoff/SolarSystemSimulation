#include "heavenlybodyrepository.h"

HeavenlyBodyRepository::HeavenlyBodyRepository()
{
    database = PostgreSQLDatabase::getInstance();
}

QList<HeavenlyBody> HeavenlyBodyRepository::fetchAllHeavenlyBodies()
{
    QSqlQuery query;
    //query.prepare("INSERT INTO person (id, forename, surname) "
    //              "VALUES (:id, :forename, :surname)");
    //query.bindValue(":id", 1001);
    //query.bindValue(":forename", "Bart");
    //query.bindValue(":surname", "Simpson");
    //query.exec();
}
