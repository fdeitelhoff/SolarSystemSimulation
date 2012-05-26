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

#ifndef HEAVENLYBODYITEMDELEGATE_H
#define HEAVENLYBODYITEMDELEGATE_H

#include <QItemDelegate>
#include <QPainter>

#include "model/heavenlybody/heavenlybodymodel.h"

/**
    Class to enable an other color view in selected rows.

    @author Fabian Deitelhoff <FH@FabianDeitelhoff.de>
    @author Christof Geisler <christof.geisler@stud.fh-swf.de>
*/

class HeavenlyBodyItemDelegate : public QItemDelegate
{

private:
    HeavenlyBodyModel *heavenlyBodyModel;

public:
    HeavenlyBodyItemDelegate(HeavenlyBodyModel *heavenlyBodyModel);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // HEAVENLYBODYITEMDELEGATE_H
