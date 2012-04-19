#include "sqlqueryexception.h"

SqlQueryException::SqlQueryException(QString message, QString sqlError)
{
    this->message = message;
    this->sqlError = sqlError;
}

const QString SqlQueryException::getMessage() const throw()
{
    return message;
}

const QString SqlQueryException::getSqlError() const throw()
{
    return sqlError;
}

