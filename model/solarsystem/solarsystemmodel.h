#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include "data/solarsystem/solarsystemrepository.h"
#include "model/solarsystem/solarsystemtablemodel.h"
#include "model/heavenlybody/heavenlybodycomboboxmodel.h"
#include "data/heavenlybody/heavenlybodyrepository.h"

class SolarSystemModel
{

public:
    SolarSystemModel();

    SolarSystemTableModel* getSolarSystemTableModel();

    void loadAllSolarSystemEntities();

    void loadOtherEntities();

    HeavenlyBodyComboBoxModel* getStarsComboBoxModel();
    HeavenlyBodyComboBoxModel* getPlanetsComboBoxModel();

private:
    SolarSystemRepository *solarSystemRepository;
    SolarSystemTableModel *solarSystemTableModel;

    HeavenlyBodyRepository *heavenlyBodyRepository;

    HeavenlyBodyComboBoxModel *starsComboBoxModel;
    HeavenlyBodyComboBoxModel *planetsComboBoxModel;
};

#endif // SOLARSYSTEMMODEL_H
