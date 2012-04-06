#include "heavenlybodytablemodel.h"

HeavenlyBodyTableModel::HeavenlyBodyTableModel()
    : QAbstractTableModel()
{
}

int HeavenlyBodyTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return entities.size();
}

int HeavenlyBodyTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 5;
}

QVariant HeavenlyBodyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    HeavenlyBody *entity = entities.at(index.row());
    QVariant value;

    switch (index.column())
    {
    case 0:
        value = QVariant(entity->getId());
        break;
    case 1:
        value = QVariant(entity->getName());
        break;
    case 2:
        value = QVariant(entity->getDiameter());
        break;
    case 3:
        value = QVariant(entity->getColor());
        break;
    case 4:
        value = QVariant(entity->getType());
        break;
    }

    return value;
}

QVariant HeavenlyBodyTableModel::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    {
        return QVariant();
    }

    QString columnHeader;

    switch (section)
    {
    case 0:
        columnHeader = "ID";
        break;
    case 1:
        columnHeader = "Name";
        break;
    case 2:
        columnHeader = "Diameter";
        break;
    case 3:
        columnHeader = "Color";
        break;
    case 4:
        columnHeader = "Type";
        break;
    }

    return columnHeader;
}

void HeavenlyBodyTableModel::addData(QList<HeavenlyBody*> entities)
{
    this->entities.append(entities);
}

HeavenlyBody* HeavenlyBodyTableModel::getHeavenlyBody(int row)
{
    if (row >= 0 && row < entities.size())
    {
        return entities.at(row);
    }

    return 0;
}


void HeavenlyBodyTableModel::addHeavenlyBody(HeavenlyBody *heavenlyBody)
{
    if (heavenlyBody)
    {
        int size = entities.size() + 1;

        beginInsertRows(QModelIndex(), size, size);
        entities.append(heavenlyBody);
        endInsertRows();
    }
}

void HeavenlyBodyTableModel::removeHeavenlyBody(HeavenlyBody *heavenlyBody)
{
    if (heavenlyBody)
    {
        int size = entities.size() - 1;

        beginRemoveRows(QModelIndex(), size, size);
        entities.removeOne(heavenlyBody);
        endRemoveRows();
    }
}
