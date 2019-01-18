#include "adminscreen.h"
#include "ui_adminscreen.h"
#include "datamanager.h"
#include "maincontroller.h"
#include "systemsettings.h"
#include "databasesetup.h"
#include "systemsettings.h"
#include "customersettings.h"
#include "employeelist.h"
#include "setupcabinet.h"
#include "taillist.h"
#include "dashboard.h"
#include "tooladmin.h"
#include "contactform.h"
#include "scanneradmin.h"


adminscreen::adminscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminscreen)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayDateTime()));
    timer->start(1000);

}

adminscreen::~adminscreen()
{
    delete ui;
}



void adminscreen::setupScreen()
{
    // setup progress bar
    progressBar = new ProgressBar(MainController::getDataManagerInstance()->currentCrib.adminTimeout, ui->progressBar_2, this);
    connect(progressBar, &ProgressBar::progressBarTimeout, this, &adminscreen::handleProgressBarEnd);

    // sets device status slots
//    connect(MainController::getCabinetManagerInstance(), &CabinetManager::connected, this, &adminscreen::deviceConnected);
//    connect(MainController::getCabinetManagerInstance(), &CabinetManager::disconnected, this, &adminscreen::deviceDisconnected);
}

void adminscreen::setScreen()
{
    // setup text fields
    DataManager* dataman = MainController::getDataManagerInstance();
    QString str = "%1";
    str = str.arg(dataman->currentUser.name);
    ui->instructionLabel->setText(str);

    ui->SystemToolsMenu->setVisible(false);

    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);
}

void adminscreen::on_customer_clicked()
{
    progressBar->stop();
    // load customersettings.ui
    CustomerSettings frmCustomerSettings;
    frmCustomerSettings.setModal(true);
    frmCustomerSettings.setWindowState(Qt::WindowFullScreen);
    frmCustomerSettings.exec();

    // restart progress bar
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);
}
void adminscreen::on_employees_clicked()
{
    progressBar->stop();
    // Load Employee List window
    employeelist frmEmployeeList;
    frmEmployeeList.setModal(true);
    frmEmployeeList.setWindowState(Qt::WindowFullScreen);
    frmEmployeeList.exec();

    // restart progress bar
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);

}

void adminscreen::on_database_clicked()
{
    progressBar->stop();
    // Load database setup screen
    databaseSetup frmdbSetup;
    frmdbSetup.setModal(true);
    frmdbSetup.setWindowState(Qt::WindowFullScreen);
    //frmdbSetup.setup();
    frmdbSetup.exec();

    // restart progress bar
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);

}


void adminscreen::handleProgressBarEnd()
{
    qDebug() << "adminscreen::handleProgressBarEnd";
    MainController::getMainViewInstance()->backToGuestMode();

}





//
//  updates the device status display
//
void adminscreen::deviceConnected()
{
    qDebug() << "adminscreen::deviceConnected()";
//    ui->deviceStatusStrLabel_2->setText("Hardware Connected");
//    ui->deviceStatusLabel->setPixmap(QPixmap(":svg/resources/led_on.svg"));

}

void adminscreen::deviceDisconnected()
{
    qDebug() << "adminscreen::deviceDisconnected()";
//    ui->deviceStatusStrLabel_2->setText("Hardware Disconnected");
//    ui->deviceStatusLabel->setPixmap(QPixmap(":svg/resources/led_off.svg"));

}




void adminscreen::displayDateTime()
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString time_text = time.toString("h:mm:ss AP");
    QString date_text = date.toString("M/d/yyyy");

 }






void adminscreen::on_cabinet_clicked()
{
    progressBar->stop();
    // Load Employee List window
//    setupcabinet frmSetupCabinet;
//    frmSetupCabinet.setModal(true);
//    frmSetupCabinet.exec();

    ScannerAdmin scannerAdmin;
    scannerAdmin.setModal(true);
    scannerAdmin.setWindowState(Qt::WindowFullScreen);
    scannerAdmin.exec();

    // restart progress bar
    if (MainController::getMainControllerInstance()->getAppMode() != MainController::toolsAdminMode)
    {
        progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);
    }
}

void adminscreen::on_system_clicked()
{
    progressBar->stop();
    // Load Employee List window
    systemsettings frmSystemSettings;
    frmSystemSettings.setModal(true);
    frmSystemSettings.setWindowState(Qt::WindowFullScreen);
    frmSystemSettings.exec();

    // restart progress bar
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);
}

void adminscreen::on_tail_clicked()
{
    progressBar->stop();
    taillist frmTailList;
    frmTailList.setModal(true);
    frmTailList.setWindowState(Qt::WindowFullScreen);
    frmTailList.exec();
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);
}

void adminscreen::on_logOut_clicked()
{
    progressBar->stop();
    MainController::getMainViewInstance()->backToGuestMode();
}

void adminscreen::on_dashboard_clicked()
{
    progressBar->stop();
    dashboard frmDashboard;
    //frmDashboard.setWindowFlags(Qt::FramelessWindowHint);
    frmDashboard.setModal(true);
    frmDashboard.setWindowState(Qt::WindowFullScreen);
    frmDashboard.exec();
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);
}


void adminscreen::on_btnPHPMyAdmin_clicked()
{
//        QProcess process;
//        QString file = QDir::homepath + "file.exe";
//        process.start(file);

    QString link = "http://localhost/phpmyadmin/";
    QDesktopServices::openUrl(QUrl(link));

}

void adminscreen::on_btnTask_clicked()
{
    // Task Manager
    QString file ="taskmgr.exe";
    QStringList arguments;
    arguments << " ";
    QProcess *myProcess = new QProcess();
    myProcess->start(file);


}

void adminscreen::on_btnNotepad_clicked()
{
    QString file ="notepad.exe";
    QStringList arguments;
    arguments << " ";
    QProcess *myProcess = new QProcess();
    myProcess->start(file);
}

void adminscreen::on_btnExplorer_clicked()
{
    QString file ="explorer.exe";
    QStringList arguments;
    arguments << " ";
    QProcess *myProcess = new QProcess();
    myProcess->start(file);
}

void adminscreen::on_btnCommand_clicked()
{
    QString file ="cmd.exe";
    QStringList arguments;
    arguments << " ";
    QProcess *cmdProcess = new QProcess();
    cmdProcess->start(file);
}

void adminscreen::on_btnInternet_clicked()
{
    QString file ="iexplorer.exe";
    QStringList arguments;
    arguments << " ";
    QProcess *myProcess = new QProcess();
    myProcess->start(file);
}

void adminscreen::on_tools_clicked()
{
    // Tools
    progressBar->stop();
    tooladmin frmToolAdmin;
    frmToolAdmin.setModal(true);
    frmToolAdmin.exec();
    progressBar->start(MainController::getDataManagerInstance()->currentCrib.adminTimeout);

}


void adminscreen::on_email_clicked()
{
    //Contact Us
    progressBar->stop();
    contactform frmContactUs;
    frmContactUs.setModal(true);
    frmContactUs.exec();
    progressBar->start();

}
