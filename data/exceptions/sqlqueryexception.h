#ifndef SQLQUERYEXCEPTION_H
#define SQLQUERYEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class SqlQueryException : public exception
{
public:
    SqlQueryException(const QString message, QString sqlError);
    virtual ~SqlQueryException() throw() {}

    virtual const QString getMessage() const throw();
    virtual const QString getSqlError() const throw();

private:
    QString message;
    QString sqlError;
};

#endif // SQLQUERYEXCEPTION_H
