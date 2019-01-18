#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>

namespace Ui {
class dashboard;
}

class dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit dashboard(QWidget *parent = 0);
    ~dashboard();
    void loadForm();
    void displayCustomerDetail();
    void displayCabinetDetail();
//    void displayDrawerList();
    void displayUserList();
    void displayCabTools();
    void displayTails();
    void displayTransaction(const QString sqltoken );
//    void displayAllTransaction();


private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_tableUserView_clicked(const QModelIndex &index);

    void on_tableDrawerView_clicked(const QModelIndex &index);

    void on_tableToolsView_clicked(const QModelIndex &index);

    void on_tableTailView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_btnClose_clicked();

    void on_btnReports_clicked();

    void on_closeButton_clicked();

private:
    Ui::dashboard *ui;
};

#endif // DASHBOARD_H
