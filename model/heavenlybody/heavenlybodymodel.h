#ifndef HEAVENLYBODYMODEL_H
#define HEAVENLYBODYMODEL_H

#include <QWidget>
#include <QList>
#include <QItemSelectionModel>
#include <QModelIndex>

#include "data/heavenlybody/heavenlybodyrepository.h"
#include "model/heavenlybody/heavenlybodytablemodel.h"
#include "model/heavenlybody/heavenlybody.h"

class HeavenlyBodyModel : public QWidget
{
    Q_OBJECT

public:
    HeavenlyBodyModel();

    void loadAllHeavenlyBodyEntities();

    HeavenlyBodyTableModel* getHeavenlyBodyTableModel();

    void setSelectionModel(QItemSelectionModel *selectionModel);

    HeavenlyBody* getSelectedEntity() { return selectedEntity; }
    bool isEntitySelected() { return selectedEntity != 0; }

    void addEntity(QString name, int diameter, QColor color, QString type);
    void updateEntity(QString name, int diameter, QColor color, QString type);
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
