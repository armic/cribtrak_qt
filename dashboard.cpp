#include "dashboard.h"
#include "ui_dashboard.h"
#include "maincontroller.h"
#include "datamanager.h"
#include <iostream>
#include <fstream>

using namespace std;


dashboard::dashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dashboard)
{
    ui->setupUi(this);
    loadForm();
    displayCustomerDetail();
    displayCabinetDetail();
//    displayDrawerList();
    displayUserList();
//    QModelIndex index = ui->tableDrawerView->currentIndex();
//    int i = index.row();
//    int DrawerNumber = ui->tableDrawerView->model()->data(ui->tableDrawerView->model()->index(i,2)).toInt();
//    qDebug()<<"Drawer No. "<<DrawerNumber;
//    displayCabTools(DrawerNumber);
    displayCabTools();
    displayTails();
    displayTransaction("");
//    displayAllTransaction();


    ui->id->setText(MainController::getDataManagerInstance()->currentCrib.cribId);
    ui->description->setText(MainController::getDataManagerInstance()->currentCrib.description);
    ui->location->setText(MainController::getDataManagerInstance()->currentCrib.location);
}

dashboard::~dashboard()
{
    delete ui;
}

void dashboard::loadForm()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    QString CompanyLogo = "images/%1"; // Customer logo
    QString kabtrakLogo = "images/%1"; // kabTRAK Logo
    QString dashboard =   "images/%1"; // Dashboard
    QString closebutton = "images/%1"; // Dashboard


    //Customer Logo
   ifstream file(CompanyLogo.arg(dataman->currentCustomer.comlogo).toStdString());
    if(!file)
        ui->logo->setPixmap(QPixmap("images/default_logo.png"));
    else

    ui->logo->setPixmap(QPixmap(CompanyLogo.arg(dataman->currentCustomer.comlogo)));




}

void dashboard::displayCustomerDetail()
{
  // use  Datamanager::getCustomerData
   DataManager* dataman = MainController::getDataManagerInstance();
   QSqlQuery customerQuery = dataman->getCustomerData();

//   ui->ownrant->setText("Revoke");
//   ui->gbAccessStatus->setEnabled(true);
//   ui->gbAccessType->setEnabled(true);
//   ui->lblName->setText(userQuery.value(1).toString());
   ui->owner->setText(customerQuery.value(0).toString());
   ui->contact->setText(customerQuery.value(1).toString());
   ui->email->setText(customerQuery.value(2).toString());
   ui->telephone->setText(customerQuery.value(3).toString());
   ui->fax->setText(customerQuery.value(4).toString());
}


void dashboard::displayCabinetDetail()
{
  // use  Datamanager::getCustomerData
   DataManager* dataman = MainController::getDataManagerInstance();
   QSqlQuery customerQuery = dataman->getCabinetData();

//   ui->ownrant->setText("Revoke");
//   ui->gbAccessStatus->setEnabled(true);
//   ui->gbAccessType->setEnabled(true);
//   ui->lblName->setText(userQuery.value(1).toString());
   ui->id->setText(customerQuery.value(0).toString());
   ui->description->setText(customerQuery.value(1).toString());
   ui->location->setText(customerQuery.value(2).toString());
   ui->firmware->setText(customerQuery.value(3).toString());

}

//void dashboard::displayDrawerList()
//{
// DataManager* dataman = MainController::getDataManagerInstance();
// QSqlQueryModel* drawerlistmodel = dataman->getDrawerList();
// drawerlistmodel->setHeaderData(2, Qt::Horizontal, tr("Drawer #"));
// drawerlistmodel->setHeaderData(4, Qt::Horizontal, tr("Description"));
// drawerlistmodel->setHeaderData(3, Qt::Horizontal, tr("Available?"));

