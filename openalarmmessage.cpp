#include "openalarmmessage.h"
#include "ui_openalarmmessage.h"

openalarmmessage::openalarmmessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::openalarmmessage)
{
    ui->setupUi(this);
//    QSound::play("sounds/emergency005.wav");
}

openalarmmessage::~openalarmmessage()
{
    delete ui;
}
