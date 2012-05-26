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

#ifndef HEAVENLYBODYOVERVIEW_H
#define HEAVENLYBODYOVERVIEW_H

#include <QDialog>
#include <QMessageBox>

#include "model/heavenlybody/heavenlybodymodel.h"
#include "forms/heavenlybody/heavenlybodydetails.h"
#include "forms/heavenlybody/heavenlybodyitemdelegate.h"

namespace Ui {
class HeavenlyBodyOverview;
}

/**
    Class with components to show the window heavenly body overview.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBodyOverview : public QDialog
{
    Q_OBJECT
    
public:
    explicit HeavenlyBodyOverview(QWidget *parent = 0, HeavenlyBodyModel *heavenlyBodyModel = 0);
    ~HeavenlyBodyOverview();

public slots:
    void on_add_clicked();
    void on_edit_clicked();
    void on_deleteEntity_clicked();

    void doubleClicked(QModelIndex modelIndex);

private:
    Ui::HeavenlyBodyOverview *ui;

    HeavenlyBodyModel *heavenlyBodyModel;

private slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // HEAVENLYBODYOVERVIEW_H
