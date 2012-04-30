#ifndef SOLARSYSTEMITEMDELEGATE_H
#define SOLARSYSTEMITEMDELEGATE_H

#include <QItemDelegate>
#include <QPainter>

#include "model/solarsystem/solarsystemmodel.h"

class SolarSystemItemDelegate : public QItemDelegate
{

private:
    SolarSystemModel *solarSystemModel;

public:
    SolarSystemItemDelegate(SolarSystemModel *solarSystemModel);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // SOLARSYSTEMITEMDELEGATE_H
