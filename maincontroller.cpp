
#include <QSound>
#include <QDialog>
//#include <QMessageBox>

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#include "trakcore.h"
#include "maincontroller.h"
#include "version.h"


//
//  the MainController is the controller of the application (hopefully)
//  It will start the
//      forntend (view)
//      backend
//      state machine
//
//  The application has three static instance variables for
//      MainController, mainView and backend. These are accessable by getter functions.
//


MainController::MainController(QWidget *parent)
    : QObject(parent)
{

    //this->installEventFilter(new mainEventFilter());

    // init main app static global variable
    mainControllerInstance = this;

    // splashscreen display
    splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":images/images/splash.png"));
    QFont splashFont;
    splashFont.setBold(true);
    splashFont.setPixelSize(20);
    splash->setFont(splashFont);
    splash->show();

    Qt::Alignment topLeft = Qt::AlignLeft | Qt::AlignTop;
    splash->showMessage("Initialising Main Controller", topLeft, Qt::white);

    // setup message logging
    qInstallMessageHandler(messageOutputBeforeInit);

    qDebug() << "Initialising iToolBox";
    qInfo() << "Initialising iToolBox ";

    // set default modes
    setAppMode(initMode);
    setDrawerMode(drawerClosedMode);
    currentOpenedDrawer = 0;
    drawersOpenCount = 0;


    // check that trak.ini file exists
    if (QFile::exists("trak.ini"))
    {
        qDebug() << "trak.ini exists";
    }
    else
    {
        qCritical() << "trak.ini does not exist, do NOT continue";
        splash->showMessage("trak.ini does NOT exist", topLeft, Qt::red);

        MyMessageBox msgBox;
        msgBox.setText("trak.ini file does NOT exist. Closing Kabtrak");
        msgBox.setTimeoutValue(5);
        msgBox.exec();
        qCritical() << "MainController::MainController() Bye Bye";
        requestExit(Trak::NoIniFile);
    }

    QSettings settings("trak.ini", QSettings::IniFormat);
    int val;



    // setup sounds and alarms
    splash->showMessage("Setting sounds and alarms", topLeft, Qt::white);
    toolReturnAlarm = new QSoundEffect();
    toolReturnAlarm->setSource(QUrl("qrc:/sounds/sounds/emergency005.wav"));
    toolReturnAlarm->setLoopCount(QSoundEffect::Infinite);
    toolReturnAlarm->setVolume(0.9f);
    toolIssuePing = new QSoundEffect();
    toolIssuePing->setSource(QUrl("qrc:/sounds/sounds/issue.wav"));
    toolIssuePing->setLoopCount(1);
    toolIssuePing->setVolume(0.9f);
    toolReturnPing = new QSoundEffect();
    toolReturnPing->setSource(QUrl("qrc:/sounds/sounds/return.wav"));
    toolReturnPing->setLoopCount(1);
    toolReturnPing->setVolume(0.9f);
    toolReturnBleep = new QSoundEffect();
    toolReturnBleep->setSource(QUrl("qrc:/sounds/sounds/alert.wav"));
    toolReturnBleep->setLoopCount(1);
    toolReturnBleep->setVolume(0.9f);

    settings.beginGroup("Cabinet");
    val = settings.value("allowSounds", 0).toInt();
    settings.endGroup();
    allowSounds = val == 1 ? true : false;


    // initialise locale if needed


    // Initialise scanner manager.
    qDebug() << "Initialising ScannerManager";
    this->scannerManagerInstance = new ScannerManager(this);


    // initialise and setup the Cabinet manager
    //    Will not return if cannot connect to cabinet
//    splash->showMessage("Constructing Cabinet Manager", topLeft, Qt::white);
//    this->cabinetManagerInstance = new CabinetManager(this);


    // mark the drawers that are present
    // this info comes from the cabinet hardware.
    // Now we can use the bool drawerExist(drwnum) function.
//    splash->showMessage("Checking drawers present", topLeft, Qt::white);
//    cabinetManagerInstance->checkDrawersPresent();


    // connect to the backend so we can initialise database etc
    //   Will not return if it cannot connect to the database
    splash->showMessage("Initialising Data Manager", topLeft, Qt::white);
    this->dataManagerInstance = new DataManager(this);
    if(!dataManagerInstance->databaseConnected())
    {
        qCritical() << "Could not connect to database";
        splash->showMessage("Could not connect to database", topLeft, Qt::red);

    }
    else
    {
        qInfo() << "Connected to database";
        splash->showMessage("Connected to database", topLeft, Qt::white);
    }


    // Create tools data array
//    splash->showMessage("Create tools data array", topLeft, Qt::white);
//    dataManagerInstance->buildToolsDataArray();

    // build the tools array for each drawer.
//    splash->showMessage("Create tools drawer data", topLeft, Qt::white);
//    dataManagerInstance->buildToolsDrawerArray();

    // Create the tools out model
    splash->showMessage("Tools out model", topLeft, Qt::white);
    dataManagerInstance->createToolsOutModel(this);

    // load the model for the users enabled for this kabtrak unit.
    splash->showMessage("Load Users", topLeft, Qt::white);
    dataManagerInstance->loadUserModel(this);


    // initialise cabinet manager
//    splash->showMessage("Initialising Cabinet Manager", topLeft, Qt::white);
//    cabinetManagerInstance->initCabinetManager();

    // check the database tool status matches the cabinet.
//    splash->showMessage("Compare tools in database to cabinet", topLeft, Qt::white);
//    dataManagerInstance->compareCabinetToDatabase();

    // Create the frontend ie the view
    splash->showMessage("Create front end view", topLeft, Qt::white);
    this->mainViewInstance = new MainView();

    // set signal/slots for the unsloicited data changes
//    connect(cabinetManagerInstance, &CabinetManager::drawerOpenChanged,this, &MainController::onDrawerOpenChanged);
//    connect(cabinetManagerInstance, &CabinetManager::drawerLightChanged,this, &MainController::onDrawerLightChanged);
//    connect(cabinetManagerInstance, &CabinetManager::drawerToolChanged,this, &MainController::onDrawerToolChanged, Qt::QueuedConnection);
//    connect(cabinetManagerInstance, &CabinetManager::confirmButtonPushed,this, &MainController::onConfirmButton);

    connect(scannerManagerInstance, &ScannerManager::barcodeScanned, this, &MainController::onBarcodeScanned);

    connect(mainViewInstance->userScreenInstance, &UserScreen::consumableIssueSelected, this, &MainController::onConsumableIssueSelected);
    connect(mainViewInstance->userScreenInstance, &UserScreen::consumableReturnSelected, this, &MainController::onConsumableReturnSelected);

    // setup the tool graphics etc
    splash->showMessage("Setup tool graphics", topLeft, Qt::white);
