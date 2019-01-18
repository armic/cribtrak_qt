#ifndef DATABASESETUP_H
#define DATABASESETUP_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include <QProcess>

namespace Ui {
class databaseSetup;
}

class databaseSetup : public QDialog
{
    Q_OBJECT

public:
    explicit databaseSetup(QWidget *parent = 0);
    ~databaseSetup();

    void setup();
    void loadSettings();
    void saveSettings();

private slots:
//    void on_btnCancel_clicked();
    void on_btnOK_clicked();

    void on_btnbackup_clicked();

    void on_btnRestore_clicked();

    void on_btnmaintain_clicked();

private:
    Ui::databaseSetup *ui;
    QString localServer;
    QString localDBName;
    QString localUsername;
    QString localPassword;
    QString localPort;
    QString remoteServer;
    QString remoteDBName;
    QString remoteUsername;
    QString remotePassword;
    int useProxy;
    QString ProxyServer;
    QString ProxyUsername;
    QString ProxyPassword;
    QString remotePort;
    QString proxyPort;
    QString url;

};

#endif // DATABASESETUP_H
