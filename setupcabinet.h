#ifndef SETUPCABINET_H
#define SETUPCABINET_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSettings>

namespace Ui {
class setupcabinet;
}

class setupcabinet : public QDialog
{
    Q_OBJECT

public:
    explicit setupcabinet(QWidget *parent = 0);
    ~setupcabinet();
//    void LoadDialog();
//    void loadToolList(int DrawNum);
//    QString sCustID;
//    int defaultCalibrationAccount;
//    int defaultServiceAccount;
//    int defaultTransferAccount;
//    int defaultTestAccount;
//    int calibration;
//    int calibrationNotify;
//    //bool allowreturn;


//public slots:
//    void on_selectDrawer();


//private slots:
//    void on_btnUnlock_clicked();
//    void on_btnLock_clicked();
//    void on_btnReset_clicked();
//    void on_btnRestart_clicked();
//    void on_buttonBox_rejected();
//    void on_buttonBox_accepted();
//    void on_btnConnect_clicked();
//    void on_btnDisconnect_clicked();
//    void on_btnPrevDrawers_clicked();
//    void on_btnNextDrawers_clicked();

//   // void on_lstDrawers_activated(const QModelIndex &index);

//    void on_cbCalibration_currentIndexChanged(int index);

//    void on_cbService_currentIndexChanged(int index);

//    void on_cbTransfer_currentIndexChanged(int index);

//    void on_cbTest_currentIndexChanged(int index);

//    void on_cbNextCalibDate_currentIndexChanged(int index);

//    void on_cbCalibDaysNotif_currentIndexChanged(int index);

//    void on_btnCalibration_clicked();

//    void on_chkAlow_toggled(bool checked);

//    void on_chkAlow_clicked(bool checked);

//    void on_btntoolprop_clicked();
    
//    void on_lstDrawers_clicked(const QModelIndex &index);
    

//    void enterAdminMaint();

private:
    Ui::setupcabinet *ui;

};

#endif // SETUPCABINET_H