//    mainViewInstance->buildUserDrawerScenes();
    connect (mainViewInstance, &MainView::changeToolService, this, &MainController::changeToolServiceableStatus);

    connect(mainViewInstance->userScreenInstance, &UserScreen::kitIssueOK, this, &MainController::onKitIssueOK);
    connect(mainViewInstance->userScreenInstance, &UserScreen::kitIssueCancelled, this, &MainController::onKitIssueCancelled);

    connect(mainViewInstance->userScreenInstance, &UserScreen::toolMarkedUnserviceable, this, &MainController::onToolMarkedUnserviceable);

    // setup message logging
    qInstallMessageHandler(messageOutput);

    splash->close();
    delete(splash);

    // NOTE: Added this to ensure guestMode is set on startup.
    setAppMode(guestMode);
}

MainController::~MainController()
{

}


void MainController::requestExit(int reason)
{
    exitApp(reason);
}

void MainController::exitApp(int reason)
{
    // hsd trouble terminating kabtrak because Cabinet is running a thread with blocking.
    // So used a sledge hammer to stop process with TerminateProcess()

    qCritical() << "MainController::exitApp() Bye Bye with error number " << reason;
    HANDLE processHandle;

    if ((processHandle = GetCurrentProcess()) != NULL)
    {
        qCritical() << "Terminate process" << processHandle;
        TerminateProcess(processHandle, reason);
    }
}

bool MainController::allsWell()
{
    return true;//(cabinetManagerInstance->cabinetConnected() && dataManagerInstance->databaseConnected());
}

//
// the getter functions for the static instances variables
//

MainController* MainController::mainControllerInstance = NULL;
MainController* MainController::getMainControllerInstance()
{
    return mainControllerInstance;
}

MainView* MainController:: mainViewInstance = NULL;
MainView* MainController::getMainViewInstance()
{
    return mainViewInstance;
}

DataManager* MainController:: dataManagerInstance = NULL;
DataManager* MainController::getDataManagerInstance()
{
    return dataManagerInstance;
}

ScannerManager* MainController::scannerManagerInstance = NULL;
ScannerManager *MainController::getScannerManagerInstance()
{
    return scannerManagerInstance;
}


//CabinetManager* MainController:: cabinetManagerInstance = NULL;
//CabinetManager* MainController::getCabinetManagerInstance()
//{
//    return cabinetManagerInstance;
//}



//
//  sets the prefix for the output and writes to a file
//

void MainController::messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile file(QDate::currentDate().toString("cribtrak-yyyy_MM_dd.log"));

    if (!file.open(QIODevice::Append | QIODevice::Text)) return;

    QTextStream out(&file);
    out << QTime::currentTime().toString("hh:mm:ss.zzz ");

    switch (type)
    {
        case QtDebugMsg:    out << "DBG"; break;
        case QtInfoMsg:     out << "INF"; break;
        case QtWarningMsg:  out << "WRN"; break;
        case QtCriticalMsg: out << "CRT"; break;
        case QtFatalMsg:    out << "FTL"; break;
    }

    QString str = "";
    if (mainControllerInstance->appMode == userMode || mainControllerInstance->appMode == adminMode || mainControllerInstance->appMode == toolsAdminMode)
    {
        str = str + "[" + dataManagerInstance->currentUser.name + "] ";
    }
    out << " KabTrak: " << str << msg << '\n';
    out.flush();
}


void MainController::messageOutputBeforeInit(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile file(QDate::currentDate().toString("cribtrak-yyyy_MM_dd.log"));

    if (!file.open(QIODevice::Append | QIODevice::Text)) return;

    QTextStream out(&file);
    out << QTime::currentTime().toString("hh:mm:ss.zzz ");

    switch (type)
    {
        case QtDebugMsg:    out << "DBG"; break;
        case QtInfoMsg:     out << "INF"; break;
        case QtWarningMsg:  out << "WRN"; break;
        case QtCriticalMsg: out << "CRT"; break;
        case QtFatalMsg:    out << "FTL"; break;
    }

    out << " KabTrak: " << msg << '\n';
    out.flush();
}



//
//  Application mode handling
//  To help keep track of the different application modes
//

void MainController::setAppMode(int mode)
{
    appMode = mode;
    qInfo() << "Application mode set to " << displayMode(mode);
}

int MainController::getAppMode()
{
    return appMode;
}

void MainController::setDrawerMode(int mode)
{
    drawerMode = mode;
    qInfo() << "Drawer mode set to " << displayMode(mode);
}

int MainController::getDrawerMode()
{
    return drawerMode;
}

QString MainController::displayMode(int mode)
{
    return  mode == initMode ? "initMode" :
            mode == guestMode ? "guestMode" :
            mode == userMode ? "userMode" :
            mode == drawerClosedMode ? "drawerClosedMode" :
            mode == drawerOpenMode ? "drawerOpenMode" :
            mode == adminMode ? "adminMode" :
            mode == toolsAdminMode ? "toolsAdminMode" : "unknownMode";
}




//
//  Drawer change processing
//      The onDrawerOpenChanged() slot receives the status change and
//      will process the data depending on the appMode and DrawerMode.
//

//void MainController::onDrawerOpenChanged(int dnum, DrawerStatus* drawer)
//{
//    qInfo() << "Drawer " << dnum << " has just been " << (drawer->drawerOpen ? "opened" : "closed");
//    qInfo() << "Entry Application Mode " << displayMode(appMode) << ", Drawer Mode " << displayMode(drawerMode);

//    quint64 memusage = readMemoryUsage();
//    qDebug() << "MainController::onDrawerOpenChanged() PagefileUsage" << memusage;

//    // Set the allowSounds local variable just in case it has changed
//    allowSounds = dataManagerInstance->currentCabinet.allowSounds;

//    // Sanity checks
//    // adjust drawers open count
//    if (drawer->drawerOpen == true)
//    {
//        drawersOpenCount++;
//    }
//    else
//    {
//        drawersOpenCount--;
//    }
//    if(drawersOpenCount > 1)
//    {
//        qWarning() << "MainController::onDrawerOpenChange() There are " << drawersOpenCount << " drawers open ";
//    }
//    if(drawersOpenCount < 0)
//    {
//        qWarning() << "MainController::onDrawerOpenChange() There are " << drawersOpenCount << " negative drawers open ";
//    }



