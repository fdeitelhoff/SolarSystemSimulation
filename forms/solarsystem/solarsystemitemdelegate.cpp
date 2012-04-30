#include "solarsystemitemdelegate.h"

SolarSystemItemDelegate::SolarSystemItemDelegate(SolarSystemModel *solarSystemModel)
{
    this->solarSystemModel = solarSystemModel;
}

void SolarSystemItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.column() == 3)
    {
        SolarSystemHeavenlyBody *solarSystemHeavenlyBody = solarSystemModel->getSolarSystemHeavenlyBodyTableModel()->getSolarSystemHeavenlyBody(index.row());

        if (solarSystemHeavenlyBody)
        {
            painter->fillRect(option.rect, solarSystemHeavenlyBody->getHeavenlyBody()->getColor());
        }
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}
