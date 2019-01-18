#include "taildetail.h"
#include "ui_taildetail.h"
#include "maincontroller.h"
#include "datamanager.h"
#include "taillist.h"
#include <QDebug>

taildetail::taildetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taildetail)
{
    ui->setupUi(this);
    editMode = false;
    setWindowTitle("Create Tail");
    ui->startDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->rtsDateTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(1));

    keybrd = new KeyPad(this);
    ui->keybrd->setLayout(new QHBoxLayout);
    ui->keybrd->layout()->addWidget(keybrd);

    ui->edtTailNumber->setFocus();
}

taildetail::~taildetail()
{
    delete ui;
}

void taildetail::setEditMode(const QString tailNumber)
{
    //ui->edtTailNumber->setText(tailNumber);
    editMode = true;
    setWindowTitle("Edit Tail");
    DataManager *dataman = MainController::getDataManagerInstance();
    QSqlQuery tailQuery = dataman->getSelectedTail(tailNumber);

    qDebug() << __FUNCTION__ << tailQuery.value(2).toDateTime();

    //------------------
    // Populate dialog.
    //------------------

    ui->edtTailNumber->setText(tailQuery.value(1).toString());
    ui->edtTailNumber->setEnabled(false);
    QDateTime start = tailQuery.value(2).toDateTime();
    QDateTime rts = tailQuery.value(3).toDateTime();

    // NOTE: There's no way to clear a QDateTimeEdit (presumably because there's no such thing as non-existent date or time).
    // I don't know if the client wants a start and rts for every tail, so I'm leaving this until later.
    if (!start.isNull())
    {
        ui->startDateTimeEdit->setDateTime(start);
    }
    else
    {
    }

    if (!rts.isNull())
    {
        ui->rtsDateTimeEdit->setDateTime(rts);
    }
    ui->edtDescription->setText(tailQuery.value(4).toString());
    ui->cbSpeedDial->setChecked(tailQuery.value(5).toBool());
    ui->cbDisabled->setChecked(tailQuery.value(6).toBool());

//    m_tailNumber = tailNumber;
//    qDebug()<<"Tail Number "<<m_tailNumber;

//    keybrd = new KeyPad(this);
//    ui->keybrd->setLayout(new QHBoxLayout);
//    ui->keybrd->layout()->addWidget(keybrd);


//    if(!m_tailNumber.isEmpty())
//    {
//        // Edit Mode
//        DataManager* dataman = MainController::getDataManagerInstance();
//        QSqlQuery tailQuery = dataman->getSelectedTail(m_tailNumber);
//        taildetail::setWindowTitle("Editing Tail  " + tailQuery.value(1).toString());
//        //Transfer data to form
//        ui->edtTailNumber->setReadOnly(true);
//        ui->edtTailNumber->setText(tailQuery.value(1).toString());
//        ui->edtDescription->setText(tailQuery.value(3).toString());

//        int iSpeedDial = tailQuery.value(4).toInt();
//        int iDisabled = tailQuery.value(5).toInt();

//        if(iSpeedDial == 1){

//            ui->cbSpeedDial->setChecked(true);
//        }
//        else
//        {
//            ui->cbSpeedDial->setChecked(false);
//        }

//        if(iDisabled == 1){

//            ui->cbDisabled->setChecked(true);
//        }
//        else
//        {
//            ui->cbDisabled->setChecked(false);
//        }




//    }
//    else
//    {
//        // Insert Mode
//        ui->edtTailNumber->setReadOnly(false);

//    }
}

void taildetail::on_buttonBox_accepted()
{
    //Ok button
    DataManager* dataman = MainController::getDataManagerInstance();
    int iSpeedDial;
    int iDisabled;
    //if(!m_tailNumber.isEmpty())
    if (editMode)
    {
        // edit mode
        if(ui->cbSpeedDial->isChecked()){
            iSpeedDial = 1;
        }
        else
        {
            iSpeedDial = 0;
        }

        if(ui->cbDisabled->isChecked()){
            iDisabled = 1;
        }
        else
        {
            iDisabled = 0;
        }


        if(dataman->updateTailRecord(ui->edtTailNumber->text(),ui->edtDescription->text(),iSpeedDial, iDisabled, dataman->currentCustomer.custId, ui->startDateTimeEdit->dateTime(), ui->rtsDateTimeEdit->dateTime()))
        {
            //QMessageBox msgBox;
            //msgBox.setText("Current tail number details successfullly updated.");
            //msgBox.exec();\

            close();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Unable to update current record.");
            msgBox.exec();
        }


    }
    else
    {
        // insert mode
        bool tailExists = dataman->isTailExists(ui->edtTailNumber->text());

        if(tailExists)
        {
            qDebug() << "Insert Tail Duplicate record";
            QMessageBox msgBox;
            msgBox.setText("Duplicate Tail Number. Please enter a unique value.");
            msgBox.exec();
            // Duplicate error message here

        }
        else
        {
            // yes allow to insert

            int isSpeedDial = ui->cbSpeedDial->isChecked();
            int isDisabled = ui->cbDisabled->isChecked();

            dataman->insertTailRecord(ui->edtTailNumber->text(), ui->edtDescription->text(), isSpeedDial,isDisabled, dataman->currentCustomer.custId);

            QMessageBox msgBox;
            msgBox.setText("New Tail Number " + ui->edtTailNumber->text() + " created. ");
            msgBox.exec();

            close();
        }

    }


}

void taildetail::on_buttonBox_rejected()
{
    // Cancel

    close();
}

void taildetail::on_edtTailNumber_textChanged(const QString &arg1)
{
     ui->edtTailNumber->setText(arg1.toUpper());
}

void taildetail::on_edtDescription_textChanged(const QString &arg1)
{
     ui->edtDescription->setText(arg1.toUpper());
}
