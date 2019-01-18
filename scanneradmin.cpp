#include "scanneradmin.h"
#include "ui_scanneradmin.h"
#include "maincontroller.h"

ScannerAdmin::ScannerAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScannerAdmin)
{
    ui->setupUi(this);
    ui->autodetectCheckBox->setChecked(true);
    ui->autodetectCheckBox->setEnabled(false);
    ui->portLineEdit->setEnabled(false);
    ui->portLineEdit->setText(MainController::getScannerManagerInstance()->portName());
}

ScannerAdmin::~ScannerAdmin()
{
    delete ui;
}
