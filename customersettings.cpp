#include "customersettings.h"
#include "ui_customersettings.h"
#include "datamanager.h"
#include "maincontroller.h"


CustomerSettings::CustomerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerSettings)
{
    ui->setupUi(this);
    setup();
}


CustomerSettings::~CustomerSettings()
{
    delete ui;
}


void CustomerSettings::loadSettings()
{
    DataManager* dataman = MainController::getDataManagerInstance();

    ui->tabWidget->removeTab(3);

    // Setup database connection here NO NO NO NO NO
    //databaseActive = dataman->connectToDatabase();
    // Check for database connection here
    if(dataman->databaseActive)
    {
        // Populate form controls with correct values

        ui->edtCompanyName->setText(dataman->currentCustomer.companyName);
        ui->edtAddress1->setText(dataman->currentCustomer.Address);
        ui->edtAddress2->setText(dataman->currentCustomer.Address1);
        ui->edtAddress3->setText(dataman->currentCustomer.Address2);
        ui->edtContactPerson->setText(dataman->currentCustomer.ContactPerson);
        ui->edtContactNumber->setText(dataman->currentCustomer.ContactNumber);
        ui->edtEmail->setText(dataman->currentCustomer.email);
        ui->mmoNotes->setPlainText(dataman->currentCustomer.Notes);

        // Set Work Order and batch Number option checkboxes
        if (dataman->currentCustomer.useWorkOrder == true)
        {
            ui->cbWorkOrder->setChecked(true);
        }
        else {
            ui->cbWorkOrder->setChecked(false);
        }

        if (dataman->currentCustomer.useBatch == true)
        {
            ui->cbbatchNumber->setChecked(true);
        }
        else {
            ui->cbbatchNumber->setChecked(false);
        }

        // Load company logo if available
        QPixmap defaultlogo ("images/defaultlogo.png");
        QPixmap companylogo ("images/" + dataman->currentCustomer.comlogo);

        QFileInfo check_file("images//" + dataman->currentCustomer.comlogo);
        // check if file exists and if yes: Is it really a file and no directory?
        if (check_file.exists() && check_file.isFile()) {
            ui->LOGO->setPixmap(companylogo);
        } else {
            ui->LOGO->setPixmap(defaultlogo);
        }
    }
    else {
        // database connection not active, inform end user and go back to admin menu
        QMessageBox* msgBox 	= new QMessageBox();
        msgBox->setWindowTitle("Database connection problem");
        msgBox->setText("Unable to connect to kabTRAk Database!");
        msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
        msgBox->show();
    }
}

void CustomerSettings::saveSettings()
{
     DataManager* dataman = MainController::getDataManagerInstance();

    QSettings settings("trak.ini",QSettings::IniFormat);
    settings.beginGroup("Customer");
    settings.setValue("Name", ui->edtCompanyName->text());
    settings.setValue("Email", ui->edtEmail->text());
    settings.setValue("Contact", ui->edtContactPerson->text());

    if (ui->cbWorkOrder->isChecked()) {
        settings.setValue("UseWorkOrder", 1);
        dataman->currentCustomer.useWorkOrder = true;
    }
    else {
        settings.setValue("UseWorkOrder", 0);
        dataman->currentCustomer.useWorkOrder = false;
    }

    if (ui->cbbatchNumber->isChecked()) {
        settings.setValue("UseBatch", 1);
        dataman->currentCustomer.useBatch = true;
    }
    else {
        settings.setValue("UseBatch", 0);
        dataman->currentCustomer.useBatch = false;
    }

    settings.endGroup();

    dataman->currentCustomer.companyName = ui->edtCompanyName->text();
    dataman->currentCustomer.Address = ui->edtAddress1->text();
    dataman->currentCustomer.Address1 = ui->edtAddress2->text();
    dataman->currentCustomer.Address2 = ui->edtAddress3->text();
    dataman->currentCustomer.ContactNumber = ui->edtContactNumber->text();
    dataman->currentCustomer.ContactPerson = ui->edtContactPerson->text();
    dataman->currentCustomer.email = ui->edtEmail->text();
    dataman->currentCustomer.Notes = ui->mmoNotes->toPlainText();
    dataman->postCabinetOwner();

}

void CustomerSettings::on_btnOK_clicked()
{
    saveSettings();
    close();
}

void CustomerSettings::setup()
{
    loadSettings();

    keybrd = new KeyPad(this);
    ui->keybrd->setLayout(new QHBoxLayout);
    ui->keybrd->layout()->addWidget(keybrd);
}



void CustomerSettings::on_btnCancel_clicked()
{
    close();
}

//void CustomerSettings::on_edtTailDescription_textChanged()
//{
//}

void CustomerSettings::on_btnLoadLogo_clicked()
{
    // load new image here
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/images/", tr("Image Files (*.png)"));
    QPixmap newlogo (fileName);
    ui->LOGO->setPixmap(newlogo);

}
