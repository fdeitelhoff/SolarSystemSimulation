#ifndef SOLARSYSTEMOVERVIEW_H
#define SOLARSYSTEMOVERVIEW_H

#include <QDialog>
#include <QObject>

#include "model/solarsystem/solarsystemmodel.h"
#include "forms/solarsystem/solarsystemdetails.h"

namespace Ui {
class SolarSystemOverview;
}

class SolarSystemOverview : public QDialog
{
    Q_OBJECT
    
public:
    explicit SolarSystemOverview(QWidget *parent = 0, SolarSystemModel *solarSystemModel = 0);
    ~SolarSystemOverview();
    
private:
    Ui::SolarSystemOverview *ui;

    SolarSystemModel *solarSystemModel;

signals:
    void simulateSolarSystem(SolarSystem *solarSystem);

private slots:
    void on_add_clicked();
    void on_edit_clicked();
    void on_deleteEntity_clicked();

    void on_startSimulation_clicked();

    void doubleClicked(QModelIndex modelIndex);
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // SOLARSYSTEMOVERVIEW_H
