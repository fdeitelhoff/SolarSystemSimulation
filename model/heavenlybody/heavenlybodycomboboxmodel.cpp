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

    return createIndex(row, column); //, entities.at(row));
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
    this->entities.clear();
    this->entities.append(entities);

    reset();
}

HeavenlyBody* HeavenlyBodyComboBoxModel::getHeavenlyBody(int index)
{
    if (index < 0 || index >= entities.size())
    {
        return 0;
    }

    return entities.at(index);
}

int HeavenlyBodyComboBoxModel::getHeavenlyBodyIndex(HeavenlyBody *heavenlyBody)
{
    if (!heavenlyBody)
    {
        return -1;
    }

    int row = -1;
    foreach(HeavenlyBody *entity, entities)
    {
        row++;
        if ((*entity) == (*heavenlyBody))
        {
            break;
        }
    }

    return row;
}
