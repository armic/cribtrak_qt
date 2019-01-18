
#include <QDebug>

#include "userscreen.h"
#include "ui_userscreen.h"
#include "maincontroller.h"
//#include "datamanager.h"
#include "trakcore.h"



const QColor UserScreen::toolInColour = QColor(80, 120, 240);             // blue
const QColor UserScreen::toolOutColour = QColor(40, 200, 40);             // green
const QColor UserScreen::toolOtherUserColour = QColor(200, 40, 40);       // red
const QColor UserScreen::toolMissingColour = QColor(200, 200, 200);       // light grey
const QColor UserScreen::toolUnserviceableColour = QColor(200, 100, 40);  // orange
const QColor UserScreen::toolTransferredColour = QColor(200, 0, 200);     // purple




UserScreen::UserScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserScreen)
{
    ui->setupUi(this);


    QSizePolicy sp_retain = ui->consumableUsedButton->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->consumableUsedButton->setSizePolicy(sp_retain);
    ui->consumableUnusedButton->setSizePolicy(sp_retain);

    ui->consumableUsedButton->setVisible(false);
    ui->consumableUnusedButton->setVisible(false);

    ui->lablUsername->setVisible(false);
    ui->ToolDetailFrame->setVisible(false);

}

UserScreen::~UserScreen()
{
    delete ui;
}


//
//  Initialise the user screen and signal/slots
//

// NOTE: Consider renaming this to initialSetup().
void UserScreen::setupScreen()
{
    // setup progress bar
    progressBar = new ProgressBar(MainController::getDataManagerInstance()->currentCrib.userTimeout, ui->progressBar, this);
    connect(progressBar, &ProgressBar::progressBarTimeout,this, &UserScreen::handleProgressBarEnd);


    //ui->closeDrawer->setVisible(true);
    //ui->OpenDrawer->setVisible(false);
    //ui->stackedWidget->setCurrentWidget(ui->readyToScan);

    // set drawer state indicators
//    setDrawerStatusIndicators();



    // sets device status slots
//    connect(MainController::getCabinetManagerInstance(), &CabinetManager::connected, this, &UserScreen::deviceConnected);
//    connect(MainController::getCabinetManagerInstance(), &CabinetManager::disconnected, this, &UserScreen::deviceDisconnected);

    // set tool detail fields
//    toolDetailDisplay();
    //toolServiceChange();

    // setup user balance fields
//    userBalanceDisplay();

    // error message
    createWrongUserReturnMsg();



//    // setup sounds and alarms
//    drawerOpenAlarm = new QSoundEffect();
//    drawerOpenAlarm->setSource(QUrl("qrc:/sounds/sounds/emergency005.wav"));
//    drawerOpenAlarm->setLoopCount(QSoundEffect::Infinite);
//    drawerOpenAlarm->setVolume(0.5f);

//    // sets drawer open message
//    drawerOpenMsg = NULL;

    // setup to displat time and date
    timer =  new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(dateTime()));
    timer->start(1000);


    issuedTimer = new QTimer(this);
    issuedTimer->setSingleShot(true);
    connect(issuedTimer, SIGNAL(timeout()), this, SLOT(onReturnToReadyScan()));
}



void UserScreen::setScreen()
{
    // setup text fields
    DataManager* dataman = MainController::getDataManagerInstance();
    QString str = "%1";
    str = str.arg(dataman->currentUser.name);
    qDebug() << "UserScreen::setScreen() dataman->currentUser.name: " << dataman->currentUser.name;
    ui->currentuser->setText(str);

    ui->lblTailNumber->setText(dataman->currentUser.tailDesc);
    ui->stackedWidget->setCurrentWidget(ui->readyToScan);

    startProgressBarTimer();
}


//
//  display the time and date on the guest screen
//
void UserScreen::dateTime()
{
  QTime time = QTime::currentTime();
  QDate date = QDate::currentDate();
  QString time_text = time.toString("hh:mm:ss AP");
  QString date_text = date.toString("dd/MM/yyyy");
//  ui->lblTime->setText("Time: " + time_text);
//  ui->lblDate->setText("Date: " + date_text);
}




//
// sets the drawer status display to open, closed or not used.
//

//void UserScreen::setDrawerStatusIndicators()
//{

//    for (int i = 1; i <= MaxDrawers; i++)
//    {
//        DrawerStatus* ds = MainController::getCabinetManagerInstance()->getDrawerStatus(i);
//        if (ds != NULL)
//        {
//            int sts = -1;
//            if (ds->present)
//                sts = 0;
//            setDrawerStatusIndicator(i, sts);
//        }
//    }
//}

//void UserScreen::setDrawerStatusIndicator(int drwnum, int drwsts)
//{
//    qDebug() << "UserScreen::setDrawerStatusIndicator() drwnum/status" << drwnum << drwsts;

//    QString img;
//    if (drwsts == 0)
//    {
//        img = ":svg/resources/led_off.svg";
//    }
//    else if (drwsts == 1)
//    {
//        img = ":svg/resources/led_on.svg";
//    }
//    else
//    {
//        img = ":images/bg_led.svg";
//    }


//    switch (drwnum) {
//    case 1:
//        ui->led1->setPixmap(QPixmap(img));
//        break;

//    case 2:
//        ui->led2->setPixmap(QPixmap(img));
//        break;

//    case 3:
//        ui->led3->setPixmap(QPixmap(img));
//        break;

//    case 4:
//        ui->led4->setPixmap(QPixmap(img));
//        break;

//    case 5:
//        ui->led5->setPixmap(QPixmap(img));
//        break;

//    case 6:
//        ui->led6->setPixmap(QPixmap(img));
//        break;

//    case 7:
//        ui->led7->setPixmap(QPixmap(img));
//        break;

//    case 8:
//        ui->led8->setPixmap(QPixmap(img));
//        break;

//    case 9:
//        ui->led9->setPixmap(QPixmap(img));
//        break;

//    case 10:
//        ui->led10->setPixmap(QPixmap(img));
//        break;
//    }

//}




////
////  updates the device status display
////
//void UserScreen::deviceConnected()
//{
//    qDebug() << "UserScreen::deviceConnected()";
//    ui->deviceStatusStrLabel_2->setText("Cabinet connected");
//    ui->deviceStatusLabel->setPixmap(QPixmap(":svg/resources/led_on.svg"));

//}

//void UserScreen::deviceDisconnected()
//{
//    qDebug() << "UserScreen::deviceDisconnected()";
//    ui->deviceStatusStrLabel_2->setText("Cabinet disconnected");
//    ui->deviceStatusLabel->setPixmap(QPixmap(":svg/resources/led_off.svg"));
//    show();
//}







////
////  display drawer closed view
////
//void UserScreen::setDrawerClosedView()
//{
//    qDebug() << "UserScreen::setDrawerClosedView";