// ui->tableDrawerView->setModel(drawerlistmodel);
// ui->tableDrawerView->setColumnHidden(0, true);
// ui->tableDrawerView->setColumnHidden(1, true);
// ui->tableDrawerView->setColumnHidden(5, true);
// ui->tableDrawerView->setColumnHidden(6, true);
// ui->tableDrawerView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
// ui->tableDrawerView->setCurrentIndex(ui->tableDrawerView->model()->index(0,0));
//}

void dashboard::displayUserList()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    QSqlQueryModel* userlistmodel = dataman->getUsersList();
    ui->tableUserView->setModel(userlistmodel);
    userlistmodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    userlistmodel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    userlistmodel->setHeaderData(2, Qt::Horizontal,  tr("Role"));
    userlistmodel->setHeaderData(3, Qt::Horizontal, tr("Active"));
    ui->tableUserView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

void dashboard::displayCabTools()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    //qDebug()<<"DrawerNum " << DrawNum;
    QSqlQueryModel* toollistmodel = NULL;
    toollistmodel = dataman->getCribToolList();
    ui->tableToolsView->setModel(toollistmodel);
//    toollistmodel->setHeaderData(0, Qt::Horizontal, tr("Tool Number #"));
//    toollistmodel->setHeaderData(6, Qt::Horizontal, tr("Item ID"));
//    toollistmodel->setHeaderData(5, Qt::Horizontal, tr("Description"));
//    toollistmodel->setHeaderData(2, Qt::Horizontal, tr("Status"));

//    ui->tableToolsView->setColumnHidden(1, true);
//    ui->tableToolsView->setColumnHidden(3, true);
//    ui->tableToolsView->setColumnHidden(4, true);
    ui->tableToolsView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


}

void dashboard::displayTails()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    QSqlQueryModel* taillistmodel = NULL;
    taillistmodel = dataman->getTailNumbersModel(dataman->currentCustomer.custId);
//    taillistmodel->setHeaderData(0,Qt::Horizontal, tr("Tail ID"));
//    taillistmodel->setHeaderData(1,Qt::Horizontal, tr("Tail #"));
//    taillistmodel->setHeaderData(2,Qt::Horizontal, tr("Description"));
//    taillistmodel->setHeaderData(3,Qt::Horizontal, tr("Speeddial"));
//    taillistmodel->setHeaderData(4,Qt::Horizontal, tr("Disabled"));

  //  ui->tableView->setColumnHidden(3,true);
    ui->tableTailView->setModel(taillistmodel);
    ui->tableTailView->setAlternatingRowColors(true);
    ui->tableTailView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableTailView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void dashboard::displayTransaction(const QString sqltoken )
{
    DataManager* dataman = MainController::getDataManagerInstance();
    QSqlQueryModel* issueancemodel = NULL;


    issueancemodel = MainController::getDataManagerInstance()->toolsOutModel;
    //issueancemodel = dataman->loadIssueanceModel(sqltoken);

//    issueancemodel->setHeaderData(0,Qt::Horizontal, tr("Date Issued"));
//    issueancemodel->setHeaderData(1,Qt::Horizontal, tr("Time Issued"));
//    issueancemodel->setHeaderData(2,Qt::Horizontal, tr("Issued To"));
//    issueancemodel->setHeaderData(3,Qt::Horizontal, tr("Tool Name"));
//    issueancemodel->setHeaderData(4,Qt::Horizontal, tr("Drawer #"));
//    issueancemodel->setHeaderData(5,Qt::Horizontal, tr("Tool #"));
//    issueancemodel->setHeaderData(6,Qt::Horizontal, tr("Tail"));

    ui->tableIssuedView->setModel(issueancemodel);\
    ui->tableIssuedView->setAlternatingRowColors(true);
    ui->tableIssuedView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableIssuedView->setSelectionMode(QAbstractItemView::SingleSelection);
    //

}

//void dashboard::displayAllTransaction()
//{
//    DataManager* dataman = MainController::getDataManagerInstance();
//    QSqlQueryModel* alltransactionmodel = NULL;



//    alltransactionmodel = dataman->loadAllTransactionModel();

