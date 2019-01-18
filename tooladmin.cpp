#include "tooladmin.h"
#include "ui_tooladmin.h"
#include "maincontroller.h"
#include "datamanager.h"
#include "tooldetail.h"
#include "cribtooldetail.h"

#include "csvreader.h"
#include "csvwriter.h"

tooladmin::tooladmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tooladmin)
{
    ui->setupUi(this);
    populateTooldataItem();
    populateCribTooldataItem();
    connect(MainController::getMainControllerInstance(), &MainController::adminBarcode, this, &tooladmin::onBarcodeScanned);

    keyPad = new KeyPad(this);
    ui->keyPadLayout->addWidget(keyPad);

    //setWindowModality(Qt::WindowModal);
    setWindowState(Qt::WindowFullScreen);

}

tooladmin::~tooladmin()
{
    delete ui;
}

void tooladmin::populateTooldataItem()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    toollistmodel = dataman->getToolInventoryList();
    toollistmodel->setHeaderData(1,Qt::Horizontal, tr("Part #"));
    toollistmodel->setHeaderData(4,Qt::Horizontal, tr("Stock Code"));
    toollistmodel->setHeaderData(2,Qt::Horizontal, tr("Description"));
    toollistmodel->setHeaderData(5,Qt::Horizontal, tr("Image"));
    toollistmodel->setHeaderData(7,Qt::Horizontal, tr("Serial Number"));
    toollistmodel->setHeaderData(8,Qt::Horizontal, tr("is a Kit"));
    toollistmodel->setHeaderData(9,Qt::Horizontal, tr("Kit Count"));

  //  ui->tableView->setColumnHidden(3,true);

    // Set up filtering.
    allToolsProxyModel = new MultiColumnSortFilterProxyModel(this);
    allToolsProxyModel->setSourceModel(toollistmodel);
    ui->tableViewAllTools->setModel(allToolsProxyModel);



    allToolsProxyModel->setFilterKeyColumns({2, 1, 4, 7});

    //ui->tableViewAllTools->setModel(toollistmodel);
    ui->tableViewAllTools->setAlternatingRowColors(true);
    ui->tableViewAllTools->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewAllTools->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewAllTools->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewAllTools->setColumnWidth(2,350);
    ui->tableViewAllTools->setColumnWidth(8,50);
    ui->tableViewAllTools->setColumnWidth(9,50);
    ui->tableViewAllTools->hideColumn(0);
    ui->tableViewAllTools->hideColumn(3);
    ui->tableViewAllTools->hideColumn(6);

}

void tooladmin::populateCribTooldataItem()
{
    DataManager* dataman = MainController::getDataManagerInstance();
    cribtoollistmodel = dataman->getCribToolList();
//    cribtoollistmodel->setHeaderData(1,Qt::Horizontal, tr("Drawer"));
//    cribtoollistmodel->setHeaderData(0,Qt::Horizontal, tr("Tool"));
//    cribtoollistmodel->setHeaderData(6,Qt::Horizontal, tr("Item ID"));
//    cribtoollistmodel->setHeaderData(5,Qt::Horizontal, tr("Description"));
//    cribtoollistmodel->setHeaderData(2,Qt::Horizontal, tr("Status"));

    //-------------------
    // Set up proxy model chain.
    //-------------------

    // Create proxy models.
    cribToolsProxyModel = new MultiColumnSortFilterProxyModel(this);
    cribToolsConsumableProxyModel = new QSortFilterProxyModel(this);

    // Connect the proxy models together.
    cribToolsProxyModel->setSourceModel(cribtoollistmodel);
    cribToolsConsumableProxyModel->setSourceModel(cribToolsProxyModel);


    // Assign columns.
    //cribToolsProxyModel->setFilterKeyColumn(3);
    //cribToolsProxyModel->setFilterKeyColumn(-1);
    cribToolsProxyModel->setFilterKeyColumns({1, 2, 3, 4});
    cribToolsConsumableProxyModel->setFilterKeyColumn(7);


    // NOTE: this is just for testing. Remove when filter options in the UI are added.
    cribToolsConsumableProxyModel->setFilterRegExp(QRegExp("YES", Qt::CaseInsensitive, QRegExp::FixedString));

    // The tableViewCribTools model should be the final proxy model in the chain.
//    ui->tableViewCribTools->setModel(cribToolsProxyModel);
    ui->tableViewCribTools->setModel(cribToolsProxyModel);




  //  ui->tableView->setColumnHidden(3,true);
    //ui->tableViewCribTools->setModel(cribToolsProxyModel);
    //ui->tableViewCribTools->setModel(cribtoollistmodel);
    ui->tableViewCribTools->setAlternatingRowColors(true);
    ui->tableViewCribTools->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewCribTools->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewCribTools->horizontalHeader()->setStretchLastSection(true);
//    ui->tableViewCribTools->setColumnWidth(5,500);
//    ui->tableViewCribTools->setColumnWidth(0,50);
//    ui->tableViewCribTools->setColumnWidth(1,50);
//    ui->tableViewCribTools->hideColumn(3);
//    ui->tableViewCribTools->hideColumn(4);

}



