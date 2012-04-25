#include "solarsystemmodel.h"

SolarSystemModel::SolarSystemModel()
{
    solarSystemRepository = new SolarSystemRepository();
    heavenlyBodyRepository = new HeavenlyBodyRepository();

    solarSystemTableModel = 0;
    solarSystemHeavenlyBodyTableModel = 0;
    starsComboBoxModel = 0;
    planetsComboBoxModel = 0;

    currentSolarSystem = 0;
}

bool SolarSystemModel::isEntitySelected()
{
    return currentSolarSystem != 0;
}

void SolarSystemModel::loadEntityData()
{
    if (currentSolarSystem)
    {
        solarSystemHeavenlyBodyTableModel->setData(currentSolarSystem->getHeavenlyBodies());
    }
}

int SolarSystemModel::getSelectedStar()
{
    if (!currentSolarSystem)
    {
        return -1;
    }

    return starsComboBoxModel->getHeavenlyBodyIndex(currentSolarSystem->getCentralStar());
}

void SolarSystemModel::setSolarSystemSelectionModel(QItemSelectionModel *solarSystemSelectionModel)
{
    this->solarSystemSelectionModel = solarSystemSelectionModel;
    QObject::connect(this->solarSystemSelectionModel,
                     SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this,
                     SLOT(currentSolarSystemRowChanged(QModelIndex,QModelIndex)),
                     Qt::DirectConnection);
}

void SolarSystemModel::setSolarSystemHeavenlyBodySelectionModel(QItemSelectionModel *selectionModel)
{
    this->solarSystemHeavenlyBodySelectionModel = selectionModel;
    QObject::connect(this->solarSystemHeavenlyBodySelectionModel,
                     SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this,
                     SLOT(currentPlanetsRowChanged(QModelIndex,QModelIndex)),
                     Qt::DirectConnection);
}

void SolarSystemModel::currentPlanetsRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.row() >= 0)
    {
        currentSolarSystemHeavenlyBody = solarSystemHeavenlyBodyTableModel->getSolarSystemHeavenlyBody(current.row());
    }
}

void SolarSystemModel::currentSolarSystemRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.row() >= 0)
    {
        currentSolarSystem = solarSystemTableModel->getSolarSystem(current.row());
    }
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
    return solarSystemHeavenlyBodyTableModel = new SolarSystemHeavenlyBodyTableModel();
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

    QList<SolarSystem *> entities = solarSystemRepository->fetchAllSolarSystemEntities();

    solarSystemTableModel->setData(entities);
}

void SolarSystemModel::loadOtherEntities()
{
    QList<HeavenlyBody *> stars = heavenlyBodyRepository->fetchExplizitTypedEntities("S");
    QList<HeavenlyBody *> planets = heavenlyBodyRepository->fetchExplizitTypedEntities("P");

    getStarsComboBoxModel()->setData(stars);
    getPlanetsComboBoxModel()->setData(planets);
}

void SolarSystemModel::createSolarSystem(QString name, int centralStarIndex)
{    
    SolarSystem *solarSystem = new SolarSystem(name, starsComboBoxModel->getHeavenlyBody(centralStarIndex));

    solarSystemRepository->insertEntity(solarSystem);
    solarSystemTableModel->addSolarSystem(solarSystem);

    currentSolarSystem = solarSystem;
}

void SolarSystemModel::updateSolarSystem(QString name, int centralStarIndex)
{
    HeavenlyBody *centralStar = starsComboBoxModel->getHeavenlyBody(centralStarIndex);

    // Create a temporary object first.
    SolarSystem *solarSystem = new SolarSystem(currentSolarSystem->getId(), name, centralStar);

    solarSystemRepository->updateEntity(solarSystem);

    // Update the original entity when there was no database error!
    currentSolarSystem->setName(name);
    currentSolarSystem->setCentralStar(centralStar);
}

void SolarSystemModel::addPlanet(int planetIndex, double excentricity, double semimajorAxis, double angle, double orbitalPlaneAngle)
{
    SolarSystemHeavenlyBody *solarSystemHeavenlyBody = new SolarSystemHeavenlyBody(planetsComboBoxModel->getHeavenlyBody(planetIndex),
                                                                                   excentricity, semimajorAxis, angle, orbitalPlaneAngle);

    solarSystemRepository->insertPlanetEntity(currentSolarSystem, solarSystemHeavenlyBody);
    solarSystemHeavenlyBodyTableModel->addSolarSystemHeavenlyBody(solarSystemHeavenlyBody);
    currentSolarSystem->addHeavenlyBody(solarSystemHeavenlyBody);
}

void SolarSystemModel::deletePlanet()
{
    solarSystemRepository->deletePlanetEntity(currentSolarSystem, currentSolarSystemHeavenlyBody);
    solarSystemHeavenlyBodyTableModel->deleteSolarSystemHeavenlyBody(currentSolarSystemHeavenlyBody);

    currentSolarSystem->removeHeavenlyBody(currentSolarSystemHeavenlyBody);

    if (solarSystemHeavenlyBodyTableModel->getEntityCount() == 0)
    {
        currentSolarSystemHeavenlyBody = 0;
    }
}

void SolarSystemModel::deleteSolarSystem()
{
    solarSystemRepository->deleteEntity(currentSolarSystem);
    solarSystemTableModel->deleteSolarSystem(currentSolarSystem);

    currentSolarSystem = 0;
    currentSolarSystemHeavenlyBody = 0;
}
