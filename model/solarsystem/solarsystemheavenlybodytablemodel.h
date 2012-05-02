#ifndef SOLARSYSTEMHEAVENLYBODYTABLEMODEL_H
#define SOLARSYSTEMHEAVENLYBODYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVariant>
#include <QList>

#include "model/solarsystem/solarsystemheavenlybody.h"

class SolarSystemHeavenlyBodyTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    SolarSystemHeavenlyBodyTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void setData(QList<SolarSystemHeavenlyBody *> entities);

    void addSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);
    void deleteSolarSystemHeavenlyBody(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

    SolarSystemHeavenlyBody* getSolarSystemHeavenlyBody(int row);

    int getEntityCount() { return entities.size(); }

    int getSolarSystemHeavenlyBodyIndex(SolarSystemHeavenlyBody *solarSystemHeavenlyBody);

    void reset();

    void resetData();

private:
    QList<SolarSystemHeavenlyBody *> entities;
};

#endif // SOLARSYSTEMHEAVENLYBODYTABLEMODEL_H
