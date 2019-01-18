#include "employeelist.h"
#include "ui_employeelist.h"
#include "maincontroller.h"
#include "employeedetail.h"
#include "datamanager.h"

employeelist::employeelist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employeelist)
{
    ui->setupUi(this);

    loadEmployeeUserList();
    connect(ui->tableViewEmployee, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_selectEmployee()));
    connect(ui->tableViewUsers, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_selectUser()));
 }

employeelist::~employeelist()
{
    delete ui;
}

//void employeelist::on_tabWidget_currentChanged(int index)
//{
//    // Display List according to tab
//    //
//    qDebug()<<"Tab Index"<<index;
//}

//void employeelist::on_toolButton_clicked()
//{
//    // Add new employee
//}

//void employeelist::on_toolButton_2_clicked()
//{
//    // Edit selected employee

//    QModelIndex index = ui->tableViewEmployee->currentIndex();

//    int i = index.row(); // now you know which record was selected
//    QString sUserID = ui->tableViewEmployee->model()->data(ui->tableViewEmployee->model()->index(i,0)).toString();
//    qDebug()<<"Selected User ID"<<sUserID;
//}

//void employeelist::on_toolButton_4_clicked()
//{
//    // Grant or Revoke current employee
//}

void employeelist::loadEmployeeUserList()
{
    DataManager* dataman = MainController::getDataManagerInstance();
       // Load employee records
       QSqlQueryModel* emplistmodel = dataman->getEmployeeList();
       // Set Headers
       emplistmodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
       emplistmodel->setHeaderData(1, Qt::Horizontal, tr("Fist Name"));
       emplistmodel->setHeaderData(2, Qt::Horizontal, tr("Last Name"));
       emplistmodel->setHeaderData(5, Qt::Horizontal, tr("cribTRAK User"));
       emplistmodel->setHeaderData(6, Qt::Horizontal, tr("Disabled"));


       ui->tableViewEmployee->setModel(emplistmodel);
       ui->tableViewEmployee->setColumnHidden(3,true);
       ui->tableViewEmployee->setColumnHidden(4,true);
       ui->tableViewEmployee->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

//       for (int i = 0; i < ui->tableViewEmployee->model()->rowCount(); i++)
//          {
//            if(emplistmodel->index(i,3).data(Qt::DisplayRole).toInt() == 1)
//              {
//                ui->tableViewEmployee->model()->setData(ui->tableViewEmployee->model()->index(i,3),QVariant("Yes"), Qt::EditRole);
//            } else {
//                ui->tableViewEmployee->model()->setData(ui->tableViewEmployee->model()->index(i,3),QVariant("No"), Qt::EditRole);
//            }
//          }


       // Load user records
       QSqlQueryModel* userlistmodel = dataman->getUsersList();
       ui->tableViewUsers->setModel(userlistmodel);
       userlistmodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
       userlistmodel->setHeaderData(1, Qt::Horizontal, tr("Name"));
       userlistmodel->setHeaderData(2, Qt::Horizontal,  tr("Role"));
       userlistmodel->setHeaderData(3, Qt::Horizontal, tr("Active"));
       ui->tableViewUsers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
   }


void employeelist::on_selectEmployee()
{
      QModelIndex index = ui->tableViewEmployee->currentIndex();
      int i = index.row(); // now you know which record was selected
      int isUser =  ui->tableViewEmployee->model()->data(ui->tableViewEmployee->model()->index(i,3)).toInt();
       qDebug() << "Index is " << isUser;

      switch(isUser){
        case 0:
          {
              ui->btnGrantRevoke->setText("Grant");
              break;
          }

      case 1:
          {
              ui->btnGrantRevoke->setText("Revoke");
             break;
          }
      }



}

void employeelist::on_selectUser()
{
    QModelIndex index = ui->tableViewUsers->currentIndex();
    int i = index.row(); // now you know which record was selected
    qDebug() << "Index is " << i;
}





void employeelist::on_buttonBox_rejected()
{
    close();
}

