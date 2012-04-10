#include "solarsystemtablemodel.h"

SolarSystemTableModel::SolarSystemTableModel()
    : QAbstractTableModel()
{
}

int SolarSystemTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return entities.size();
}

int SolarSystemTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

QVariant SolarSystemTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    SolarSystem *entity = entities.at(index.row());
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
        value = QVariant(entity->getCentralStar()->getName());
        break;
    case 3:
        value = QVariant(entity->getPlanetCount());
        break;
    }

    return value;
}

QVariant SolarSystemTableModel::headerData(int section, Qt::Orientation orientation,
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
        columnHeader = "Central Star";
        break;
    case 3:
        columnHeader = "Planet count";
        break;
    }

    return columnHeader;
}

void SolarSystemTableModel::setData(QList<SolarSystem *> entities)
{
    this->entities.clear();
    this->entities.append(entities);
}

SolarSystem* SolarSystemTableModel::getSolarSystem(int row)
{
    if (row >= 0 && row < entities.size())
    {
        return entities.at(row);
    }

    return 0;
}

void SolarSystemTableModel::addSolarSystem(SolarSystem *solarSystem)
{
    if (solarSystem)
    {
        int size = entities.size() + 1;

        beginInsertRows(QModelIndex(), size, size);
        entities.append(solarSystem);
        endInsertRows();
    }
}

void SolarSystemTableModel::deleteSolarSystem(SolarSystem *solarSystem)
{
    if (solarSystem)
    {
        int size = entities.size() - 1;

        beginRemoveRows(QModelIndex(), size, size);
        entities.removeOne(solarSystem);
        endRemoveRows();
    }
}
