#include "accessdenied.h"
#include "ui_accessdenied.h"

accessdenied::accessdenied(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accessdenied)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(closeMessage()));
    timer->start(3000);

}

accessdenied::~accessdenied()
{
    delete ui;
}

void accessdenied::closeMessage()
{
  close();
}
