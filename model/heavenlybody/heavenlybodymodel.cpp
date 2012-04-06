#include "heavenlybodymodel.h"

HeavenlyBodyModel::HeavenlyBodyModel()
{
    heavenlyBodyRepository = new HeavenlyBodyRepository();
}

void HeavenlyBodyModel::loadAllHeavenlyBodies()
{
    heavenlyBodyRepository->fetchAllHeavenlyBodies();
}
