#include "toolsmanager.h"
#include "ui_toolsmanager.h"
#include "datamanager.h"
#include "maincontroller.h"
//#include "ui_userscreen.h"


ToolsManager::ToolsManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolsManager)
{
    ui->setupUi(this);


    currentToolData = NULL;

    // setup connections
    connect(ui->updateBtn, &QPushButton::clicked, this, &ToolsManager::updateChanges, Qt::UniqueConnection);
    connect(ui->requiresCalibCheckBox, &QCheckBox::stateChanged, this, &ToolsManager::reqCalibrationChange, Qt::UniqueConnection);
    connect(ui->missingCheckBox, &QCheckBox::stateChanged, this, &ToolsManager::removedChange, Qt::UniqueConnection);
    connect(ui->transferredCheckBox, &QCheckBox::stateChanged, this, &ToolsManager::transferredChange, Qt::UniqueConnection);
}

ToolsManager::~ToolsManager()
{
    delete ui;
}




void ToolsManager::onDrawerChanged(int drwnum, bool opened)
{
    if(opened == false)
    {
        // drawer closed, last tool updated?
        updateChanges();
    }
    clearToolDetailDisplay();
    currentToolData = NULL;
}



void ToolsManager::onDrawerToolChanged(int drwnum, int toolnum, int sts)
{
    Tool* tool = MainController::getDataManagerInstance()->getToolDetail(drwnum, toolnum);
    ToolData* tooldata = MainController::getDataManagerInstance()->getToolData(drwnum, toolnum);

    // Is this current tool?
    if (currentToolData != NULL && (tooldata->toolNumber != currentToolData->toolNumber || tooldata->drawerNum != currentToolData->drawerNum))
    {
        updateChanges();
    }

    //setup for next tool
    newToolSelection(drwnum, toolnum);
    updateToolDetailDisplay(drwnum, toolnum);
    if (sts == Trak::Returned)
    {
        toolReturned();
    }
    else
    {
        toolRemoved();
    }

    //currentToolPresent = sts == Trak::Returned ? true : false;
    MainController::getMainViewInstance()->userScreenInstance->startProgressBarTimer();
}



void ToolsManager::toolReturned()
{
    // use currentToolData
    currentToolData->status = Trak::Returned;
    ui->missingCheckBox->setChecked(false);
    ui->transferredCheckBox->setChecked(false);
    ui->missingCheckBox->setDisabled(true);
    ui->transferredCheckBox->setDisabled(true);
    ui->serviceableCheckBox->setDisabled(currentToolData->serviceable == Trak::Serviceable ? true : false);
    qDebug() <<"ToolsManager::toolReturned() missing/transferred/serviceable " << ui->missingCheckBox->isChecked() <<
               ui->transferredCheckBox->isChecked() <<
               ui->serviceableCheckBox->isChecked();
}



void ToolsManager::toolRemoved()
{
    // use currentToolData
    currentToolData->status = Trak::Issued;
    if(currentToolData->status == currentToolData->prevstatus)
    {
        ui->missingCheckBox->setChecked(true);
        ui->transferredCheckBox->setChecked(false);
        ui->missingCheckBox->setEnabled(true);
        ui->transferredCheckBox->setEnabled(true);
        ui->serviceableCheckBox->setDisabled(currentToolData->serviceable == Trak::Serviceable ? true : false);
    }
}




void ToolsManager::toolSelectionChanged(int drwnum, int toolnum)
{
    // update last tool changes
    if (currentToolData != NULL && (toolnum != currentToolData->toolNumber || drwnum != currentToolData->drawerNum))
    {
        updateChanges();
    }
    newToolSelection(drwnum, toolnum);
    updateToolDetailDisplay(drwnum, toolnum);
    MainController::getMainViewInstance()->userScreenInstance->startProgressBarTimer();
}



