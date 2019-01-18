#include "loadingscreen.h"
#include "ui_loadingscreen.h"

loadingscreen::loadingscreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadingscreen)
{
    ui->setupUi(this);
}

loadingscreen::~loadingscreen()
{
    delete ui;
}
