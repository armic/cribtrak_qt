#include "employeedetail.h"
#include "ui_employeedetail.h"
#include "maincontroller.h"
#include "datamanager.h"
#include "employeelist.h"

employeedetail::employeedetail(const bool &what, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employeedetail)
    , m_what(what)
{
    ui->setupUi(this);

    keyBrd = new KeyPad(this);
//    ui->keyboard->setLayout(new QHBoxLayout);
//    ui->keyboard->layout()->addWidget(keyBrd);
    ui->keybrd->setLayout(new QHBoxLayout);
    ui->keybrd->layout()->addWidget(keyBrd);

    ui->edtUserID->setEnabled(false);
    ui->edtUserID->setReadOnly(true);

    // NOTE: This may introduce spurious white space.
    ui->edtUserID->setInputMask("NNNNNNNNNNNNNNNN");

    ui->btnManual->setText("Manual");
    ui->lblIdMessage->setText("Please present your CARD");
    ui->edtUserID->setFocus();

    // create layout and set buttons in layout
    ui->buttonBox->setLayout(new QHBoxLayout);
    ui->buttonBox->layout()->addWidget(ui->okayBtn);
    ui->buttonBox->layout()->addWidget(ui->cancelBtn);
    connect (ui->okayBtn, &QPushButton::clicked, this, &employeedetail::on_buttonBox_accepted);
    connect (ui->cancelBtn, &QPushButton::clicked, this, &employeedetail::on_buttonBox_rejected);

}


employeedetail::~employeedetail()
{
    delete ui;
}

void employeedetail::updateUsertab()
{
  DataManager* dataman = MainController::getDataManagerInstance();
  // check user record

  if(dataman->isUserExists(m_UserID)) {
      QSqlQuery userQuery = dataman->getSelectedUser(m_UserID);

      ui->btnGrant->setText("Revoke");
      ui->gbAccessStatus->setEnabled(true);
      ui->gbAccessType->setEnabled(true);
      ui->lblName->setText(userQuery.value(1).toString());

      // update controls
      int AccessType = userQuery.value(5).toInt();
      qDebug() << "User ID" << userQuery.value(0).toString() << "Fullname " << userQuery.value(1).toString();

      switch (AccessType) { // accessTypeKab
      case 0:
          // User
          ui->rbCribtrakUser->setChecked(true);
          break;
      case 1:
          // Admin
          ui->rbAdmin_2->setChecked(true);
          break;

      case 2:

          // Supervisor
          ui->rbSupervisor->setChecked(true);
          break;

      default:
          ui->rbCribtrakUser->setChecked(true);
          break;
      }


      int activeCrib = userQuery.value(3).toInt();

      switch (activeCrib) { // enabledKab
      case 0:
          ui->rbDisabled->setChecked(true);

          break;
      case 1:
          ui->rbEnabled->setChecked(true);

          break;
      default:
          ui->rbDisabled->setChecked(true);
          break;
      }




  } else {

       ui->btnGrant->setText("Grant");
       ui->gbAccessStatus->setEnabled(false);
       ui->gbAccessType->setEnabled(false);
       ui->lblName->setText("");

  }


}

