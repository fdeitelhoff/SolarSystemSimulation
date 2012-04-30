#include "heavenlybodyitemdelegate.h"

HeavenlyBodyItemDelegate::HeavenlyBodyItemDelegate(HeavenlyBodyModel *heavenlyBodyModel)
{
    this->heavenlyBodyModel = heavenlyBodyModel;
}

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
