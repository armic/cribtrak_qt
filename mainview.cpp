

#include "mainview.h"
#include "maincontroller.h"




//
//  This class controlls the different screen views
//  The main screen views are:
//      GuestScreen
//      UserScreen
//      AdminScreen
//

MainView::MainView(QWidget *parent) : QWidget(parent)
{

//
//  using stacked widgets for main screens
    stackedWidget = new QStackedWidget(this);

    // stack the screens
    guestScreenInstance = new GuestScreen(stackedWidget);
    userScreenInstance = new UserScreen(stackedWidget);
    adminScreenInstance = new adminscreen(stackedWidget);
    stackedWidget->addWidget(guestScreenInstance);
    stackedWidget->addWidget(userScreenInstance);
    stackedWidget->addWidget(adminScreenInstance);

    stackedWidget->setCurrentWidget(guestScreenInstance);

    // setup user screen
    userScreenInstance->setupScreen();
    // setup admin screen
    adminScreenInstance->setupScreen();




    mainWindowLayout = new QVBoxLayout;
    mainWindowLayout->addWidget(stackedWidget);
    mainWindowLayout->layout()->setContentsMargins(0,0,0,0);
    setLayout(mainWindowLayout);

    // get screen size from ini file
    QSettings settings("trak.ini", QSettings::IniFormat);
    settings.beginGroup("System");
    QString fullscreen = settings.value("FullScreen", "yes").toString();
    if (fullscreen == "yes")
    {
        setWindowState(Qt::WindowFullScreen);
//        setMaximumSize(1024, 768);
//        setMinimumSize(1024, 768);
        qDebug() << __FUNCTION__ << "Window size:" << this->geometry();
    }
    settings.endGroup();

    // setup some connections
    connect (userScreenInstance, &UserScreen::toolServiceableBtn, this, &MainView::toolServiceableBtnPressed);


    show();

}



//
//  Add the graphics items and scenes to the DrawerList for display in user mode.
//

//void MainView::buildUserDrawerScenes()
//{
//    userScreenInstance->buildDrawerScenes();
//}



void MainView::userButton()
{
    ;

}










void MainView::processSwitchClicked()
{
    stackedWidget->setCurrentWidget(userScreenInstance);  // just for testing

}








//void MainView::keyPressEvent(QKeyEvent* event){
//    qDebug() << "MainView keyevent" << event->key();
//}



//
//  message box class functions
//

void MyMessageBox::setTimeoutValue(int time)
{
    timeout = time;
    setStyleSheet("QMessageBox {font-size:20px; background-color: red; color: white; }"
                  "QMessageBox QLabel {color: white;}");
}

int MyMessageBox::exec()
{
    QTimer::singleShot(timeout * 1000, this, SLOT(reject()));
    return QMessageBox::exec();
}






//
//  setGuestScreen
//  Bring forth the guest screen
//  and setup ready to use it
//
void MainView::setGuestScreen()
{
    stackedWidget->setCurrentWidget(guestScreenInstance);

    MainController::getMainControllerInstance()->setAppMode(MainController::guestMode);

}


//
//  backToGuestMode
//  Return to guest mode, need to set screen
//
void MainView::backToGuestMode()
{
    setGuestScreen();
    guestScreenInstance->setScreen();
    // lock drawers
//    MainController::getCabinetManagerInstance()->lockDrawers();
    qInfo() << "MainView::backToGuestMode() set guest screen and locked drawers";

}




//
// setUserScreen
// Bring forth the user screen
// and setup ready to use it
//
void MainView::setUserScreen()
{
    stackedWidget->setCurrentWidget(userScreenInstance);

    // reset nonconstant fields
    userScreenInstance->setScreen();

    MainController::getMainControllerInstance()->setAppMode(MainController::userMode);
    MainController::getMainControllerInstance()->setDrawerMode(MainController::drawerClosedMode);

//    userScreenInstance->setDrawerClosedView();

    // unlock drawers
//    MainController::getCabinetManagerInstance()->unlockDrawers();
    qInfo() << "MainView::setUserScreen() set user screen and unlocked drawers";

    //  set tools out count for this user
    MainController::getDataManagerInstance()->toolsOutForUser(MainController::getDataManagerInstance()->currentUser.userId);

    // CribTRAK version of tools out count.
    qDebug() << __FUNCTION__ << "Current user:" << MainController::getDataManagerInstance()->currentUser.userId;
    qDebug() << __FUNCTION__ << "Tools out:" << MainController::getDataManagerInstance()->getToolsOutCountForUser(MainController::getDataManagerInstance()->currentUser.userId);
    userScreenInstance->setUserNumToolsOut(MainController::getDataManagerInstance()->getToolsOutCountForUser(MainController::getDataManagerInstance()->currentUser.userId));

    // make independent fnc
//    userScreenInstance->updateUserBalanceDisplay();
}



