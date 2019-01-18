#include "taillist.h"
#include "ui_taillist.h"
#include "maincontroller.h"
#include "datamanager.h"
#include "taildetail.h"



taillist::taillist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taillist)
{
    ui->setupUi(this);
    populatedataItem();
    connect(ui->btnEdit, SIGNAL(clicked(bool)),this,SLOT(editTail()));
    connect(ui->btnNew, SIGNAL(clicked(bool)),this,SLOT(newTail()));

}

taillist::~taillist()
{
    delete ui;
}


void taillist::populatedataItem()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    taillistmodel = dataman->getTailNumbersAdminModel(dataman->currentCustomer.custId);
    taillistmodel->setHeaderData(0,Qt::Horizontal, tr("Tail ID"));
    taillistmodel->setHeaderData(1,Qt::Horizontal, tr("Tail #"));
    taillistmodel->setHeaderData(2,Qt::Horizontal, tr("Description"));
    taillistmodel->setHeaderData(3,Qt::Horizontal, tr("Speeddial"));
    taillistmodel->setHeaderData(4,Qt::Horizontal, tr("Disabled"));

    //  ui->tableView->setColumnHidden(3,true);
    ui->tableViewTail->setModel(taillistmodel);
    ui->tableViewTail->setAlternatingRowColors(true);
    ui->tableViewTail->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewTail->setSelectionMode(QAbstractItemView::SingleSelection);
}

void taillist::on_buttonBox_rejected()
{
    close();
}

void taillist::editTail()
{
    int i;
    QString sTailNumber;
    QModelIndex index = ui->tableViewTail->currentIndex();
    i = index.row();
    qDebug() << __FUNCTION__ << "index:" << i;

    if (i > -1)
    {
        sTailNumber = ui->tableViewTail->model()->data(ui->tableViewTail->model()->index(i,1)).toString();
        taildetail frmTailDetail(false);
        frmTailDetail.setEditMode(sTailNumber);
        int exitCode = frmTailDetail.exec();
        qDebug() << __FUNCTION__ << "Tail Detail exit code" << exitCode;
        populatedataItem();
    }
}

void taillist::newTail() {
    QString sTailNumber = "";
    taildetail frmTailDetail(false);
    //frmTailDetail.setEditMode(sTailNumber);
    int exitCode = frmTailDetail.exec();
    qDebug() << "Tail Detail Exec Code" << exitCode;
    populatedataItem();
}


void taillist::on_buttonBox_accepted()
{
    close();
}