//    DataManager* dataman = MainController::getDataManagerInstance();
//    ui->lblTailNumber->setText(dataman->currentUser.tailDesc);
//    ui->closeDrawer->setVisible(true);
//    ui->OpenDrawer->setVisible(false);
//    setDrawerStatusIndicators();
////    if (MainController::getMainControllerInstance()->getAppMode() != MainController::toolsAdminMode)
////    {
//        progressBar->start(MainController::getDataManagerInstance()->currentCabinet.closeDrawerTimeOut);
////    }
//    drawerOpenAlarmOff();       // jic it is on

//    ui->lblDrawerNum->setText("No drawer open");

//    clearToolDetail();
//    disableToolServiceChange();
//    //clearUserBalanceDisplay();
//}



////
////  display drawer open view
////
//void UserScreen::setDrawerOpenView(int dnum, DrawerList* list)
//{

//    qDebug() << "UserScreen::setDrawerOpenView() Calling setDrawer";

//    ui->OpenDrawer->setVisible(true);
//    ui->closeDrawer->setVisible(false);
//    setDrawerStatusIndicator(dnum, 1);
////    if (MainController::getMainControllerInstance()->getAppMode() != MainController::toolsAdminMode)
////    {
//        progressBar->start(MainController::getDataManagerInstance()->currentCabinet.openDrawerTimeout);
////    }

//    QString str = QString("Drawer %1").arg(dnum);
//    ui->lblDrawerNum->setText(str);

//    ui->graphicsView->setScene(sceneArray[dnum-1]);
//    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
//    ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
//    QRectF rect = ui->graphicsView->scene()->itemsBoundingRect();
//    ui->graphicsView->fitInView(rect);
//    currentScene = sceneArray[dnum-1];
//    connect(sceneArray[dnum-1], &QGraphicsScene::selectionChanged, this, &UserScreen::toolSelectionChanged, Qt::UniqueConnection);
//    currentScene->clearSelection();

//    // update the display as it could be set to last user status.
//    updateToolDisplay(dnum, list);

//    qDebug() << "UserScreen::setDrawerOpenView() exit ";
//}

////
////  update tool display
////
//void UserScreen::updateToolDisplay(int dnum, DrawerList* list)
//{
//    (void)dnum;

//    qDebug() << "UserScreen::updateToolDisplay() Calling setDrawer";

//    ui->graphicsView->setScene(sceneArray[dnum-1]);
//    ui->OpenDrawer->setVisible(true);

//    updateDrawerScene(dnum, list);

//    //QRectF rect = scene->itemsBoundingRect();
//    //ui->graphicsView->fitInView(rect);


////    if (MainController::getMainControllerInstance()->getAppMode() != MainController::toolsAdminMode)
////    {
//        progressBar->start(MainController::getDataManagerInstance()->currentCabinet.openDrawerTimeout);
////    }
//    drawerOpenAlarmOff();    // jic

//    qDebug() << "UserScreen::updateToolDisplay";
//}


//void UserScreen::resizeEvent(QResizeEvent *event)
//{
//    qDebug() << "UserScreen::resizeEvent() ";
//    //QGraphicsView::resizeEvent(event);
//    //fitInView(this->sceneRect());
//    //QRectF rect = scene->itemsBoundingRect();
//    QRectF rect = ui->graphicsView->scene()->itemsBoundingRect();
//    ui->graphicsView->fitInView(rect);
//}






bool UserScreen::event(QEvent *event)
{
    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        qDebug() << "UserScreen::event KEY is " << ke->key();

#ifdef TRAK_TESTKEYS
        if (ke->key() == Qt::Key_F1)
        {
            MainController::getScannerManagerInstance()->emitScanSignal("800003");
            return true;
        }
        if (ke->key() == Qt::Key_F2)
        {
            //ui->lblScanMessage->setText("hi");
            //MainController::getMainControllerInstance()->onConfirmButton();
            MainController::getScannerManagerInstance()->emitScanSignal("800095");
            return true;
        }
        if (ke->key() == Qt::Key_F3)
        {
            MainController::getScannerManagerInstance()->emitScanSignal("800002");
            return true;
        }
        if (ke->key() == Qt::Key_F4)
        {
            MainController::getScannerManagerInstance()->emitScanSignal("900003");
            return true;
        }
        if (ke->key() == Qt::Key_F5)
        {
            //ui->lblScanMessage->setText("hi");
            //MainController::getMainControllerInstance()->onConfirmButton();
            MainController::getScannerManagerInstance()->emitScanSignal("123");
            //ui->stackedWidget->setCurrentIndex(!ui->stackedWidget->currentIndex());
            return true;
        }
        if (ke->key() == Qt::Key_F6)
        {
            //ui->lblScanMessage->setText("hi");
            //MainController::getMainControllerInstance()->onConfirmButton();
            //MainController::getScannerManagerInstance()->emitScanSignal("800095");
            //ui->stackedWidget->setCurrentWidget(ui->transactionTypePage);
            return true;
        }
        if (ke->key() == Qt::Key_F7)
        {
            //ui->lblScanMessage->setText("hi");
            //MainController::getMainControllerInstance()->onConfirmButton();
            //MainController::getScannerManagerInstance()->emitScanSignal("800095");
            ui->stackedWidget->setCurrentWidget(ui->kitPage);
            return true;
        }
        if (ke->key() == Qt::Key_F8)
        {
            ui->stackedWidget->setCurrentWidget(ui->consumableOutPage);
            return true;
        }
#endif
        return true;
    }

    return QWidget::event(event);
}



//
//  User mode timeout.
//      if no drawers open logout user
//      if drawer still open then sound alarm
//
void UserScreen::handleProgressBarEnd()
{
    int appmode = MainController::getMainControllerInstance()->getAppMode();
    int drwmode = MainController::getMainControllerInstance()->getDrawerMode();

    qDebug() << "UserScreen::handleProgressBarEnd";
    if ((appmode == MainController::userMode || appmode == MainController::toolsAdminMode) && drwmode == MainController::drawerClosedMode)
    {
        // logout user and go back to guest mode.
        qInfo() << "UserScreen::handleProgressBarEnd() Timeout, forced back to Guest mode";
        MainController::getMainControllerInstance()->onConfirmButton();
    }
    else if ((appmode == MainController::userMode || appmode == MainController::toolsAdminMode) && drwmode == MainController::drawerOpenMode)
    {
        // alarm drawer is open
        qInfo() << "UserScreen::handleProgressBarEnd() Timeout, drawer still open";
//        drawerOpenAlarmOn();
    }
    //MainController::getMainViewInstance()->backToGuestMode();
    progressBar->stop();

}


void UserScreen::cancelProgressBarTimer()
{
    progressBar->stop();
}


void UserScreen::startProgressBarTimer()
{
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.userTimeout);
}

