#ifndef SOLARSYSTEMDETAILS_H
#define SOLARSYSTEMDETAILS_H

#include <QDialog>

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
    double currentExcentricity;

    void setPlanetManagementActive(bool isActive);

private slots:
    void on_accept_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();

    void on_excentricity_valueChanged();

    void on_addPlanet_clicked();
    void on_deletePlanet_clicked();

    void on_starSelectionChanged(int index);
};

#endif // SOLARSYSTEMDETAILS_H
