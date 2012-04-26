#include "heavenlybodytypeexception.h"

HeavenlyBodyTypeException::HeavenlyBodyTypeException(QString message)
{
    this->message = message;
}

const QString HeavenlyBodyTypeException::getMessage() const throw()
{
    return message;
}
