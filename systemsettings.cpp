#include "systemsettings.h"
#include "ui_systemsettings.h"
#include "maincontroller.h"
//#include "cabinet.h"
#include "datamanager.h"
#include "logviewer.h"



systemsettings::systemsettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::systemsettings)
{
    ui->setupUi(this);

    // load values

    DataManager* dataman = MainController::getDataManagerInstance();
    ui->edtUserTimeout->setValue(dataman->currentCrib.userTimeout);
    ui->edtAdmin->setValue(dataman->currentCrib.adminTimeout);
    //ui->edtOpenAlarm->setValue(dataman->currentCrib.userTimeout);
    //ui->edtIssuedTools->setValue(dataman->currentCrib.issuedToolsTimeout);
    ui->edtwebUpdateURL->setText(dataman->currentCrib.url);
    ui->edtUpdateDir->setText(dataman->currentCrib.updateDir);

    ui->rtsNotifySpinBox->setValue(dataman->currentCrib.rtsNotifyBefore);

   // Toggled options
    ui->cbAlertSound->setChecked(dataman->currentCrib.allowSounds);

    keybrd = new KeyPad(this);
    ui->keybrd->setLayout(new QHBoxLayout);
    ui->keybrd->layout()->addWidget(keybrd);

}

systemsettings::~systemsettings()
{
    delete ui;
}


void systemsettings::on_btnOK_clicked()
{
    // Accept Changes

    DataManager* dataman = MainController::getDataManagerInstance();

     QSettings settings("trak.ini", QSettings::IniFormat);
     settings.beginGroup("Cabinet");
//     settings.setValue("DefaultCalibrationAccount",dataman->currentCabinet.defaultCalibrationAccount);
//     settings.setValue("DefaultServiceAccount",dataman->currentCabinet.defaultServiceAccount);
//     settings.setValue("DefaultTransferAccount",dataman->currentCabinet.defaultTransferAccount);
//     settings.setValue("DefaultTestAccount",dataman->currentCabinet.defaultTestAccount);
     settings.endGroup();

     //dataman->currentCrib.closeDrawerTimeOut = ui->edtCloseDrawer->text().toInt();
     dataman->currentCrib.userTimeout = ui->edtUserTimeout->text().toInt();
     dataman->currentCrib.adminTimeout = ui->edtAdmin->text().toInt();
     //dataman->currentCrib.issuedToolsTimeout = ui->edtIssuedTools->text().toInt();
     dataman->currentCrib.url = ui->edtwebUpdateURL->text();
     dataman->currentCrib.updateDir = ui->edtUpdateDir->text();

     dataman->currentCrib.allowSounds = ui->cbAlertSound->isChecked();
     dataman->currentCrib.rtsNotifyBefore = ui->rtsNotifySpinBox->value();

     //Timers
     settings.beginGroup("System");
     //settings.setValue("CloseDrawerToLogoff",dataman->currentCrib.closeDrawerTimeOut);
     settings.setValue("UserTimeout",dataman->currentCrib.userTimeout);
     settings.setValue("AdminTimeout",dataman->currentCrib.adminTimeout);
     //settings.setValue("IssuedToolsTime",dataman->currentCrib.issuedToolsTimeout);
     settings.setValue("URL",dataman->currentCrib.url);
     settings.setValue("UpdateDir",dataman->currentCrib.updateDir);
     settings.endGroup();


     // Toggled options
     settings.beginGroup("Cabinet");
     settings.setValue("allowSounds",dataman->currentCrib.allowSounds == true ? 1 : 0);
     settings.setValue("RTSNotifyBefore", dataman->currentCrib.rtsNotifyBefore);
    // settings.setValue("AllowReturnByOthers",dataman->currentCabinet.allowReturnByOthers);

     settings.endGroup();

    close();

}

//void systemsettings::on_btnbackup_clicked()
//{

//}

void systemsettings::on_btnterminate_clicked()
{
    // Terminate kabtrak
    qInfo() << "Kabtrak terminated from system";
     MainController::getMainControllerInstance()->requestExit(Trak::AdminRequestExit);

}

void systemsettings::on_btnRestart_clicked()
{
    // Restart kabtrak
    qInfo() << "Kabtrak terminated and restarted from system";
    QProcess::startDetached(QApplication::arguments()[0], QApplication::arguments());
    MainController::getMainControllerInstance()->requestExit(Trak::AdminRequestExit);
}

void systemsettings::on_btnLogOff_clicked()
{
    //Logoff to windows
     QApplication::quit();
     QProcess proc;
     proc.start("shutdown", QStringList() << "/l");
//     if (!proc.waitForStarted()) {
//         return 1;
//     }
}

void systemsettings::on_btnCheck_clicked()
{
    // Web Update
}

void systemsettings::on_btnLocalUpdate_clicked()
{
    //Local Update
}

void systemsettings::on_btnCancel_clicked()
{
    // Cancel button
    // No changes were made
    close();
}

void systemsettings::on_btnClear_clicked()
{
    //Clear transactions
     DataManager* dataman = MainController::getDataManagerInstance();
     QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "kabTRAK Transactions", "Would you really want to clear transaction record?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
       dataman->clearTransactions();
      } else {
        qDebug() << "Yes was *not* clicked";
      }


}

void systemsettings::on_btnViewLogs_clicked()
{
    // View kabtrak logs file
    // Load Employee List window
    logViewer frmLogViewer;
    frmLogViewer.setModal(true);
    frmLogViewer.exec();

}

void systemsettings::on_btnViewLogin_clicked()
{
    // view Reader log
}

void systemsettings::on_btnDeleteLogs_clicked()
{
    //Delete all logs
}

void systemsettings::on_cbAlertSound_clicked(bool checked)
{
    // Use alert sound
    DataManager* dataman = MainController::getDataManagerInstance();
    if(checked) {
      dataman->currentCrib.allowSounds = true;
    }
   else
     {
        dataman->currentCrib.allowSounds = false;
    }




}

//void systemsettings::on_edtCloseDrawer_valueChanged(const QString &arg1)
//{
//    // Close drawer value
//     DataManager* dataman = MainController::getDataManagerInstance();
//     dataman->currentCrib.closeDrawerTimeOut = arg1.toInt();
//}

void systemsettings::on_edtAdmin_valueChanged(const QString &arg1)
{
    //Admin time out value
    DataManager* dataman = MainController::getDataManagerInstance();
    dataman->currentCrib.adminTimeout = arg1.toInt();
}

//void systemsettings::on_edtOpenAlarm_valueChanged(const QString &arg1)
//{
//    //Open Drawer timer value
//    DataManager* dataman = MainController::getDataManagerInstance();
//    dataman->currentCrib.userTimeout = arg1.toInt();
//}

//void systemsettings::on_edtIssuedTools_valueChanged(const QString &arg1)
//{
//    // Issued tools value
//    DataManager* dataman = MainController::getDataManagerInstance();
//    dataman->currentCrib.issuedToolsTimeout = arg1.toInt();
//}

void systemsettings::on_edtUserTimeout_valueChanged(const QString &arg1)
{
    // Close drawer value
     DataManager* dataman = MainController::getDataManagerInstance();
     dataman->currentCrib.userTimeout = arg1.toInt();
}
