#include "databaseconnectionfailedexception.h"

DatabaseConnectionFailedException::DatabaseConnectionFailedException(QString message, QString sqlError)
{
    this->message = message;
    this->sqlError = sqlError;
}

const QString DatabaseConnectionFailedException::getMessage() const throw()
{
    return message;
}

const QString DatabaseConnectionFailedException::getSqlError() const throw()
{
    return sqlError;
}
