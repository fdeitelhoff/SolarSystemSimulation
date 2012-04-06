#ifndef HEAVENLYBODYMODEL_H
#define HEAVENLYBODYMODEL_H

#include <QWidget>
#include <QList>
#include <QItemSelectionModel>
#include <QModelIndex>

#include "data/heavenlybody/heavenlybodyrepository.h"
#include "data/heavenlybody/heavenlybodytablemodel.h"
#include "data/heavenlybody/heavenlybody.h"

class HeavenlyBodyModel : public QWidget
{
    Q_OBJECT

public:
    HeavenlyBodyModel();

    void loadAllHeavenlyBodyEntities();

    HeavenlyBodyTableModel* getHeavenlyBodyTableModel();

    void setSelectionModel(QItemSelectionModel *selectionModel);

    HeavenlyBody* getSelectedEntity() { return selectedEntity; }

    void addEntity(HeavenlyBody *heavenlyBody);
    void updateEntity(HeavenlyBody *heavenlyBody);
    void deleteEntity();

private slots:
    void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    HeavenlyBodyRepository *heavenlyBodyRepository;
    HeavenlyBodyTableModel *heavenlyBodyTableModel;

    QItemSelectionModel *selectionModel;
    HeavenlyBody *selectedEntity;
};

#endif // HEAVENLYBODYMODEL_H
