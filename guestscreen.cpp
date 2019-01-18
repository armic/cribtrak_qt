
#include <QSqlQueryModel>

#include <windows.h>
#include <stdio.h>
#include <psapi.h>

#include "guestscreen.h"
#include "ui_guestscreen.h"
#include "datamanager.h"
#include "maincontroller.h"
#include "ui_selecttail.h"
#include <iostream>
#include <fstream>
#include "selecttail.h"
//#include "cabinetmanager.h"
#include "tooloutform.h"
#include "accessdenied.h"
#include "version.h"
#include "toolfinder.h"

using namespace std;

//#define TRAK_TESTKEYS

#ifdef TRAK_TESTKEYS
#include <QtTest/QtTest>
#endif

GuestScreen::GuestScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuestScreen)
{

    ui->setupUi(this);

    ui->rtsButton->setVisible(false);

    // setup to displat time and date
    timer =  new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(dateTime()));
    timer->start(1000);

    rtsTimer =  new QTimer(this);
    connect(rtsTimer, SIGNAL(timeout()),this,SLOT(rtsCheck()));
    rtsTimer->start(10000);


    setupScreen();

    setScreen();
    show();
}

GuestScreen::~GuestScreen()
{
    delete ui;
}




//
//  display the time and date on the guest screen
//
void GuestScreen::dateTime()
{
  QTime time = QTime::currentTime();
  QDate date = QDate::currentDate();
  QString time_text = time.toString("h:mm:ss AP");
  QString date_text = date.toString("M/d/yyyy");
  ui->lblTime->setText("Time: " + time_text);
  ui->lblDate->setText("Date: " + date_text);
}





//
//  set initial colour and text of button
//

void GuestScreen::setupScreen()
{
    // setup text fields
    DataManager* dataman = MainController::getDataManagerInstance();
    QString CompanyLogo = "images/%1"; // Customer logo

//    ui->switchButton->setVisible(false);
//    ui->about->setVisible(false);
//    ui->vesionNumber->setVisible(false);

//    qDebug() << __FUNCTION__ << CompanyLogo.arg(dataman->currentCustomer.comlogo);

    ifstream file(CompanyLogo.arg(dataman->currentCustomer.comlogo).toStdString());
    if(!file)
    {
        qDebug() << __FUNCTION__ << "Company logo not found.";
        ui->CustomerLogo->setPixmap(QPixmap("images/default_logo.png"));
    }
    else
    {
        ui->CustomerLogo->setPixmap(QPixmap(CompanyLogo.arg(dataman->currentCustomer.comlogo)));
    }

//    This works:
//    ui->CustomerLogo->setPixmap(QPixmap("E:/Work/cribtrak/final/cribtrak/images/5.png"));

//    This doesn't:
//    ui->CustomerLogo->setPixmap(QPixmap("images/5.png"));

    //ui->kabDescription->setText(dataman->currentCrib.description);
    //ui->kabSerial->setText(dataman->currentCrib.serialNumber);
    ui->kabDescription->setText(dataman->currentCrib.description);
    ui->kabSerial->setText(dataman->currentCrib.cribId);
//    qDebug() << __FUNCTION__ << "currentCrib.description:" << dataman->currentCrib.description;
//    qDebug() << __FUNCTION__ << dataman->currentCrib.cribId;
    //qDebug() << __FUNCTION__ << dataman->currentCustomer.comlogo;

    ui->FirmwareVersion->setText("Firmware " + dataman->currentCrib.fw);
    ui->vesionNumber->setText(Version::getVersionString());

    tailWidget = new QWidget(this);
    selecttailDialog = new SelectTail(tailWidget);
    tailWidget->setVisible(false);

    ui->toolsStatusButton->setStyleSheet("background-color:rgb(254,0,0);");
    ui->toolsStatusButton->setVisible(false);
    connect(ui->toolsStatusButton, &QPushButton::clicked, this, &GuestScreen::toolButtonClicked);


    // sets device status slots
//    connect(MainController::getCabinetManagerInstance(), &CabinetManager::connected, this, &GuestScreen::deviceConnected);
//    connect(MainController::getCabinetManagerInstance(), &CabinetManager::disconnected, this, &GuestScreen::deviceDisconnected);


}

void GuestScreen::setScreen()
{
    DataManager* backend = MainController::getDataManagerInstance();
    backend->refreshToolsOut();
    int cnt = backend->getToolsOutCount();
    if (cnt >0)
    {
        ui->pnlBand->setVisible(false);
        ui->toolsStatusButton->setStyleSheet("background-color:rgb(230,0,0);"
                                             "font-size: 40pt;"
                                             "font-weight: bold;");
        ui->toolsStatusButton->setVisible(true);
        QString str = QString("TOOLS OUT (%1)\nTouch to view").arg(QString::number(cnt));
        //ui->toolsStatusButton->setText(tr("TOOLS OUT \n TOUCH TO VIEW"));
        ui->toolsStatusButton->setText(str);
    }
    else
    {
        ui->pnlBand->setVisible(true);
        ui->toolsStatusButton->setVisible(false);
    }
    tailWidget->setVisible(false);   // jic
    rtsCheck();

}



