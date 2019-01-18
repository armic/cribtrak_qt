#include "cabtooldetail.h"
#include "ui_cabtooldetail.h"
#include "maincontroller.h"
#include "datamanager.h"


cabtooldetail::cabtooldetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cabtooldetail)
{
    ui->setupUi(this);

    keybrd = new KeyPad(this);
    ui->keybrd->setLayout(new QHBoxLayout);
    ui->keybrd->layout()->addWidget(keybrd);
}


cabtooldetail::~cabtooldetail()
{
    delete ui;

}

void cabtooldetail::loadDialog(const int DrawerNum, int ToolNum)
{
  DataManager* dataman = MainController::getDataManagerInstance();
  QSqlQuery cabToolResult = dataman->getCabToolQry(DrawerNum, ToolNum);

  cabtooldetail::setWindowTitle(cabToolResult.value(12).toString());
  ui->edtCode->setText(cabToolResult.value(14).toString());
  ui->edtDesc->setText(cabToolResult.value(12).toString());
  ui->edtPartNum->setText(cabToolResult.value(13).toString());
  ui->edtDrawNumber->setText(QString::number(DrawerNum));
  ui->edtToolNumber->setText(QString::number(ToolNum));

  // Serviceable

  int serviceable_tag = cabToolResult.value(9).toInt();

  if(serviceable_tag == 1) {
     ui->chkServiceable->setChecked(true);
  } else
  {
    ui->chkServiceable->setChecked(false);
  }

  int calibration_tag = cabToolResult.value(6).toInt();

  if(calibration_tag == 1) {
      ui->chkCalibration->setChecked(true);
      ui->chkCalibrated->setVisible(true);
      ui->lblCalibDate->setVisible(true);
      ui->lblLastCalib->setVisible(true);
      ui->dateCurrentCalibration->setVisible(true);
      ui->datelastCalibration->setVisible(true);
  }else
  {
      ui->chkCalibration->setChecked(false);
      ui->chkCalibrated->setVisible(false);
      ui->lblCalibDate->setVisible(false);
      ui->lblLastCalib->setVisible(false);
      ui->dateCurrentCalibration->setVisible(false);
      ui->datelastCalibration->setVisible(false);
  }

  int calibrated_tag = cabToolResult.value(10).toInt();

  if(calibrated_tag == 1) {
      ui->chkCalibrated->setChecked(true);
  }else
 {
    ui->chkCalibrated->setChecked(false);
  }


  int transferred_tag = cabToolResult.value(11).toInt();
  if(transferred_tag == 1){
     ui->chkTransferred->setChecked(true);
  }else
    {
       ui->chkTransferred->setChecked(false);
  }

  ui->dateCurrentCalibration->setDate(cabToolResult.value(7).toDate());
  ui->datelastCalibration->setDate(cabToolResult.value(8).toDate());



}




void cabtooldetail::on_btnBox_accepted()
{
    // OK
     int drawNum;
     int toolNum;
     int serviceable_tag;
     int calibration_tag;
     int calibrated_tag;
     int transferred_tag;
     QDate curCalibDate;
     QDate lastCalibDate;

     DataManager* dataman = MainController::getDataManagerInstance();

     drawNum = ui->edtDrawNumber->text().toInt();
     toolNum = ui->edtToolNumber->text().toInt();

     if(ui->chkServiceable->isChecked())
     {
         serviceable_tag = 1;
     }else
      {
         serviceable_tag = 0;
     }

     if(ui->chkCalibration->isChecked())
      {
         calibration_tag = 1;
         curCalibDate = ui->dateCurrentCalibration->date();
         lastCalibDate = ui->datelastCalibration->date();
     }else
     {
         calibration_tag = 0;
         curCalibDate = ui->dateCurrentCalibration->date();
         lastCalibDate = ui->datelastCalibration->date();

     }

     if(ui->chkCalibrated->isChecked())
     {
         calibrated_tag = 1;
     }else
     {
         calibrated_tag = 0;
     }

     if(ui->chkTransferred->isChecked())
    {
       transferred_tag = 1;
     } else
      {
         transferred_tag = 0;
     }

     QMessageBox msgBox;
     QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this,"Please confirm", "Do you really want to update the current record?",
                         QMessageBox::Yes|QMessageBox::No);
     if(reply ==QMessageBox::Yes) {
         dataman->setCabTool(drawNum,toolNum,serviceable_tag,calibration_tag, calibrated_tag, transferred_tag,curCalibDate,lastCalibDate );
         close();
     }


}

void cabtooldetail::on_btnBox_rejected()
{
    close();
}

void cabtooldetail::on_chkCalibration_toggled(bool checked)
{
    if(checked) {

        ui->lblCalibDate->setVisible(true);
        ui->lblLastCalib->setVisible(true);
        ui->chkCalibrated->setVisible(true);
        ui->dateCurrentCalibration->setVisible(true);
        ui->datelastCalibration->setVisible(true);
    } else
    {
        ui->lblCalibDate->setVisible(false);
        ui->lblLastCalib->setVisible(false);
        ui->chkCalibrated->setVisible(false);
        ui->dateCurrentCalibration->setVisible(false);
        ui->datelastCalibration->setVisible(false);
    }


}