//    alltransactionmodel->setHeaderData(0,Qt::Horizontal, tr("Date Issued"));
//    alltransactionmodel->setHeaderData(1,Qt::Horizontal, tr("Date Returned"));
//    alltransactionmodel->setHeaderData(2,Qt::Horizontal, tr("Issued To"));
//    alltransactionmodel->setHeaderData(3,Qt::Horizontal, tr("Tool Name"));
//    alltransactionmodel->setHeaderData(4,Qt::Horizontal, tr("Drawer #"));
//    alltransactionmodel->setHeaderData(5,Qt::Horizontal, tr("Tool #"));
//    alltransactionmodel->setHeaderData(6,Qt::Horizontal, tr("Tail"));

//    ui->tableHistoryView->setModel(alltransactionmodel);\
//    ui->tableHistoryView->setAlternatingRowColors(true);
//    ui->tableHistoryView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableHistoryView->setSelectionMode(QAbstractItemView::SingleSelection);
//    //

//}


void dashboard::on_calendarWidget_clicked(const QDate &date)
{
    //date selected
    QString sql;
    qDebug()<<"Date "<<date.toString("yyyy-MM-dd");
    QString givenDate = date.toString("yyyy-MM-dd");

    sql =   "SELECT \
            kabemployeeitemtransactions.outDate, \
            kabemployeeitemtransactions.transTime, \
            users.fullName, \
            tools.description, \
            kabemployeeitemtransactions.drawerNum, \
            kabemployeeitemtransactions.toolNum, \
            kabemployeeitemtransactions.trailId \
            FROM \
            kabemployeeitemtransactions \
            LEFT JOIN tools ON tools.PartNo = kabemployeeitemtransactions.itemId \
            LEFT JOIN users ON users.userId = kabemployeeitemtransactions.userId \
            WHERE \
            kabemployeeitemtransactions.custId = %1 AND \
            kabemployeeitemtransactions.kabId = '%2' AND ";


        sql = sql +  " kabemployeeitemtransactions.outDate = '" + givenDate + "' AND  kabemployeeitemtransactions.transType = 0 \
            ORDER BY \
            kabemployeeitemtransactions.transTime DESC";

       displayTransaction(sql);

}

void dashboard::on_tableDrawerView_clicked(const QModelIndex &index)

{
//     QString sql;
//     int i = index.row(); // now you know which record was selected
//     QString drawNum = ui->tableDrawerView->model()->data(ui->tableDrawerView->model()->index(i,2)).toString();

//     sql =   "SELECT \
//             kabemployeeitemtransactions.outDate, \
//             kabemployeeitemtransactions.transTime, \
//             users.fullName, \
//             tools.description, \
//             kabemployeeitemtransactions.drawerNum, \
//             kabemployeeitemtransactions.toolNum, \
//             kabemployeeitemtransactions.trailId \
//             FROM \
//             kabemployeeitemtransactions \
//             LEFT JOIN tools ON tools.PartNo = kabemployeeitemtransactions.itemId \
//             LEFT JOIN users ON users.userId = kabemployeeitemtransactions.userId \
//             WHERE \
//             kabemployeeitemtransactions.custId = %1 AND \
//             kabemployeeitemtransactions.kabId = '%2' AND ";

//             sql = sql +  " kabemployeeitemtransactions.drawerNum = " + drawNum + " AND  kabemployeeitemtransactions.transType = 0 \
//                 ORDER BY \
//                 kabemployeeitemtransactions.transTime DESC";

//            displayCabTools(drawNum.toInt());
//            displayTransaction(sql);


}

