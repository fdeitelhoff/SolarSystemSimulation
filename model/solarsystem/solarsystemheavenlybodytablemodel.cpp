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
    return 8;
}

void SolarSystemHeavenlyBodyTableModel::reset()
{
    QAbstractTableModel::reset();
}

QVariant SolarSystemHeavenlyBodyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    SolarSystemHeavenlyBody *entity = entities.at(index.row());

    if (role == Qt::DisplayRole)
    {
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
            value = QVariant(QString("%L1").arg(entity->getHeavenlyBody()->getDiameter()));
            break;
        case 4:
            value = QVariant(entity->getNumericExcentricity());
            break;
        case 5:
            value = QVariant(entity->getSemimajorAxis());
            break;
        case 6:
            value = QVariant(entity->getAngle());
            break;
        case 7:
            value = QVariant(entity->getOrbitalPlaneAngle());
            break;
        }

        return value;
    }
    else if (role == Qt::TextAlignmentRole)
    {
        QVariant value;

        switch (index.column())
        {
        case 0:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 2:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 4:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 5:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 6:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        case 7:
            value = QVariant(Qt::AlignRight | Qt::AlignVCenter);
            break;
        default:
            value = QVariant(Qt::AlignLeft | Qt::AlignVCenter);
            break;
        }

        return value;
    }
    else if (role == Qt::BackgroundRole)
    {
        if (index.column() == 3)
        {
            return QVariant(entity->getHeavenlyBody()->getColor());
        }
        else
        {
            return QVariant(QColor(Qt::white));
        }
    }
    else
    {
        return QVariant();
    }
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
    case 6:
        columnHeader = "Angle";
        break;
    case 7:
        columnHeader = "Orbital Plane Angle";
        break;
    }

    return columnHeader;
}

void SolarSystemHeavenlyBodyTableModel::setData(QList<SolarSystemHeavenlyBody *> entities)
{
    this->entities.clear();
    this->entities.append(entities);

    reset();
}

SolarSystemHeavenlyBody* SolarSystemHeavenlyBodyTableModel::getSolarSystemHeavenlyBody(int row)
{
    if (row >= 0 && row < entities.size())
    {
        return entities.at(row);
    }

    return 0;
}

void SolarSystemHeavenlyBodyTableModel::addSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        int size = entities.size() + 1;

        beginInsertRows(QModelIndex(), size, size);
        entities.append(solarSystemHeavenlyBody);
        endInsertRows();
    }
}

void SolarSystemHeavenlyBodyTableModel::deleteSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (solarSystemHeavenlyBody)
    {
        int size = entities.size() - 1;

        beginRemoveRows(QModelIndex(), size, size);
        entities.removeOne(solarSystemHeavenlyBody);
        endRemoveRows();
    }
}

int SolarSystemHeavenlyBodyTableModel::getSolarSystemHeavenlyBodyIndex(SolarSystemHeavenlyBody *solarSystemHeavenlyBody)
{
    if (!solarSystemHeavenlyBody)
    {
        return -1;
    }

    int row = -1;
    foreach(SolarSystemHeavenlyBody *entity, entities)
    {
        row++;
        if ((*entity) == (*solarSystemHeavenlyBody))
        {
            break;
        }
    }

    return row;
}
