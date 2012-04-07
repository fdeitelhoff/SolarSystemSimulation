#include "heavenlybodycomboboxmodel.h"

HeavenlyBodyComboBoxModel::HeavenlyBodyComboBoxModel()
    : QAbstractItemModel()
{
}

QModelIndex HeavenlyBodyComboBoxModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( column < 0 || row < 0 )
    {
        return QModelIndex();
    }

    return createIndex(row, column, entities.at(row));
}

QModelIndex HeavenlyBodyComboBoxModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int HeavenlyBodyComboBoxModel::rowCount(const QModelIndex &index) const
{
    return entities.size();
}

int HeavenlyBodyComboBoxModel::columnCount(const QModelIndex &index) const
{
    return 1;
}

QVariant HeavenlyBodyComboBoxModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    return entities.at(index.row())->getName();
}

void HeavenlyBodyComboBoxModel::setData(QList<HeavenlyBody *> entities)
{
    this->entities.append(entities);
}
