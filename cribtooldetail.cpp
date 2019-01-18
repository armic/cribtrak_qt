#include <QDebug>

#include "cribtooldetail.h"
#include "ui_cribtooldetail.h"
#include "datamanager.h"
#include "maincontroller.h"
#include <QSqlQuery>
#include <QInputDialog>

CribToolDetail::CribToolDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CribToolDetail)
{
    ui->setupUi(this);

    editMode = false;
    setWindowTitle("New Crib Tool");
    toolId = -1;

    setup();

    qDebug() << __FUNCTION__ << " Enter ";
    keybrd = new KeyPad(this);
    ui->keybrd->setLayout(new QHBoxLayout);
    ui->keybrd->layout()->addWidget(keybrd);

    ui->toolLabel->setVisible(false);
    ui->locationLabel->setVisible(false);
    ui->barcodeErrorLabel->setVisible(false);

    ui->serviceableCheckBox->setChecked(true);

    connect(MainController::getMainControllerInstance(), &MainController::adminBarcode, this, &CribToolDetail::onBarcodeScanned);
}

CribToolDetail::~CribToolDetail()
{
    delete ui;
}

void CribToolDetail::setNewMode()
{
    editMode = false;
    setWindowTitle("New Crib Tool");
}

void CribToolDetail::setEditMode(int toolId)
{
//    qDebug() << __FUNCTION__ << "index:" << index;
    editMode = true;
//    int comboIdx = getToolIndex(toolId);
//    qDebug() << __FUNCTION__ << "comboIdx:" << comboIdx;
//    ui->toolComboBox->setCurrentIndex(comboIdx);
//    DataManager* backend = MainController::getDataManagerInstance();
//    QSqlQuery query = backend->getSelectedCribTool(toolId);
//    if (query.size() > 0)
//    {
//        query.next();
//        ui->barcodeLineEdit->setText(query.value("barcodeTAG").toString());
//        //ui->toolComboBox->set
//    }

    this->toolId = toolId;

    //ui->barcodeLineEdit->setEnabled(false);
    ui->toolComboBox->setVisible(false);
    ui->locationComboBox->setVisible(false);
    ui->toolLabel->setVisible(true);
    ui->locationLabel->setVisible(true);

    DataManager* backend = MainController::getDataManagerInstance();
    QSqlQuery query = backend->getSelectedCribTool(toolId);
    if (query.size() > 0)
    {
        query.next();
        currentBarcode = query.value("barcodeTAG").toString();
        ui->barcodeLineEdit->setText(query.value("barcodeTAG").toString());
        ui->toolLabel->setText(query.value("description").toString());
        ui->locationLabel->setText(query.value("locdescription").toString());
        ui->dateEdit->setDate(query.value("currentcalibrationdate").toDate());
        ui->requiresCalibrationCheckBox->setChecked(query.value("calibration").toBool());
        ui->kitCheckBox->setChecked(query.value("kit").toBool());
        ui->consumableCheckBox->setChecked(query.value("consumable").toBool());
        ui->kitCountLineEdit->setText(query.value("kitcount").toString());
        ui->consumableQtyLineEdit->setText(query.value("consumableBalance").toString());
        ui->serviceableCheckBox->setChecked(query.value("serviceable").toBool());
        //ui->toolComboBox->set
    }
    setWindowTitle("Edit Crib Tool");
}

int CribToolDetail::getToolIndex(int toolId)
{
    //qDebug() << __FUNCTION__ << ui->toolComboBox->model()->index(index, 0).data().toString();
    qDebug() << __FUNCTION__ << "Looking for toolId:" << toolId;
    int numElements = ui->toolComboBox->model()->rowCount();
    for (int i = 0; i < numElements; ++i)
    {
        int id = ui->toolComboBox->model()->index(i, 0).data().toInt();
        qDebug() << __FUNCTION__ << id;
        if (id == toolId)
        {
            return i;
        }
    }
    return -1;
}


void CribToolDetail::setup()
{
    DataManager* backend = MainController::getDataManagerInstance();

    QSqlQueryModel *model = backend->getToolInventoryList();
//    QTableView* view = new QTableView(this);
//    view->setModel(model);
//    ui->toolComboBox->setView(view);
//    view->setRowHidden(0, true);
//    view->setRowHidden(1, true);
//    view->setRowHidden(2, false);
//    view->setRowHidden(3, true);
//    view->setRowHidden(4, false);
//    view->setRowHidden(5, true);
//    view->setRowHidden(6, true);
//    view->setRowHidden(7, true);
//    view->setRowHidden(8, true);
//    view->setRowHidden(9, true);

    ui->toolComboBox->setModel(model);
    ui->toolComboBox->setModelColumn(10);
    ui->toolComboBox->setEditable(false);
    //ui->tailComboBox->setInsertPolicy(QComboBox::InsertAtTop);
    //ui->toolComboBox->completer()->setCompletionMode(QCompleter::QCompleter::PopupCompletion);
    //ui->tailComboBox->completer()->setCompletionMode(QCompleter::QCompleter::InlineCompletion);
    //ui->toolComboBox->setStyleSheet("background-color: rgb(240, 240, 240);"
                                    //"font-size: 12pt;");
                                    //"font-weight: bold;");
    //ui->toolComboBox->clearEditText();
    ui->toolComboBox->setFocusPolicy(Qt::StrongFocus);



    // crib tool location combo box
    model = backend->cribToolLocationList();
    ui->locationComboBox->setModel(model);
    ui->locationComboBox->setModelColumn(1);
    ui->locationComboBox->setEditable(false);
    ui->locationComboBox->setFocusPolicy(Qt::StrongFocus);


}




