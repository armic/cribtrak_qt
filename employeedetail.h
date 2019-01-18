#ifndef EMPLOYEEDETAIL_H
#define EMPLOYEEDETAIL_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QCryptographicHash>

#include "keypad.h"


namespace Ui {
class employeedetail;
}

class employeedetail : public QDialog
{
    Q_OBJECT

public:
    explicit employeedetail(const bool &what, QWidget *parent = 0);
    ~employeedetail();

    void setUserID(const QString &userID);
    QString m_UserID;
    void updateUsertab();
    bool event(QEvent *event);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btnGrant_clicked();

    void on_employeedetail_finished(int result);

    void on_btnManual_clicked();

    void on_cbDisbaled_clicked();

    void on_rbEnabled_clicked();

    void on_rbDisabled_clicked();

    void on_edtFirstName_textChanged(const QString &arg1);

    void on_edtMiddleName_textChanged(const QString &arg1);

    void on_edtLastName_textChanged(const QString &arg1);

    void on_edtExt_textChanged(const QString &arg1);

    void on_edtJobTitle_textChanged(const QString &arg1);

private:
    Ui::employeedetail *ui;
    //void loadEmployeeRecord();
    bool m_what;
    QString tokenString;
    bool enteringToken;
    bool waitingForReturn;
    void checkForTokenData(QEvent* event);
    void processToken();

    KeyPad* keyBrd;
};

#endif // EMPLOYEEDETAIL_H