void ToolsManager::newToolSelection(int drwnum, int toolnum)
{
    Tool* tooldetail = MainController::getDataManagerInstance()->getToolDetail(drwnum, toolnum);
    ToolData* tooldata = MainController::getDataManagerInstance()->getToolData(drwnum, toolnum);
    currentToolData = tooldata;
    currentToolDetail = tooldetail;

    currentUserId = MainController::getDataManagerInstance()->findToolUser(drwnum, toolnum, DataManager::Issued);
    currentUser = MainController::getDataManagerInstance()->getUserName(currentUserId);
}



void ToolsManager::updateToolDetailDisplay(int drwnum, int toolnum)
{
    ToolData* tooldata = currentToolData;

    if (tooldata)
    {
        //qDebug() << "UserScreen::updateToolDetail()" << stockcode << desc << toolnum;
        // tool description fields
        ui->toolNumLbl->setText(QString::number(tooldata->toolNumber));
        ui->stockCodeLbl->setText(tooldata->stockcode);
        ui->descLbl->setText(tooldata->description);
        ui->statusLbl->setText((tooldata->status == Trak::Issued ? "Issued" : "Returned"));
        ui->ownerLbl->setText(currentUser);


        ui->missingCheckBox->setChecked(tooldata->missing == Trak::ToolMissing ? true : false);
        ui->transferredCheckBox->setChecked(tooldata->transferred == Trak::Transferred ? true : false);
        ui->serviceableCheckBox->setChecked(tooldata->serviceable == Trak::Serviceable ? true : false);



        if (!currentUserId.isEmpty() && tooldata->status == Trak::Issued &&
                tooldata->missing == Trak::ToolAvaliable && tooldata->transferred == Trak::NotTransferred)
        {
            // issued to someone
            ui->missingCheckBox->setEnabled(true);

            // transferred cannot be checked
            //ui->transferredCheckBox->setChecked(false);
            ui->transferredCheckBox->setDisabled(true);

            // cannot make unserviceable
            ui->serviceableCheckBox->setDisabled(tooldata->serviceable == Trak::Serviceable ? true : false);
        }

        else if (currentUserId.isEmpty() && tooldata->status == Trak::Returned &&
                tooldata->missing == Trak::ToolAvaliable && tooldata->transferred == Trak::NotTransferred)
        {
            // tool is currently available
            ui->missingCheckBox->setDisabled(true);
            ui->transferredCheckBox->setDisabled(true);

            ui->serviceableCheckBox->setDisabled(tooldata->serviceable == Trak::Serviceable ? true : false);
        }
        else
        {
            ui->missingCheckBox->setEnabled(true);
            ui->transferredCheckBox->setEnabled(true);
            ui->serviceableCheckBox->setDisabled(tooldata->serviceable == Trak::Serviceable ? true : false);

        }

        // calibration fields
        if (tooldata->calibration == Trak::CalibratedTool)
        {
            ui->requiresCalibCheckBox->setChecked(true);
            ui->calibratedCheckBox->setVisible(true);
            ui->calibrationDateEdit->setVisible(true);
        }
        else
        {
            ui->requiresCalibCheckBox->setChecked(false);
            ui->calibratedCheckBox->setVisible(false);
            ui->calibrationDateEdit->setVisible(false);
        }
        if (tooldata->calibrated == Trak::Yes)
        {
            ui->calibratedCheckBox->setChecked(true);
        }
        else
        {
            ui->calibratedCheckBox->setChecked(false);
        }
        ui->calibrationDateEdit->setDate(tooldata->currentCalibrationDate);
    }
}



void ToolsManager::clearToolDetailDisplay()
{
    qDebug() << "UserScreen::clearToolDetailDisplay()";
    // tool description fields
    ui->toolNumLbl->setText("");
    ui->stockCodeLbl->setText("");
    ui->descLbl->setText("");
    ui->statusLbl->setText("");

    // status fields
    ui->serviceableCheckBox->setChecked(false);
    ui->transferredCheckBox->setChecked(false);
    ui->missingCheckBox->setChecked(false);

    // calibration fields
    ui->requiresCalibCheckBox->setChecked(false);
    ui->calibratedCheckBox->setVisible(false);
    ui->calibrationDateEdit->setVisible(false);
    ui->calibratedCheckBox->setVisible(false);
    //ui->calibrationDateEdit->setDate(tooldata->currentCalibrationDate);

    currentToolData = NULL;
}