void employeedetail::setUserID(const QString &userID)
{

    m_UserID = userID;
    qDebug()<<"User ID "<<m_UserID;

    ui->edtUserID->setEnabled(false);
    ui->edtUserID->setReadOnly(true);
    ui->btnManual->setText("Manual");
    ui->lblIdMessage->setText("Please present your CARD");
    ui->edtUserID->setFocus();

    if(!m_UserID.isEmpty())
    {
        // Edit Mode
        ui->btnManual->setVisible(false);
        ui->lblIdMessage->setVisible(false);
        ui->edtUserID->setReadOnly(true);

        DataManager* dataman = MainController::getDataManagerInstance();
        QSqlQuery empQuery = dataman->getSelectedEmp(m_UserID);

         employeedetail::setWindowTitle("Editing " + empQuery.value(0).toString() + " - " + empQuery.value(1).toString() + " " + empQuery.value(3).toString());

        if(dataman->isUserExists(m_UserID))
        {
          ui->gbWebCredentials->setVisible(true);
          employeedetail::resize(800, 556);
        }
       else
        {
           ui->gbWebCredentials->setVisible(false);
           employeedetail::resize(450, 556);

        }
        // Transfer data to form
        ui->edtUserID->setText(empQuery.value(0).toString());
        ui->edtFirstName->setText(empQuery.value(1).toString());
        ui->edtMiddleName->setText(empQuery.value(2).toString());
        ui->edtLastName->setText(empQuery.value(3).toString());
        ui->edtExt->setText(empQuery.value(4).toString());
        ui->edtJobTitle->setText(empQuery.value(5).toString());
        ui->edtMobile->setText(empQuery.value(9).toString());
        ui->edtEmail->setText(empQuery.value(17).toString());
        ui->edtUsername->setText(empQuery.value(13).toString());
        ui->edtpassword->setText(empQuery.value(14).toString());


        //Web Credentials

        if(empQuery.value(11).toInt() == 1) {
            ui->cbActive->setChecked(true);
        } else {
           ui->cbActive->setChecked(false);
         }


        if(empQuery.value(15).toInt() == 1) {
            ui->rbAdmin->setChecked(true);
        }




        // Employee Disabled
        if(empQuery.value(16).toInt() == 1) {
            ui->cbDisbaled->setChecked(true);
        } else {
           ui->cbDisbaled->setChecked(false);
         }

        // Employee isUser_kab

        if(empQuery.value(12).toInt() == 1) {
            ui->cbCribUser->setChecked(true);

        } else {

            ui->cbCribUser->setChecked(false);
        }
        updateUsertab();



    }
    else
    {
        // Insert Mode
//        ui->btnManual->setVisible(true);
//        ui->lblIdMessage->setVisible(true);
        ui->gbWebCredentials->setVisible(false);
        employeedetail::resize(450, 556);
        employeedetail::setWindowTitle("New Employee Record");
        ui->tabAccess->setEnabled(false);
        updateUsertab();
        ui->btnGrant->setEnabled(false);

        ui->btnManual->setVisible(false);
        ui->lblIdMessage->setVisible(true);
        ui->edtUserID->setEnabled(true);
        ui->edtUserID->setReadOnly(false);
    }





}


