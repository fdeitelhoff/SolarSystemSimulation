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

void HeavenlyBodyModel::updateEntity(QString name, int diameter, QColor color, QString type)
{
    selectedEntity->setName(name);
    selectedEntity->setDiameter(diameter);
    selectedEntity->setColor(color);
    selectedEntity->setType(type);

    heavenlyBodyRepository->updateEntity(selectedEntity);
}

void HeavenlyBodyModel::addEntity(QString name, int diameter, QColor color, QString type)
{
    HeavenlyBody *heavenlyBody = new HeavenlyBody(name, diameter, color, type);

    heavenlyBodyRepository->addEntity(heavenlyBody);

    heavenlyBodyTableModel->addHeavenlyBody(heavenlyBody);
}

void HeavenlyBodyModel::deleteEntity()
{
    if (isEntitySelected())
    {
        heavenlyBodyRepository->deleteEntity(selectedEntity);
        heavenlyBodyTableModel->removeHeavenlyBody(selectedEntity);

        if (heavenlyBodyTableModel->getEntityCount() == 0)
        {
            selectedEntity = 0;
        }
    }
}
