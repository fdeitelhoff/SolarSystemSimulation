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

#include "heavenlybodyitemdelegate.h"

/*!
 \brief Set an other color to collumn 3 (color) when row is selected.

 \param heavenlyBodyModel
*/
HeavenlyBodyItemDelegate::HeavenlyBodyItemDelegate(HeavenlyBodyModel *heavenlyBodyModel)
{
    this->heavenlyBodyModel = heavenlyBodyModel;
}

/*!
 \brief Set the color of the selected color-collumn to the color of the heavenly body. Others to default.

 \param painter Paint options
 \param option Style options.
 \param index Selected row.
*/
void HeavenlyBodyItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.column() == 3)
    {
        HeavenlyBody *heavenlyBody = heavenlyBodyModel->getHeavenlyBodyTableModel()->getHeavenlyBody(index.row());

        if (heavenlyBody)
        {
            painter->fillRect(option.rect, heavenlyBody->getColor());
        }
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}
