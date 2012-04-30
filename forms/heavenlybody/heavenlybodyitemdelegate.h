#ifndef HEAVENLYBODYITEMDELEGATE_H
#define HEAVENLYBODYITEMDELEGATE_H

#include <QItemDelegate>
#include <QPainter>

#include "model/heavenlybody/heavenlybodymodel.h"

class HeavenlyBodyItemDelegate : public QItemDelegate
{

private:
    HeavenlyBodyModel *heavenlyBodyModel;

public:
    HeavenlyBodyItemDelegate(HeavenlyBodyModel *heavenlyBodyModel);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // HEAVENLYBODYITEMDELEGATE_H