void dashboard::on_tableUserView_clicked(const QModelIndex &index)
{
    QString sql;
    int i = index.row(); // now you know which record was selected
    QString fullname = ui->tableUserView->model()->data(ui->tableUserView->model()->index(i,1)).toString();

    sql =   "SELECT \
            kabemployeeitemtransactions.outDate, \
            kabemployeeitemtransactions.transTime, \
            users.fullName, \
            tools.description, \
            kabemployeeitemtransactions.drawerNum, \
            kabemployeeitemtransactions.toolNum, \
            kabemployeeitemtransactions.trailId \
            FROM \
            kabemployeeitemtransactions \
            LEFT JOIN tools ON tools.PartNo = kabemployeeitemtransactions.itemId \
            LEFT JOIN users ON users.userId = kabemployeeitemtransactions.userId \
            WHERE \
            kabemployeeitemtransactions.custId = %1 AND \
            kabemployeeitemtransactions.kabId = '%2' AND ";

            sql = sql +  " users.fullname = '" + fullname + "' AND  kabemployeeitemtransactions.transType = 0 \
                ORDER BY \
                kabemployeeitemtransactions.transTime DESC";

           displayTransaction(sql);
}

void dashboard::on_tableToolsView_clicked(const QModelIndex &index)
{
//    QString sql;
//    int i = index.row(); // now you know which record was selected
//    QString toolnumber = ui->tableToolsView->model()->data(ui->tableToolsView->model()->index(i,0)).toString();

//    QModelIndex drawindex = ui->tableDrawerView->currentIndex();
//    int j = drawindex.row();
//    QString DrawerNumber = ui->tableDrawerView->model()->data(ui->tableDrawerView->model()->index(j,2)).toString();

//    sql =   "SELECT \
//            kabemployeeitemtransactions.outDate, \
//            kabemployeeitemtransactions.transTime, \
//            users.fullName, \
//            tools.description, \
//            kabemployeeitemtransactions.drawerNum, \
//            kabemployeeitemtransactions.toolNum, \
//            kabemployeeitemtransactions.trailId \
//            FROM \
//            kabemployeeitemtransactions \
//            LEFT JOIN tools ON tools.PartNo = kabemployeeitemtransactions.itemId \
//            LEFT JOIN users ON users.userId = kabemployeeitemtransactions.userId \
//            WHERE \
//            kabemployeeitemtransactions.custId = %1 AND \
//            kabemployeeitemtransactions.kabId = '%2' AND ";

//            sql = sql +  " kabemployeeitemtransactions.toolNum = " + toolnumber + " AND kabemployeeitemtransactions.drawerNum = " + DrawerNumber + " AND    kabemployeeitemtransactions.transType = 0 \
//                ORDER BY \
//                kabemployeeitemtransactions.transTime DESC";

//           displayTransaction(sql);
}

void dashboard::on_tableTailView_clicked(const QModelIndex &index)
{
    QString sql;
    int i = index.row(); // now you know which record was selected
    QString tailnumber = ui->tableTailView->model()->data(ui->tableTailView->model()->index(i,1)).toString();

    sql =   "SELECT \
            kabemployeeitemtransactions.outDate, \
            kabemployeeitemtransactions.transTime, \
            users.fullName, \
            tools.description, \
            kabemployeeitemtransactions.drawerNum, \
            kabemployeeitemtransactions.toolNum, \
            kabemployeeitemtransactions.trailId \
            FROM \
            kabemployeeitemtransactions \
            LEFT JOIN tools ON tools.PartNo = kabemployeeitemtransactions.itemId \
            LEFT JOIN users ON users.userId = kabemployeeitemtransactions.userId \
            WHERE \
            kabemployeeitemtransactions.custId = %1 AND \
            kabemployeeitemtransactions.kabId = '%2' AND ";

            sql = sql +  " kabemployeeitemtransactions.trailId  = '" + tailnumber + "' AND  kabemployeeitemtransactions.transType = 0 \
                ORDER BY \
                kabemployeeitemtransactions.transTime DESC";

           displayTransaction(sql);
}

void dashboard::on_pushButton_clicked()
{
  displayTransaction("");
}

void dashboard::on_btnClose_clicked()
{
    close();
}

void dashboard::on_btnReports_clicked()
{
    //Reports
}

void dashboard::on_closeButton_clicked()
{
    close();
}
