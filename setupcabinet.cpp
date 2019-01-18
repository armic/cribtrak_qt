#include "cabtooldetail.h"
#include "setupcabinet.h"
#include "ui_setupcabinet.h"
#include "maincontroller.h"
//#include "cabinet.h"
#include "datamanager.h"


setupcabinet::setupcabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setupcabinet)
{
    ui->setupUi(this);
//    connect(ui->lstDrawers, SIGNAL(clicked(const QModelIndex&)),this,SLOT(on_selectDrawer()));

//    connect(ui->btnAdminMaint, &QPushButton::clicked,this, &setupcabinet::enterAdminMaint);

//    LoadDialog();
}

setupcabinet::~setupcabinet()
{
    delete ui;
}


//void setupcabinet::LoadDialog()
//{
//    DataManager* dataman = MainController::getDataManagerInstance();


//   QSqlQuery qryCabinet = dataman->getCabinetDetails();
//   QSqlQuery qryLoc = dataman->getLocationListQry();
//   QSqlQuery qryDefaultCal = dataman->getTailListQry();

//   setupcabinet::setWindowTitle( "Editing CABINET " + qryCabinet.value(0).toString() + " CUSTOMER ID " + sCustID.setNum(dataman->currentCustomer.custId));

//   // Transfer data to form

//    ui->lblCabinet->setText( "CABINET " + qryCabinet.value(0).toString() + " CUSTOMER ID " + sCustID.setNum(dataman->currentCustomer.custId));

//    //update Drawer List table

//    QSqlQueryModel* drawerlistmodel = dataman->getDrawerList();
//    drawerlistmodel->setHeaderData(2, Qt::Horizontal, tr("Drawer #"));
//    drawerlistmodel->setHeaderData(4, Qt::Horizontal, tr("Description"));
//    drawerlistmodel->setHeaderData(3, Qt::Horizontal, tr("Available?"));

//    ui->lstDrawers->setModel(drawerlistmodel);
//    ui->lstDrawers->setColumnHidden(0, true);
//    ui->lstDrawers->setColumnHidden(1, true);
//    ui->lstDrawers->setColumnHidden(5, true);
//    ui->lstDrawers->setColumnHidden(6, true);
//    ui->lstDrawers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

//     int DrawerNumber = ui->lstDrawers->model()->data(ui->lstDrawers->model()->index(1,2)).toInt();
//     loadToolList(DrawerNumber);

// // Calibration
//     ui->cbNextCalibDate->setCurrentIndex(dataman->currentCabinet.calibration);

//  // Calibration Notify

//      ui->cbCalibDaysNotif->setCurrentIndex(dataman->currentCabinet.calibrationNotify);




//     // Model Number combobox
//     ui->cbModelNumber->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//     QString sModelNumber = qryCabinet.value(2).toString();
//     qDebug()<< "Model Number " << sModelNumber;
//    int index = ui->cbModelNumber->findText(sModelNumber );
//    if (index != -1 ) {
//        ui->cbModelNumber->setCurrentIndex(index);
//    } else {
//       ui->cbModelNumber->setCurrentIndex(0);
//    }

//    // Location combobox

//    ui->cbLocation->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//    int location = qryCabinet.value(6).toInt();
//    ui->cbLocation->clear();
//    ui->cbLocation->addItem("Please select location" ,0);
//    while (qryLoc.next()) {
//          //comboBox-&gt;addItem("First Element", myEnumeration::firstElem);
//           qDebug()<<"Location " << qryLoc.value(2).toString() << "Value " << qryLoc.value(0).toInt();
//           ui->cbLocation->addItem(qryLoc.value(2).toString(), qryLoc.value(0).toInt());
//        }

//    int locIndex = ui->cbLocation->findData(location);

//    if (locIndex != -1 ) {
//        ui->cbLocation->setCurrentIndex(locIndex);
//    } else{
//        ui->cbLocation->setCurrentIndex(0);
//    }