//    if (getAppMode() == userMode)
//    {
//        if (drawer->drawerOpen == true)
//        {
//            if (getDrawerMode() == drawerClosedMode)
//            {
//                // drawer has just been opened, set mode and display tools
//                setDrawerMode(drawerOpenMode);
//                setDrawerOpened(dnum, drawer);
//                currentOpenedDrawer = dnum;
//            }
//            else
//            {
//                // problem, a drawer already open
//                qWarning() << "MainController::onDrawerOpenChanged a drawer already open!!!";
//                // is it the same drawer?
//                if (currentOpenedDrawer == dnum)
//                {
//                    qWarning() << "MainController::onDrawerOpenChange() This drawer opened same as current drawer opened " << currentOpenedDrawer << dnum;
//                }
//                else if (currentOpenedDrawer >= Trak::MinDrawerNumber && currentOpenedDrawer <= Trak::MaxDrawerNumber)
//                {
//                    // close current open drawer to save status
//                    qWarning() << "MainController::onDrawerOpenChange() Closing previous open drawer " << currentOpenedDrawer;
//                    //setDrawerClosed(currentOpenedDrawer, drawer);
//                    // maybe just save all drawer status changes?
//                    dataManagerInstance->updateToolsChangedAllDrawers();    // update all drawers !!!
//                    // open new drawer
//                    setDrawerMode(drawerOpenMode);
//                    setDrawerOpened(dnum, drawer);
//                    currentOpenedDrawer = dnum;
//                }
//                else
//                {
//                    // no valid drawer open, just open new drawer
//                    qWarning() << "MainController::onDrawerOpenChange() No current drawer open so status is wrong " << currentOpenedDrawer << dnum;
//                    setDrawerMode(drawerOpenMode);
//                    setDrawerOpened(dnum, drawer);
//                    currentOpenedDrawer = dnum;
//                }
//            }
//        }
//        else  // drawer closed mode
//        {
//            if (getDrawerMode() == drawerOpenMode)
//            {
//                // drawer has just been closed, set mode and display tools
//                setDrawerMode(drawerClosedMode);
//                setDrawerClosed(dnum, drawer);
//            }
//            else
//            {
//                // problem, a drawer already closed
//                qWarning() << "MainController::onDrawerOpenChanged a drawer already closed!!!";
//            }
//        }
//    }
//    else if (getAppMode() == toolsAdminMode)
//    {
//        if (drawer->drawerOpen == true)
//        {
//            // let tools manager know
//            mainViewInstance->toolsManager->onDrawerChanged(dnum, drawer->drawerOpen);
//            if (getDrawerMode() == drawerClosedMode)
//            {
//                // drawer has just been opened, set mode and display tools
//                setDrawerMode(drawerOpenMode);
//                setDrawerOpened(dnum, drawer);
//                currentOpenedDrawer = dnum;
//            }
//            else
//            {
//                // problem, a drawer already open
//                qWarning() << "MainController::onDrawerOpenChanged a drawer already open!!!";
//                // is it the same drawer?
//                if (currentOpenedDrawer == dnum)
//                {
//                    qWarning() << "MainController::onDrawerOpenChange() This drawer opened same as current drawer opened " << currentOpenedDrawer << dnum;
//                }
//                else if (currentOpenedDrawer >= Trak::MinDrawerNumber && currentOpenedDrawer <= Trak::MaxDrawerNumber)
//                {
//                    // close current open drawer to save status
//                    qWarning() << "MainController::onDrawerOpenChange() Closing previous open drawer " << currentOpenedDrawer;
//                    //setDrawerClosed(currentOpenedDrawer, drawer);
//                    // maybe just save all drawer status changes?
//                    dataManagerInstance->updateToolsChangedAllDrawers();    // update all drawers !!!
//                    // open new drawer
//                    setDrawerMode(drawerOpenMode);
//                    setDrawerOpened(dnum, drawer);
//                    currentOpenedDrawer = dnum;
//                }
//                else
//                {
//                    // no valid drawer open, just open new drawer
//                    qWarning() << "MainController::onDrawerOpenChange() No current drawer open so status is wrong " << currentOpenedDrawer << dnum;
//                    setDrawerMode(drawerOpenMode);
//                    setDrawerOpened(dnum, drawer);
//                    currentOpenedDrawer = dnum;
//                }
//            }
//        }
//        else  // drawer closed mode
//        {
//            // let tools manager know
//            mainViewInstance->toolsManager->onDrawerChanged(dnum, drawer->drawerOpen);
//            if (getDrawerMode() == drawerOpenMode)
//            {
//                // drawer has just been closed, set mode and display tools
//                setDrawerMode(drawerClosedMode);
//                setDrawerClosed(dnum, drawer);
//            }
//            else
//            {
//                // problem, a drawer already closed
//                qWarning() << "MainController::onDrawerOpenChanged a drawer already closed!!!";
//            }
//        }
//        // let tools manager know
////        mainViewInstance->toolsManager->onDrawerChanged(dnum, drawer->drawerOpen);

//    }
//    else
//    {
//        // wrong mode, ignore message
//        qWarning() << "MainController::onDrawerOpenChanged Wrong mode ignore change";
//    }
//    qInfo() << "Leave Application Mode " << displayMode(appMode) << ", Drawer Mode " << displayMode(drawerMode);
//}


//
//  Drawer has opened, need to set lights on, gather tool dada from
//  dataManager and set the tool display.
//

//void MainController::setDrawerOpened(int dnum, DrawerStatus* drawer)
//{
//    // turn lights on
//    cabinetManagerInstance->setDrawerLightsOn(dnum);

//    // Create tool data model with current tool state
//    dataManagerInstance->updateToolsDrawer(dnum);
//    DrawerList* list = dataManagerInstance->getDrawerTools(dnum);
////    QAbstractTableModel* model = dataManagerInstance->getToolModelForDrawer(dnum);

//    //  set tools out count for this user
//    //dataManagerInstance->toolsOutForUser(dataManagerInstance->currentUser.userId);

//    mainViewInstance->setUserDrawerOpenedView(dnum, list);

//}




////
////  Drawer has closed, need to update tool status in the database
////
//void MainController::setDrawerClosed(int dnum, DrawerStatus* drawer)
//{

//    mainViewInstance->setUserDrawerClosedView(dnum);

//    // double check tool status is correct
////    dataManagerInstance->checkToolStatusBeforeUpdate(dnum);

//    // turn lights off
//    cabinetManagerInstance->setDrawerLightsOff(dnum);

//    // update tools that have changed status
//    dataManagerInstance->updateToolsChanged(dnum);
//    dataManagerInstance->updateToolsChangedAllDrawers();    // update all drawers !!!
//    //dataManagerInstance->updateToolsStatusChange(dnum);

//    // refresh tools out model
//    dataManagerInstance->refreshToolsOut();

//    //  sound alarm if necessary
//    if (dataManagerInstance->currentCabinet.allowReturnByOthers == false && illegalReturnListCount() > 0)
//    {
//        illegalReturnAlarmOn();
//    }
//}



//void MainController::onDrawerLightChanged(int dnum, struct DrawerStatus* drawer)
//{

//    qInfo() << "MainController::onDrawerLightChanged() Drawer " << dnum << " light has just been turned " << (drawer->lightOn ? "on" : "off");
//}





//
//  A tool in a drawer has been removed or returned. Need to
//      set status in toolTable
//      set status in display list
//      update the display of tools
//


//void MainController::onDrawerToolChanged(int dnum, int toolnum, bool out)
//{

//    qDebug() << "MainController::onDrawerToolChanged Drawer/tool/out " << dnum << toolnum << out ;

