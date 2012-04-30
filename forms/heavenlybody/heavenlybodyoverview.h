#ifndef HEAVENLYBODYOVERVIEW_H
#define HEAVENLYBODYOVERVIEW_H

#include <QDialog>
#include <QMessageBox>

#include "model/heavenlybody/heavenlybodymodel.h"
#include "forms/heavenlybody/heavenlybodydetails.h"
#include "forms/heavenlybody/heavenlybodyitemdelegate.h"

namespace Ui {
class HeavenlyBodyOverview;
}

class HeavenlyBodyOverview : public QDialog
{
    Q_OBJECT
    
public:
    explicit HeavenlyBodyOverview(QWidget *parent = 0, HeavenlyBodyModel *heavenlyBodyModel = 0);
    ~HeavenlyBodyOverview();

public slots:
    void on_add_clicked();
    void on_edit_clicked();
    void on_deleteEntity_clicked();

    void doubleClicked(QModelIndex modelIndex);

private:
    Ui::HeavenlyBodyOverview *ui;

    HeavenlyBodyModel *heavenlyBodyModel;

private slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif // HEAVENLYBODYOVERVIEW_H
