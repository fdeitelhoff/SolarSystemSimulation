#ifndef SOLARSYSTEMTABLEMODEL_H
#define SOLARSYSTEMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVariant>
#include <QList>

#include "model/solarsystem/solarsystem.h"

class SolarSystemTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    SolarSystemTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void addData(QList<SolarSystem *> entities);

    SolarSystem* getSolarSystem(int row);

    //void addHeavenlyBody(HeavenlyBody *heavenlyBody);

    //void removeHeavenlyBody(HeavenlyBody *heavenlyBody);

private:
    QList<SolarSystem *> entities;
};

#endif // SOLARSYSTEMTABLEMODEL_H
