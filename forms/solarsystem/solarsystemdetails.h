#ifndef SOLARSYSTEMDETAILS_H
#define SOLARSYSTEMDETAILS_H

#include <QDialog>
#include <QMessageBox>

#include "model/solarsystem/solarsystemmodel.h"

namespace Ui {
class SolarSystemDetails;
}

class SolarSystemDetails : public QDialog
{
    Q_OBJECT
    
public:
    explicit SolarSystemDetails(QWidget *parent = 0, SolarSystemModel *solarSystemModel = 0, bool isEdit = false);
    ~SolarSystemDetails();

    HeavenlyBodyComboBoxModel *getHeavenlyBodyComboBoxModel();
    
private:
    Ui::SolarSystemDetails *ui;

    SolarSystemModel *solarSystemModel;

    bool isEdit;

    void setPlanetManagementActive(bool isActive);
    bool updateOrCreateSolarSystem();

private slots:
    void on_accept_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();

    void on_excentricity_valueChanged();

    void on_addPlanet_clicked();
    void on_deletePlanet_clicked();

    void starSelected(int index);

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // SOLARSYSTEMDETAILS_H