//
//  Writes the changes to the tool to the database
//

void ToolsManager::updateChanges()
{
    if (currentToolData == NULL)
    {
        qWarning() << "ToolsManager::updateChanges() No tool data to update ";
        return;
    }

    // Check for tool removed
    if((currentToolData->status == currentToolData->prevstatus) && currentToolData->status == Trak::Issued)
    {
        // tool has been removed for service or transfer

    }



    // has there been a change?
    bool changed = toolChanged();
    ToolData* tooldata = currentToolData;
    qInfo() << "ToolsManager::updateChanges() for tool number " << tooldata->toolNumber << " in drawer" << tooldata->drawerNum;

//    if (changed)
//    {
//        qInfo() << "    Data has changed";
//    }
//    else
//    {
//        qInfo() << "    Data has NOT changed";
//        return;
//    }

    if (tooldata->status == tooldata->prevstatus)
    {
        if (tooldata->status == Trak::Issued)
        {
            // tool has been taken
            if (tooldata->status == Trak::Issued) tooldata->prevstatus = Trak::Returned; else tooldata->prevstatus = Trak::Issued;
            tooldata->missing = (ui->missingCheckBox->isChecked() ? Trak::ToolRemoved : Trak::ToolAvaliable);
            tooldata->transferred = (ui->transferredCheckBox->isChecked() ? Trak::Transferred : Trak::NotTransferred);
            tooldata->serviceable = (ui->serviceableCheckBox->isChecked() ? Trak::Serviceable : Trak::Unserviceable);
            MainController::getDataManagerInstance()->updateToolFromToolData(tooldata->drawerNum, tooldata->toolNumber);
            qInfo() << "Tool manager updating Tool drawer/tool/status/removed/transferred/serviceable"
                    << tooldata->drawerNum << tooldata->toolNumber
                    << (tooldata->status == Trak::Issued ? "Issued" : "Returned")
                    << (tooldata->missing == Trak::ToolRemoved ? "Removed" : "Available")
                    << (tooldata->transferred == Trak::Transferred ? "Transferred" : "NotTransferred")
                    << (tooldata->serviceable == Trak::Serviceable ? "Serviceable" : "Unserviceable");
        }
        else
        {
            // tool has been returned
            if (tooldata->status == Trak::Issued) tooldata->prevstatus = Trak::Returned; else tooldata->prevstatus = Trak::Issued;
            tooldata->missing = (ui->missingCheckBox->isChecked() ? Trak::ToolRemoved : Trak::ToolAvaliable);
            tooldata->transferred = (ui->transferredCheckBox->isChecked() ? Trak::Transferred : Trak::NotTransferred);
            tooldata->serviceable = (ui->serviceableCheckBox->isChecked() ? Trak::Serviceable : Trak::Unserviceable);
            MainController::getDataManagerInstance()->updateToolFromToolData(tooldata->drawerNum, tooldata->toolNumber);
            qInfo() << "Tool manager updating Tool drawer/tool/status/removed/transferred/serviceable"
                    << tooldata->drawerNum << tooldata->toolNumber
                    << (tooldata->status == Trak::Issued ? "Issued" : "Returned")
                    << (tooldata->missing == Trak::ToolRemoved ? "Removed" : "Available")
                    << (tooldata->transferred == Trak::Transferred ? "Transferred" : "NotTransferred")
                    << (tooldata->serviceable == Trak::Serviceable ? "Serviceable" : "Unserviceable");
            // clear transaction record if it exists
            MainController::getDataManagerInstance()->updateToolTransactionStatus(tooldata->drawerNum, tooldata->toolNumber, tooldata->status, tooldata->itemId);
        }
    }
    else if (tooldata->status == Trak::Issued)
    {
        if (ui->missingCheckBox->isChecked())  // marked to be removed
        {
            tooldata->missing = (ui->missingCheckBox->isChecked() ? Trak::ToolRemoved : Trak::ToolAvaliable);
            tooldata->transferred = Trak::NotTransferred;  // cannot be transferred
            tooldata->serviceable = Trak::Serviceable;
            MainController::getDataManagerInstance()->updateToolFromToolData(tooldata->drawerNum, tooldata->toolNumber);
            qInfo() << "Tool manager updating Tool drawer/tool/status/removed/transferred/serviceable"
                    << tooldata->drawerNum << tooldata->toolNumber
                    << (tooldata->status == Trak::Issued ? "Issued" : "Returned")
                    << (tooldata->missing == Trak::ToolRemoved ? "Removed" : "Available")
                    << (tooldata->transferred == Trak::Transferred ? "Transferred" : "NotTransferred")
                    << (tooldata->serviceable == Trak::Serviceable ? "Serviceable" : "Unserviceable");
            // clear transaction record if it exists
            MainController::getDataManagerInstance()->updateToolTransactionStatus(tooldata->drawerNum, tooldata->toolNumber, Trak::Returned, tooldata->itemId);

        }
    }
    else // tool not out
    {
        if ((tooldata->missing == Trak::ToolMissing) != ui->missingCheckBox->isChecked())
        {
            qInfo() << "    Update missing to " << ui->missingCheckBox->isChecked();
            MainController::getDataManagerInstance()->updateToolMissing(tooldata->drawerNum, tooldata->toolNumber,
                                                                        (ui->missingCheckBox->isChecked() ? Trak::ToolMissing : Trak::ToolNotMissing));
        }

        if ((tooldata->serviceable == Trak::Serviceable) != ui->serviceableCheckBox->isChecked())
        {
            qInfo() << "    Update servicable to " << ui->serviceableCheckBox->isChecked();
            tooldata->serviceable = (ui->serviceableCheckBox->isChecked() ? Trak::Serviceable : Trak::Unserviceable);
            MainController::getDataManagerInstance()->updateToolServiceable(tooldata);
        }

        if ((tooldata->transferred == Trak::Transferred) != ui->transferredCheckBox->isChecked())
        {
            qInfo() << "    Update transferred to " << ui->transferredCheckBox->isChecked();
            tooldata->transferred = (ui->transferredCheckBox->isChecked() ? Trak::Transferred : Trak::NotTransferred);
            //MainController::getDataManagerInstance()->updateToolTransferred(tooldata);
        }
    }

    if ((tooldata->calibration == Trak::CalibratedTool) != ui->requiresCalibCheckBox->isChecked()||
        (tooldata->calibrated == Trak::Yes) != ui->calibratedCheckBox->isChecked() ||
        (tooldata->currentCalibrationDate) != ui->calibrationDateEdit->date())
    {
        tooldata->calibration = (ui->requiresCalibCheckBox->isChecked() ? Trak::CalibratedTool : Trak::NonCalibratedTool);
        if(tooldata->calibration == Trak::CalibratedTool)
        {
            tooldata->calibrated = (ui->calibratedCheckBox->isChecked() ? Trak::Yes : Trak::No);
            tooldata->lastCalibrationDate = tooldata->currentCalibrationDate;
            tooldata->currentCalibrationDate = ui->calibrationDateEdit->date();
        }
        qInfo() << "    Update calibration information ";
        MainController::getDataManagerInstance()->updateToolCalibrationInfo(tooldata);
    }
//    updateToolDisplay(tooldata->drawerNum, tooldata->toolNumber);
}




