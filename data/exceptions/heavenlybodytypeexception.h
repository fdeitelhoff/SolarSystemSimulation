#ifndef HEAVENLYBODYTYPEEXCEPTION_H
#define HEAVENLYBODYTYPEEXCEPTION_H

#include <QString>
#include <exception>

using namespace std;

/**
    Class for wrong type exceptions.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

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
