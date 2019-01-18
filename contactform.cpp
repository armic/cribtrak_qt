#include "contactform.h"
#include "ui_contactform.h"
#include "smtp.h"

contactform::contactform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contactform)
{
    ui->setupUi(this);

    keybrd = new KeyPad(this);
    ui->kbpanel->setLayout(new QHBoxLayout);
    ui->kbpanel->layout()->addWidget(keybrd);

}

contactform::~contactform()
{
    delete ui;
}

void contactform::on_btnCancel_clicked()
{
    // Cancel
    close();
}

void contactform::on_btnSend_clicked()
{
    //Send Email
}