void UserScreen::toolIssued(QString description)
{
//    if (issued)
//    {
//        ui->lblScannedItem->setText("Item issued:\n" + description);
//    }
//    else
//    {
//        ui->lblScannedItem->setText("Item returned:\n" + description);
//    }
//    //ui->stackedWidget->setCurrentIndex(1);
//    ui->stackedWidget->setCurrentWidget(ui->itemScanned);
//    startProgressBarTimer();
//    //progressBar->start(MainController::getDataManagerInstance()->currentCabinet.openDrawerTimeout);
    ui->lblToolIssuedMessage->setText(description);
    ui->stackedWidget->setCurrentWidget(ui->toolIssuedPage);
    issuedTimer->start(2000);
    startProgressBarTimer();
}

void UserScreen::toolReturned(QString description, bool consumable)
{
    ui->lblToolReturnedMessage->setText(description);
    if (consumable)
    {
        ui->unserviceableButton->setVisible(false);
    }
    else
    {
        ui->unserviceableButton->setVisible(true);
    }
    ui->stackedWidget->setCurrentWidget(ui->toolReturnedPage);
    issuedTimer->start(3000);
    startProgressBarTimer();
}

void UserScreen::showError(QString errorString)
{
    ui->lblScanError->setText(errorString);
    //ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->setCurrentWidget(ui->errorPage);

    // NOTE: Should set longer timeout for this occurrence.
    //progressBar->start(MainController::getDataManagerInstance()->currentCabinet.openDrawerTimeout);
}

void UserScreen::showConsumableScreen(const QString description, const int numOut, const int numAvailable, const bool returnable)
{
    maxConsumableReturn = numOut;
    maxConsumableIssue = numAvailable;

    // The following is the simplest way to uncheck all autoexclusive pushbuttons.
    // Simply setting them as unchecked does not work.
    ui->consumableIssuingButton->setAutoExclusive(false);
    ui->consumableReturningButton->setAutoExclusive(false);
    ui->consumableIssuingButton->setChecked(false);
    ui->consumableReturningButton->setChecked(false);
    ui->consumableIssuingButton->setAutoExclusive(true);
    ui->consumableReturningButton->setAutoExclusive(true);


    ui->consumableDescriptionLabel->setText(description + "\n(" + QString::number(numOut) + " out, " + QString::number(numAvailable) + " available)");
//    ui->consumableReturningButton->setEnabled(returnable);

    ui->consumableUsedButton->setAutoExclusive(false);
    ui->consumableUnusedButton->setAutoExclusive(false);
    ui->consumableUsedButton->setChecked(false);
    ui->consumableUnusedButton->setChecked(false);
    ui->consumableUsedButton->setAutoExclusive(true);
    ui->consumableUnusedButton->setAutoExclusive(true);

    ui->consumableReturningButton->setVisible(false);

    ui->consumableIssuingButton->setVisible(true);

    ui->consumableCountSpinBox->setMinimum(1);
    ui->consumableCountSpinBox->setMaximum(maxConsumableIssue);
    ui->consumableCountSpinBox->setValue(1);

    if (numOut == 0)
    {
        ui->consumableReturningButton->setVisible(false);
        ui->consumableUsedButton->setVisible(false);
        ui->consumableUnusedButton->setVisible(false);
        ui->consumableIssuingButton->setChecked(true);
        ui->issueConsumablesButton->setEnabled(true);
    }
    else
    {
        ui->consumableReturningButton->setVisible(true);
        ui->consumableUsedButton->setVisible(false);
        ui->consumableUnusedButton->setVisible(false);
        ui->issueConsumablesButton->setEnabled(false);
        ui->consumableCountSpinBox->setEnabled(false);
    }
    if (numAvailable == 0)
    {
        ui->consumableIssuingButton->setVisible(false);
        ui->consumableReturningButton->setChecked(true);
    }
    ui->stackedWidget->setCurrentWidget(ui->consumableOutPage);
}

void UserScreen::showKitScreen(int kitCount)
{
    ui->kitMessage->setText("This is a kit.\nPlease ensure it contains " + QString::number(kitCount) + " items.");
    ui->stackedWidget->setCurrentWidget(ui->kitPage);
}

void UserScreen::setUserNumToolsOut(int num)
{
    if (num == 0)
    {
        ui->userToolsOutLbl->setText("No tools out");
    }
    else if (num == 1)
    {
        ui->userToolsOutLbl->setText(QString::number(num) + " tool out");
    }
    else
    {
        ui->userToolsOutLbl->setText(QString::number(num) + " tools out");
    }
}



////
////  Display and sound alarm that drawer is open too long
////
//void UserScreen::drawerOpenAlarmOn()
//{
//    drawerOpenAlarm->play();

//    // display warning
//    drawerOpenMsg = new openalarmmessage();
//    drawerOpenMsg->setWindowFlags(Qt::FramelessWindowHint);
//    drawerOpenMsg->show();
//}

//void UserScreen::drawerOpenAlarmOff()
//{
//    drawerOpenAlarm->stop();

//    if (drawerOpenMsg != NULL)
//    {
//        drawerOpenMsg->close();
//        delete(drawerOpenMsg);
//        drawerOpenMsg = NULL;
//    }
//}




//void UserScreen::toolServiceChange()
//{
//    ui->serviceableBtn->setText("Disabled");
//    ui->serviceableBtn->setStyleSheet("background-color: rgb(200, 200, 200);");
//    ui->serviceableBtn->setEnabled(false);
//    connect(ui->serviceableBtn, &QPushButton::clicked,this, &UserScreen::toolServiceBtnClicked);
//}


//void UserScreen::updateToolServiceChange(bool disable, int currentService)
//{
//    if (disable == true)
//    {
//        ui->serviceableBtn->setEnabled(false);
//        ui->serviceableBtn->setVisible(false);
//    }
//    else
//    {
//        if (currentService == Trak::Unserviceable)
//        {
//            // want to make serviceable?
//            ui->serviceableBtn->setText("Mark Serviceable");
//            ui->serviceableBtn->setStyleSheet("background-color: rgb(0, 200, 0);");
//            ui->serviceableBtn->setEnabled(true);
//            ui->serviceableBtn->setVisible(true);
//        }
//        else
//        {
//            ui->serviceableBtn->setText("Mark Unserviceable");
//            ui->serviceableBtn->setStyleSheet("background-color: rgb(200, 0, 0);");
//            ui->serviceableBtn->setEnabled(true);
//            ui->serviceableBtn->setVisible(true);
//        }
//    }
//}


//void UserScreen::disableToolServiceChange()
//{
//    ui->serviceableBtn->setText("Mark Unserviceable");
//    ui->serviceableBtn->setStyleSheet("background-color: rgb(200, 0, 0);");
//    ui->serviceableBtn->setEnabled(false);
//    ui->serviceableBtn->setVisible(false);
//    qDebug() << "UserScreen::disableToolServiceChange()";
//}


void UserScreen::toolServiceBtnClicked()
{
    qDebug() << "UserScreen::toolServiceBtnClicked()";
    emit toolServiceableBtn();
}





