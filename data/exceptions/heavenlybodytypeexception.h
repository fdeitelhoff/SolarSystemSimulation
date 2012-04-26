#ifndef HEAVENLYBODYTYPEEXCEPTION_H
#define HEAVENLYBODYTYPEEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

class HeavenlyBodyTypeException : public exception
{

public:
    HeavenlyBodyTypeException(const QString message);
    virtual ~HeavenlyBodyTypeException() throw() {}

    virtual const QString getMessage() const throw();

private:
    QString message;
};

#endif // HEAVENLYBODYTYPEEXCEPTION_H
