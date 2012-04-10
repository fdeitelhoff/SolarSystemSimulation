#ifndef HEAVENLYBODYTABLEMODEL_H
#define HEAVENLYBODYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QVariant>
#include <QList>

#include "model/heavenlybody/heavenlybody.h"

class HeavenlyBodyTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    HeavenlyBodyTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    void setData(QList<HeavenlyBody *> entities);

    HeavenlyBody* getHeavenlyBody(int row);

    void addHeavenlyBody(HeavenlyBody *heavenlyBody);

    void removeHeavenlyBody(HeavenlyBody *heavenlyBody);

    int getEntityCount() { return entities.size(); }

private:
    QList<HeavenlyBody *> entities;
};

#endif // HEAVENLYBODYTABLEMODEL_H