//void UserScreen::toolDetailDisplay()
//{
//    toolDetailLayout = new QGridLayout();
//    //ui->ToolDetailFrame->setLayout(toolDetailLayout);
//    QLabel* heading0 = new QLabel("Stock code");
//    QLabel* heading1 = new QLabel("Description");
//    QLabel* heading2 = new QLabel("Tool number");
//    QLabel* heading3 = new QLabel("Status");
//    toolDetailLayout->addWidget(heading0, 0, 0);
//    toolDetailLayout->addWidget(heading1, 1, 0);
//    toolDetailLayout->addWidget(heading2, 2, 0);
//    toolDetailLayout->addWidget(heading3, 3, 0);
//    heading0->setStyleSheet("QLabel {color: white; font-size: 12px; }");
//    heading1->setStyleSheet("QLabel {color: white; font-size: 12px; }");
//    heading2->setStyleSheet("QLabel {color: white; font-size: 12px; }");
//    heading3->setStyleSheet("QLabel {color: white; font-size: 12px; }");

//    value0 = new QLabel("");
//    value1 = new QLabel("");
//    value2 = new QLabel("");
//    value3 = new QLabel("");
//    toolDetailLayout->addWidget(value0, 0, 1);
//    toolDetailLayout->addWidget(value1, 1, 1);
//    toolDetailLayout->addWidget(value2, 2, 1);
//    toolDetailLayout->addWidget(value3, 3, 1);
//    value0->setStyleSheet("QLabel {color: white; font-size: 12px; }");
//    value1->setStyleSheet("QLabel {color: white; font-size: 12px; }");
//    value2->setStyleSheet("QLabel {color: white; font-size: 12px; }");
//    value3->setStyleSheet("QLabel {color: white; font-size: 12px; }");

////    serviceableBtn = new QPushButton("Serviceable?");
////    toolDetailLayout->addWidget(serviceableBtn, 4, 0);
//      ui->serviceableBtn->setStyleSheet("background-color: rgb(240, 240, 240);");
////    serviceableBtn->setVisible(true);
//    //serviceableBtn->setText((name));
//}



//void UserScreen::updateToolDetail(QString stockcode, QString desc, int toolnum, ToolStates status, QString user)
//{
//    qDebug() << "UserScreen::updateToolDetail()" << stockcode << desc << toolnum;
//    value0->setText(stockcode);
//    value1->setText(desc);
//    value2->setText(QString::number(toolnum));
//    QString str = status == ToolStates::TOOL_IN ? "In" : "Out";
//    value3->setText(str);
//    if (status == ToolStates::TOOL_IN)
//    {
//        ui->lablUsername->setText("IS AVAILABLE");
//        ui->lablUsername->setStyleSheet("QLabel {color: blue; }");
//    }
//    else if (status == ToolStates::TOOL_OUT)
//    {
//        ui->lablUsername->setText(QString("Issued to %1").arg(user));
//        ui->lablUsername->setStyleSheet("QLabel {color: green; }");
//    }
//    else if (status == ToolStates::TOOL_OTHER_USER)
//    {
//        ui->lablUsername->setText(QString("Issued to %1").arg(user));
//        ui->lablUsername->setStyleSheet("QLabel {color: red; }");
//    }
//    else if (status == ToolStates::TOOL_MISSING)
//    {
//        ui->lablUsername->setText("TOOL REMOVED");
//        ui->lablUsername->setStyleSheet("QLabel {color: red; }");
//    }
//    else if (status == ToolStates::TOOL_TRANSFERRED)
//    {
//        ui->lablUsername->setText("TOOL TRANSFERRED");
//        ui->lablUsername->setStyleSheet("QLabel {color: red; }");
//    }
//    else if (status == ToolStates::TOOL_UNSERVICEABLE)
//    {
//        ui->lablUsername->setText("TOOL UNSERVICEABLE");
//        ui->lablUsername->setStyleSheet("QLabel {color: red; }");
//    }
//    else
//    {
//        ui->lablUsername->setText("TOOL REMOVED");
//        ui->lablUsername->setStyleSheet("QLabel {color: red; }");
//    }
//}


//void UserScreen::clearToolDetail()
//{
//    ui->lablUsername->setText("");
//    value0->setText("");
//    value1->setText("");
//    value2->setText("");
//    value3->setText("");
//}




//void UserScreen::toolSelectionChanged()
//{
//    //QList<QGraphicsItem *> items = scene->selectedItems();
//    QList<QGraphicsItem *> items = currentScene->selectedItems();
//    if(items.count() > 0)
//    {
//        QGraphicsItem* item = items[0];
//        int drwnum = item->data(UserScreen::DRAWERNUM).toInt();
//        int toolnum = item->data(UserScreen::TOOLNUM).toInt();
//        ToolStates state =  (ToolStates)item->data(UserScreen::STATE).toInt();
//        qDebug() << "UserScreen::toolSelectionChanged() updating tool detail" << drwnum << toolnum;

//        if (MainController::getMainControllerInstance()->getAppMode() == MainController::toolsAdminMode)
//        {
//            qInfo() << "In tools admin mode";
//            MainController::getMainViewInstance()->toolsManager->toolSelectionChanged(drwnum, toolnum);
//        }
//        else
//        {
//            MainController::getMainViewInstance()->updateToolDetailView(drwnum, toolnum, state == ToolStates::TOOL_IN ? false : true);
//        }
//        //currentScene->clearSelection();
//    }
//    qDebug() << "UserScreen::toolSelectionChanged() " << items.count();
//}



//void UserScreen::userBalanceDisplay()
//{
//    userBalanceLayout = new QGridLayout();
//    ui->UserBalanceFrame->setLayout(userBalanceLayout);

//    // NOTE: What are these magic numbers?
//    for (int i=0; i<10+1; i++)
//    {
//        for (int j=0; j<2; j++)
//        {
//            QLabel *lbl = new QLabel("");
//            lbl->setStyleSheet("QLabel {color: white; font: bold 12px }");
//            //lbl->setStyleSheet("QLabel {color: white; font-size: 12px; background-color: rgb(105,105,31057) }");
//            userBalanceLayout->addWidget(lbl, i, j);
//        }
//    }

//}




//void UserScreen::updateUserBalanceDisplay()
//{

//    QGridLayout* layout = userBalanceLayout;
//    QLabel* lbl;

//    clearUserBalanceDisplay();

//    int row = 0;
//    int total = 0;
//    for (int i = 0; i < MaxDrawers; i++)
//    {
//        int cnt = MainController::getDataManagerInstance()->toolsOutCountArray[i];
//        qDebug() << "UserScreen::updateUserBalanceDisplay() " << row << cnt;
//        if (cnt > 0)
//        {
//            lbl = static_cast<QLabel*>(layout->itemAtPosition(row,0)->widget());
//            lbl->setText(QString("Drawer %1").arg(i+1));
//            lbl = static_cast<QLabel*>(layout->itemAtPosition(row,1)->widget());
//            lbl->setText(QString("%1").arg(cnt));
//            row++;
//            total += cnt;
//        }
//    }
//    if (row > 0)
//    {
//        lbl = static_cast<QLabel*>(layout->itemAtPosition(row,0)->widget());
//        lbl->setText(QString("Total "));
//        lbl = static_cast<QLabel*>(layout->itemAtPosition(row,1)->widget());
//        lbl->setText(QString("%1").arg(total));