//    // Default Calibration account combobox
//    // Fill with data
//    ui->cbCalibration->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//    ui->cbCalibration->clear();
//    ui->cbCalibration->addItem("Please select tail number", 0);
//    qryDefaultCal.first();
//    while (qryDefaultCal.next()) {
//         qDebug()<<"Tail Numbers " << qryDefaultCal.value(1).toString() << "Value " << qryDefaultCal.value(0).toInt();
//        ui->cbCalibration->addItem(qryDefaultCal.value(1).toString(), qryDefaultCal.value(0).toInt());

//    }

//    int calIndex = ui->cbCalibration->findData(dataman->currentCabinet.defaultCalibrationAccount);

//   if (calIndex != -1 ) {
//       ui->cbCalibration->setCurrentIndex(calIndex);
//   } else{
//       ui->cbCalibration->setCurrentIndex(0);
//   }


//   // Default Service account combobox
//   // Fill with data
//   ui->cbService->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//   ui->cbService->clear();
//   ui->cbService->addItem("Please select tail number", 0);
//   qryDefaultCal.first();
//   while (qryDefaultCal.next()) {
//        qDebug()<<"Tail Numbers " << qryDefaultCal.value(1).toString() << "Value " << qryDefaultCal.value(0).toInt();
//       ui->cbService->addItem(qryDefaultCal.value(1).toString(), qryDefaultCal.value(0).toInt());

//   }

//   int servIndex = ui->cbService->findData(dataman->currentCabinet.defaultServiceAccount);

//  if (servIndex != -1 ) {
//      ui->cbService->setCurrentIndex(servIndex);
//  } else{
//      ui->cbService->setCurrentIndex(0);
//  }


//  // Default Transfer account combobox
//  // Fill with data
//  ui->cbTransfer->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//  ui->cbTransfer->clear();
//  ui->cbTransfer->addItem("Please select tail number", 0);
//  qryDefaultCal.first();
//  while (qryDefaultCal.next()) {
//       qDebug()<<"Tail Numbers " << qryDefaultCal.value(1).toString() << "Value " << qryDefaultCal.value(0).toInt();
//      ui->cbTransfer->addItem(qryDefaultCal.value(1).toString(), qryDefaultCal.value(0).toInt());

//  }



//  int transIndex = ui->cbTransfer->findData(dataman->currentCabinet.defaultTransferAccount);
//  if (transIndex != -1 ) {
//      ui->cbTransfer->setCurrentIndex(transIndex);
//  } else{
//      ui->cbTransfer->setCurrentIndex(0);
//  }

//// Default test account
//// Fill with data
//  ui->cbTest->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
//  ui->cbTest->clear();
//  ui->cbTest->addItem("Please select tail number", 0);
//  qryDefaultCal.first();
//  while (qryDefaultCal.next()) {
//       qDebug()<<"Tail Numbers " << qryDefaultCal.value(1).toString() << "Value " << qryDefaultCal.value(0).toInt();
//      ui->cbTest->addItem(qryDefaultCal.value(1).toString(), qryDefaultCal.value(0).toInt());

//  }



//  int testIndex = ui->cbTest->findData(dataman->currentCabinet.defaultTestAccount);
//  if (testIndex != -1 ) {
//      ui->cbTest->setCurrentIndex(testIndex);
//  } else{
//      ui->cbTest->setCurrentIndex(0);
//  }





//    ui->edtFirmware->setText(qryCabinet.value(4).toString());
//    ui->edtDescription->setText(qryCabinet.value(1).toString());
//    ui->edtSerial->setText(qryCabinet.value(5).toString());
//    ui->edtNotes->setText(qryCabinet.value(7).toString());


//    ui->chkByOthers->setChecked(dataman->currentCabinet.allowReturnByOthers);
//    ui->chkByAdmin->setChecked(dataman->currentCabinet.allowReturnByAdmin);
//    ui->chkCalibVerify->setChecked(dataman->currentCabinet.calibrationVerify);
//    ui->chkCalibUserModeUpdate->setChecked(dataman->currentCabinet.calibrationUserModeUpdate);




