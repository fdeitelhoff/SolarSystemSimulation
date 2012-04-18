#ifndef SOLARSYSTEMMODEL_H
#define SOLARSYSTEMMODEL_H

#include <QWidget>
#include <QItemSelectionModel>

#include "data/solarsystem/solarsystemrepository.h"
#include "model/solarsystem/solarsystemtablemodel.h"
#include "model/heavenlybody/heavenlybodycomboboxmodel.h"
#include "data/heavenlybody/heavenlybodyrepository.h"
#include "model/solarsystem/solarsystemheavenlybodytablemodel.h"

class SolarSystemModel : public QWidget
{
    Q_OBJECT

public:
    SolarSystemModel();

    void loadAllSolarSystemEntities();

    void loadOtherEntities();
    void loadEntityData();

    void setSolarSystemSelectionModel(QItemSelectionModel *selectionModel);
    void setSolarSystemHeavenlyBodySelectionModel(QItemSelectionModel *selectionModel);

    SolarSystemTableModel* getSolarSystemTableModel();
    SolarSystemHeavenlyBodyTableModel* getSolarSystemHeavenlyBodyTableModel();

    HeavenlyBodyComboBoxModel* getStarsComboBoxModel();
    HeavenlyBodyComboBoxModel* getPlanetsComboBoxModel();

    SolarSystem* getCurrentSolarSystem() { return currentSolarSystem; }
    SolarSystemHeavenlyBody* getCurrentSolarSystemHeavenlyBody() { return currentSolarSystemHeavenlyBody; }

    void createSolarSystem(QString name, int centralStarIndex);
    void updateSolarSystem(QString name, int centralStarIndex);
    void deleteSolarSystem();

    void addPlanet(int planetIndex, double excentricity, double semimajorAxis, int angle);
    void deletePlanet();

    bool isEntitySelected();

signals:
    void starSelectionChanged(const int index);

private slots:
    void currentSolarSystemRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void currentPlanetsRowChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    SolarSystemRepository *solarSystemRepository;
    HeavenlyBodyRepository *heavenlyBodyRepository;

    SolarSystemTableModel *solarSystemTableModel;
    SolarSystemHeavenlyBodyTableModel *solarSystemHeavenlyBodyTableModel;
    HeavenlyBodyComboBoxModel *starsComboBoxModel;
    HeavenlyBodyComboBoxModel *planetsComboBoxModel;

    QItemSelectionModel *solarSystemSelectionModel;
    QItemSelectionModel *solarSystemHeavenlyBodySelectionModel;

    SolarSystem *currentSolarSystem;
    SolarSystemHeavenlyBody *currentSolarSystemHeavenlyBody;
};

#endif // SOLARSYSTEMMODEL_H
