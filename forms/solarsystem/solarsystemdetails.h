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

#ifndef SOLARSYSTEMDETAILS_H
#define SOLARSYSTEMDETAILS_H

#include <QDialog>
#include <QMessageBox>

#include "model/solarsystem/solarsystemmodel.h"
#include "forms/solarsystem/solarsystemitemdelegate.h"

namespace Ui {
class SolarSystemDetails;
}

/**
    Class with components to enable the window solar system details.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class SolarSystemDetails : public QDialog
{
    Q_OBJECT
    
public:
    explicit SolarSystemDetails(QWidget *parent = 0, SolarSystemModel *solarSystemModel = 0, bool isEdit = false);
    ~SolarSystemDetails();

    HeavenlyBodyComboBoxModel *getHeavenlyBodyComboBoxModel();
    
private:
    Ui::SolarSystemDetails *ui;

    SolarSystemModel *solarSystemModel;

    bool isEdit;

    void setPlanetManagementActive(bool isActive);
    bool updateOrCreateSolarSystem();
    void updateOrCreatePlanet(bool isUpdate);

private slots:
    void on_accept_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();

    void on_excentricity_valueChanged();

    void on_addPlanet_clicked();
    void on_editPlanet_clicked();
    void on_deletePlanet_clicked();

    void starSelected(int index);

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void currentPlanetsRowChanged(const QModelIndex &current, const QModelIndex &previous);
};

#endif // SOLARSYSTEMDETAILS_H
