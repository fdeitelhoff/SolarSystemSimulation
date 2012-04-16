#ifndef DATABASECONNECTIONFAILEDEXCEPTION_H
#define DATABASECONNECTIONFAILEDEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class DatabaseConnectionFailedException : public exception
{
public:
    DatabaseConnectionFailedException(const QString message, QString sqlError);
    virtual ~DatabaseConnectionFailedException() throw() {}

    virtual const QString getMessage() const throw();
    virtual const QString getSqlError() const throw();

private:
    QString message;
    QString sqlError;
};

#endif // DATABASECONNECTIONFAILEDEXCEPTION_H
