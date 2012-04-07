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

private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // SOLARSYSTEMDETAILS_H
