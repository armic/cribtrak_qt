#include "databasesetup.h"
#include "ui_databasesetup.h"
#include "dbmaintenance.h"

databaseSetup::databaseSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseSetup)
{

    ui->setupUi(this);

    //Initialize required variables
    setup();

}

databaseSetup::~databaseSetup()
{
    delete ui;
}

void databaseSetup::loadSettings()
{
    // Load ini data here
    QSettings settings("trak.ini", QSettings::IniFormat);

    // Local Database configuration
    settings.beginGroup("Database");
    localServer = settings.value("Server").toString();
    localDBName = settings.value("Schema").toString();
    localUsername = settings.value("Username").toString();
    localPassword = settings.value("Password").toString();
    localPort = settings.value("Port").toString();
    settings.endGroup();

    // Remote Database configuration
    settings.beginGroup("Cloud");
    remoteServer = settings.value("Server").toString();
    remoteDBName = settings.value("Schema").toString();
    remoteUsername = settings.value("Username").toString();
    remotePassword = settings.value("Password").toString();
    remotePort = settings.value("Port").toString();
    ProxyServer = settings.value("proxyhost").toString();
    ProxyUsername = settings.value("proxyusername").toString();
    ProxyPassword = settings.value("proxypassword").toString();
    url = settings.value("url").toString();
    useProxy =  settings.value("UseProxy").toInt();
    proxyPort = settings.value("proxyport").toString();
    useProxy = settings.value("UseProxy").toInt();
    settings.endGroup();
}


void databaseSetup::saveSettings()
{
    // Load ini data here
    QSettings settings("trak.ini", QSettings::IniFormat);

    // Local Database configuration
    settings.beginGroup("Database");
    settings.setValue("Server", ui->edtHost->toPlainText());
    settings.setValue("Schema", ui->edtdatabaseName->toPlainText());
    settings.setValue("Username",ui->edtUsername->toPlainText());
    settings.setValue("Password", ui->edtpassword->toPlainText());
    settings.setValue("Port",ui->edtPort->toPlainText());
    settings.endGroup();

    // Remote Database configuration
    settings.beginGroup("Cloud");
    settings.setValue("Server", ui->edtRHost->toPlainText());
    settings.setValue("Schema", ui->edtRDatabase->toPlainText());
    settings.setValue("Username", ui->edtRUsername->toPlainText());
    settings.setValue("Password", ui->edtRPassword->toPlainText());
    settings.setValue("Port", ui->edtRPort->toPlainText());
    settings.setValue("proxyhost", ui->edtProxyHost->toPlainText());
    settings.setValue("proxyusername", ui->edtProxyUsername->toPlainText());
    settings.setValue("proxypassword", ui->edtProxyPassword->toPlainText());
    settings.setValue("url", ui->edtRURL->toPlainText());

    if (ui->cbProxy->isChecked()) {
        settings.setValue("UseProxy", 1);
    }
   else
    {
        settings.setValue("UseProxy", 0);

    }

    settings.setValue("proxyport", ui->edtProxyPort->toPlainText());
    settings.endGroup();

}


void databaseSetup::setup()
{
    // Load Settings

    loadSettings();
    ui->tabWidget->setCurrentIndex(0);
    // Transfer values to from controls
    ui->edtHost->setText(localServer);
    ui->edtpassword->setText(localPassword);
    ui->edtdatabaseName->setText(localDBName);
    ui->edtUsername->setText(localUsername);
    ui->edtPort->setText(localPort);

    ui->edtRHost->setText(remoteServer);
    ui->edtRPassword->setText(remotePassword);
    ui->edtRDatabase->setText(remoteDBName);
    ui->edtRUsername->setText(remoteUsername);
    ui->edtRPort->setText(remotePort);
    ui->edtProxyHost->setText(ProxyServer);
    ui->edtProxyUsername->setText(ProxyUsername);
    ui->edtRURL->setText(url);
    ui->edtProxyPort->setText(proxyPort);

    if(useProxy == 0) {
        ui->cbProxy->setChecked(false);
    }
   else  ui->cbProxy->setChecked(true);


}

//void databaseSetup::on_btnCancel_clicked()
//{
//   // Close database setup dialog here
//   close();
//}

void databaseSetup::on_btnOK_clicked()
{
    // Save setup here
    saveSettings();
    close();

}

void databaseSetup::on_btnbackup_clicked()
{
    ui->lblToolStatus->setText("Backing up MYSQL Database....");
    // Load ini data here
    QSettings settings("trak.ini", QSettings::IniFormat);

    // Local Database configuration
    settings.beginGroup("Database");
    QString Databasename = settings.value("Schema").toString();
    QString UserName = settings.value("Username").toString();
    QString Password = settings.value("Password").toString();
    settings.endGroup();


    // Create database backup here
    QProcess dumpProcess(this);
    QString program =  "C:/wamp/bin/mysql/mysql5.6.17/bin/mysqldump.exe";
    QStringList args;
    qDebug() << UserName << Password << Databasename << program;

    args << "-u" + UserName << Databasename;
    qDebug() << args;
    dumpProcess.setStandardOutputFile("backup/" + Databasename +".sql");

    dumpProcess.start(program, args);
    dumpProcess.waitForFinished();
    ui->lblToolStatus->setText("Backup process done!");
    dumpProcess.close();



}

void databaseSetup::on_btnRestore_clicked()
{
    ui->lblToolStatus->setText("Restoring MYSQL Database....");
    // Load ini data here
    QSettings settings("trak.ini", QSettings::IniFormat);

    // Local Database configuration
    settings.beginGroup("Database");
    QString Databasename = settings.value("Schema").toString();
    QString UserName = settings.value("Username").toString();
    QString Password = settings.value("Password").toString();
    settings.endGroup();


    // Create database backup here
    QProcess restoreProcess(this);
    QString program =  "C:/wamp/bin/mysql/mysql5.6.17/bin/mysqldump.exe";
    QStringList args;
    qDebug() << UserName << Password << Databasename << program;

    args << "-u" + UserName << Databasename;
    qDebug() << args;
    restoreProcess.setStandardInputFile("backup/" + Databasename +".sql");

    restoreProcess.start(program, args);
    restoreProcess.waitForFinished();
    ui->lblToolStatus->setText("Database restored from "  + Databasename + ".sql");
    restoreProcess.close();

}

void databaseSetup::on_btnmaintain_clicked()
{
  dbMaintenance frmdbmaintenance;
  frmdbmaintenance.setModal(true);
  frmdbmaintenance.exec();
}