bool ToolsManager::toolChanged()
{
    // has there been a change?
    bool changed = false;
    ToolData* tooldata = currentToolData;

    if ((tooldata->serviceable == Trak::Serviceable) != ui->serviceableCheckBox->isChecked())
    {
        changed = true;
    }
    if ((tooldata->transferred == Trak::Transferred) != ui->transferredCheckBox->isChecked())
    {
        changed = true;
    }
    if ((tooldata->missing == Trak::ToolMissing) != ui->missingCheckBox->isChecked())
    {
        changed = true;
    }
    if ((tooldata->calibration == Trak::CalibratedTool) != ui->requiresCalibCheckBox->isChecked())
    {
        changed = true;
    }
    if ((tooldata->calibrated == Trak::Yes) != ui->calibratedCheckBox->isChecked())
    {
        changed = true;
    }
    if ((tooldata->currentCalibrationDate) != ui->calibrationDateEdit->date())
    {
        changed = true;
    }
    return changed;
}


//void ToolsManager::updateToolDisplay(int drwnum, int toolnum)
//{
//    // change status in the display list for the drawer
//    MainController::getDataManagerInstance()->setToolStatus(drwnum, toolnum, true);

//    // update tool display
//    DrawerList* list = MainController::getDataManagerInstance()->getTooldisplayList(drwnum);
//    MainController::getMainViewInstance()->updateToolStatusView(drwnum, toolnum, true, list);