//    }
//}



//void UserScreen::clearUserBalanceDisplay()
//{
//    QGridLayout* layout = userBalanceLayout;
//    QLabel* lbl;

//    for (int i = 0; i < MaxDrawers+1; i++)
//    {
//        lbl = static_cast<QLabel*>(layout->itemAtPosition(i,0)->widget());
//        lbl->setText(QString(""));
//        lbl = static_cast<QLabel*>(layout->itemAtPosition(i,1)->widget());
//        lbl->setText(QString(""));
//    }
//}



//-------------------------------------------------------------------------
//
//  Setup the drawer scenes
//  The DrawList in data manager and drawer status in cabinet manager
//  need to be initialised first.
//  The scene instance is saved in sceneArray and the svg graphics item and scene
//  is saved in the DrawerList.
//
//-------------------------------------------------------------------------


//void UserScreen::buildDrawerScenes()
//{
//    for (int i=0; i < MaxDrawers; i++)
//    {
//        // does the drawer exist?
//        bool exist = MainController::getCabinetManagerInstance()->drawerExist(i+1);
//        if (exist)
//        {
//            // get tool list for this drawer
//            DrawerList* tools = MainController::getDataManagerInstance()->getDrawerTools(i+1);
//            if (tools != NULL)
//            {
//                sceneArray[i] = buildDrawerScene(i+1, tools);
//            }
//            else
//            {
//                sceneArray[i] = NULL;
//            }
//        }
//        else
//        {
//            sceneArray[i] = NULL;
//        }
//    }
//}

/*--------------------------------------
QGraphicsScene* UserScreen::buildDrawerScene(int drwnum, DrawerList* drawer)
{
    QGraphicsScene* scene = new QGraphicsScene();
    QBrush brush(QColor(0x00, 0x00, 0x00, 255));
    scene->setBackgroundBrush(brush);


    QGraphicsSvgItem *toolitem;

    qDebug() << "UserScreen::buildDrawerScene() Displaying drawer tools/drawer " << drawer->tools.size() << drwnum;
    for(int i = 0; i < drawer->tools.size(); ++i)
    {
        Tool *tool = drawer->tools[i].get();
        QString toolimage = QString("../toolimages/%1").arg(tool->imageID);
        //QString toolimage = QString("../toolimagefiles/svgFromAi/SVG finished/%1").arg(tool->imageID);
        QString defaultimage = QString("../toolimages/%1").arg("J4759_B.svg");
        qDebug() << "UserScreen::buildDrawerScene() image file " << toolimage;
        if (toolimage.endsWith(".svg", Qt::CaseInsensitive))
        {
            // use an image file
            if (QFile(toolimage).exists())
            {
                // image does exist
                qDebug() << "UserScreen::buildDrawerScene() Image exists: " << toolimage;

                toolitem = new QGraphicsSvgItem(toolimage);
                toolitem->setZValue(10);

                // testing elementid method
                QString image = tool->imageID;
                image = image.remove(".svg", Qt::CaseInsensitive);
                toolitem->setElementId(image);
            }
            else
            {
                // no file, use default
                qDebug() << "UserScreen::buildDrawerScene() Use default image: " << defaultimage;
                toolitem = new QGraphicsSvgItem(defaultimage);

                toolitem = new QGraphicsSvgItem(defaultimage);
                toolitem->setElementId("path20");

            }
        }
        else
        {
            // use image from loaded image file
            qDebug() << "UserScreen::buildDrawerScene() Use image from image file: " << tool->imageID;
            QString toolimages = QString("../toolimages/%1").arg("tool_test_001_003.svg");
            toolitem = new QGraphicsSvgItem(toolimages);
            toolitem->setElementId(tool->imageID);

        }

        toolitem->setTransformOriginPoint(toolitem->boundingRect().center());
        // set image size
        toolitem->boundingRect().setSize(QSizeF(tool->transform.width,tool->transform.height));
        // set rotation
        toolitem->setRotation(tool->transform.rotation);
        toolitem->setTransform(QTransform::fromTranslate(tool->transform.x - toolitem->boundingRect().center().x(), tool->transform.y - toolitem->boundingRect().center().y()));

        toolitem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        // add some personal data to item
        toolitem->setData(UserScreen::DESC,tool->name);
        toolitem->setData(UserScreen::STOCKCODE,tool->stockCode);
        toolitem->setData(UserScreen::TOOLNUM,tool->toolNumber);
        toolitem->setData(UserScreen::STATE,(int)tool->state);
        toolitem->setData(UserScreen::DRAWERNUM,tool->drawerNum);


        // Simple way to colour tools.
        QGraphicsColorizeEffect *colour = new QGraphicsColorizeEffect();
        if (tool->state == ToolStates::TOOL_IN) {
            colour->setColor(UserScreen::toolInColour);
        }
        else if (tool->state == ToolStates::TOOL_OUT) {
            colour->setColor(UserScreen::toolOutColour);
        }
        else if (tool->state == ToolStates::TOOL_MISSING) {
            colour->setColor(UserScreen::toolMissingColour);
        }
        else if (tool->state == ToolStates::TOOL_OTHER_USER) {
            colour->setColor(UserScreen::toolOtherUserColour);
        }
        toolitem->setGraphicsEffect(colour);

        // scaling!!!
        QRectF box = toolitem->boundingRect();
        qreal scale = tool->transform.height / box.height();
        toolitem->setScale(scale);

        scene->addItem(toolitem);
        tool->scene = scene;
        tool->svgItem = toolitem;

        qDebug() << "UserScreen::buildDrawerScene" << tool->toolNumber << tool->transform.x << tool->transform.y;
        qDebug() << "UserScreen::buildDrawerScene bounding rectangle " << box.height() << box.width() << tool->transform.height << tool->transform.width << scale;
    }

    return scene;
}
--------------------------*/

//QGraphicsScene* UserScreen::buildDrawerScene(int drwnum, DrawerList* drawer)
//{
//    QGraphicsScene* scene = new QGraphicsScene();
//    QBrush brush(QColor(0x00, 0x00, 0x00, 255));
//    scene->setBackgroundBrush(brush);


//    QGraphicsSvgItem *toolitem;