//
//  updates the device status display
//
void GuestScreen::deviceConnected()
{
    qDebug() << "GuestScreen::deviceConnected()";
//    ui->deviceStatusStrLabel->setText("Hardware connected");
//    ui->deviceStatusLabel->setPixmap(QPixmap(":svg/resources/led_on.svg"));

}

void GuestScreen::deviceDisconnected()
{
    qDebug() << "GuestScreen::deviceDisconnected()";
//    ui->deviceStatusStrLabel->setText("Hardware disconnected");
//    ui->deviceStatusLabel->setPixmap(QPixmap(":svg/resources/led_off.svg"));

}

void GuestScreen::rtsCheck()
{
    DataManager *dataman = MainController::getDataManagerInstance();
    if (dataman->currentCrib.rtsEnabled)
    {
        ui->rtsButton->setVisible(dataman->rtsToolsOut());
    }
}




void GuestScreen::on_switchButton_clicked()
{
    //MainController::getMainViewInstance()->processSwitchClicked();  // just for testing
}


//
//  Displays the tools out table
//
void GuestScreen::toolButtonClicked()
{
    // load tool out form ui
    toolOutForm frmToolOut;
    frmToolOut.setWindowFlags(Qt::FramelessWindowHint);
    frmToolOut.setWindowState(Qt::WindowFullScreen);
    frmToolOut.setModal(true);
    frmToolOut.exec();

//    QSqlQueryModel* model = MainController::getDataManagerInstance()->toolsOutModel;

//    QTableView *view = new QTableView(this);

//    view->setWindowTitle("TOOLS OUT");

//    model->setHeaderData(0, Qt::Horizontal, tr("Date"));
//    model->setHeaderData(1, Qt::Horizontal, tr("User Id"));
//    model->setHeaderData(2, Qt::Horizontal, tr("Issued to"));
//    model->setHeaderData(3, Qt::Horizontal, tr("Tool name"));
//    model->setHeaderData(4, Qt::Horizontal, tr("Drawer"));
//    model->setHeaderData(5, Qt::Horizontal, tr("Tool number"));
//    model->setHeaderData(6, Qt::Horizontal, tr("Tail number"));

//    // sorting columns
//    QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
//    sort_filter->setSourceModel(model);
//    sort_filter->sort (2);
//    view->setModel (sort_filter);

//    //view->setModel(model);
//    view->resizeRowsToContents();
//    view->setAlternatingRowColors(true);

//    view->hideColumn(1);
//    view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    view->setSortingEnabled(true);

//    // calculate total width of columns
//    int cnt = model->columnCount();
//    int totalwidth = 0;
//    for (int i = 0; i < cnt; i++)
//    {
//        totalwidth += view->columnWidth(i);
//    }
//    totalwidth += view->verticalHeader()->width();
//    totalwidth += 2;
//    view->resize(totalwidth,400);

//    // set timeout for this window
//    // Get timer values from ini file
//    QSettings settings("trak.ini", QSettings::IniFormat);
//    settings.beginGroup("System");
//    int tmr = settings.value("IssuedToolsTimeout", 10).toInt();
//    settings.endGroup();
//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, view, &QTableView::deleteLater);
//    timer->start(tmr * 1000);

//    view->show();

}







//
//  the standby state keyPressEvent handler
//      Currently used to wait for the token reader string id
//      which is !<idNumber># as keystrokes.
//      Key presses are not passes on but consumed ie return true
//

bool GuestScreen::event(QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        qDebug() << "GuestScreen::event KEY is " << ke->key();

#ifdef TRAK_TESTKEYS
        if (ke->key() == Qt::Key_F1)
        {
            QTest::keyClicks(this, "!00140007#");
            QTest::keyClick(this, Qt::Key_Enter);
            return true;
        }
        if (ke->key() == Qt::Key_F2)
        {
            QTest::keyClicks(this, "!04611092E53480#");
            QTest::keyClick(this, Qt::Key_Enter);
            return true;
        }
#endif

        // waiting for token data
        checkForTokenData(event);
        return true;
    }
    else
    {
        return QWidget::event(event);
    }
}