void CribToolDetail::on_barcodeLineEdit_textChanged(const QString &arg1)
{
    DataManager* backend = MainController::getDataManagerInstance();
//    if (backend->barcodeExists(arg1) && !editMode)
    if (backend->barcodeExists(arg1) && (editMode && (currentBarcode != ui->barcodeLineEdit->text())))
    {
        ui->barcodeErrorLabel->setVisible(true);
        ui->saveButton->setEnabled(false);
    }
    else
    {
        ui->barcodeErrorLabel->setVisible(false);
        ui->saveButton->setEnabled(true);
    }
}

void CribToolDetail::on_toolComboBox_currentIndexChanged(int index)
{
    qDebug() << __FUNCTION__ << ui->toolComboBox->model()->index(index, 0).data().toString();
}

void CribToolDetail::on_kitCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->kitCountLineEdit->setEnabled(true);
    }
    else
    {
        ui->kitCountLineEdit->setEnabled(false);
    }
}

void CribToolDetail::on_consumableCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->consumableQtyLineEdit->setEnabled(true);
    }
    else
    {
        ui->consumableQtyLineEdit->setEnabled(false);
    }
}

void CribToolDetail::on_requiresCalibrationCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->dateEdit->setEnabled(true);
    }
    else
    {
        ui->dateEdit->setEnabled(false);
    }
}

void CribToolDetail::on_cancelButton_clicked()
{
    close();
}

void CribToolDetail::on_saveButton_clicked()
{
    if (editMode)
    {
        auto backend = MainController::getDataManagerInstance();
        QString itemId = ui->toolComboBox->model()->index(ui->toolComboBox->currentIndex(), 1).data().toString();
        QString description = ui->toolComboBox->model()->index(ui->toolComboBox->currentIndex(), 2).data().toString();
        int location = ui->locationComboBox->model()->index(ui->locationComboBox->currentIndex(), 0).data().toInt();
        QString locDescr = ui->locationComboBox->model()->index(ui->locationComboBox->currentIndex(), 1).data().toString();
        //backend->insertCribTool(itemId, ui->barcodeLineEdit->text().toInt(), description, location, ui->kitCheckBox->isChecked(), ui->kitCountLineEdit->text().toInt(), ui->consumableCheckBox->isChecked(), ui->consumableQtyLineEdit->text().toInt(), locDescr, ui->requiresCalibrationCheckBox->isChecked(), ui->dateEdit->date());
        backend->updateCribTool(toolId, ui->barcodeLineEdit->text(), ui->kitCheckBox->isChecked(), ui->kitCountLineEdit->text().toInt(), ui->consumableCheckBox->isChecked(), ui->consumableQtyLineEdit->text().toInt(), ui->requiresCalibrationCheckBox->isChecked(), ui->dateEdit->date(), ui->serviceableCheckBox->isChecked());

        close();
    }
    else
    {
        auto backend = MainController::getDataManagerInstance();
        QString itemId = ui->toolComboBox->model()->index(ui->toolComboBox->currentIndex(), 1).data().toString();
        QString description = ui->toolComboBox->model()->index(ui->toolComboBox->currentIndex(), 2).data().toString();
        int location = ui->locationComboBox->model()->index(ui->locationComboBox->currentIndex(), 0).data().toInt();
        QString locDescr = ui->locationComboBox->model()->index(ui->locationComboBox->currentIndex(), 1).data().toString();
        backend->insertCribTool(itemId, ui->barcodeLineEdit->text(), description, location, ui->kitCheckBox->isChecked(), ui->kitCountLineEdit->text().toInt(), ui->consumableCheckBox->isChecked(), ui->consumableQtyLineEdit->text().toInt(), locDescr, ui->requiresCalibrationCheckBox->isChecked(), ui->dateEdit->date(), ui->serviceableCheckBox->isChecked());

        close();
    }
}

void CribToolDetail::onBarcodeScanned(QString barcode)
{
    //if (!editMode)
    //{
        ui->barcodeLineEdit->setText(barcode);
    //}
}

void CribToolDetail::on_newLocationButton_clicked()
{
    QDialog *d = new QDialog();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QLineEdit *locDescEdit = new QLineEdit();
    QLabel *lbl = new QLabel();

    KeyPad *k = new KeyPad();

    vLayout->addWidget(lbl);
    vLayout->addWidget(locDescEdit);
    vLayout->addWidget(buttonBox);
    vLayout->addWidget(k);

    d->setLayout(vLayout);

    locDescEdit->setFocus();

    lbl->setText("Enter name of new location");
    d->setWindowTitle("New Location");

    QObject::connect(buttonBox, SIGNAL(accepted()), d, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), d, SLOT(reject()));

    int result = d->exec();

    auto backend = MainController::getDataManagerInstance();
    //QString newLocation = QInputDialog::getText(this,"New Location","Enter new location");
    if (result == QDialog::Accepted)
    {
        QString newLocation = locDescEdit->text();
        if (!newLocation.isEmpty())
        {
            if (MainController::getDataManagerInstance()->createLocation(newLocation))
            {
                ui->locationComboBox->setModel(backend->cribToolLocationList());
            }
        }
    }
}
