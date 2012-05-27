/*
    Copyright (C) 2012 by
    Fabian Deitelhoff (FH@FabianDeitelhoff.de) and
    Christof Geisler (christof.geisler@stud.fh-swf.de)

    This file is part of the project SolarSystemSimulation.

    SolarSystemSimulation is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SolarSystemSimulation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SolarSystemSimulation.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "solarsystemmodel.h"

/*!
 \brief Class to image the content of the whole solar system.

*/
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

/*!
 \brief Check if there is an selected solar system.

 \return bool
*/
bool SolarSystemModel::isEntitySelected()
{
    return currentSolarSystem != 0;
}

/*!
 \brief Set the data of the heavenly bodies to the solar system heavenly body model.

*/
void SolarSystemModel::loadEntityData()
{
    if (currentSolarSystem)
    {
        solarSystemHeavenlyBodyTableModel->setData(currentSolarSystem->getHeavenlyBodies());
    }
}

/*!
 \brief Resets the data of the solar system heavenly body model.

*/
void SolarSystemModel::resetSolarSystemEntityData()
{
    solarSystemHeavenlyBodyTableModel->resetData();
}

/*!
 \brief Returns the position of the selected star in the star combo box.

 \return int
*/
int SolarSystemModel::getSelectedStarIndex()
{
    if (!currentSolarSystem)
    {
        return -1;
    }

    return starsComboBoxModel->getHeavenlyBodyIndex(currentSolarSystem->getCentralStar());
}

/*!
 \brief Returns the position of the selected heavenly body in the planet combo box.

 \return int
*/
int SolarSystemModel::getSelectedHeavenlyBodyIndex()
{
    if (!currentSolarSystemHeavenlyBody)
    {
        return -1;
    }

    return planetsComboBoxModel->getHeavenlyBodyIndex(currentSolarSystemHeavenlyBody->getHeavenlyBody());
}

/*!
 \brief Connect to solarSystemSelectionModel.

 \param solarSystemSelectionModel
*/
void SolarSystemModel::setSolarSystemSelectionModel(QItemSelectionModel *solarSystemSelectionModel)
{
    this->solarSystemSelectionModel = solarSystemSelectionModel;
    QObject::connect(this->solarSystemSelectionModel,
                     SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this,
                     SLOT(currentSolarSystemRowChanged(QModelIndex,QModelIndex)),
                     Qt::DirectConnection);
}

/*!
 \brief Connect to solarSystemHeavenlyBodySelectionModel.

 \param selectionModel
*/
void SolarSystemModel::setSolarSystemHeavenlyBodySelectionModel(QItemSelectionModel *selectionModel)
{
    this->solarSystemHeavenlyBodySelectionModel = selectionModel;
    QObject::connect(this->solarSystemHeavenlyBodySelectionModel,
                     SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this,
                     SLOT(currentPlanetsRowChanged(QModelIndex,QModelIndex)),
                     Qt::DirectConnection);
}

/*!
 \brief Method called when selected row of planet in heavenly body overview changed.

 \param current
 \param previous
*/
void SolarSystemModel::currentPlanetsRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.row() >= 0)
    {
        currentSolarSystemHeavenlyBody = solarSystemHeavenlyBodyTableModel->getSolarSystemHeavenlyBody(current.row());
    }
}

/*!
 \brief Method called when selected row of solar system in solar system overview changed.

 \param current
 \param previous
*/
void SolarSystemModel::currentSolarSystemRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.row() >= 0)
    {
        currentSolarSystem = solarSystemTableModel->getSolarSystem(current.row());
    }
}

/*!
 \brief Getter for solar system model.

 \return SolarSystemTableModel *
*/
SolarSystemTableModel* SolarSystemModel::getSolarSystemTableModel()
{
    if (!solarSystemTableModel)
    {
        solarSystemTableModel = new SolarSystemTableModel();
    }

    return solarSystemTableModel;
}

/*!
 \brief Getter for solar system heavenly body model.

 \return SolarSystemHeavenlyBodyTableModel *
*/
SolarSystemHeavenlyBodyTableModel* SolarSystemModel::getSolarSystemHeavenlyBodyTableModel()
{
    if (!solarSystemHeavenlyBodyTableModel)
    {
        solarSystemHeavenlyBodyTableModel = new SolarSystemHeavenlyBodyTableModel();
    }

    return solarSystemHeavenlyBodyTableModel;
}

/*!
 \brief Getter for the star combo box model.

 \return HeavenlyBodyComboBoxModel *
*/
HeavenlyBodyComboBoxModel* SolarSystemModel::getStarsComboBoxModel()
{
    if (!starsComboBoxModel)
    {
        starsComboBoxModel = new HeavenlyBodyComboBoxModel();
    }

    return starsComboBoxModel;
}

/*!
 \brief Getter for the planet combo box model.

 \return HeavenlyBodyComboBoxModel *
*/
HeavenlyBodyComboBoxModel* SolarSystemModel::getPlanetsComboBoxModel()
{
    if (!planetsComboBoxModel)
    {
        planetsComboBoxModel = new HeavenlyBodyComboBoxModel();
    }

    return planetsComboBoxModel;
}

