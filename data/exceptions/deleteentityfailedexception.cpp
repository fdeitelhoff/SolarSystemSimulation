#include "deleteentityfailedexception.h"

DeleteEntityFailedException::DeleteEntityFailedException(QString message)
{
    this->message = message;
    sqlError = "";
}

DeleteEntityFailedException::DeleteEntityFailedException(QString message, QString sqlError)
{
    this->message = message;
    this->sqlError = sqlError;
}

const QString DeleteEntityFailedException::getMessage() const throw()
{
    return message;
}

const QString DeleteEntityFailedException::getSqlError() const throw()
{
    return sqlError;
}
