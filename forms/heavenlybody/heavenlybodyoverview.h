#ifndef HEAVENLYBODYOVERVIEW_H
#define HEAVENLYBODYOVERVIEW_H

#include <QDialog>
#include "model/heavenlybody/heavenlybodymodel.h"

namespace Ui {
class HeavenlyBodyOverview;
}

class HeavenlyBodyOverview : public QDialog
{
    Q_OBJECT
    
public:
    explicit HeavenlyBodyOverview(QWidget *parent = 0);
    ~HeavenlyBodyOverview();
    
private:
    Ui::HeavenlyBodyOverview *ui;

    HeavenlyBodyModel *heavenlyBodyModel;
};

#endif // HEAVENLYBODYOVERVIEW_H