void tooladmin::on_btnNew_clicked()
{
//    // New button
//    toolDetail frmToolDetail;
//    frmToolDetail.setStockCode("");
//    int exitCode = frmToolDetail.exec();
//    qDebug() << "Tool Detail Exec Code" << exitCode;
//    populateTooldataItem();
    if (ui->tabList->currentIndex() == 1)
    {
        qDebug() << __FUNCTION__ << "Current tab is 1";
        CribToolDetail cribTool;
        cribTool.setModal(true);
        int exitCode = cribTool.exec();
        populateCribTooldataItem();
    }
    else
    {
        // New button
        toolDetail frmToolDetail;
        frmToolDetail.setStockCode("");
        int exitCode = frmToolDetail.exec();
        qDebug() << "Tool Detail Exec Code" << exitCode;
        populateTooldataItem();
    }
}

void tooladmin::on_btnEdit_clicked()
{
    if (ui->tabList->currentIndex() == 1)
    {
        QModelIndex index = ui->tableViewCribTools->currentIndex();
        int i = index.row();
        if (i == -1)
        {

        }
        else
        {
            int toolId = ui->tableViewCribTools->model()->data(ui->tableViewCribTools->model()->index(i, 0)).toInt();
            qDebug() << __FUNCTION__ << "toolId:" << toolId;
            CribToolDetail cribTool;
            cribTool.setEditMode(toolId);
            //cribTool.setEditMode(i);
            cribTool.setModal(true);
            int exitCode = cribTool.exec();
            populateCribTooldataItem();
        }
    }
    else
    {

        // Edit
        int i;
        QString sStockCode;
        QModelIndex index = ui->tableViewAllTools->currentIndex();
        i = index.row();
        if(i == -1)
        {
            //No selected row

        }
        else
        {
            qDebug()<< "Tool Index "<<i;
            //     sStockCode = ui->tableViewAllTools->model()->data(ui->tableViewAllTools->model()->index(i,1)).toString();
            sStockCode = ui->tableViewAllTools->model()->data(ui->tableViewAllTools->model()->index(i,4)).toString();
            toolDetail frmToolDetail;
            frmToolDetail.setStockCode(sStockCode);
            int exitCode = frmToolDetail.exec();
            qDebug() << "Tool Detail Exec Code" << exitCode;
            populateTooldataItem();

        }
    }
}