void employeedetail::on_buttonBox_accepted()
{

    //
    // there could be a problem in this code if password exists but not changed!!!!!
    //

    QString vUserID = ui->edtUserID->text();
    QString vFirstName = ui->edtFirstName->text();
    QString vMiddleName = ui->edtMiddleName->text();
    QString vLastName = ui->edtLastName->text();
    QString vExtName = ui->edtExt->text();
    QString vPosition = ui->edtJobTitle->text();
    QString vEmail = ui->edtEmail->text();
    QString vMobileNumber = ui->edtMobile->text();
    QString vUserName = ui->edtUsername->text();
    QString vPassword = ui->edtpassword->text();
    QString encryptedPassword("");
    if (!vPassword.isNull() && !vPassword.isEmpty())
    {
        encryptedPassword = QCryptographicHash::hash( vPassword.toLatin1() , QCryptographicHash::Md5 ).toHex();
    }
    QString vConfirmPasword = ui->edtConfirmPassword->text();

    //Required Fields

    if(vFirstName.isEmpty() || vLastName.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Please complete the required fields.");
        msgBox.exec();
        return;
    }

    // Password did nor match

    if(!vPassword.isNull() && !vPassword.isEmpty() && vPassword != vConfirmPasword)
    {
        QMessageBox msgBox;
        msgBox.setText("Password did not match!.");
        msgBox.exec();
        return;
    }


    int isCribUser;
    // Employee isKabtrak User flag
    if(ui->cbCribUser->isChecked()) {
        isCribUser = 1;
    }else {
        isCribUser = 0;
    }

     // Employee Disbaled flag
    int vEmpDisabled;

    if(ui->cbDisbaled->isChecked()) {
        vEmpDisabled = 1;
    }else {
       vEmpDisabled = 0;
    }


    // Employee Portal Access flag
    int vWebActive;

    if(ui->cbActive->isChecked()) {
        vWebActive = 1;
    } else {
        vWebActive = 0;
    }

    int vUserRole;

    if(ui->rbAdmin->isChecked()) {
        vUserRole = 1;
    }

    if(ui->rbUser->isChecked()) {
        vUserRole = 0;
    }

    qDebug()<< "User Role is " << vUserRole;


    // User
    int vUserAccessType;

    if (ui->rbCribtrakUser->isChecked())
    {
        vUserAccessType = 0;
    }

    if (ui->rbAdmin_2->isChecked())
    {
        vUserAccessType = 1;
    }

    if (ui->rbSupervisor->isChecked())
    {
        vUserAccessType = 2;
    }

    int vUserAccessStatus;

    if (ui->rbDisabled->isChecked())
    {
        vUserAccessStatus = 0;
    } else{
       vUserAccessStatus = 1;
    }



    // Button OK clicked - apply settings and close window
     DataManager* dataman = MainController::getDataManagerInstance();

     if(m_what)

     {   // Edit Mode
         QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Please Confirm", "Do you really want to update current record?",
                                           QMessageBox::Yes|QMessageBox::No);
          // Grant access
         if (reply == QMessageBox::Yes) {
             qDebug() << "Yes was clicked";
             dataman->updateEmployeeRecord(vUserID, vFirstName,vMiddleName,vLastName,vExtName, vPosition, vEmail,vMobileNumber, vUserName, encryptedPassword,  vWebActive, vUserRole, isCribUser, vEmpDisabled);
             dataman->updateUserRecord(vUserID, vFirstName, vMiddleName, vLastName, vUserAccessStatus, vUserAccessType );
             close();
         }
     }else

     {
         if(!dataman->isEmployeeExists(vUserID)){
             // Insert Mode
             QMessageBox::StandardButton reply;
             reply = QMessageBox::question(this, "Please Confirm", "Do you really want to insert current record?",
                                               QMessageBox::Yes|QMessageBox::No);
              // Grant access
             if (reply == QMessageBox::Yes) {
                 qDebug() << "Yes was clicked";
                 dataman->insertEmployeeRecord(vUserID, vFirstName,vMiddleName,vLastName,vExtName, vPosition, vEmail,vMobileNumber, vUserName, encryptedPassword,  vWebActive, vUserRole, isCribUser, vEmpDisabled);
                 close();
             }

         }
         else{
              // UserID exist, abort insert
             QMessageBox msgBox;
             msgBox.setText("Card Number is in use. Please choose another.");
             msgBox.exec();
         }


     }






}

void employeedetail::on_buttonBox_rejected()
{
   // Button Cancel clicked - nothing to do but close the window
     QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Please Confirm", "Do you really want to CANCEL all updates to current record?",
                                      QMessageBox::Yes|QMessageBox::No);
     // Grant access
    if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        close();
    }
}


void employeedetail::on_btnGrant_clicked()
{

    DataManager* dataman = MainController::getDataManagerInstance();
    QString grantOPtion = ui->btnGrant->text();
    qDebug()<< "Caption is" << grantOPtion;

    if(grantOPtion == "Grant")
    {

     QMessageBox::StandardButton reply;
     reply = QMessageBox::question(this, "User Access", "Do you really want to grant access to the current user?",
                                       QMessageBox::Yes|QMessageBox::No);
      // Grant access
     if (reply == QMessageBox::Yes) {
         QString Fullname = ui->edtFirstName->text() + " " + ui->edtLastName->text();
         qDebug() << "employeedetail::on_btnGrant_clicked() Granting user access to " << m_UserID << Fullname;
         dataman->grantUserAccess(m_UserID, Fullname);
         updateUsertab();
       }


    }else {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "User Access", "Do you really want to revoke access to the current user?",
                                          QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            //Revoke access
            dataman->revokeUserAccess(m_UserID);
            updateUsertab();
          }



    }

}

void employeedetail::on_employeedetail_finished(int result)
{
    //
    qDebug()<< "Exit Code is " << result;
   // employeelist::loadEmployeeUserList();

}

