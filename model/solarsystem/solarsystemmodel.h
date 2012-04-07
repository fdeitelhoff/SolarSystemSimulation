#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include "data/solarsystem/solarsystemrepository.h"
#include "model/solarsystem/solarsystemtablemodel.h"
#include "model/heavenlybody/heavenlybodycomboboxmodel.h"
#include "data/heavenlybody/heavenlybodyrepository.h"
#include "model/solarsystem/solarsystemheavenlybodytablemodel.h"

class SolarSystemModel
{

public:
    SolarSystemModel();

    void loadAllSolarSystemEntities();

    void loadOtherEntities();

    SolarSystemTableModel* getSolarSystemTableModel();
    SolarSystemHeavenlyBodyTableModel* getSolarSystemHeavenlyBodyTableModel();

    HeavenlyBodyComboBoxModel* getStarsComboBoxModel();
    HeavenlyBodyComboBoxModel* getPlanetsComboBoxModel();

private:
    SolarSystemRepository *solarSystemRepository;
    HeavenlyBodyRepository *heavenlyBodyRepository;

    SolarSystemTableModel *solarSystemTableModel;
    SolarSystemHeavenlyBodyTableModel *solarSystemHeavenlyBodyTableModel;
    HeavenlyBodyComboBoxModel *starsComboBoxModel;
    HeavenlyBodyComboBoxModel *planetsComboBoxModel;
};

#endif // SOLARSYSTEMMODEL_H