/*!
 \brief Load all solar system entities from repository.

*/
void SolarSystemModel::loadAllSolarSystemEntities()
{
    SolarSystemTableModel *solarSystemTableModel = getSolarSystemTableModel();

    QList<SolarSystem *> entities = solarSystemRepository->fetchAllSolarSystemEntities();

    solarSystemTableModel->setData(entities);
}

/*!
 \brief Load stars and planets entities from repository.

*/
void SolarSystemModel::loadOtherEntities()
{
    QList<HeavenlyBody *> stars = heavenlyBodyRepository->fetchExplizitTypedEntities("S");
    QList<HeavenlyBody *> planets = heavenlyBodyRepository->fetchExplizitTypedEntities("P");

    getStarsComboBoxModel()->setData(stars);
    getPlanetsComboBoxModel()->setData(planets);
}

/*!
 \brief Create new solar system in model and repository.

 \param name
 \param centralStarIndex
*/
void SolarSystemModel::createSolarSystem(QString name, int centralStarIndex)
{    
    SolarSystem *solarSystem = new SolarSystem(name, starsComboBoxModel->getHeavenlyBody(centralStarIndex));

    solarSystemRepository->insertEntity(solarSystem);
    solarSystemTableModel->addSolarSystem(solarSystem);

    currentSolarSystem = solarSystem;
}

/*!
 \brief Update solar system in model and repository.

 \param name
 \param centralStarIndex
*/
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

/*!
 \brief Add planet with its configuration to model and repository.

 \param planetIndex
 \param excentricity
 \param semimajorAxis
 \param angle
 \param orbitalPlaneAngle
*/
void SolarSystemModel::addPlanet(int planetIndex, double excentricity, double semimajorAxis, double angle, double orbitalPlaneAngle)
{
    SolarSystemHeavenlyBody *solarSystemHeavenlyBody = new SolarSystemHeavenlyBody(planetsComboBoxModel->getHeavenlyBody(planetIndex),
                                                                                   excentricity, semimajorAxis, angle, orbitalPlaneAngle);

    solarSystemRepository->insertPlanetEntity(currentSolarSystem, solarSystemHeavenlyBody);
    solarSystemHeavenlyBodyTableModel->addSolarSystemHeavenlyBody(solarSystemHeavenlyBody);
    currentSolarSystem->addHeavenlyBody(solarSystemHeavenlyBody);
}

/*!
 \brief Update planet and its configuration to model and repository.

 \param planetIndex
 \param excentricity
 \param semimajorAxis
 \param angle
 \param orbitalPlaneAngle
*/
void SolarSystemModel::updatePlanet(int planetIndex, double excentricity, double semimajorAxis, double angle, double orbitalPlaneAngle)
{
    // Create the tmp object first!
    SolarSystemHeavenlyBody *solarSystemHeavenlyBody = new SolarSystemHeavenlyBody(planetsComboBoxModel->getHeavenlyBody(planetIndex),
                                                                                   excentricity, semimajorAxis, angle, orbitalPlaneAngle);

    solarSystemRepository->updatePlanetEntity(currentSolarSystem, solarSystemHeavenlyBody, currentSolarSystemHeavenlyBody);

    // Change the current selected planet.
    currentSolarSystemHeavenlyBody->setHeavenlyBody(solarSystemHeavenlyBody->getHeavenlyBody());
    currentSolarSystemHeavenlyBody->setNumericExcentricity(solarSystemHeavenlyBody->getNumericExcentricity());
    currentSolarSystemHeavenlyBody->setSemimajorAxis(solarSystemHeavenlyBody->getSemimajorAxis());
    currentSolarSystemHeavenlyBody->setAngle(solarSystemHeavenlyBody->getAngle());
    currentSolarSystemHeavenlyBody->setOrbitalPlaneAngle(solarSystemHeavenlyBody->getOrbitalPlaneAngle());

    solarSystemHeavenlyBodyTableModel->reset();
}

/*!
 \brief Delete planet from model and repository.

*/
void SolarSystemModel::deletePlanet()
{
    solarSystemRepository->deletePlanetEntity(currentSolarSystem, currentSolarSystemHeavenlyBody);
    solarSystemHeavenlyBodyTableModel->deleteSolarSystemHeavenlyBody(currentSolarSystemHeavenlyBody);

    currentSolarSystem->removeHeavenlyBody(currentSolarSystemHeavenlyBody);

    if (solarSystemHeavenlyBodyTableModel->getEntityCount() > 0)
    {
        currentSolarSystemHeavenlyBody = solarSystemHeavenlyBodyTableModel->getSolarSystemHeavenlyBody(solarSystemHeavenlyBodySelectionModel->currentIndex().row());
    }
    else
    {
        currentSolarSystemHeavenlyBody = 0;
    }
}

/*!
 \brief Delete complete solar system.

*/
void SolarSystemModel::deleteSolarSystem()
{
    if (isEntitySelected())
    {
        solarSystemRepository->deleteEntity(currentSolarSystem);
        solarSystemTableModel->deleteSolarSystem(currentSolarSystem);

        if (solarSystemTableModel->getEntityCount() > 0)
        {
            currentSolarSystem = solarSystemTableModel->getSolarSystem(solarSystemSelectionModel->currentIndex().row());
            currentSolarSystemHeavenlyBody = 0;
        }
        else
        {
            currentSolarSystem = 0;
            currentSolarSystemHeavenlyBody = 0;
        }
    }
}
