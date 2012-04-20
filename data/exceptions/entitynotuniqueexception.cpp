#include "entitynotuniqueexception.h"

EntityNotUniqueException::EntityNotUniqueException(QString message)
{
    this->message = message;
}

const QString EntityNotUniqueException::getMessage() const throw()
{
    return message;
}