//}

//void setupcabinet::on_btnUnlock_clicked()
//{
//  //Cabinet::unlockDrawers();
//}

//void setupcabinet::on_btnLock_clicked()
//{
// // Cabinet::lockDrawers();
//}

//void setupcabinet::on_btnReset_clicked()
//{

//}

//void setupcabinet::on_btnRestart_clicked()
//{

//}

//void setupcabinet::on_buttonBox_rejected()
//{
//    close();
//}

//void setupcabinet::on_buttonBox_accepted()
//{
//     DataManager* dataman = MainController::getDataManagerInstance();
//    // Accept Changes
//    dataman->currentCabinet.defaultCalibrationAccount = ui->cbCalibration->itemData(ui->cbCalibration->currentIndex()).toInt();
//    dataman->currentCabinet.defaultServiceAccount = ui->cbService->itemData(ui->cbService->currentIndex()).toInt();
//    dataman->currentCabinet.defaultTransferAccount = ui->cbTransfer->itemData(ui->cbTransfer->currentIndex()).toInt();
//    dataman->currentCabinet.defaultTestAccount = ui->cbTest->itemData(ui->cbTest->currentIndex()).toInt();


//    dataman->currentCabinet.allowReturnByOthers = ui->chkByOthers->isChecked();
//    dataman->currentCabinet.allowReturnByAdmin = ui->chkByAdmin->isChecked();
//    dataman->currentCabinet.calibrationVerify = ui->chkCalibVerify->isChecked();
//    dataman->currentCabinet.calibrationUserModeUpdate = ui->chkCalibUserModeUpdate->isChecked();



//    QSettings settings("trak.ini", QSettings::IniFormat);
//    settings.beginGroup("Cabinet");
//    settings.setValue("DefaultCalibrationAccount",dataman->currentCabinet.defaultCalibrationAccount);
//    settings.setValue("DefaultServiceAccount",dataman->currentCabinet.defaultServiceAccount);
//    settings.setValue("DefaultTransferAccount",dataman->currentCabinet.defaultTransferAccount);
//    settings.setValue("DefaultTestAccount",dataman->currentCabinet.defaultTestAccount);
//    settings.setValue("Calibration",dataman->currentCabinet.calibration);
//    settings.setValue("CalibrationNotification",dataman->currentCabinet.calibrationNotify);

//    settings.setValue("AllowReturnByOthers",(dataman->currentCabinet.allowReturnByOthers == true ? 1 : 0));
//    settings.setValue("AllowReturnByAdmin",(dataman->currentCabinet.allowReturnByAdmin == true ? 1 : 0));
//    settings.setValue("CalibrationVerify",(dataman->currentCabinet.calibrationVerify == true ? 1 : 0));
//    settings.setValue("CalibrationUserModeUpdate",(dataman->currentCabinet.calibrationUserModeUpdate == true ? 1 : 0));

//    settings.endGroup();

//    qInfo() << "Cabinet options";
//    qInfo() << "    DefaultCalibrationAccount " << dataman->currentCabinet.defaultCalibrationAccount;
//    qInfo() << "    DefaultServiceAccount" << dataman->currentCabinet.defaultServiceAccount;
//    qInfo() << "    DefaultTransferAccount"  << dataman->currentCabinet.defaultTransferAccount;
//    qInfo() << "    DefaultTestAccount" << dataman->currentCabinet.defaultTestAccount;
//    qInfo() << "    Calibration" << dataman->currentCabinet.calibration;
//    qInfo() << "    CalibrationNotification" << dataman->currentCabinet.calibrationNotify;