//    if (dnum < Trak::MinDrawerNumber || dnum > Trak::MaxDrawerNumber)
//    {
//        qWarning() << "MainController::onDrawerToolChanged() Invalid drawer number: " << dnum;
//        return;
//    }

//    qInfo() << "MainController::onDrawerToolChanged() before checking";
//    logToolState(dnum, toolnum);

//    // checked if logged on here and exit if not.



//    //qDebug() << "MainController::onDrawerToolChanged() tool data" << toolData.drawerNum << toolData.toolNumber << toolData.description;

//    int sts = out==true ? DataManager::Issued : DataManager::Returned;

//    // is this admin tools manager mode?
//    if (getAppMode() == MainController::toolsAdminMode)
//    {
//        qInfo() << "In tools admin mode";
//        mainViewInstance->toolsManager->onDrawerToolChanged(dnum, toolnum, sts);
//        return;
//    }




//    if (sts == Trak::Returned)
//    {
//        if (!returningTool(dnum, toolnum))
//        {
//            qWarning() << "Not updating tool display for returned tool";
//            logToolState(dnum, toolnum);
//            return;
//        }
//    }
//    else
//    {
//        if (!issuingTool(dnum, toolnum))
//        {
//            qWarning() << "Not updating tool display for issued tool";
//            logToolState(dnum, toolnum);
//            return;
//        }
//    }




//    if (sts == DataManager::Returned)
//    {
//        if (allowSounds) toolReturnPing->play();
//    }
//    else
//    {
//        if (allowSounds) toolIssuePing->play();
//    }

//    qInfo() << "MainController::onDrawerToolChanged() after checking";
//    logToolState(dnum, toolnum);

//    qInfo() << "Updating tool display ";

//    // change status in the display list for the drawer
//    dataManagerInstance->setToolStatus(dnum, toolnum, sts);
////    if (!dataManagerInstance->isToolMissing(dnum, toolnum))
////    {
////        dataManagerInstance->incToolsOutForUser(dnum, sts);
////    }

//    // update tool display
//    DrawerList* list = dataManagerInstance->getTooldisplayList(dnum);
//    mainViewInstance->updateToolStatusView(dnum, toolnum, out, list);

//    mainViewInstance->updateToolDetailView(dnum, toolnum, out);

//}



//
//  returningTool function
//


bool MainController::returningTool(int dnum, int toolnum)
{

    ToolData* tool = dataManagerInstance->getToolData(dnum, toolnum);

    if (tool == NULL)
    {
        qWarning() << "Returned tool does not exist " << dnum << toolnum;
        return false;
    }

    qInfo() << "[" << dataManagerInstance->currentUser.name << "] Returning tool " << toolnum << " in drawer " << dnum;

    if(isToolOnIllegalList(dnum,toolnum))
    {
        qDebug() << "        MainController::issuingTool() On illegal list Drawer/tool " << dnum << toolnum;
        removeFromIllegalReturnList(dnum, toolnum);
        if (illegalReturnListCount() == 0)
        {
            //removeIllegalReturnMessage();
            mainViewInstance->userScreenInstance->clearWrongUserRetrunMsg();
            illegalReturnAlarmOff();
        }
        else
        {
            displayNextIllegalMessage();
        }
        if (allowSounds) toolIssuePing->play();
        return false;
    }

    int userAccess = dataManagerInstance->getUserAccessType(dataManagerInstance->currentUser.userId);
    QString tooluser = dataManagerInstance->findToolUser(dnum, toolnum, DataManager::Issued);
    qDebug() << "      MainController::returningTool() RETURN Drawer/tool/thisUser/toolUser/thisUserAccess " << dnum << toolnum << dataManagerInstance->currentUser.userId << tooluser << userAccess;


    if (tool->status == Trak::Returned)
    {
        qWarning() << "        Returned tool is not out " << dnum << toolnum;
        return false;
    }

    // missing tool?
    if (tool->missing == Trak::ToolMissing)
    {
        // tool is missing
        qWarning() << "        Trying to return missing tool " << dnum << toolnum;
        qDebug() << "        MainController::returningTool() Tool missing. Add to illegal list Drawer/tool " << dnum << toolnum;
        displayIllegalReturnMessage(dnum, toolnum, dataManagerInstance->currentUser.userId, Trak::Returned);
        addToIllegalReturnList(dnum, toolnum, dataManagerInstance->currentUser.userId, Trak::Returned);
        if (allowSounds) toolReturnBleep->play();

        return false;   // do not want to update display!!
    }

    if (!tooluser.isNull() && !tooluser.isEmpty() && tooluser != dataManagerInstance->currentUser.userId)
    {
        // Tool NOT issued to current user
        qInfo() << "        Tool NOT issued to current user, issued to  " << dataManagerInstance->getUserName(tooluser);
        qDebug() << "        MainController::returningTool() This userAccess/ allowed " << userAccess <<  dataManagerInstance->currentCrib.allowReturnByAdmin;
        if (userAccess == Trak::AdminAccess && dataManagerInstance->currentCrib.allowReturnByAdmin == true)
        {
            // admin user can return tool
            // do nothing but fall through
            qInfo() << "        Manager returning tool issued to " << dataManagerInstance->getUserName(tooluser);
        }
        else if (dataManagerInstance->currentCrib.allowReturnByOthers == true)
        {
            qInfo() << "        Returning tool issued to " << dataManagerInstance->getUserName(tooluser);

        }
        else
        {
            qWarning() << "        This user cannot return tool issued to " << dataManagerInstance->getUserName(tooluser);
            qDebug() << "        MainController::returningTool() Add to illegal list Drawer/tool " << dnum << toolnum;
            displayIllegalReturnMessage(dnum, toolnum, tooluser, Trak::Returned);
            //mainViewInstance->userScreenInstance->displayWrongUserRetrunMsg(dnum, toolnum, tooluser);
            addToIllegalReturnList(dnum, toolnum, tooluser, Trak::Returned);
            if (allowSounds) toolReturnBleep->play();
            return false;   // do not want to update display!!
        }
    }
    else
    {
        // tool return by this user so decrement tool out count for this user
        dataManagerInstance->incToolsOutForUser(dnum, Trak::Returned);

    }

    if (tool->isKit == Trak::AKit)
    {
        if (allowSounds) toolReturnBleep->play();
        qDebug() << "        MainController::returningTool() Waiting for kit confirmation " << dnum << toolnum;

        QString str = QString("The tool you are returning is a kit. Please confirm all %1 tools are included").arg(tool->kitcount);
        QMessageBox* msgBox = new QMessageBox();
        msgBox->setText(str);
        msgBox->setAttribute(Qt::WA_DeleteOnClose, true);
        msgBox->show();
        if (allowSounds) toolReturnBleep->play();
//        msgBox->exec();

        qInfo() << "        Confirmed all tools in kit";
    }


    if (tool->serviceable == Trak::Unserviceable)
    {
        // Should never get here because a removed unserviceable tool will also be missing/removed
        qWarning() << "        Tool is unserviceable";

        // if admin user query to change to serviceable.
//        if (userAccess == Trak::AdminAccess)
//        {
//            if (allowSounds) toolReturnBleep->play();
//            QMessageBox::StandardButton reply;
//            reply = QMessageBox::question(NULL, "Unserviceable", "Should this tool be updarted from Unserviceable to Serviceable?",
//                                          QMessageBox::Yes|QMessageBox::No);


//            if (reply == QMessageBox::Yes) {
//                tool->serviceable = Trak::Serviceable;
//                dataManagerInstance->updateToolServiceable(tool);
//                qInfo() << "        Admin user changed tool to servicable";

//            } else {
//                qInfo() << "        Admin user did not change tool to servicable";
//            }
//        }
    }

    if (tool->calibration == Trak::CalibratedTool)
    {
        if (!tool->currentCalibrationDate.isNull() && tool->currentCalibrationDate.isValid())
        {
            // check if tool needs calibtation
            qInfo() << "        Calibratable tool";
            if (tool->currentCalibrationDate < QDate::currentDate())
            {
                qWarning() << "        Tool past calibration date " << tool->currentCalibrationDate;
                if (dataManagerInstance->currentCrib.calibrationUserModeUpdate)
                {
                    if (userAccess == Trak::AdminAccess)
                    {
                        // admin user can return uncalibrated tools
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::question(NULL, "Uncalibrated Tool", "Has tool been calibrated? Should the calibration date be updated?",
                                                      QMessageBox::Yes|QMessageBox::No);
                        if (reply == QMessageBox::Yes) {
                            // update lastCalibrationDate and currentCalibrationDate
                            tool->lastCalibrationDate = tool->currentCalibrationDate;
                            int months = dataManagerInstance->currentCrib.calibration;
                            if (months > 0 && months < 25)
                            {
                                //QDate date = tool->currentCalibrationDate.addMonths(months);
                                QDate date = QDate::currentDate();
                                date = date.addMonths(months);
                                tool->currentCalibrationDate = date;
                                dataManagerInstance->updateToolCalibrationDate(tool);
                                qInfo() << "        Calibration date updated to " << date;
                            }
                        }
                        else
                        {
                            qWarning() << "        Calibration date was not updated";
                        }
                    }
                    else
                    {
                        // user returning uncalibrated tool - error
                        //QMessageBox::warning(0, "Uncalibrated", "Uncalibrated tool is being returned");
                        qWarning() << "        Uncalibrated tool is being returned";
                        QMessageBox* msgBox = new QMessageBox();
                        msgBox->setText("Uncalibrated tool is being returned");
                        msgBox->setAttribute(Qt::WA_DeleteOnClose, true);
                        msgBox->show();
                        QTimer::singleShot(2000, msgBox, SLOT(close()));
                        if (allowSounds) toolReturnBleep->play();
                    }
                }
                else
                {
                    // uncalibrated tool has to be marked as unserviceable
                    tool->serviceable = Trak::Unserviceable;
                    qWarning() << "        Tool past calibration date, marked as Unserviceable";
                }
            }
            else if (dataManagerInstance->currentCrib.calibrationVerify)
            {
                // request calibration verification
                if (allowSounds) toolReturnBleep->play();
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(NULL, "Uncalibrated Tool", "Confirm tool is in calibration",
                                              QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::No)
                {
                    // mark tool unserviceable
                    tool->serviceable = Trak::Unserviceable;
                    qWarning() << "        Tool not in calibration, marked as Unserviceable";
                }
                else
                {
                    qInfo() << "        Tool is in calibration";
                }

            }
        }
        else
        {
            qWarning() << "        Invalid calibration date";
        }
    }
    tool->status = Trak::Returned;
    tool->changed = true;
    return true;
}



