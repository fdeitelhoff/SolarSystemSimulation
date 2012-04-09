#ifndef SOLARSYSTEMOVERVIEW_H
#define SOLARSYSTEMOVERVIEW_H

#include <QDialog>

#include "model/solarsystem/solarsystemmodel.h"
#include "forms/solarsystem/solarsystemdetails.h"

namespace Ui {
class SolarSystemOverview;
}

class SolarSystemOverview : public QDialog
{
    Q_OBJECT
    
public:
    explicit SolarSystemOverview(QWidget *parent = 0);
    ~SolarSystemOverview();
    
private:
    Ui::SolarSystemOverview *ui;

    SolarSystemModel *solarSystemModel;

private slots:
    void on_add_clicked();
    void on_edit_clicked();
    void on_deleteEntity_clicked();
};

#endif // SOLARSYSTEMOVERVIEW_H
