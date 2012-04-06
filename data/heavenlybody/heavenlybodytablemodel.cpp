#include "heavenlybodytablemodel.h"

HeavenlyBodyTableModel::HeavenlyBodyTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int HeavenlyBodyTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return rowList.size();
}

int HeavenlyBodyTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return rowList[0].size();
}

QVariant HeavenlyBodyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return rowList[index.row()][index.column()];
    else
        return QVariant();
}

QVariant HeavenlyBodyTableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}
