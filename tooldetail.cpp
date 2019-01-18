#include "tooldetail.h"
#include "ui_tooldetail.h"
#include "maincontroller.h"
#include "datamanager.h"

toolDetail::toolDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::toolDetail)
{
    ui->setupUi(this);

    keybrd = new KeyPad(this);
    ui->keybrd->setLayout(new QHBoxLayout);
    ui->keybrd->layout()->addWidget(keybrd);

}

toolDetail::~toolDetail()
{
    delete ui;
}

void toolDetail::setStockCode(const QString &stockCode)
{

    m_stockCode = stockCode;
    qDebug()<<"Stock Code "<<m_stockCode;

    if(!m_stockCode.isEmpty())
    {
        // Edit Mode
        isEdit = true;
        DataManager* dataman = MainController::getDataManagerInstance();
        QSqlQuery toolQuery = dataman->getSelectedTool(m_stockCode);
        QSqlQuery qryCategory = dataman->getToolCategoryList();
        toolDetail::setWindowTitle("Editing Tool  " + toolQuery.value(1).toString());
        //Transfer data to form
        ui->edtStockCode->setReadOnly(true);
        ui->edtpartNum->setReadOnly(true);
        ui->edtStockCode->setText(toolQuery.value(2).toString());
        ui->edtpartNum->setText(toolQuery.value(0).toString());
        ui->edtDescription->setText(toolQuery.value(1).toString());
        ui->edtKitCount->setText(toolQuery.value(6).toString());
        int iIsKit = toolQuery.value(5).toInt();

        if(iIsKit == 1){
            ui->lblKitCount->setVisible(true);
            ui->edtKitCount->setVisible(true);
            ui->cbIsKit->setChecked(true);
        }
        else
        {
            ui->lblKitCount->setVisible(false);
            ui->edtKitCount->setVisible(false);
            ui->cbIsKit->setChecked(false);
        }

        // category combobox

        ui->cbCategory->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        int category = toolQuery.value(7).toInt();
        ui->cbCategory->clear();
        ui->cbCategory->addItem("Please select a category" ,0);
        while (qryCategory.next()) {
            //comboBox-&gt;addItem("First Element", myEnumeration::firstElem);
            qDebug()<<"Category " << qryCategory.value(1).toString() << "Value " << qryCategory.value(0).toInt();
            ui->cbCategory->addItem(qryCategory.value(1).toString(), qryCategory.value(0).toInt());
        }

        int catIndex = ui->cbCategory->findData(category);

        if (catIndex != -1 ) {
            ui->cbCategory->setCurrentIndex(catIndex);
        } else{
            ui->cbCategory->setCurrentIndex(0);
        }


    }
    else
    {
        // Insert Mode
        DataManager* dataman = MainController::getDataManagerInstance();
        QSqlQuery toolQuery = dataman->getSelectedTool(m_stockCode);
        QSqlQuery qryCategory = dataman->getToolCategoryList();
        toolDetail::setWindowTitle("Insert new tool");
        isEdit = false;
        ui->edtStockCode->setReadOnly(false);
        // category combobox

        ui->cbCategory->view()->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        int category = toolQuery.value(7).toInt();
        ui->cbCategory->clear();
        ui->cbCategory->addItem("Please select a category" ,0);
        while (qryCategory.next()) {
            //comboBox-&gt;addItem("First Element", myEnumeration::firstElem);
            qDebug()<<"Category " << qryCategory.value(1).toString() << "Value " << qryCategory.value(0).toInt();
            ui->cbCategory->addItem(qryCategory.value(1).toString(), qryCategory.value(0).toInt());
        }

        int catIndex = ui->cbCategory->findData(category);

        if (catIndex != -1 ) {
            ui->cbCategory->setCurrentIndex(catIndex);
        } else{
            ui->cbCategory->setCurrentIndex(0);
        }

    }
}

void toolDetail::on_btnBox_accepted()
{
    //Ok Button

    if (isEdit)
    {
        // Post edit
        int isAKit;
        int iCatID;

        DataManager* dataman = MainController::getDataManagerInstance();
        if (ui->cbIsKit->isChecked()) {
            isAKit = 1;
        }else{isAKit = 0; }

        iCatID =  ui->cbCategory->itemData(ui->cbCategory->currentIndex()).toInt();

        if(dataman->updateToolRecord(m_stockCode,ui->edtDescription->text(),isAKit, ui->edtKitCount->text().toInt(), iCatID))
        {
            qDebug() << "Post Tool records OK";
            close();
        }
        else
        {
            qDebug() << "Post Tool records failed";
            close();
        }
    }
    else
    {
        // Post Insert
        // Post edit
        int isAKit;
        int iCatID;

        DataManager* dataman = MainController::getDataManagerInstance();
        if (ui->cbIsKit->isChecked()) {
            isAKit = 1;
        }else{isAKit = 0; }

        iCatID =  ui->cbCategory->itemData(ui->cbCategory->currentIndex()).toInt();

        if(dataman->insertToolRecord(ui->edtStockCode->text(),ui->edtDescription->text(),isAKit, ui->edtKitCount->text().toInt(), iCatID))
        {
            qDebug() << "Post Tool records OK";
            close();
        }
        else
        {
            qDebug() << "Post Tool records failed";
            close();
        }


    }
}

void toolDetail::on_btnBox_rejected()
{
    //Cancel
    close();
}

void toolDetail::on_edtStockCode_textChanged(const QString &arg1)
{
    // Change to upper
    ui->edtStockCode->setText(arg1.toUpper());

}

void toolDetail::on_edtDescription_textChanged(const QString &arg1)
{
    //Change to upper
    ui->edtDescription->setText(arg1.toUpper());
}



void toolDetail::on_cbIsKit_toggled(bool checked)
{
    if(checked)
    {
        ui->lblKitCount->setVisible(true);
        ui->edtKitCount->setVisible(true);
    }else
    {
        ui->lblKitCount->setVisible(false);
        ui->edtKitCount->setVisible(false);
    }
}
