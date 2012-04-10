#ifndef HEAVENLYBODYCOMBOBOXMODEL_H
#define HEAVENLYBODYCOMBOBOXMODEL_H

#include <QDebug>
#include <QAbstractItemModel>

#include "model/heavenlybody/heavenlybody.h"

class HeavenlyBodyComboBoxModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    HeavenlyBodyComboBoxModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &index = QModelIndex()) const;
    int columnCount(const QModelIndex &index = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setData(QList<HeavenlyBody *> entities);

    HeavenlyBody* getHeavenlyBody(int index);
    int getHeavenlyBodyIndex(HeavenlyBody *heavenlyBody);

private:
    QList<HeavenlyBody *> entities;
};

#endif // HEAVENLYBODYCOMBOBOXMODEL_H
