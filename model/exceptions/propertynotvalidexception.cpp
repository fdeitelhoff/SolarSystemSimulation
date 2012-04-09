#include "propertynotvalidexception.h"

PropertyNotValidException::PropertyNotValidException(const QString property, QString message)
{
    this->property = property;
    this->message = message.arg(property);
}

const QString PropertyNotValidException::getMessage() const throw()
{
    return message;
}

const QString PropertyNotValidException::getProperty() const throw()
{
    return property;
}
