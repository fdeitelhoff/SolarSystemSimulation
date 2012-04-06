#include "solarsystemmodel.h"

SolarSystemModel::SolarSystemModel()
{
    solarSystemRepository = new SolarSystemRepository();

    solarSystemTableModel = 0;
}

SolarSystemTableModel* SolarSystemModel::getSolarSystemTableModel()
{
    if (!solarSystemTableModel)
    {
        solarSystemTableModel = new SolarSystemTableModel();
    }

    return solarSystemTableModel;
}

void SolarSystemModel::loadAllSolarSystemEntities()
{
    SolarSystemTableModel *solarSystemTableModel = getSolarSystemTableModel();
    //heavenlyBodyTableModel->resetInternalData();

    QList<SolarSystem *> entities = solarSystemRepository->fetchAllSolarSystemEntities();

    solarSystemTableModel->addData(entities);
}
