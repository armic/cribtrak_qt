#include "disconnected.h"
#include "ui_disconnected.h"

disconnected::disconnected(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::disconnected)
{
    ui->setupUi(this);
}

disconnected::~disconnected()
{
    delete ui;
}
