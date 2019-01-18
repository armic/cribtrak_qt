#include "dbmaintenance.h"
#include "ui_dbmaintenance.h"
#include "maincontroller.h"
#include "datamanager.h"




dbMaintenance::dbMaintenance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dbMaintenance)
{
    ui->setupUi(this);
}

dbMaintenance::~dbMaintenance()
{
    delete ui;
}


void dbMaintenance::setup()
{
    // Load initial data from the table

}

void dbMaintenance::on_btnOK_clicked()
{
    close();
}

void dbMaintenance::on_btnCheckTables_clicked()
{
    DataManager* dataman = MainController::getDataManagerInstance();

    QSqlQueryModel* model = dataman->checkTables();
    ui->grdView->setModel(model);
}

void dbMaintenance::on_btnAnalyze_clicked()
{
    DataManager* dataman = MainController::getDataManagerInstance();

    QSqlQueryModel* model = dataman->analyzeTables();
    ui->grdView->setModel(model);
}

void dbMaintenance::on_btnOptimized_clicked()
{
    DataManager* dataman = MainController::getDataManagerInstance();

    QSqlQueryModel* model = dataman->optimizeTables();
    ui->grdView->setModel(model);
}

void dbMaintenance::on_btnrepair_clicked()
{
    DataManager* dataman = MainController::getDataManagerInstance();

    QSqlQueryModel* model = dataman->repairTables();
    ui->grdView->setModel(model);
}
