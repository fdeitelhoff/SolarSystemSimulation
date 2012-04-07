#include "solarsystemheavenlybodytablemodel.h"

SolarSystemHeavenlyBodyTableModel::SolarSystemHeavenlyBodyTableModel()
    : QAbstractTableModel()
{
}

int SolarSystemHeavenlyBodyTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return entities.size();
}

int SolarSystemHeavenlyBodyTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 6;
}

QVariant SolarSystemHeavenlyBodyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    SolarSystemHeavenlyBody *entity = entities.at(index.row());
    QVariant value;

    switch (index.column())
    {
    case 0:
        value = QVariant(entity->getHeavenlyBody()->getId());
        break;
    case 1:
        value = QVariant(entity->getHeavenlyBody()->getName());
        break;
    case 2:
        value = QVariant(entity->getHeavenlyBody()->getDiameter());
        break;
    case 3:
        value = QVariant(entity->getHeavenlyBody()->getColor());
        break;
    case 4:
        value = QVariant(entity->getExcentricity());
        break;
    case 5:
        value = QVariant(entity->getSemimajorAxis());
        break;
    }

    return value;
}

QVariant SolarSystemHeavenlyBodyTableModel::headerData(int section, Qt::Orientation orientation,
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
        columnHeader = "Excentricity";
        break;
    case 5:
        columnHeader = "Semimajor Axis";
        break;
    }

    return columnHeader;
}

void SolarSystemHeavenlyBodyTableModel::setData(QList<SolarSystemHeavenlyBody *> entities)
{
    this->entities.append(entities);
}

SolarSystemHeavenlyBody* SolarSystemHeavenlyBodyTableModel::getSolarSystemHeavenlyBody(int row)
{
    if (row >= 0 && row < entities.size())
    {
        return entities.at(row);
    }

    return 0;
}