void employeedetail::on_btnManual_clicked()
{
    // Switch to Manual and reader
    if(ui->btnManual->text() == "Manual") {
      ui->edtUserID->setEnabled(true);
      ui->edtUserID->setReadOnly(false);
      ui->btnManual->setText("Reader");
      ui->lblIdMessage->setText("Please type in your CARD Number");
      ui->edtUserID->setFocus();
    } else{
      ui->edtUserID->setEnabled(false);
      ui->edtUserID->setReadOnly(true);
      ui->btnManual->setText("Manual");
      ui->lblIdMessage->setText("Please present your CARD");
      ui->edtUserID->setFocus();

    }

}

void employeedetail::on_cbDisbaled_clicked()
{

    if(ui->cbDisbaled->isChecked()) {
        ui->rbDisabled->setChecked(true);
    }else{
        ui->rbDisabled->setChecked(false);
    }

}

void employeedetail::on_rbEnabled_clicked()
{
  if(ui->rbEnabled->isChecked())
  {
     ui->cbDisbaled->setChecked(false);
  }


}

void employeedetail::on_rbDisabled_clicked()
{
    if(ui->rbDisabled->isChecked())
    {
       ui->cbDisbaled->setChecked(true);
    }


}

void employeedetail::processToken()
{

    ui->edtUserID->setText(tokenString);
    qDebug() << "User ID from Reader " << tokenString;
 }
//    // remove spaces from string
//    // does this user exist?
//    bool result = MainController::getDataManagerInstance()->getUserDetails(tokenString);
//    // Valid user?
//    if (result)
//    {
//        qDebug() << "valid user for token";
//        addSelectTailWidget();
//    }
//    else {
//        // invalid user, display error
//        qDebug() << "Invalid user for token";
//        invalidUserMessage();
//        enteringToken = false;
//        tokenString.clear();
//    }



bool employeedetail::event(QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        qDebug() << "Employee Detail::event KEY is " << ke->key();
        // waiting for token data
        checkForTokenData(event);
        return true;
    }
    else
    {
        return QWidget::event(event);
    }
}

void employeedetail::checkForTokenData(QEvent* event)
{

    QChar key = static_cast<QKeyEvent *>(event)->key();
    qDebug() << "Employee Detail::checkForTokenData:: key entered" << key;
    if (key <= 0x00 || key > Qt::Key_AsciiTilde)
    {
        return;  // key not in range
    }
    if (key == Qt::Key_Exclam)
    {
        enteringToken = true;
        waitingForReturn = false;
        tokenString.clear();
    }
    else if(enteringToken)
    {
        if (waitingForReturn)
        {
            if (key == Qt::Key_Enter || key == Qt::Key_Return)
            {
                qDebug() << "Employee Detail::checkForTokenData:: token entered" << tokenString;
                processToken();

            }
            else
            {
                //return key shuold be next
                enteringToken = false;
                qDebug() << "Employee Detail::checkForTokenData:: return key was NOT entered";
            }
        }
        if (key == Qt::Key_NumberSign)
        {
            // now have a token now wait for return key
            waitingForReturn = true;
            qDebug() << "Employee Detail::checkForTokenData:: token entered" << tokenString << "now waiting for return key";
        }
        else
        {
            // append char to token string
            if (key != ' ')
            {
                tokenString.append(key);
                if (tokenString.length() > MAXTOKENLENGTH)
                {
                    enteringToken = false;
                    tokenString.clear();
                }
            }
        }
    }
}

void employeedetail::on_edtFirstName_textChanged(const QString &arg1)
{

    ui->edtFirstName->setText(arg1.toUpper());
}

void employeedetail::on_edtMiddleName_textChanged(const QString &arg1)
{
     ui->edtMiddleName->setText(arg1.toUpper());
}

void employeedetail::on_edtLastName_textChanged(const QString &arg1)
{
     ui->edtLastName->setText(arg1.toUpper());
}

void employeedetail::on_edtExt_textChanged(const QString &arg1)
{
     ui->edtExt->setText(arg1.toUpper());
}

void employeedetail::on_edtJobTitle_textChanged(const QString &arg1)
{
     ui->edtJobTitle->setText(arg1.toUpper());
}