void tooladmin::on_btnDelete_clicked()
{
    if (ui->tabList->currentIndex() == 0)
    {
        DataManager* dataman = MainController::getDataManagerInstance();
        int i;
        QString sPartNumber;
        QModelIndex index = ui->tableViewAllTools->currentIndex();
        i = index.row();
        if(i == -1)
        {
            // No index selected
            QMessageBox msgBox;
            msgBox.setText("Please select a tool to delete.");
            msgBox.exec();

        }
        else
        {
            sPartNumber = ui->tableViewAllTools->model()->data(ui->tableViewAllTools->model()->index(i,1)).toString();
            int toolId = ui->tableViewAllTools->model()->data(ui->tableViewAllTools->model()->index(i, 0)).toInt();
            if(dataman->cribToolExists(sPartNumber))
            {
                // Cannot delete
                QMessageBox msgBox;
                msgBox.setText("Current tool is linked to one of the crib tools and cannot be deleted.");
                msgBox.exec();
            }
            else
            {
                // Delete too
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Please Confirm", "Do you really want to delete current tool?",
                                              QMessageBox::Yes|QMessageBox::No);
                // Grant access
                if (reply == QMessageBox::Yes) {
                    qDebug() << "Yes was clicked";
                    dataman->deleteToolRecord(toolId);
                    populateTooldataItem();
                }

            }

        }
    }
    else
    {
        // Crib tool list.
        DataManager* dataman = MainController::getDataManagerInstance();
        int index = ui->tableViewCribTools->currentIndex().row();
        if (index > -1)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Please Confirm", "Do you really want to delete current tool?",
                                          QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                dataman->deleteCribToolRecord(ui->tableViewCribTools->model()->data(ui->tableViewCribTools->model()->index(index, 0)).toInt());
            }
            populateCribTooldataItem();
        }
    }
}

// NOTE: This isn't going to work on its own as the strings can (and do) have commas.
// The number of commas should be known (from the first line). Counting the commas will
// provide a hint to handling the line.
//QString tooladmin::csvRemoveQuotes(QString str)
//{
//    QString out = "";
//    for (int i = 0; i < str.length(); ++i)
//    {
//        QString ch = str.at(i);
//        if (ch == "\"")
//        {
//            if (str.at(i+1) == "\"")
//            {
//                out += ch;
//                ++i;
//            }
//        }
//        else
//        {
//            out += ch;
//        }
//    }
//    return out;
//}

//QStringList tooladmin::parseCsvLine(QString line)
//{
//    QStringList result;
//    bool insideString = false;
//    QString token;
//    QChar separator = ',';
//    QChar stringEncloser = '\"';
//    for (int i = 0; i < line.length(); ++i)
//    {
//        QChar ch = line.at(i);
//        if (ch == separator)
//        {
//            if (insideString)
//            {
//                token += ch;
//            }
//            else
//            {
//                result << token;
//                //qDebug() << __FUNCTION__ << "Token:" << token;
//                token = "";
//            }
//        }
//        else if (ch == stringEncloser)
//        {
//            if (insideString)
//            {
//                if (line.at(i + 1) == stringEncloser)
//                {
//                    token += stringEncloser;
//                    ++i;
//                }
//                else
//                {
//                    insideString = false;
//                }
//            }
//            else
//            {
//                insideString = true;
//            }
//        }
//        else if (i == line.length() - 1)
//        {
//            token += ch;
//            result << token;
//            //qDebug() << __FUNCTION__ << "Token:" << token;
//            token = "";
//        }
//        else
//        {
//            token += ch;
//        }

//        if ((i == line.length() - 1) && (ch == stringEncloser || ch == separator))
//        {
//            result << token;
//        }
//    }
//    qDebug() << __FUNCTION__ << result.length();
//    return result;
//}