//    qInfo() << "    AllowReturnByOthers" << (dataman->currentCabinet.allowReturnByOthers == true ? 1 : 0);
//    qInfo() << "    AllowReturnByAdmin" << (dataman->currentCabinet.allowReturnByAdmin == true ? 1 : 0);
//    qInfo() << "    CalibrationVerify" << (dataman->currentCabinet.calibrationVerify == true ? 1 : 0);
//    qInfo() << "    CalibrationUserModeUpdate" << (dataman->currentCabinet.calibrationUserModeUpdate == true ? 1 : 0);

//    //Cabinet tab
//    dataman->updateCabinetRecord(
//       dataman->currentCabinet.kabId,
//       dataman->currentCustomer.custId,
//       ui->edtDescription->text(),
//       ui->cbModelNumber->itemText(ui->cbModelNumber->currentIndex()),
//       ui->edtFirmware->text(),
//       ui->edtNotes->toPlainText(),
//       ui->edtSerial->text(),
//       ui->cbLocation->itemData(ui->cbLocation->currentIndex()).toInt()
//      );

//    close();

//}

//void setupcabinet::on_btnConnect_clicked()
//{
//    // Connect HID
//   // Cabinet::usbConnect();
//}

//void setupcabinet::on_btnDisconnect_clicked()
//{
//    //Disconnect HID
//}



//void setupcabinet::on_btnPrevDrawers_clicked()
//{
// QModelIndex index = ui->lstDrawers->currentIndex();
//int i = index.row(); // now you know which record was selected
//if(i > 0) {
//    ui->lstDrawers->selectRow(i - 1);
//    int DrawerNumber = ui->lstDrawers->model()->data(ui->lstDrawers->model()->index(i-1,2)).toInt();
//    loadToolList(DrawerNumber);
//}else {
//    ui->lstDrawers->selectRow(0);
//    int DrawerNumber = ui->lstDrawers->model()->data(ui->lstDrawers->model()->index(0,2)).toInt();
//    loadToolList(DrawerNumber);

//}

//}

//void setupcabinet::on_btnNextDrawers_clicked()
//{
//   int totalRow =  ui->lstDrawers->model()->rowCount();
//   QModelIndex index = ui->lstDrawers->currentIndex();
//   int i = index.row(); // now you know which record was selected

//   qDebug()<<" i is " << i<<" and totalRow is "<< totalRow;
//   if(i == totalRow - 1) {

//       ui->lstDrawers->selectRow(totalRow -1);
//       int DrawerNumber = ui->lstDrawers->model()->data(ui->lstDrawers->model()->index(totalRow-1,2)).toInt();
//       loadToolList(DrawerNumber);
//   } else {
//       ui->lstDrawers->selectRow(i+1);
//       int DrawerNumber = ui->lstDrawers->model()->data(ui->lstDrawers->model()->index(i+1,2)).toInt();
//       loadToolList(DrawerNumber);
//   }


//}

//void setupcabinet::on_selectDrawer()
//{

//QModelIndex index = ui->lstDrawers->currentIndex();
//int i = index.row(); // now you know which record was selected
//// int isUser =  ui->tableViewEmployee->model()->data(ui->tableViewEmployee->model()->index(i,3)).toInt();
// qDebug() << "Drawer Index is " << i;
// int DrawerNumber = ui->lstDrawers->model()->data(ui->lstDrawers->model()->index(i,2)).toInt();
// loadToolList(DrawerNumber);
//}


//void setupcabinet::loadToolList(int DrawNum)
//{
//    DataManager* dataman = MainController::getDataManagerInstance();
//    qDebug()<<"DrawerNum " << DrawNum;
//    QSqlQueryModel* toollistmodel = NULL;
//    toollistmodel = dataman->getToolList(DrawNum);
//    ui->lstTools->setModel(toollistmodel);
//    toollistmodel->setHeaderData(0, Qt::Horizontal, tr("Tool Number #"));
//    toollistmodel->setHeaderData(6, Qt::Horizontal, tr("Item ID"));
//    toollistmodel->setHeaderData(5, Qt::Horizontal, tr("Description"));
//    toollistmodel->setHeaderData(2, Qt::Horizontal, tr("Status"));