//    qDebug() << "UserScreen::buildDrawerScene() Displaying drawer tools/drawer " << drawer->tools.size() << drwnum;
//    for(int i = 0; i < drawer->tools.size(); ++i)
//    {
//        Tool *tool = drawer->tools[i].get();
//        QString toolimage = QString("../toolimages/%1").arg(tool->imageID);
//        //QString toolimage = QString("../toolimagefiles/svgFromAi/SVG finished/%1").arg(tool->imageID);
//        QString defaultimage = QString("../toolimages/%1").arg("J4759_B.svg");
//        qDebug() << "UserScreen::buildDrawerScene() image file " << toolimage;
//        if (toolimage.endsWith(".svg", Qt::CaseInsensitive))
//        {
//            // use an image file
//            if (QFile(toolimage).exists())
//            {
//                // image does exist
//                qDebug() << "UserScreen::buildDrawerScene() Image exists: " << toolimage;

//                toolitem = new QGraphicsSvgItem(toolimage);
//                toolitem->setZValue(10);

//                // testing elementid method
//                QString image = tool->imageID;
//                image = image.remove(".svg", Qt::CaseInsensitive);
//                toolitem->setElementId(image);
//            }
//            else
//            {
//                // no file, use default
//                qDebug() << "UserScreen::buildDrawerScene() Use default image: " << defaultimage;
//                toolitem = new QGraphicsSvgItem(defaultimage);

//                toolitem = new QGraphicsSvgItem(defaultimage);
//                toolitem->setElementId("path20");

//            }
//        }
//        else
//        {
//            // use image from loaded image file
//            qDebug() << "UserScreen::buildDrawerScene() Use image from image file: " << tool->imageID;
//            QString toolimages = QString("../toolimages/%1").arg("tool_test_001_003.svg");
//            toolitem = new QGraphicsSvgItem(toolimages);
//            toolitem->setElementId(tool->imageID);

//        }
//        scene->addItem(toolitem);
//        tool->scene = scene;
//        tool->svgItem = toolitem;

//        qDebug() << "DrawerScene::setToolItemTransformation";

//        // reset to identity matrix
//        QTransform tf = toolitem->transform();
//        tf.reset();
//        toolitem->setTransform(tf);

//        toolitem->setTransformOriginPoint(toolitem->boundingRect().center());
//        // set position
//        toolitem->setPos(tool->transform.x, tool->transform.y);

//        toolitem->setFlag(QGraphicsItem::ItemIsSelectable, true);
////        toolitem->setFlag(QGraphicsItem::ItemIsMovable, true);
////        toolitem->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
////        toolitem->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

//        // add some personal data to item
//        toolitem->setData(UserScreen::DESC,tool->name);
//        toolitem->setData(UserScreen::STOCKCODE,tool->stockCode);
//        toolitem->setData(UserScreen::TOOLNUM,tool->toolNumber);
//        toolitem->setData(UserScreen::STATE,(int)tool->state);
//        toolitem->setData(UserScreen::DRAWERNUM,tool->drawerNum);



//        // scaling
//        QRectF box = toolitem->boundingRect();
//        qreal scale = tool->transform.height / box.height();
//        //qreal scale = tool->scale;
//        toolitem->setScale(scale);

//        // flips
//        if (tool->transform.vFlip)
//        {
//            flipVertical(toolitem);
//        }
//        if (tool->transform.hFlip)
//        {
//            flipHorizontal(toolitem);
//        }
//        // set rotation
//        toolitem->setRotation(tool->transform.rotation);






//        // Simple way to colour tools.
//        QGraphicsColorizeEffect *colour = new QGraphicsColorizeEffect();

//        colour->setColor(getToolStatusColour(tool->state));

////        if (tool->state == ToolStates::TOOL_IN) {
////            colour->setColor(UserScreen::toolInColour);
////        }
////        else if (tool->state == ToolStates::TOOL_OUT) {
////            colour->setColor(UserScreen::toolOutColour);
////        }
////        else if (tool->state == ToolStates::TOOL_MISSING) {
////            colour->setColor(UserScreen::toolMissingColour);
////        }
////        else if (tool->state == ToolStates::TOOL_OTHER_USER) {
////            colour->setColor(UserScreen::toolOtherUserColour);
////        }
//        toolitem->setGraphicsEffect(colour);

//        qDebug() << "UserScreen::buildDrawerScene" << tool->toolNumber << tool->transform.x << tool->transform.y;
//        qDebug() << "UserScreen::buildDrawerScene bounding rectangle " << box.height() << box.width() << tool->transform.height << tool->transform.width << scale;
//    }

//    return scene;
//}






void UserScreen::flipHorizontal(QGraphicsSvgItem *toolitem)
{
    // Get the current transform
    QTransform transform(toolitem->transform());

    qreal m11 = transform.m11();    // Horizontal scaling
    qreal m12 = transform.m12();    // Vertical shearing
    qreal m13 = transform.m13();    // Horizontal Projection
    qreal m21 = transform.m21();    // Horizontal shearing
    qreal m22 = transform.m22();    // vertical scaling
    qreal m23 = transform.m23();    // Vertical Projection
    qreal m31 = transform.m31();    // Horizontal Position (DX)
    qreal m32 = transform.m32();    // Vertical Position (DY)
    qreal m33 = transform.m33();    // Addtional Projection Factor

    // We need this in a minute
    qreal scale = m11;

    // Horizontal flip
    m11 = -m11;

    // Re-position back to origin
    if(m31 > 0)
        m31 = 0;
    else
        m31 = (toolitem->boundingRect().width() * scale);

    // Write back to the matrix
    transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

    // Set the items transformation
    toolitem->setTransform(transform);

}




void UserScreen::flipVertical(QGraphicsSvgItem *toolitem)
{
    // Get the current transform
    QTransform transform(toolitem->transform());

    qreal m11 = transform.m11();    // Horizontal scaling
    qreal m12 = transform.m12();    // Vertical shearing
    qreal m13 = transform.m13();    // Horizontal Projection
    qreal m21 = transform.m21();    // Horizontal shearing
    qreal m22 = transform.m22();    // vertical scaling
    qreal m23 = transform.m23();    // Vertical Projection
    qreal m31 = transform.m31();    // Horizontal Position (DX)
    qreal m32 = transform.m32();    // Vertical Position (DY)
    qreal m33 = transform.m33();    // Addtional Projection Factor

    // We need this in a minute
    qreal scale = m22;

    // Vertical flip
    m22 = -m22;

    // Re-position back to origin
    if(m32 > 0)
        m32 = 0;
    else
        m32 = (toolitem->boundingRect().height() * scale);

    // Write back to the matrix
    transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

    // Set the items transformation
    toolitem->setTransform(transform);

}





//void UserScreen::updateDrawerScene(int drwnum, DrawerList* drawer)
//{

//    for(int i = 0; i < drawer->tools.size(); ++i)
//    {

//        Tool *tool = drawer->tools[i].get();
//        // Simple way to colour tools.
//        QGraphicsColorizeEffect *colour = new QGraphicsColorizeEffect();

//        colour->setColor(getToolStatusColour(tool->state));

