#ifndef ENTITYNOTUNIQUEEXCEPTION_H
#define ENTITYNOTUNIQUEEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class EntityNotUniqueException : public exception
{
public:
    EntityNotUniqueException(const QString message);
    virtual ~EntityNotUniqueException() throw() {}

    virtual const QString getMessage() const throw();

private:
    QString message;
};

#endif // ENTITYNOTUNIQUEEXCEPTION_H
