#ifndef DELETEENTITYFAILEDEXCEPTION_H
#define DELETEENTITYFAILEDEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class DeleteEntityFailedException : public exception
{
public:
    DeleteEntityFailedException(const QString message, QString sqlError);
    virtual ~DeleteEntityFailedException() throw() {}

    virtual const QString getMessage() const throw();
    virtual const QString getSqlError() const throw();

private:
    QString message;
    QString sqlError;
};

#endif // DELETEENTITYFAILEDEXCEPTION_H