bool MainController::issuingTool(int dnum, int toolnum)
{



    ToolData* tool = dataManagerInstance->getToolData(dnum, toolnum);

    qInfo() << "[" << dataManagerInstance->currentUser.name << "] Issuing tool " << toolnum << " in drawer " << dnum;

    if(isToolOnIllegalList(dnum,toolnum))
    {
        qDebug() << "        MainController::issuingTool() On illegal list Drawer/tool " << dnum << toolnum;
        removeFromIllegalReturnList(dnum, toolnum);
        if (illegalReturnListCount() == 0)
        {
            //removeIllegalReturnMessage();
            mainViewInstance->userScreenInstance->clearWrongUserRetrunMsg();
            illegalReturnAlarmOff();
        }
        else
        {
            displayNextIllegalMessage();
        }
        if (allowSounds) toolIssuePing->play();
        return false;
    }

    if (tool == NULL)
    {
        qWarning() << "        Issued tool does not exist " << dnum << toolnum;
        return false;
    }


    int userAccess = dataManagerInstance->getUserAccessType(dataManagerInstance->currentUser.userId);
    QString tooluser = dataManagerInstance->findToolUser(dnum, toolnum, DataManager::Issued);
    qDebug() << "        MainController::issuingTool() ISSUE Drawer/tool/thisUser/toolUser/thisUserAccess " << dnum << toolnum << dataManagerInstance->currentUser.userId << tooluser << userAccess;

    // missing tool?
    if (tool->missing == Trak::ToolMissing)
    {
        // tool is missing
        qWarning() << "        Issued tool marked as missing " << dnum << toolnum;
        if (allowSounds) toolReturnBleep->play();
        tool->status = Trak::Issued;     // ???? IS THIS RIGHT???
        tool->changed = true;
        return true;
    }

    if (!tooluser.isNull() && !tooluser.isEmpty())
    {
        qWarning() << "        Issued tool is already out to " << dataManagerInstance->getUserName(tooluser);
        // but maybe tool was just returned by admin user and then removed again?
        if (tool->changed && tool->status == Trak::Returned)
        {
            // the tool has to be issued to someone so leave as original user
            tool->status = Trak::Issued;
            tool->changed = false;
            qWarning() << "        Tool was previously returned by this admin user so ignore original change ";
            if (dataManagerInstance->currentUser.userId == tooluser)
            {
                // same user so increment tool count
                dataManagerInstance->incToolsOutForUser(dnum, Trak::Issued);
            }
            return true;
        }
        qWarning() << "        Should never happen, issue to current user ";
        tool->status = Trak::Issued;
        tool->changed = true;
        return true;
    }


    qDebug() << "        MainController::issuingTool() ISSUE Drawer/tool " << dnum << toolnum;
    if (tool->serviceable == Trak::Unserviceable)
    {
        qInfo() << "        Tool is unserviceable";

        qWarning() << "        Unserviceable tool cannot taken ";
        qDebug() << "        MainController::returningTool() Add to illegal list Drawer/tool " << dnum << toolnum;
        displayIllegalReturnMessage(dnum, toolnum, tooluser, Trak::Issued);
        addToIllegalReturnList(dnum, toolnum, tooluser, Trak::Returned);
        if (allowSounds) toolReturnBleep->play();
        return false;   // do not want to update display!!

//        if (userAccess == Trak::AdminAccess)
//        {
//            qInfo() << "        Unserviceable tool issued to admin user";
//        }
//        else
//        {
////            QMessageBox::question(NULL, "Unserviceable", "This tool is unserviceable and should not be used!!",
////                                          QMessageBox::Ok);
//            qWarning() << "        Unserviceable tool has been removed by unortherized user";
//            QMessageBox* msgBox = new QMessageBox();
//            msgBox->setText("This tool is unserviceable and should not be used");
//            msgBox->setAttribute(Qt::WA_DeleteOnClose, true);
//            msgBox->show();
//            QTimer::singleShot(2000, msgBox, SLOT(close()));
//            if (allowSounds) toolReturnBleep->play();
//        }
    }

    if (tool->calibration == Trak::CalibratedTool)
    {
        // check if tool needs calibtation
        qInfo() << "        Calibratable tool";
        if (!tool->currentCalibrationDate.isNull() && tool->currentCalibrationDate.isValid())
        {
            if (tool->currentCalibrationDate < QDate::currentDate())
            {
                if (userAccess == Trak::AdminAccess)
                {
                    qInfo() << "        Uncalibrated tool being issued to admin user";
                    //QMessageBox::warning(0, "Uncalibrated", "Uncalibrated tool is being issued", QMessageBox::Ok);
                    QMessageBox* msgBox = new QMessageBox();
                    msgBox->setText("Uncalibrated tool is being issued");
                    msgBox->setAttribute(Qt::WA_DeleteOnClose, true);
                    msgBox->show();
                    QTimer::singleShot(2000, msgBox, SLOT(close()));
                    if (allowSounds) toolReturnBleep->play();
                }
                else
                {
                    qWarning() << "        Uncalibrated tool issued to non admin user";
                    //QMessageBox::warning(0, "Uncalibrated", "Uncalibrated tool is being issued", QMessageBox::Ok);
                    QMessageBox* msgBox = new QMessageBox();
                    msgBox->setText("Uncalibrated tool is being issued");
                    msgBox->setAttribute(Qt::WA_DeleteOnClose, true);
                    msgBox->show();
                    QTimer::singleShot(2000, msgBox, SLOT(close()));
                    if (allowSounds) toolReturnBleep->play();
                }
            }
        }
        else
        {
            qWarning() << "        Invalid calibration date";
        }
    }
    tool->status = Trak::Issued;
    tool->changed = true;
    // tool issued to this user so increment tool out count for this user
    dataManagerInstance->incToolsOutForUser(dnum, Trak::Issued);
    return true;
}

