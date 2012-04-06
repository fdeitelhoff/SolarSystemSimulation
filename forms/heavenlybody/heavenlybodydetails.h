#ifndef HEAVENLYBODYDETAILS_H
#define HEAVENLYBODYDETAILS_H

#include <QDialog>
#include <QColorDialog>

#include "model/heavenlybody/heavenlybodymodel.h"

namespace Ui {
class HeavenlyBodyDetails;
}

class HeavenlyBodyDetails : public QDialog
{
    Q_OBJECT
    
public:
    HeavenlyBodyDetails(QWidget *parent = 0, HeavenlyBodyModel *heavenlyBodyModel = 0, bool edit = false);

    ~HeavenlyBodyDetails();
    
private:
    Ui::HeavenlyBodyDetails *ui;

    bool isEdit;

    HeavenlyBodyModel *heavenlyBodyModel;

    HeavenlyBody *currentEntity;

    QColorDialog *colorDialog;
    QColor tmpColor;

private slots:
    void on_chooseColor_clicked();
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // HEAVENLYBODYDETAILS_H