//void MainView::setUserDrawerOpenedView(int dnum, DrawerList* list)
//{
//    qDebug() << "MainView::setUserDrawerOpenedView drawer " << dnum;
//    userScreenInstance->setDrawerOpenView(dnum, list);
//}

//void MainView::setUserDrawerClosedView(int dnum)
//{
//    qDebug() << "MainView::setUserDrawerClosedView drawer " << dnum;
//    userScreenInstance->setDrawerClosedView();

//}


// NOTE: This method now does nothing. Keeping it in case this functionality is needed.
void MainView::updateToolStatusView(int dnum, int toolnum, bool out, DrawerList* list)
{
//    qDebug() << "MainView::updateToolStatusView drawer " << dnum;
//    userScreenInstance->updateToolDisplay(dnum, list);

    // make independent fnc
//    if (MainController::getMainControllerInstance()->getAppMode() != MainController::toolsAdminMode)
//    {
//        userScreenInstance->updateUserBalanceDisplay();
//    }
}


// NOTE: Temporary(?) removal of tool detail view.

//void MainView::updateToolDetailView(int drwnum, int toolnum, bool out)
//{

//QString userid = QString("");
//QString user = QString("");

//    Tool* tool = MainController::getDataManagerInstance()->getToolDetail(drwnum, toolnum);
//    ToolData* tooldata = MainController::getDataManagerInstance()->getToolData(drwnum, toolnum);
//    if (tool && tooldata)
//    {
//        qDebug() << "MainController::onDrawerToolChanged() updating tool detail" << tool->stockCode << tool->name;
////        if (out)
//        if (tool->state == ToolStates::TOOL_OUT || tool->state == ToolStates::TOOL_OTHER_USER)
//        {
//            userid = MainController::getDataManagerInstance()->findToolUser(drwnum, toolnum, DataManager::Issued);
//            user = MainController::getDataManagerInstance()->getUserName(userid);
//            if (user.isEmpty() && tool->state == ToolStates::TOOL_OUT)
//            {
//                // assuming current user just removed it
//                user = MainController::getDataManagerInstance()->currentUser.name;
//            }
//        }
//        currentToolDetail = tooldata;
//        userScreenInstance->updateToolDetail(tool->stockCode, tool->name, tool->toolNumber, tool->state, user);

//        // update the tool serviceable button
////        if (MainController::getDataManagerInstance()->currentUser.adminPriv == false && tooldata->serviceable == Trak::Unserviceable)
//        if (tooldata->serviceable == Trak::Unserviceable || tooldata->status == Trak::Issued)
//        {
//            userScreenInstance->updateToolServiceChange(true, tooldata->serviceable);
//        }
//        else
//        {
//            userScreenInstance->updateToolServiceChange(false, tooldata->serviceable);
//        }
//    }
//}


//
// setAdminScreen
// Bring forth the admin screen
// and setup ready to use it
//
void MainView::setAdminScreen()
{
    stackedWidget->setCurrentWidget(adminScreenInstance);
    MainController::getMainControllerInstance()->setAppMode(MainController::adminMode);

    // reset nonconstant fields
    adminScreenInstance->setScreen();

}



void MainView::toolServiceableBtnPressed()
{
    qDebug() << "mainView::toolServiceableBtnPressed()";
    emit changeToolService(currentToolDetail);
}


void MainView::setToolServiceScreen()
{
    stackedWidget->setCurrentWidget(userScreenInstance);

    // reset nonconstant fields
    userScreenInstance->setScreen();

    MainController::getMainControllerInstance()->setAppMode(MainController::toolsAdminMode);
    MainController::getMainControllerInstance()->setDrawerMode(MainController::drawerClosedMode);

//    userScreenInstance->setDrawerClosedView();

    // unlock drawers
//    MainController::getCabinetManagerInstance()->unlockDrawers();
//    qInfo() << "MainView::setToolServiceScreen() set user screen and unlocked drawers";

    //  set tools out count for this user
//    MainController::getDataManagerInstance()->toolsOutForUser(MainController::getDataManagerInstance()->currentUser.userId);

    // make independent fnc
//    userScreenInstance->updateUserBalanceDisplay();

    // display the tool manager dialog
    //toolsManager = new ToolsManager();
    toolsManager = new ToolsManager(userScreenInstance);
    //toolsManager->setAttribute(Qt::WA_ShowWithoutActivating);
    toolsManager->setWindowFlags(Qt::WindowStaysOnTopHint);
    //toolsManager->setWindowFlags(Qt::FramelessWindowHint);

//    qDebug() << "MainView::setToolServiceScreen()" << userScreenInstance->toolManagerAnchor();
    // set toolmanager position
//    toolsManager->move(userScreenInstance->toolManagerAnchor());

    userScreenInstance->setFocus();
    //userScreenInstance->setWindowState( Qt::WindowFullScreen | Qt::WindowActive);
    qDebug() << "MainView::setToolServiceScreen() showing tools manager";
    toolsManager->show();
    qDebug() << "MainView::setToolServiceScreen() leaving tools manager";
}





