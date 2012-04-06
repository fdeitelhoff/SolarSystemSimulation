#ifndef HEAVENLYBODY_H
#define HEAVENLYBODY_H

#include <QString>

class HeavenlyBody
{
public:
    HeavenlyBody();

    long getId() { return id; }
    QString getName() { return name; }

private:
    long id;
    QString name;
};

#endif // HEAVENLYBODY_H
