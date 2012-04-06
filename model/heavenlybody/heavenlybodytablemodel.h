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

    void addData(QList<HeavenlyBody *> entities);

    HeavenlyBody* getHeavenlyBody(int row);

    void addHeavenlyBody(HeavenlyBody *heavenlyBody);

    void removeHeavenlyBody(HeavenlyBody *heavenlyBody);

//    Qt::ItemFlags flags(const QModelIndex &index) const;
//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole);

//    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
//    bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
//    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
//    bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex());

private:
    QList<HeavenlyBody *> entities;
};

#endif // HEAVENLYBODYTABLEMODEL_H
