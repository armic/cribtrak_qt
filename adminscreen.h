#ifndef ADMINSCREEN_H
#define ADMINSCREEN_H

#include <QWidget>

#include "progressbar.h"


namespace Ui {
class adminscreen;
}

class adminscreen : public QWidget
{
    Q_OBJECT

public:
    explicit adminscreen(QWidget *parent = 0);
    ~adminscreen();
    void setupScreen();
    void setScreen();

private slots:
    void on_customer_clicked();
    void on_employees_clicked();
    void on_database_clicked();

    void handleProgressBarEnd();
    void deviceConnected();
    void deviceDisconnected();
    void displayDateTime();

    void on_cabinet_clicked();

    void on_system_clicked();

    void on_tail_clicked();

    void on_logOut_clicked();

    void on_dashboard_clicked();

    void on_btnPHPMyAdmin_clicked();

    void on_btnTask_clicked();

    void on_btnNotepad_clicked();

    void on_btnExplorer_clicked();

    void on_btnCommand_clicked();

    void on_btnInternet_clicked();

    void on_tools_clicked();

    void on_email_clicked();

private:
    Ui::adminscreen *ui;

    ProgressBar* progressBar;
    QTimer *timer;

};

#endif // ADMINSCREEN_H