////        if (tool->state == ToolStates::TOOL_IN) {
////            colour->setColor(UserScreen::toolInColour);
////        }
////        else if (tool->state == ToolStates::TOOL_OUT) {
////            colour->setColor(UserScreen::toolOutColour);
////        }
////        else if (tool->state == ToolStates::TOOL_MISSING) {
////            colour->setColor(UserScreen::toolMissingColour);
////        }
////        else if (tool->state == ToolStates::TOOL_OTHER_USER) {
////            colour->setColor(UserScreen::toolOtherUserColour);
////        }
//        tool->svgItem->setGraphicsEffect(colour);
//    }

//}




//-------------------------------------------------------------------------
//
//  DrawerScene class functions
//
//-------------------------------------------------------------------------

//#include <QGraphicsColorizeEffect>

//DrawerScene::DrawerScene()
//{
//    DrawerScene(Q_NULLPTR);
//}

//DrawerScene::DrawerScene(DrawerList *drawer)
//{
//    //QString toolimages = QString("../toolimages/%1").arg("tool_test_001_003.svg");
//    //renderer.reset(new QSvgRenderer(toolimages));
//    QBrush brush(QColor(0x00, 0x00, 0x00, 255));
//    setBackgroundBrush(brush);
//    qDebug() << "DrawerScene::DrawerScene() Calling setDrawer";
//    setDrawer(drawer);
//}

//void DrawerScene::setDrawer(DrawerList *drawer)
//{
//    QGraphicsSvgItem *toolitem;
//    clear();

//    qDebug() << "DrawerScene::setDrawer() Displaying drawer tools: " << drawer->tools.size();
//    // The code here should be in an update function.
//    for(int i = 0; i < drawer->tools.size(); ++i)
//    {
//        Tool *tool = drawer->tools[i].get();
//        //QString toolimage = QString("../toolimages/%1").arg(tool->imageID);
//        QString toolimage = QString("../toolimagefiles/svgFromAi/SVG finished/%1").arg(tool->imageID);
//        QString defaultimage = QString("../toolimages/%1").arg("J4759_B.svg");
//        qDebug() << "DrawerScene::setDrawer() image file " << toolimage;
//        if (toolimage.endsWith(".svg", Qt::CaseInsensitive))
//        {
//            // use an image file
//            if (QFile(toolimage).exists())
//            {
//                // image does exist
//                qDebug() << "DrawerScene::setDrawer() Image exists: " << toolimage;

//                toolitem = new QGraphicsSvgItem(toolimage);

//            }
//            else
//            {
//                // no file, use default
//                qDebug() << "DrawerScene::setDrawer() Use default image: " << defaultimage;
//                toolitem = new QGraphicsSvgItem(defaultimage);

//                //renderer.reset(new QSvgRenderer(defaultimage));
//                //renderer.get()->load(defaultimage);
//                toolitem = new QGraphicsSvgItem(defaultimage);
//                //toolitem->setSharedRenderer(renderer.get());
//                toolitem->setElementId("path20");

//            }
//        }
//        else
//        {
//            // use image from loaded image file
//            qDebug() << "DrawerScene::setDrawer() Use image from image file: " << tool->imageID;
//            QString toolimages = QString("../toolimages/%1").arg("tool_test_001_003.svg");
////            renderer.reset(new QSvgRenderer(toolimages));

////            renderer.get()->load(toolimages);
////            toolitem->setSharedRenderer(renderer.get());
//            toolitem = new QGraphicsSvgItem(toolimages);
//            toolitem->setElementId(tool->imageID);

//        }

//        //QGraphicsSvgItem *toolitem = new QGraphicsSvgItem();
//        //QString toolimage = QString("../toolimages/%1").arg(tool->imageID);
//        //qDebug() << "DrawerScene::setDrawer() image file " << toolimage;
//        //QGraphicsSvgItem *toolitem = new QGraphicsSvgItem(toolimage);
//        //QGraphicsSvgItem *toolitem = new QGraphicsSvgItem(tool->imageID);

//        //toolitem->setSharedRenderer(renderer.get());
//        //toolitem->setElementId(tool->imageID);
//        toolitem->setTransformOriginPoint(toolitem->boundingRect().center());
//        // set image size
//        toolitem->boundingRect().setSize(QSizeF(tool->transform.width,tool->transform.height));
//        // set rotation
//        toolitem->setRotation(tool->transform.rotation);
//        toolitem->setTransform(QTransform::fromTranslate(tool->transform.x - toolitem->boundingRect().center().x(), tool->transform.y - toolitem->boundingRect().center().y()));

//        toolitem->setFlag(QGraphicsItem::ItemIsSelectable, true);
//        // add some personal data to item
//        toolitem->setData(UserScreen::DESC,tool->name);
//        toolitem->setData(UserScreen::STOCKCODE,tool->stockCode);
//        toolitem->setData(UserScreen::TOOLNUM,tool->toolNumber);
//        toolitem->setData(UserScreen::STATE,(int)tool->state);
//        toolitem->setData(UserScreen::DRAWERNUM,tool->drawerNum);

//        //qDebug() << "DrawerScene::setDrawer()  drawer : " << tool->drawerNum;


//        // Simple way to colour tools.
//        QGraphicsColorizeEffect *colour = new QGraphicsColorizeEffect();

////        colour->setColor(getToolStatusColour(tool->state));

//        if (tool->state == ToolStates::TOOL_IN) {
//            //colour->setColor(QColor(40, 200, 40));
//            colour->setColor(UserScreen::toolInColour);
//        }
//        else if (tool->state == ToolStates::TOOL_OUT) {
//            colour->setColor(UserScreen::toolOutColour);
//            //toolIn->setRotation(45);
//        }
//        else if (tool->state == ToolStates::TOOL_MISSING) {
//            colour->setColor(UserScreen::toolMissingColour);
//        }
//        else if (tool->state == ToolStates::TOOL_OTHER_USER) {
//            colour->setColor(UserScreen::toolOtherUserColour);
//        }
//        toolitem->setGraphicsEffect(colour);

//        // scaling!!!
//        QRectF box = toolitem->boundingRect();
//        qreal scale = tool->transform.height / box.height();
//        toolitem->setScale(scale);
//        //toolitem->setScale(tool->transform.scale);
//        //box.setHeight(tool->transform.height);
//        //box.setWidth(tool->transform.width);

//        addItem(toolitem);
//        qDebug() << "DrawerScene::setDrawer" << tool->toolNumber << tool->transform.x << tool->transform.y;
//        qDebug() << "DrawerScene::setDrawer bounding rectangle " << box.height() << box.width() << tool->transform.height << tool->transform.width << scale;
//    }
//}




//-------------------------------------------------------------------------
//
//  Display functions for wrong users returning tools.
//
//-------------------------------------------------------------------------

