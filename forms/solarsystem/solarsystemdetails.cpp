#include "solarsystemdetails.h"
#include "ui_solarsystemdetails.h"

SolarSystemDetails::SolarSystemDetails(QWidget *parent, SolarSystemModel *solarSystemModel, bool isEdit) :
    QDialog(parent),
    ui(new Ui::SolarSystemDetails)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    setWindowFlags(windowFlags() ^ Qt::WindowMaximizeButtonHint);

    QObject::connect(ui->stars,
                     SIGNAL(currentIndexChanged(int)),
                     this,
                     SLOT(starSelected(int)),
                     Qt::DirectConnection);

    this->solarSystemModel = solarSystemModel;

    this->isEdit = isEdit;

    ui->planetsTableView->setModel(solarSystemModel->getSolarSystemHeavenlyBodyTableModel());
    ui->stars->setModel(solarSystemModel->getStarsComboBoxModel());
    ui->planets->setModel(solarSystemModel->getPlanetsComboBoxModel());

    solarSystemModel->setSolarSystemHeavenlyBodySelectionModel(ui->planetsTableView->selectionModel());

    connect(ui->planetsTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,
            SLOT(currentPlanetsRowChanged(QModelIndex,QModelIndex)),
            Qt::DirectConnection);

    if (solarSystemModel->getStarsComboBoxModel()->rowCount() > 0)
    {
        ui->stars->setCurrentIndex(0);
    }

    if (isEdit)
    {
        ui->name->setText(solarSystemModel->getCurrentSolarSystem()->getName());

        solarSystemModel->loadEntityData();

        setPlanetManagementActive(true);

        setWindowTitle(QString("Edit Solar System '%1'").arg(solarSystemModel->getCurrentSolarSystem()->getName()));

        ui->stars->setCurrentIndex(solarSystemModel->getSelectedStarIndex());
    }

    QObject::connect(ui->planetsTableView->selectionModel(),
                     SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     this,
                     SLOT(selectionChanged(QItemSelection,QItemSelection)),
                     Qt::DirectConnection);

    if (solarSystemModel->getPlanetsComboBoxModel()->rowCount() > 0)
    {
        ui->planets->setCurrentIndex(0);
    }

    ui->planetsTableView->setColumnWidth(0, 50);
}

SolarSystemDetails::~SolarSystemDetails()
{
    delete ui;
}

void SolarSystemDetails::currentPlanetsRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    SolarSystemHeavenlyBody *solarSystemHeavenlyBody = solarSystemModel->getCurrentSolarSystemHeavenlyBody();

    if (solarSystemHeavenlyBody)
    {
        ui->planets->setCurrentIndex(solarSystemModel->getSelectedHeavenlyBodyIndex());
        ui->excentricity->setValue(solarSystemHeavenlyBody->getNumericExcentricity() * 100);
        ui->excentricityEdit->setText(QString::number(solarSystemHeavenlyBody->getNumericExcentricity()));
        ui->semimajorAxis->setText(QString::number(solarSystemHeavenlyBody->getSemimajorAxis()));
        ui->angle->setText(QString::number(solarSystemHeavenlyBody->getAngle()));
        ui->orbitalPlaneAngle->setText(QString::number(solarSystemHeavenlyBody->getOrbitalPlaneAngle()));
    }
}

void SolarSystemDetails::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    ui->deletePlanet->setEnabled(selected.size() == 1);
    ui->editPlanet->setEnabled(selected.size() == 1);
}

void SolarSystemDetails::setPlanetManagementActive(bool isActive)
{
    ui->planetsTableView->setEnabled(isActive);
    ui->planets->setEnabled(isActive);
    ui->excentricity->setEnabled(isActive);
    ui->excentricityEdit->setEnabled(isActive);
    ui->semimajorAxis->setEnabled(isActive);
    ui->angle->setEnabled(isActive);
    ui->orbitalPlaneAngle->setEnabled(isActive);
    ui->addPlanet->setEnabled(isActive);
}

void SolarSystemDetails::starSelected(int index)
{
    HeavenlyBody *heavenlyBody = solarSystemModel->getStarsComboBoxModel()->getHeavenlyBody(index);

    if (heavenlyBody)
    {
        ui->diameterLabel->setText(QString("Diameter: %L1").arg(heavenlyBody->getDiameter()));

        QPalette palette = ui->colorLabel->palette();
        palette.setColor(QPalette::Background, heavenlyBody->getColor());
        ui->colorLabel->setPalette(palette);
    }
}

