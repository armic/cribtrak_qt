#include "toolfinder.h"
#include "ui_toolfinder.h"
#include "datamanager.h"
#include "maincontroller.h"

ToolFinder::ToolFinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolFinder)
{
    ui->setupUi(this);

    keypad = new KeyPad(this);
    ui->keypadLayout->addWidget(keypad);

    ui->toolFinderTableView->setAlternatingRowColors(true);
    //ui->toolFinderTableView->setModel(MainController::getDataManagerInstance()->getToolFinderModel());
    ui->toolFinderTableView->setSortingEnabled(true);
    ui->filterLineEdit->setFocus();


    //-------------------
    // Set up proxy model.
    //-------------------

    // Create proxy model.
    filterProxy = new MultiColumnSortFilterProxyModel(this);

    filterProxy->setSourceModel(MainController::getDataManagerInstance()->getToolFinderModel(this));
    // Connect the proxy models together.


    // Assign columns.
    filterProxy->setFilterKeyColumn(3);
    filterProxy->setFilterKeyColumns({2, 3, 4});


    ui->toolFinderTableView->setModel(filterProxy);
    ui->toolFinderTableView->resizeColumnsToContents();
    ui->toolFinderTableView->resizeRowsToContents();
    ui->toolFinderTableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

ToolFinder::~ToolFinder()
{
    delete ui;
}

void ToolFinder::on_filterLineEdit_textChanged(const QString &arg1)
{
    filterProxy->setFilterRegExp(QRegExp(arg1, Qt::CaseInsensitive, QRegExp::FixedString));
}

void ToolFinder::on_pushButton_clicked()
{
    close();
}
