#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include "data/solarsystem/solarsystemrepository.h"
#include "model/solarsystem/solarsystemtablemodel.h"

class SolarSystemModel
{

public:
    SolarSystemModel();

    SolarSystemTableModel* getSolarSystemTableModel();

    void loadAllSolarSystemEntities();

private:
    SolarSystemRepository *solarSystemRepository;
    SolarSystemTableModel *solarSystemTableModel;
};

#endif // SOLARSYSTEMMODEL_H
