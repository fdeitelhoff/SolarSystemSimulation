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

#ifndef SOLARSYSTEMOVERVIEW_H
#define SOLARSYSTEMOVERVIEW_H

#include <QDialog>
#include <QObject>

#include "model/solarsystem/solarsystemmodel.h"
#include "forms/solarsystem/solarsystemdetails.h"

namespace Ui {
class SolarSystemOverview;
}

/**
    Class with components to show the solar system overview.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class SolarSystemOverview : public QDialog
{
    Q_OBJECT
    
public:
    explicit SolarSystemOverview(QWidget *parent = 0, SolarSystemModel *solarSystemModel = 0);
    ~SolarSystemOverview();
    
private:
    Ui::SolarSystemOverview *ui;

    SolarSystemModel *solarSystemModel;

    void showSolarSystemDetails(bool isEdit);

signals:
    void simulateSolarSystem(SolarSystem *solarSystem);

private slots:
    void on_add_clicked();
    void on_edit_clicked();
    void on_deleteEntity_clicked();

    void on_startSimulation_clicked();

    void doubleClicked(QModelIndex modelIndex);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // SOLARSYSTEMOVERVIEW_H