// Issue tool or increment number of consumables out.
// NOTE: Never gets called.
//void MainController::issueCurrentTool(QString barcode, int quantity)
//{
//    qDebug() << __FUNCTION__;
//    int toolRecord = dataManagerInstance->findCribToolTransaction(toolData.toolId, Trak::Issued, dataManagerInstance->currentUser.userId);

//    if (toolRecord > -1)
//    {
//        // TODO: Increment quantity.
//        mainViewInstance->userScreenInstance->toolIssued(toolData.description);
//    }
//    else
//    {
//        // Tool not found. Issue it.
//        dataManagerInstance->insertCribToolTransaction(Trak::Issued, toolData.itemId, toolData.toolId, barcode, quantity);
//        mainViewInstance->userScreenInstance->toolIssued(toolData.description);
//    }
//}








//
//  Confirm button processing
//      The onDrawerOpenChanged() slot receives the status change and
//      will process the data depending on the appMode and DrawerMode.
//

void MainController::onConfirmButton()
{

    if (getAppMode() == userMode && getDrawerMode() == drawerClosedMode)
    {
        qInfo() << __FUNCTION__ << "Returning to guest mode";
        setAppMode(guestMode);
        mainViewInstance->userScreenInstance->cancelProgressBarTimer();
        // go back from user screen to guest screen
        mainViewInstance->backToGuestMode();
    }
    else if (getAppMode() == toolsAdminMode && getDrawerMode() == drawerClosedMode)
    {
        qInfo() << __FUNCTION__ << "Exit tools manager and returning to guest mode";
        setAppMode(guestMode);
        // go back from user screen to guest screen
        mainViewInstance->backToGuestMode();
        delete mainViewInstance->toolsManager;
    }
    else
    {
        // wrong mode, ignore message
        qWarning() << "MainController::onConfirmButton Wrong mode ignore change";
    }
}

void MainController::onConsumableIssueSelected(int num)
{
    qDebug() << __FUNCTION__ << "Request to issue" << num << "consumables of type" << toolData.description;
    int transactionId = dataManagerInstance->findCribToolTransaction(toolData.toolId, Trak::Issued, dataManagerInstance->currentUser.userId);
    if (transactionId > -1)
    {
        dataManagerInstance->changeConsumableAmount(transactionId, num);
        dataManagerInstance->changeConsumableBalance(toolData.toolId, -num);
    }
    else
    {
        dataManagerInstance->insertCribToolTransaction(Trak::Issued, toolData.itemId, toolData.toolId, toolData.barcode, num);
        dataManagerInstance->setCribToolStatus(toolData.toolId, Trak::Issued);
        dataManagerInstance->changeConsumableBalance(toolData.toolId, -num);
    }
    //mainViewInstance->userScreenInstance->itemScanned(toolData.description + "\n(" + QString::number(num) + ")", true);
    showIssuedMessage(true, num);
    mainViewInstance->userScreenInstance->setUserNumToolsOut(dataManagerInstance->getToolsOutCountForUser(dataManagerInstance->currentUser.userId));
}