void employeelist::on_btnGrantRevoke_clicked()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    // Grant/Revoke user
    // Check active tab
    int i;
    QString sUserID;
    int activeindex =  ui->tabList->currentIndex();
    qDebug()<<"Active Tab Index " <<activeindex;


    switch(activeindex)
    {

    case 0: // Employee list
    {
        QModelIndex index = ui->tableViewEmployee->currentIndex();
        i = index.row(); // now you know which record was selected
        sUserID = ui->tableViewEmployee->model()->data(ui->tableViewEmployee->model()->index(i,0)).toString();
        break;
    }
    case 1: // Users list
    {
        QModelIndex index = ui->tableViewUsers->currentIndex();
        i = index.row(); // now you know which record was selected
        sUserID = ui->tableViewUsers->model()->data(ui->tableViewUsers->model()->index(i,0)).toString();
        break;

    }
    }

    // Quick fix/hack for granting access to non-existent user.
    // Should be fixed by disabling the grant/revoke button.
    if (i == -1)
    {
        QMessageBox::information(this, "No User Selected", "Please select a user.");
        return;
    }

    //
    qDebug()<<"Selected User ID"<<sUserID;

    QString grantOPtion = ui->btnGrantRevoke->text();
    qDebug()<< "Caption is" << grantOPtion;

    if(grantOPtion == "Grant")
    {
        // Grant access
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "User Access", "Do you really want to grant access to the current user?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QString Fullname = ui->tableViewEmployee->model()->data(ui->tableViewEmployee->model()->index(i,1)).toString() + " " + ui->tableViewEmployee->model()->data(ui->tableViewEmployee->model()->index(i,2)).toString() ;
            qDebug() << "employeelist::on_btnGrantRevoke_clicked() Granting user access to " << sUserID << Fullname;
            dataman->grantUserAccess(sUserID, Fullname);
            // Reload employee list
            loadEmployeeUserList();
        }



    }else
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "User Access", "Do you really want to revoke access to the current user?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            //Revoke access
            dataman->revokeUserAccess(sUserID);
            //Reload user list
            loadEmployeeUserList();
        }


    }


}

void employeelist::on_tabList_currentChanged(int index)
{
      qDebug()<<"Tab Index"<<index;
      switch(index)
      {
        case 0:
          {
           ui->btnEdit->setEnabled(true);
           ui->btnNew->setEnabled(true);
           break;
          }
        case 1:
          {
           ui->btnEdit->setEnabled(false);
           ui->btnNew->setEnabled(false);
           ui->btnGrantRevoke->setText("Revoke");
           break;
          }

      }
}



void employeelist::on_btnEdit_clicked()
{

    int i;
    QString sUserID;
    QModelIndex index = ui->tableViewEmployee->currentIndex();
    i = index.row(); // now you know which record was selected
    sUserID = ui->tableViewEmployee->model()->data(ui->tableViewEmployee->model()->index(i,0)).toString();


    // Load Employee Detail
    // Load Employee List window
    employeedetail frmEmployeeDetail(true);
    frmEmployeeDetail.setModal(true);
    frmEmployeeDetail.setWindowState(Qt::WindowFullScreen);

    frmEmployeeDetail.setUserID(sUserID);
    int exitCode = frmEmployeeDetail.exec();
    qDebug() << "Employee Detail Exec Code" << exitCode;
    loadEmployeeUserList();



}





void employeelist::on_btnNew_clicked()
{
     // Insert New Employee Record
     QString sUserID;
     sUserID = "";

    employeedetail frmEmployeeDetail(false);
    frmEmployeeDetail.setModal(true);
    frmEmployeeDetail.setWindowState(Qt::WindowFullScreen);
    frmEmployeeDetail.setUserID(sUserID);
    int exitCode = frmEmployeeDetail.exec();
    qDebug() << "Employee Detail Exec Code" << exitCode;
    loadEmployeeUserList();

 }

void employeelist::on_buttonBox_accepted()
{
     close();
}