void tooladmin::on_btnImport_clicked()
{
    auto dataman = MainController::getDataManagerInstance();

    if (ui->tabList->currentIndex() == 0)
    {
        // tools
        auto query = dataman->getToolExportList();

        QString fileName = QFileDialog::getOpenFileName(this, tr("Import Tool List"), "c:/", tr("CSV Files (*.csv)"));
        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                return;
            }
            CsvReader csvReader;

            QTextStream in(&file);



            // Ignore first line for now.
            if(csvReader.parseLine(in.readLine()).length() != 5)
            {
                qWarning() << __FUNCTION__ << "Incorrect number of fields in CSV.";
                return;
            }

            while (!in.atEnd())
            {
                QString line = in.readLine();
                //out << csvRemoveQuotes(line) << "\n";
                //out << parseCsvLine(line);
                //qDebug() << parseCsvLine(line);
                //qDebug() << csvReader.parseLine(line);
                //parseCsvLine(line);
                //qDebug() << csvRemoveQuotes(line);
                QStringList list = csvReader.parseLine(line);

                //dataman->insertToolRecord(list.at(1), list.at(2), list.at(3).toInt(), list.at(4).toInt(), 0);
                dataman->insertToolRecordFromCSV(list.at(0), list.at(1), list.at(2), list.at(3).toInt(), list.at(4).toInt());
            }

            file.close();
            populateTooldataItem();
        }
    }
    else
    {
        // cribtools
        auto query = dataman->getToolExportList();

        QString fileName = QFileDialog::getOpenFileName(this, tr("Import Crib Tool List"), "c:/", tr("CSV Files (*.csv)"));
        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                return;
            }
            CsvReader csvReader;

            QTextStream in(&file);



            // Ignore first line for now.
            int len = csvReader.parseLine(in.readLine()).length();
            if(len != 17)
            {
                qWarning() << __FUNCTION__ << "Incorrect number of fields in CSV:" << len;
                return;
            }


            while (!in.atEnd())
            {
                QString line = in.readLine();
                //out << csvRemoveQuotes(line) << "\n";
                //out << parseCsvLine(line);
                //qDebug() << parseCsvLine(line);
                //qDebug() << csvReader.parseLine(line);
                //parseCsvLine(line);
                //qDebug() << csvRemoveQuotes(line);
                QStringList list = csvReader.parseLine(line);

                //dataman->insertToolRecord(list.at(1), list.at(2), list.at(3).toInt(), list.at(4).toInt(), 0);
                QString lastCalDate = list.at(13);
                QString curCalDate = list.at(14);
                /*if (lastCalDate.isEmpty())
                {
                    lastCalDate = "null";
                }
                if (curCalDate.isEmpty())
                {
                    curCalDate = "null";
                }*/
                dataman->insertCribToolRecordFromCSV(list.at(0), list.at(1), list.at(2), list.at(3), list.at(4).toInt(), list.at(5).toInt(), list.at(6).toInt(), list.at(7).toInt(), list.at(8).toInt(), list.at(9).toInt(), list.at(10), list.at(11).toInt(), list.at(12).toInt(), lastCalDate, curCalDate, list.at(15).toInt(), list.at(16));
            }

            file.close();
            populateCribTooldataItem();
        }
    }



    return;





    QFile file("E:\\Work\\cribtrak\\csvtest\\tools4.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << __FUNCTION__ << "File open failed:" << file.errorString();
        return;
    }

    QFile outFile("E:\\Work\\cribtrak\\csvtest\\tools_converted.csv");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << __FUNCTION__ << "File open failed:" << file.errorString();
        return;
    }

    CsvReader csvReader;

    QTextStream in(&file);
    QTextStream out(&outFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        //out << csvRemoveQuotes(line) << "\n";
        //out << parseCsvLine(line);
        //qDebug() << parseCsvLine(line);
        qDebug() << csvReader.parseLine(line);
        //parseCsvLine(line);
        //qDebug() << csvRemoveQuotes(line);
    }

    file.close();
    outFile.close();
}

