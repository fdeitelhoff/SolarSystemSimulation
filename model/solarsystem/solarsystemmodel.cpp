#include "solarsystemmodel.h"

SolarSystemModel::SolarSystemModel()
{
    solarSystemRepository = new SolarSystemRepository();
    heavenlyBodyRepository = new HeavenlyBodyRepository();

    solarSystemTableModel = 0;
    solarSystemHeavenlyBodyTableModel = 0;
    starsComboBoxModel = 0;
    planetsComboBoxModel = 0;
}

SolarSystemTableModel* SolarSystemModel::getSolarSystemTableModel()
{
    if (!solarSystemTableModel)
    {
        solarSystemTableModel = new SolarSystemTableModel();
    }

    return solarSystemTableModel;
}

SolarSystemHeavenlyBodyTableModel* SolarSystemModel::getSolarSystemHeavenlyBodyTableModel()
{
    if (!solarSystemHeavenlyBodyTableModel)
    {
        solarSystemHeavenlyBodyTableModel = new SolarSystemHeavenlyBodyTableModel();
    }

    return solarSystemHeavenlyBodyTableModel;
}

HeavenlyBodyComboBoxModel* SolarSystemModel::getStarsComboBoxModel()
{
    if (!starsComboBoxModel)
    {
        starsComboBoxModel = new HeavenlyBodyComboBoxModel();
    }

    return starsComboBoxModel;
}

HeavenlyBodyComboBoxModel* SolarSystemModel::getPlanetsComboBoxModel()
{
    if (!planetsComboBoxModel)
    {
        planetsComboBoxModel = new HeavenlyBodyComboBoxModel();
    }

    return planetsComboBoxModel;
}

void SolarSystemModel::loadAllSolarSystemEntities()
{
    SolarSystemTableModel *solarSystemTableModel = getSolarSystemTableModel();
    //heavenlyBodyTableModel->resetInternalData();

    QList<SolarSystem *> entities = solarSystemRepository->fetchAllSolarSystemEntities();

    solarSystemTableModel->setData(entities);
}

void SolarSystemModel::loadOtherEntities()
{
    QList<HeavenlyBody *> stars = heavenlyBodyRepository->fetchExplizitTypedEntities("S");
    QList<HeavenlyBody *> planets = heavenlyBodyRepository->fetchExplizitTypedEntities("P");

    starsComboBoxModel->setData(stars);
    planetsComboBoxModel->setData(planets);
}