void SolarSystemDetails::on_excentricity_valueChanged()
{
    ui->excentricityEdit->setText(QString::number(ui->excentricity->value() / 100.0));
}

void SolarSystemDetails::on_cancel_clicked()
{
    close();
}

void SolarSystemDetails::on_accept_clicked()
{
    if (updateOrCreateSolarSystem())
    {
        setPlanetManagementActive(true);

        isEdit = true;
    }
}

void SolarSystemDetails::on_ok_clicked()
{
    if (updateOrCreateSolarSystem())
    {
        close();
    }
}

bool SolarSystemDetails::updateOrCreateSolarSystem()
{
    bool ok = true;

    try
    {
        if (!isEdit)
        {
            solarSystemModel->createSolarSystem(ui->name->text(), ui->stars->currentIndex());
        }
        else
        {
            solarSystemModel->updateSolarSystem(ui->name->text(), ui->stars->currentIndex());
        }
    }
    catch (const PropertyNotValidException &notValidException)
    {
        ok = false;

        QMessageBox::critical(this,
                              QString("The field '%1' is not valid").arg(notValidException.getProperty()),
                              notValidException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const EntityNotUniqueException &notUniqueException)
    {
        ok = false;

        QMessageBox::critical(this,
                              "Not unique",
                              notUniqueException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const SqlQueryException &sqlQueryException)
    {
        ok = false;

        QMessageBox::critical(this,
                              "Database SQL error",
                              QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                              QMessageBox::Ok);
    }

    return ok;
}

void SolarSystemDetails::updateOrCreatePlanet(bool isUpdate)
{
    bool ok = true;
    double currentExcentricity = ui->excentricityEdit->text().toDouble(&ok);

    if (!ok)
    {
        currentExcentricity = -1;
    }

    double angle = ui->angle->text().toDouble(&ok);

    if (!ok)
    {
        angle = 500;
    }

    double orbitalPlaneAngle = ui->orbitalPlaneAngle->text().toDouble(&ok);

    if (!ok)
    {
        orbitalPlaneAngle = 500;
    }

    try
    {
        if (isUpdate)
        {
            solarSystemModel->updatePlanet(ui->planets->currentIndex(),
                                           currentExcentricity,
                                           ui->semimajorAxis->text().toDouble(),
                                           angle,
                                           orbitalPlaneAngle);

            ui->planetsTableView->selectRow(solarSystemModel->getSelectedHeavenlyBodyIndex());
        }
        else
        {
            solarSystemModel->addPlanet(ui->planets->currentIndex(),
                                        currentExcentricity,
                                        ui->semimajorAxis->text().toDouble(),
                                        angle,
                                        orbitalPlaneAngle);

            ui->planetsTableView->selectRow(ui->planetsTableView->model()->rowCount() - 1);
        }
    }
    catch (const PropertyNotValidException &notValidException)
    {
        QMessageBox::critical(this,
                              QString("The field '%1' is not valid").arg(notValidException.getProperty()),
                              notValidException.getMessage() + "\n\nThe planet could not be added to the solar system!",
                              QMessageBox::Ok);
    }
    catch (const EntityNotUniqueException &notUniqueException)
    {
        QMessageBox::critical(this,
                              "Not unique",
                              notUniqueException.getMessage(),
                              QMessageBox::Ok);
    }
    catch (const SqlQueryException &sqlQueryException)
    {
        QMessageBox::critical(this,
                              "Database SQL error",
                              QString("There was an error with an SQL statement!\n\nError:\n\n%1").arg(sqlQueryException.getSqlError()),
                              QMessageBox::Ok);
    }
}

void SolarSystemDetails::on_addPlanet_clicked()
{
    updateOrCreatePlanet(false);
}

void SolarSystemDetails::on_editPlanet_clicked()
{
    updateOrCreatePlanet(true);
}

void SolarSystemDetails::on_deletePlanet_clicked()
{
    if (solarSystemModel->getCurrentSolarSystemHeavenlyBody())
    {
        QString name = solarSystemModel->getCurrentSolarSystemHeavenlyBody()->getHeavenlyBody()->getName();

        int result = QMessageBox::question(this,
                                           "Delete Heavenly Body",
                                           QString("Would you like to delete the Heavenly Body '%1'?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);

        if (result == QMessageBox::Yes)
        {
            solarSystemModel->deletePlanet();
        }
    }
}
