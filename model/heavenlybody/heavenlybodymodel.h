#ifndef HEAVENLYBODYMODEL_H
#define HEAVENLYBODYMODEL_H

#include "data/heavenlybody/heavenlybodyrepository.h"

class HeavenlyBodyModel
{

public:
    HeavenlyBodyModel();

    void loadAllHeavenlyBodies();

private:
    HeavenlyBodyRepository *heavenlyBodyRepository;
};

#endif // HEAVENLYBODYMODEL_H