void UserScreen::createWrongUserReturnMsg()
{
    illegalReturnMsg = new QLabel();
//    illegalReturnMsg->resize(ui->Statuspanel->size());
//    int x = ui->Statuspanel->pos().x();
//    int y = ui->mid->pos().y();
//    illegalReturnMsg->move(x, y);
//    illegalReturnMsg->setFrameStyle(QFrame::Panel | QFrame::Raised);
    illegalReturnMsg->setVisible(false);

}

void UserScreen::displayWrongUserRetrunMsg(int dnum, int toolnum, QString toolname, int action)
{
    qDebug() << "UserScreen::displayWrongUserRetrunMsg() DISPLAYING MSG BOX";

//    illegalReturnMsg->resize(ui->Statuspanel->size());
    int x = 0;//ui->Statuspanel->pos().x();
    int y = ui->mid->pos().y();
    illegalReturnMsg->move(x, y);
    illegalReturnMsg->setFrameStyle(QFrame::Panel | QFrame::Raised);
    //illegalReturnMsg->setVisible(false);

    illegalReturnMsg->setLineWidth(3);
    illegalReturnMsg->setWordWrap(true);
    illegalReturnMsg->setStyleSheet("background-color:rgb(230,0,0);"
                                         "font-size: 30pt;"
                                         "font-weight: bold;");
    illegalReturnMsg->setAttribute(Qt::WA_ShowWithoutActivating);

    QString txt = "Tool should not be %4 \nDrawer %1 \nTool Number %2 \n%3";
    txt = txt.arg(dnum).arg(toolnum).arg(toolname).arg(action == Trak::Returned ? "Returned" : "Taken");
    illegalReturnMsg->setText(txt);

    Qt::WindowFlags wFlags = illegalReturnMsg->windowFlags();
    wFlags = wFlags | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint;
    illegalReturnMsg->setWindowFlags(wFlags);

    illegalReturnMsg->setVisible(true);
    illegalReturnMsg->show();

}



void UserScreen::clearWrongUserRetrunMsg()
{
    qDebug() << "UserScreen::clearWrongUserRetrunMsg() CLOSSING MSG BOX";
    illegalReturnMsg->setVisible(false);
    //illegalReturnMsg->close();

}



QColor UserScreen::getToolStatusColour(ToolStates state)
{

    if (state == ToolStates::TOOL_IN) {
        return UserScreen::toolInColour;
    }
    else if (state == ToolStates::TOOL_OUT) {
        return UserScreen::toolOutColour;
    }
    else if (state == ToolStates::TOOL_MISSING) {
        return UserScreen::toolMissingColour;
    }
    else if (state == ToolStates::TOOL_OTHER_USER) {
        return UserScreen::toolOtherUserColour;
    }
    else if (state == ToolStates::TOOL_TRANSFERRED) {
        return UserScreen::toolTransferredColour;
    }
    else if (state == ToolStates::TOOL_UNSERVICEABLE) {
        return UserScreen::toolUnserviceableColour;
    }
    else
    {
        return QColor(250, 250, 250);
    }

}



//QPoint UserScreen::toolManagerAnchor()
//{
//    return ui->label_31->mapToGlobal(QPoint(0,0));
//}



//void UserScreen::clearCurrentSelection()
//{
//    if (currentScene != NULL)
//        currentScene->clearSelection();
//}



void UserScreen::on_logoutButton_clicked()
{
    MainController::getMainControllerInstance()->onConfirmButton();
}

void UserScreen::on_dismissErrorButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void UserScreen::on_consumableIssuingButton_toggled(bool checked)
{
    startProgressBarTimer();
    ui->issueConsumablesButton->setEnabled(true);
    ui->consumableCountSpinBox->setEnabled(true);
    if (checked)
    {
        ui->consumableUsedButton->setVisible(false);
        ui->consumableUnusedButton->setVisible(false);
        ui->consumableCountSpinBox->setMaximum(maxConsumableIssue);
    }
}

void UserScreen::on_consumableReturningButton_toggled(bool checked)
{
    startProgressBarTimer();
    if (ui->consumableUnusedButton->isChecked() || ui->consumableUsedButton->isChecked())
    {
        ui->issueConsumablesButton->setEnabled(true);
        ui->consumableCountSpinBox->setEnabled(true);
    }
    else
    {
        ui->issueConsumablesButton->setEnabled(false);
        ui->consumableCountSpinBox->setEnabled(false);
    }
    if (checked)
    {
        ui->consumableUsedButton->setVisible(true);
        ui->consumableUnusedButton->setVisible(true);
        ui->consumableCountSpinBox->setMaximum(maxConsumableReturn);
    }
}

// Quick and dirty way to set defaults on StackedWidget changes.
void UserScreen::on_stackedWidget_currentChanged(int arg1)
{
    //cancelProgressBarTimer();
    startProgressBarTimer();
    issuedTimer->stop();
    //progressBar->start(MainController::getDataManagerInstance()->currentCabinet.openDrawerTimeout);

    if (arg1 == ui->stackedWidget->indexOf(ui->consumableOutPage))
    {

        //ui->consumableUsedButton->setChecked(false);
        //ui->consumableCountSpinBox->setValue(1);
        //ui->issueConsumablesButton->setEnabled(false);
    }
}

void UserScreen::on_issueConsumablesButton_clicked()
{
    ui->issueConsumablesButton->setEnabled(false);

    if (ui->consumableIssuingButton->isChecked())
    {
        emit consumableIssueSelected(ui->consumableCountSpinBox->value());
    }
    else
    {
        emit consumableReturnSelected(ui->consumableCountSpinBox->value(), ui->consumableUsedButton->isChecked());
    }
    //ui->stackedWidget->setCurrentWidget(ui->readyToScan);
}

void UserScreen::on_kitCancelButton_clicked()
{
    //ui->stackedWidget->setCurrentWidget(ui->readyToScan);
    emit kitIssueCancelled();
}

void UserScreen::on_kitOKButton_clicked()
{
    emit kitIssueOK();
}

void UserScreen::on_consumableCountSpinBox_valueChanged(int arg1)
{
    startProgressBarTimer();
}

void UserScreen::on_consumableUsedButton_toggled(bool checked)
{
    if (checked)
    {
        ui->issueConsumablesButton->setEnabled(true);
        ui->consumableCountSpinBox->setEnabled(true);
    }
    startProgressBarTimer();
}

void UserScreen::on_unserviceableButton_clicked()
{
    ui->lblGeneralMessage->setText("Tool marked as unserviceable.");
    ui->stackedWidget->setCurrentWidget(ui->messagePage);
    emit toolMarkedUnserviceable();
}

void UserScreen::on_consumableUnusedButton_toggled(bool checked)
{
    if (checked)
    {
        ui->issueConsumablesButton->setEnabled(true);
        ui->consumableCountSpinBox->setEnabled(true);
    }
    startProgressBarTimer();
}

void UserScreen::onReturnToReadyScan()
{
    qDebug() << __FUNCTION__;
    ui->stackedWidget->setCurrentWidget(ui->readyToScan);
    issuedTimer->stop();
}
