#include "heavenlybodymodel.h"

HeavenlyBodyModel::HeavenlyBodyModel()
{
    heavenlyBodyRepository = new HeavenlyBodyRepository();

    heavenlyBodyTableModel = 0;
    selectedEntity = 0;
}

void HeavenlyBodyModel::loadAllHeavenlyBodyEntities()
{
    HeavenlyBodyTableModel *heavenlyBodyTableModel = getHeavenlyBodyTableModel();

    QList<HeavenlyBody *> entities = heavenlyBodyRepository->fetchAllHeavenlyBodyEntities();

    heavenlyBodyTableModel->setData(entities);
}

void HeavenlyBodyModel::setSelectionModel(QItemSelectionModel *selectionModel)
{
    this->selectionModel = selectionModel;
    QObject::connect(this->selectionModel,
                     SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this,
                     SLOT(currentRowChanged(QModelIndex,QModelIndex)),
                     Qt::DirectConnection);
}

void HeavenlyBodyModel::currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.row() >= 0)
    {
        selectedEntity = heavenlyBodyTableModel->getHeavenlyBody(current.row());
    }
}

HeavenlyBodyTableModel* HeavenlyBodyModel::getHeavenlyBodyTableModel()
{
    if (!heavenlyBodyTableModel)
    {
        heavenlyBodyTableModel = new HeavenlyBodyTableModel();
    }

    return heavenlyBodyTableModel;
}

void HeavenlyBodyModel::updateEntity(HeavenlyBody *heavenlyBody)
{
    heavenlyBodyRepository->updateEntity(heavenlyBody);
}

void HeavenlyBodyModel::addEntity(HeavenlyBody *heavenlyBody)
{
    heavenlyBodyRepository->addEntity(heavenlyBody);

    heavenlyBodyTableModel->addHeavenlyBody(heavenlyBody);
}

void HeavenlyBodyModel::deleteEntity()
{
    if (selectedEntity)
    {
        heavenlyBodyRepository->deleteEntity(selectedEntity);
        heavenlyBodyTableModel->removeHeavenlyBody(selectedEntity);

        if (heavenlyBodyTableModel->getEntityCount() == 0)
        {
            selectedEntity = 0;
        }
    }
}
