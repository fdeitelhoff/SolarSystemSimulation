#ifndef PROPERTYNOTVALIDEXCEPTION_H
#define PROPERTYNOTVALIDEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class PropertyNotValidException : public exception
{
public:
    PropertyNotValidException(const QString property, const QString message);
    virtual ~PropertyNotValidException() throw() {}

    virtual const QString getMessage() const throw();
    virtual const QString getProperty() const throw();

private:
    QString property;
    QString message;
};

#endif // PROPERTYNOTVALIDEXCEPTION_H