//}



void ToolsManager::reqCalibrationChange(int state)
{
    if(currentToolData != NULL)
    {
        if (ui->requiresCalibCheckBox->isChecked())
        {
            ui->calibratedCheckBox->setVisible(true);
            ui->calibrationDateEdit->setVisible(true);
            ui->calibratedCheckBox->setVisible(true);
            //ui->calibrationDateEdit->setDate(currentToolData->currentCalibrationDate);
        }
        else
        {
            ui->calibratedCheckBox->setVisible(false);
            ui->calibrationDateEdit->setVisible(false);
            ui->calibratedCheckBox->setVisible(false);
        }
    }
}




void ToolsManager::removedChange(int state)
{
    qDebug() << "ToolsManager::removedChange() Changed to " << ui->missingCheckBox->isChecked();
    if(currentToolData != NULL)
    {
//        if((currentToolData->status == currentToolData->prevstatus) && currentToolData->status == Trak::Issued)
//        {
//            qDebug() << "ToolsManager::removedChange() Changed transferredCheckBox to " << !ui->missingCheckBox->isChecked();
//            ui->transferredCheckBox->setChecked(!ui->missingCheckBox->isChecked());
//        }

        if (ui->missingCheckBox->isChecked())
        {
            // uncheck transfer if checked
            if (ui->transferredCheckBox->isChecked())
            {
                ui->transferredCheckBox->setChecked(false);
            }
        }
    }
}





void ToolsManager::transferredChange(int state)
{
    qDebug() << "ToolsManager::transferredChange() Changed to " << ui->transferredCheckBox->isChecked();
    if(currentToolData != NULL)
    {
//        if((currentToolData->status == currentToolData->prevstatus) && currentToolData->status == Trak::Issued)
//        {
//            qDebug() << "ToolsManager::transferredChange() Changed missingCheckBox to " << !ui->transferredCheckBox->isChecked();
//            ui->missingCheckBox->setChecked(!ui->transferredCheckBox->isChecked());
//        }
        if (ui->transferredCheckBox->isChecked())
        {
            // uncheck missing if checked
            if (ui->missingCheckBox->isChecked())
            {
                ui->missingCheckBox->setChecked(false);
            }
        }
    }
}





//void ToolsManager::serviceableConstraint(ToolData* tooldata)
//{
//    if (ui->serviceableCheckBox->isChecked())
//    {
//        if (currentToolPresent == true && tooldata->missing == Trak::ToolWithdrawn && tooldata->transferred == Trak::Transferred)
//        {
//            ui->serviceableCheckBox->setEnabled(true);
//        }
//        else
//        {
//            ui->serviceableCheckBox->setEnabled(false);
//        }
//    }
//    else{
//        if (currentToolPresent == true && tooldata->missing == Trak::ToolWithdrawn && tooldata->transferred == Trak::Transferred)
//        {
//            ui->serviceableCheckBox->setEnabled(true);
//        }
//        else
//        {
//            ui->serviceableCheckBox->setEnabled(false);
//        }
//    }
//}