//    ui->lstTools->setColumnHidden(1, true);
//    ui->lstTools->setColumnHidden(3, true);
//    ui->lstTools->setColumnHidden(4, true);
//    ui->lstTools->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


//}

//void setupcabinet::on_lstDrawers_clicked(const QModelIndex &index)
//{
//  // index = ui->lstDrawers->currentIndex();
//   int i = index.row(); // now you know which record was selected
//   int DrawerNumber = ui->lstDrawers->model()->data(ui->lstDrawers->model()->index(i,0)).toInt();
//   qDebug() << "DrawerNum " << DrawerNumber;
//   loadToolList(DrawerNumber);



//}

//void setupcabinet::on_cbCalibration_currentIndexChanged(int index)

//{
////  DataManager* dataman = MainController::getDataManagerInstance();
////  dataman->currentCabinet.defaultCalibrationAccount = ui->cbCalibration->itemData(index).toInt();
//}

//void setupcabinet::on_cbService_currentIndexChanged(int index)
//{
////    DataManager* dataman = MainController::getDataManagerInstance();
////    dataman->currentCabinet.defaultServiceAccount = ui->cbService->itemData(index).toInt();
//}

//void setupcabinet::on_cbTransfer_currentIndexChanged(int index)
//{
////   DataManager* dataman = MainController::getDataManagerInstance();
////  dataman->currentCabinet.defaultTransferAccount = ui->cbTransfer->itemData(index).toInt();
//}

//void setupcabinet::on_cbTest_currentIndexChanged(int index)
//{
////    DataManager* dataman = MainController::getDataManagerInstance();
////    dataman->currentCabinet.defaultTestAccount = ui->cbTest->itemData(index).toInt();
//}

//void setupcabinet::on_cbNextCalibDate_currentIndexChanged(int index)
//{
//    DataManager* dataman = MainController::getDataManagerInstance();
//    dataman->currentCabinet.calibration = index;
//}

//void setupcabinet::on_cbCalibDaysNotif_currentIndexChanged(int index)
//{
//    DataManager* dataman = MainController::getDataManagerInstance();
//    dataman->currentCabinet.calibrationNotify = index;
//}

//void setupcabinet::on_btnCalibration_clicked()
//{
//    // set all calibration date

//}

//void setupcabinet::on_chkAlow_toggled(bool checked)
//{
////   DataManager* dataman = MainController::getDataManagerInstance();
////    if(checked){
////      dataman->currentCabinet.allowReturnByOthers = true;
////    }
////    else
////      {
////      dataman->currentCabinet.allowReturnByOthers = false;
////    }

//}

//void setupcabinet::on_chkAlow_clicked(bool checked)
//{
////    DataManager* dataman = MainController::getDataManagerInstance();
////     if(checked){
////       dataman->currentCabinet.allowReturnByOthers = true;
////     }
////     else
////       {
////       dataman->currentCabinet.allowReturnByOthers = false;
////     }
//}

//void setupcabinet::on_btntoolprop_clicked()
//{
//    //open tool properties
//    QModelIndex index = ui->lstTools->currentIndex();
//    int i = index.row();
//    int DrawerNumber = ui->lstTools->model()->data(ui->lstTools->model()->index(i,1)).toInt();
//    int ToolNumber = ui->lstTools->model()->data(ui->lstTools->model()->index(i,0)).toInt();

//    cabtooldetail frmCabTool;
//    frmCabTool.setModal(true);
//    frmCabTool.loadDialog(DrawerNumber,ToolNumber);
//    frmCabTool.exec();

//}



//void setupcabinet::enterAdminMaint()
//{
//    qInfo() << "Entering tools manager";
////    MainController::getMainControllerInstance()->setAppMode(MainController::toolsAdminMode);
//    //setModal(false);
//    this->hide();
//    MainController::getMainViewInstance()->setToolServiceScreen();
//}