void tooladmin::on_tabList_currentChanged(int index)
{
    // Tab Changed
//    qDebug() << "Current Tab Index " << index;
//    switch (index) {
//    case 0:
//        ui->btnNew->setEnabled(true);
//        ui->btnEdit->setEnabled(true);
//        ui->btnDelete->setEnabled(true);
//        ui->btnImport->setEnabled(true);
//        break;

//    case 1:
//        ui->btnNew->setEnabled(false);
//        ui->btnEdit->setEnabled(false);
//        ui->btnDelete->setEnabled(false);
//        ui->btnImport->setEnabled(false);

//        break;

//    default:
//        break;
    //    }
}

void tooladmin::onBarcodeScanned(QString barcode)
{
    //TODO
    for (int i = 0; i < ui->tableViewCribTools->model()->rowCount(); ++i)
    {
        QString bcode = ui->tableViewCribTools->model()->index(i, 2).data().toString();
        if (bcode == barcode)
        {
            ui->tabList->setCurrentIndex(1);
            ui->tableViewCribTools->setFocus();
            ui->tableViewCribTools->selectRow(i);
            return;
        }
    }
}

void tooladmin::on_filterEdit_textChanged(const QString &arg1)
{
    allToolsProxyModel->setFilterRegExp(QRegExp(arg1, Qt::CaseInsensitive, QRegExp::FixedString));
    cribToolsProxyModel->setFilterRegExp(QRegExp(arg1, Qt::CaseInsensitive, QRegExp::FixedString));
    cribToolsProxyModel->invalidate();
    allToolsProxyModel->invalidate();
}


void tooladmin::on_btnexport_clicked()
{
    CsvWriter writer;
    auto dataman = MainController::getDataManagerInstance();

    if (ui->tabList->currentIndex() == 0)
    {
        auto query = dataman->getToolExportList();

        QString fileName = QFileDialog::getSaveFileName(this, tr("Export Tool List"), "c:/", tr("CSV File (*.csv)"));
        if (!fileName.isEmpty())
        {
            QFile outFile(fileName);
            if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                return;
            }
            QTextStream out(&outFile);

            out << writer.constructLine(QVariantList() << "part" << "serial" << "description" << "iskit" << "kitcount") << "\n";
            while (query.next())
            {
                QString csvLine = writer.constructLine(QVariantList() << query.value(0) << query.value(1) << query.value(2) << query.value(3) << query.value(4));
                out << csvLine << "\n";
                //qDebug().noquote() << __FUNCTION__ << csvLine;
            }
        }
    }
    else
    {
        auto query = dataman->getCribToolExportList();

        QString fileName = QFileDialog::getSaveFileName(this, tr("Export Crib Tool List"), "c:/", tr("CSV File (*.csv)"));
        if (!fileName.isEmpty())
        {
            QFile outFile(fileName);
            if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                return;
            }
            QTextStream out(&outFile);

            out << writer.constructLine(QVariantList() << "itemId" << "cribId" << "barcodeTAG" << "description" << "location" << "kit" << "kitcount" << "consumable" << "consumed" << "consumableBalance" << "locdescription" << "serviceable" << "calibration" << "lastcalibrationdate" << "currentcalibrationdate" << "calibrated" << "custId") << "\n";
            while (query.next())
            {
                QString csvLine = writer.constructLine(QVariantList() << query.value(0) << query.value(1) << query.value(2) << query.value(3) << query.value(4) << query.value(5) << query.value(6) << query.value(7) << query.value(8) << query.value(9) << query.value(10) << query.value(11) << query.value(12) << query.value(13) << query.value(14) << query.value(15) << query.value(16));
                out << csvLine << "\n";
                //qDebug().noquote() << __FUNCTION__ << csvLine;
            }
        }
    }

    //qDebug().noquote() << __FUNCTION__ << writer.constructLine(QVariantList() << "Hi" << "Hi, \"everyone!\"" << 4 << 0) << "\n" << writer.constructLine(QVariantList() << "Ho" << "Hi, \"everyone!\"" << 4 << 0 << "sdujfkhk");
}

void tooladmin::on_closeButton_clicked()
{
    close();
}
