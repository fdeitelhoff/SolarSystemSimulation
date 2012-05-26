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

#ifndef HEAVENLYBODYDETAILS_H
#define HEAVENLYBODYDETAILS_H

#include <QDialog>
#include <QColorDialog>
#include <QMessageBox>

#include "model/heavenlybody/heavenlybodymodel.h"

namespace Ui {
class HeavenlyBodyDetails;
}

/**
    Class for the components to show the window heavenly body details.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBodyDetails : public QDialog
{
    Q_OBJECT
    
public:
    HeavenlyBodyDetails(QWidget *parent = 0, HeavenlyBodyModel *heavenlyBodyModel = 0, bool edit = false);

    ~HeavenlyBodyDetails();
    
private:
    Ui::HeavenlyBodyDetails *ui;

    bool isEdit;

    HeavenlyBodyModel *heavenlyBodyModel;

    HeavenlyBody *currentEntity;

    QColorDialog *colorDialog;
    QColor tmpColor;

private slots:
    void on_chooseColor_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // HEAVENLYBODYDETAILS_H