void GuestScreen::checkForTokenData(QEvent* event)
{

    QChar key = static_cast<QKeyEvent *>(event)->key();
    qDebug() << "GuestScreen::checkForTokenData:: key entered" << key;
    if (key <= 0x00 || key > Qt::Key_AsciiTilde)
    {
        return;  // key not in range
    }
    if (key == Qt::Key_Exclam)
    {
        enteringToken = true;
        waitingForReturn = false;
        tokenString.clear();
    }
    else if(enteringToken)
    {
        if (waitingForReturn)
        {
            if (key == Qt::Key_Enter || key == Qt::Key_Return)
            {
                qDebug() << "GuestScreen::checkForTokenData:: token entered" << tokenString;
                processToken();

            }
            else
            {
                //return key shuold be next
                enteringToken = false;
                qDebug() << "GuestScreen::checkForTokenData:: return key was NOT entered";
            }
        }
        if (key == Qt::Key_NumberSign)
        {
            // now have a token now wait for return key
            waitingForReturn = true;
            qDebug() << "GuestScreen::checkForTokenData:: token entered" << tokenString << "now waiting for return key";
        }
        else
        {
            // append char to token string
            if (key != ' ')
            {
                tokenString.append(key);
                if (tokenString.length() > MAXTOKENLENGTH)
                {
                    enteringToken = false;
                    tokenString.clear();
                }
            }
        }
    }
}


//
//  Checks the entered token belongs to a valid user
//
void GuestScreen::processToken()
{

    quint64 memusage = readMemoryUsage();
    qDebug() << "GuestScreen::processToken() PagefileUsage" << memusage;

    // remove spaces from string
    // does this user exist?
    bool result = MainController::getDataManagerInstance()->getUserDetails(tokenString);
    // Valid user?
    if (result)
    {
        qDebug() << "valid user for token";
        addSelectTailWidget();
        MainController::getDataManagerInstance()->updateUserAccessCount(tokenString);
    }
    else {
        // invalid user, display error
        qDebug() << "Invalid user for token";
        invalidUserMessage();
        enteringToken = false;
        tokenString.clear();
    }
}


void GuestScreen::invalidUserMessage()
{
    // Load Employee List window
    accessdenied frmDeniedMessage;
    frmDeniedMessage.setWindowFlags(Qt::FramelessWindowHint);
    frmDeniedMessage.setModal(true);
    frmDeniedMessage.exec();
  //  MyMessageBox msgBox;
    //msgBox.setText("Invalid token or user");

//    Qt::WindowFlags wFlags = msgBox.windowFlags();
//    if(Qt::WindowCloseButtonHint == (wFlags & Qt::WindowCloseButtonHint))
//    {
//        wFlags = wFlags ^ Qt::WindowCloseButtonHint;
//    }
//    wFlags = wFlags | Qt::FramelessWindowHint;
//    msgBox.setWindowFlags(wFlags);
//    msgBox.setStandardButtons(0);
//    msgBox.setIconPixmap(QPixmap(":/images/images/accessdenied.png"));
//    msgBox.setTimeoutValue(5);
//    msgBox.exec();
}


//
//  Displays the select tail widget
//
void GuestScreen::addSelectTailWidget()
{

    selecttailDialog->setWidget();
    //qDebug() << __FUNCTION__ << "width:" << this->window()->width();

    tailWidget->move((this->window()->width() / 2) - (tailWidget->width() / 2), (this->height() / 2) - (tailWidget->height() / 2));

    tailWidget->setVisible(true);
    tailWidget->setFocus();

//    // setup combo box
//    DataManager* backend = MainController::getDataManagerInstance();

//    QSqlQueryModel *model = backend->getTailNumbersModel(backend->currentCustomer.custId);
//    selecttailDialog->tailComboBox->setModel(model);

        qDebug() << "GuestScreen::addSelectTailWidget";

}



//
//  Read the current process memory usage
//
quint64 GuestScreen::readMemoryUsage()
{
    HANDLE processHandle;
    PROCESS_MEMORY_COUNTERS pmc;

    if ((processHandle = GetCurrentProcess()) != NULL)
    {
        if (GetProcessMemoryInfo(processHandle, &pmc, sizeof(pmc)))
        {

            //qDebug() << "GuestScreen::readMemoryUsage() PagefileUsage" << pmc.PagefileUsage << sizeof(pmc.PagefileUsage);
            return pmc.PagefileUsage;
        }
    }
    return 0;
}




void GuestScreen::on_toolFinderButton_clicked()
{
    ToolFinder *finder = new ToolFinder();
    finder->setWindowModality(Qt::WindowModal);
    finder->setWindowState(Qt::WindowFullScreen);
    finder->show();
}

void GuestScreen::on_rtsButton_clicked()
{
    toolOutForm frmToolOut(0, true);
    frmToolOut.setWindowFlags(Qt::FramelessWindowHint);
    frmToolOut.setModal(true);
    frmToolOut.exec();
}
