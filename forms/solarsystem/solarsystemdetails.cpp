#include "solarsystemdetails.h"
#include "ui_solarsystemdetails.h"

SolarSystemDetails::SolarSystemDetails(QWidget *parent, SolarSystemModel *solarSystemModel, bool isEdit) :
    QDialog(parent),
    ui(new Ui::SolarSystemDetails)
{
    ui->setupUi(this);

    this->solarSystemModel = solarSystemModel;

    this->isEdit = isEdit;

    QObject::connect(this->solarSystemModel,
                     SIGNAL(starSelectionChanged(int)),
                     this,
                     SLOT(on_starSelectionChanged(int)),
                     Qt::DirectConnection);

    ui->planetsTableView->setModel(solarSystemModel->getSolarSystemHeavenlyBodyTableModel());
    ui->stars->setModel(solarSystemModel->getStarsComboBoxModel());
    ui->planets->setModel(solarSystemModel->getPlanetsComboBoxModel());

    solarSystemModel->setSolarSystemHeavenlyBodySelectionModel(ui->planetsTableView->selectionModel());

    solarSystemModel->loadOtherEntities();

    ui->planets->setCurrentIndex(0);
    ui->stars->setCurrentIndex(0);

    currentExcentricity = 0;

    if (isEdit)
    {
        ui->name->setText(solarSystemModel->getCurrentSolarSystem()->getName());

        solarSystemModel->loadEntityData();

        setPlanetManagementActive(true);

        setWindowTitle(QString("Edit Solar System '%1'").arg(solarSystemModel->getCurrentSolarSystem()->getName()));
    }
}

SolarSystemDetails::~SolarSystemDetails()
{
    delete ui;
}

void SolarSystemDetails::setPlanetManagementActive(bool isActive)
{
    ui->planetsTableView->setEnabled(isActive);
    ui->deletePlanet->setEnabled(isActive);
    ui->planets->setEnabled(isActive);
    ui->excentricity->setEnabled(isActive);
    ui->semimajorAxis->setEnabled(isActive);
    ui->angle->setEnabled(isActive);
    ui->addPlanet->setEnabled(isActive);
}

void SolarSystemDetails::on_starSelectionChanged(int index)
{
    ui->stars->setCurrentIndex(index);
}

void SolarSystemDetails::on_excentricity_valueChanged()
{
    currentExcentricity = ui->excentricity->value() / 100.0;
    ui->excentricityLabel->setText("Excentricity: " + QString::number(currentExcentricity));
}

void SolarSystemDetails::on_cancel_clicked()
{
    close();
}

void SolarSystemDetails::on_accept_clicked()
{
    if (!isEdit)
    {
        solarSystemModel->createSolarSystem(ui->name->text(), ui->stars->currentIndex());
        setPlanetManagementActive(true);

        isEdit = true;
    }
    else
    {
        solarSystemModel->updateSolarSystem(ui->name->text(), ui->stars->currentIndex());
    }
}

void SolarSystemDetails::on_ok_clicked()
{
    if (!isEdit)
    {
        solarSystemModel->createSolarSystem(ui->name->text(), ui->stars->currentIndex());
    }
    else
    {
        solarSystemModel->updateSolarSystem(ui->name->text(), ui->stars->currentIndex());
    }

    close();
}

void SolarSystemDetails::on_addPlanet_clicked()
{
    solarSystemModel->addPlanet(ui->planets->currentIndex(),
                                currentExcentricity,
                                ui->semimajorAxis->text().toDouble(),
                                ui->angle->text().toInt());
}

void SolarSystemDetails::on_deletePlanet_clicked()
{
    solarSystemModel->deletePlanet();
}
