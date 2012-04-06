#ifndef SOLARSYSTEMDETAILS_H
#define SOLARSYSTEMDETAILS_H

#include <QDialog>

namespace Ui {
class SolarSystemDetails;
}

class SolarSystemDetails : public QDialog
{
    Q_OBJECT
    
public:
    explicit SolarSystemDetails(QWidget *parent = 0);
    ~SolarSystemDetails();
    
private:
    Ui::SolarSystemDetails *ui;
};

#endif // SOLARSYSTEMDETAILS_H
