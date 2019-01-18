#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSettings>
#include <windows.h>

#include "keypad.h"


namespace Ui {
class systemsettings;
}

class systemsettings : public QDialog
{
    Q_OBJECT

public:
    explicit systemsettings(QWidget *parent = 0);
    ~systemsettings();



private slots:


    void on_btnOK_clicked();

//    void on_btnbackup_clicked();

    void on_btnterminate_clicked();

    void on_btnRestart_clicked();

    void on_btnLogOff_clicked();

    void on_btnCheck_clicked();

    void on_btnLocalUpdate_clicked();

    void on_btnCancel_clicked();

    void on_btnClear_clicked();

    void on_btnViewLogs_clicked();

    void on_btnViewLogin_clicked();

    void on_btnDeleteLogs_clicked();

    void on_cbAlertSound_clicked(bool checked);

    //void on_edtCloseDrawer_valueChanged(const QString &arg1);

    void on_edtAdmin_valueChanged(const QString &arg1);

    //void on_edtOpenAlarm_valueChanged(const QString &arg1);

    //void on_edtIssuedTools_valueChanged(const QString &arg1);

    void on_edtUserTimeout_valueChanged(const QString &arg1);

private:
    Ui::systemsettings *ui;
    KeyPad* keybrd;

};

#endif // SYSTEMSETTINGS_H