void MainController::onConsumableReturnSelected(int num, bool used)
{
    qDebug() << __FUNCTION__ << "Request to return" << num << "consumables of type" << toolData.description << "used:" << used;
    int transactionId = dataManagerInstance->findCribToolTransaction(toolData.toolId, Trak::Issued, dataManagerInstance->currentUser.userId);
    if (transactionId > -1)
    {
        int numIssued = dataManagerInstance->getNumConsumablesIssued(transactionId);
        qDebug() << __FUNCTION__ << "Number of consumables of type" << toolData.description << "issued:" << numIssued;
        if (num >= numIssued)
        {
            dataManagerInstance->updateCribToolTransactionWithId(transactionId, Trak::Returned);
            dataManagerInstance->setCribToolStatus(toolData.toolId, Trak::Returned);

            if (!used)
            {
                dataManagerInstance->changeConsumableBalance(toolData.toolId, num);
            }
            else
            {
                dataManagerInstance->removeUsedConsumables(toolData.toolId, num);
            }
            //mainViewInstance->userScreenInstance->itemScanned(toolData.description + "\n(All returned)", false);
            showReturnedMessage(true, num);
        }
        else
        {
            qDebug() << __FUNCTION__ << "Adjusting the number of consumables issued by" << -num;
            dataManagerInstance->changeConsumableAmount(transactionId, -num);
            if (!used)
            {
                dataManagerInstance->changeConsumableBalance(toolData.toolId, num);
            }
            else
            {
                dataManagerInstance->removeUsedConsumables(toolData.toolId, num);
            }
            //mainViewInstance->userScreenInstance->itemScanned(toolData.description + "\n(" + QString::number(num) + ")", false);
            showReturnedMessage(true, num);
            qDebug() << __FUNCTION__ << "Amount issued remaining:" << dataManagerInstance->getNumConsumablesIssued(transactionId);
        }
    }
    else
    {
        // FIXME: Adds consumables when it shouldn't do anything to the database. User cannot return items not issued!
        // dataManagerInstance->insertCribToolTransaction(Trak::Issued, toolData.itemId, toolData.barcode, num);
    }
    mainViewInstance->userScreenInstance->setUserNumToolsOut(dataManagerInstance->getToolsOutCountForUser(dataManagerInstance->currentUser.userId));
}





//
//  Illegal return list functions
//

void MainController::addToIllegalReturnList(int drwnum, int toolnum, QString user, int action)
{
    ToolUser str;
    str.drawerNum = drwnum;
    str.toolNum = toolnum;
    str.userId = user;
    str.action = action;
    illegalReturn.append(str);
}

void MainController::removeFromIllegalReturnList(int drwnum, int toolnum)
{
    for (int i = 0; i < illegalReturn.count(); i++)
    {
        if (illegalReturn[i].drawerNum == drwnum && illegalReturn[i].toolNum == toolnum)
        {
            illegalReturn.removeAt(i);
            break;
        }
    }
}

int MainController::illegalReturnListCount()
{
    return illegalReturn.count();
}

bool MainController::isToolOnIllegalList(int drwnum,int toolnum)
{
    for (int i = 0; i < illegalReturn.count(); i++)
    {
        if (illegalReturn[i].drawerNum == drwnum && illegalReturn[i].toolNum == toolnum)
        {
            return true;
        }
    }
    return false;
}


void MainController::displayNextIllegalMessage()
{
    if (illegalReturnListCount() > 0)
    {
        displayIllegalReturnMessage(illegalReturn[0].drawerNum, illegalReturn[0].toolNum, illegalReturn[0].userId, illegalReturn[0].action);
    }
}


void MainController::displayIllegalReturnMessage(int dnum, int toolnum, QString tooluser, int action)
{

    qDebug() << "MainController::removeIllegalReturnMessage() DISPLAYING MSG BOX";

    Tool* tool = MainController::getDataManagerInstance()->getToolDetail(dnum, toolnum);
    mainViewInstance->userScreenInstance->displayWrongUserRetrunMsg(dnum, toolnum, tool->name, action);

}

void MainController::removeIllegalReturnMessage()
{
    qDebug() << "MainController::removeIllegalReturnMessage() CLOSSING MSG BOX";
    illegalReturnMsg.setVisible(false);
    //illegalReturnMsg.close();

    illegalReturnAlarmOff();

}


void MainController::illegalReturnAlarmOn()
{
    qDebug() << "MainController::illegalReturnAlarmOn()";
    toolReturnAlarm->play();
}

void MainController::illegalReturnAlarmOff()
{
    qDebug() << "MainController::illegalReturnAlarmOff()";
    toolReturnAlarm->stop();
}




void MainController::changeToolServiceableStatus(ToolData* tool)
{
    qDebug() << "MainController::changeToolServiceableStatus()";
    if (tool->serviceable == Trak::Unserviceable)
    {
        tool->serviceable = Trak::Serviceable;
    }
    else
    {
        tool->serviceable = Trak::Unserviceable;
    }
    dataManagerInstance->updateToolServiceable(tool);
    // Change the tool display status
    dataManagerInstance->setToolStatus(tool->drawerNum, tool->toolNumber, tool->status);
    // update tool display
//    DrawerList* list = dataManagerInstance->getTooldisplayList(tool->drawerNum);
//    mainViewInstance->updateToolStatusView(tool->drawerNum, tool->toolNumber, true, list);

    // NOTE: Commented out tool views to clean up user screen.
    // update the tool serviceable button
//    if (dataManagerInstance->currentUser.adminPriv == false && tool->serviceable == Trak::Unserviceable)
    if (tool->serviceable == Trak::Unserviceable || tool->status == Trak::Issued)
    {
        //mainViewInstance->userScreenInstance->updateToolServiceChange(true, tool->serviceable);
    }
    else
    {
        //mainViewInstance->userScreenInstance->updateToolServiceChange(false, tool->serviceable);
    }
    qInfo() << "Changed tool " << tool->toolNumber << " drawer " << tool->drawerNum << " servicable to " << (tool->serviceable == Trak::Unserviceable ? "Unserviceable" : "Serviceable");
}

void MainController::onBarcodeScanned(QString barcode)
{
    qDebug() << __FUNCTION__ << barcode;
    qDebug() << __FUNCTION__ << "AppMode: " << getAppMode();


    // NOTE: getAppMode() returns 0 on startup. Should be 1 as it starts in guest screen.
    // After logging out, function returns correct mode.
    // UPDATE: Tried to fix this by setting guestMode at the end of the initialisation process.
    if (getMainControllerInstance()->getAppMode() == MainController::guestMode)
    {
        qDebug() << __FUNCTION__ << "Barcode scanned while not logged in.";
        return;
    }
    else if (getAppMode() == userMode)
    {
        scannerManagerInstance->setEnabled(false);
        toolData.init(barcode);
        processToolTransaction();
    }
    else if (getAppMode() == adminMode)
    {
        emit adminBarcode(barcode);
    }
}

