#include "logviewer.h"
#include "ui_logviewer.h"

logViewer::logViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logViewer)
{
    ui->setupUi(this);

//    QString fileName = QDate::currentDate().toString("kabtrak-dd_MM_yyyy.log");
    QString fileName = QDate::currentDate().toString("cribtrak-yyyy_MM_dd.log");
    ui->lblFilename->setText("Viewing log file " + fileName);
//    if (fileName.isNull())
//            fileName = "kabtrak-30_05_2017.log";

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            ui->logView->setPlainText(file.readAll());
    }


}

logViewer::~logViewer()
{
    delete ui;
}

void logViewer::on_btnClose_clicked()
{
    close();
}