void MainController::processToolTransaction(bool kitOK)
{
    if (toolData.toolId > -1)
    {
        qDebug() << __FUNCTION__ << "toolData.toolId:" << toolData.toolId;
        qDebug() << __FUNCTION__ << "toolData.description:" << toolData.description;
        qDebug() << __FUNCTION__ << "toolData.kit:" << toolData.kit;
        qDebug() << __FUNCTION__ << "kitOK:" << kitOK;
        qDebug() << __FUNCTION__ << "toolData.currentCalibrationDate.isNull():" << toolData.currentCalibrationDate.isNull();


        int toolRecord = dataManagerInstance->findCribToolTransaction(toolData.toolId, Trak::Issued);

        // NOTE: Temporary setting for testing purposes.
        bool returnable = false;

        int transactionId;
        if (toolData.consumable == 1)
        {
            transactionId = dataManagerInstance->findCribToolTransaction(toolData.toolId, Trak::Issued, dataManagerInstance->currentUser.userId);
            qDebug() << __FUNCTION__ << "userId (consumable):" << dataManagerInstance->currentUser.userId;
            qDebug() << __FUNCTION__ << "transactionId for consumable:" << transactionId;
        }
        else
        {
            transactionId = dataManagerInstance->findCribToolTransaction(toolData.toolId, Trak::Issued);
        }
        int numOut = dataManagerInstance->getNumConsumablesIssued(transactionId);
        if (numOut < 0) numOut = 0;

        int numAvailable = dataManagerInstance->getNumConsumablesAvailable(toolData.toolId);
        if (numAvailable < 0) numAvailable = 0;

        qDebug() << __FUNCTION__ << "Consumable, out, available:" << toolData.consumable << numOut << numAvailable;
        if (toolData.consumable && (numOut == 0) && (numAvailable == 0))
        {
            showError(toolData.description + " is unavailable.");
            return;
        }

        if (toolData.serviceable == Trak::Unserviceable)
        {
            showError(toolData.description + " is marked as unserviceable.\nPlease alert supervisor.");
            return;
        }

        bool notCalibrated = toolData.calibratable && !toolData.currentCalibrationDate.isNull() && (toolData.currentCalibrationDate < QDate::currentDate());

        if ((toolRecord == -1) && !toolData.consumable && notCalibrated)
        {
            showError(toolData.description + " is past its calibration date.\nPlease alert supervisor.");
            return;
        }

        if ((toolData.kit ==Trak::AKit) && !kitOK)
        {
            qDebug() << __FUNCTION__ << "Showing kit screen";
            showKitScreen();
            return;
        }

        if (toolRecord > -1)
        {
            qDebug() << __FUNCTION__ << "Transaction found: " << toolRecord;
            // TODO: Update transaction record.

            if (toolData.consumable == 1)
            {
                // NOTE: toolData.consumed is probably not the correct variable.
                mainViewInstance->userScreenInstance->showConsumableScreen(toolData.description, numOut, numAvailable, returnable);
            }
            else
            {
                if ((dataManagerInstance->cribToolIssuedTo(toolData.toolId, Trak::Issued) == dataManagerInstance->currentUser.userId) || dataManagerInstance->currentUser.adminPriv)
                {
                    dataManagerInstance->updateCribToolTransactionWithId(toolRecord, Trak::Returned);
                    dataManagerInstance->setCribToolStatus(toolData.toolId, Trak::Returned);

                    //mainViewInstance->userScreenInstance->itemScanned(toolData.description, false);
                    showReturnedMessage();
                }
                else
                {
                    showError("Cannot return another user's tool.\nPlease contact supervisor.");
                    //scannerManagerInstance->setEnabled(true);
                }

            }
        }
        else
        {
            if (toolData.consumable == 1)
            {
                mainViewInstance->userScreenInstance->showConsumableScreen(toolData.description, numOut, numAvailable, returnable);
            }
            else
            {
                qDebug() << __FUNCTION__ << "Transaction not found. Creating record.";
                dataManagerInstance->insertCribToolTransaction(Trak::Issued, toolData.itemId, toolData.toolId, toolData.barcode);
                dataManagerInstance->setCribToolStatus(toolData.toolId, Trak::Issued);

                //mainViewInstance->userScreenInstance->itemScanned(toolData.description, true);
                showIssuedMessage();
            }
        }
    }
    else
    {
        showError(QString("Item not found in cribTRAK database.\nAdvise supervisor to enrol item.\nBarcode: %1").arg(toolData.barcode));
        //scannerManagerInstance->setEnabled(true);
    }

    mainViewInstance->userScreenInstance->setUserNumToolsOut(dataManagerInstance->getToolsOutCountForUser(dataManagerInstance->currentUser.userId));
}

void MainController::onKitIssueCancelled()
{
    showReadyScreen();
}

void MainController::onKitIssueOK()
{
    processToolTransaction(true);
}

void MainController::onToolMarkedUnserviceable()
{
    dataManagerInstance->setCribToolServiceable(toolData.toolId, false);
}



void MainController::logToolState(int drwnum, int toolnum)
{
    ToolData* tool = dataManagerInstance->getToolData(drwnum, toolnum);
    qInfo() << "Tool state for tool " << toolnum << " in drawer " << drwnum;
    qInfo() << "    changed     " << tool->changed;
    qInfo() << "    status      " << (tool->status == Trak::Issued ? "Issued" : "Returned");
    qInfo() << "    prevstatus  " << (tool->prevstatus == Trak::Issued ? "Issued" : "Returned");
    qInfo() << "    missing     " << (tool->missing == Trak::ToolMissing ? "Missing" : "Not missing");
    qInfo() << "    serviceable " << (tool->serviceable == Trak::Serviceable ? "Serviceable" : "Unserviceable");
    qInfo() << "    isKit       " << (tool->isKit == Trak::AKit ? "A kit" : "Not a kit");
    qInfo() << "    calibration " << (tool->calibration == Trak::CalibratedTool ? "Calibratable" : "Not calibratable");
}




//
//  Read the current process memory usage
//
quint64 MainController::readMemoryUsage()
{
    HANDLE processHandle;
    PROCESS_MEMORY_COUNTERS pmc;

    if ((processHandle = GetCurrentProcess()) != NULL)
    {
        if (GetProcessMemoryInfo(processHandle, &pmc, sizeof(pmc)))
        {

            //qDebug() << "MainController::readMemoryUsage() PagefileUsage" << pmc.PagefileUsage << sizeof(pmc.PagefileUsage);
            return pmc.PagefileUsage;
        }
    }
    return 0;
}

void MainController::showReadyScreen()
{
    scannerManagerInstance->setEnabled(true);
    mainViewInstance->userScreenInstance->setScreen();
}

void MainController::showIssuedMessage(bool consumable, int num)
{
    scannerManagerInstance->setEnabled(true);
    if (consumable)
    {
        mainViewInstance->userScreenInstance->toolIssued(toolData.description + "\n(" + QString::number(num) + ")");
    }
    else
    {
        mainViewInstance->userScreenInstance->toolIssued(toolData.description);
    }
}

void MainController::showReturnedMessage(bool consumable, int num)
{
    scannerManagerInstance->setEnabled(true);
    if (consumable)
    {
        mainViewInstance->userScreenInstance->toolReturned(toolData.description + "\n(" + QString::number(num) + ")", true);
    }
    else
    {
        mainViewInstance->userScreenInstance->toolReturned(toolData.description);
    }
}

void MainController::cancelTransaction()
{
    scannerManagerInstance->setEnabled(true);
    mainViewInstance->userScreenInstance->setScreen();
}

void MainController::showError(QString error)
{
    mainViewInstance->userScreenInstance->showError("WARNING - TOOL CANNOT BE ISSUED\n" + error);
    scannerManagerInstance->setEnabled(true);
}

void MainController::showKitScreen()
{
    mainViewInstance->userScreenInstance->showKitScreen(toolData.kitcount);
}



