#include "scannermanager.h"
#include <QDebug>

ScannerManager::ScannerManager(QObject *parent) : QObject(parent)
{
    qDebug() << __FUNCTION__ << "creating serial connection";
    scanner = new BarcodeScanner(this);
    connect(scanner, &BarcodeScanner::barcodeScanned, this, &ScannerManager::onBarcode);
    scanningEnabled = true;
}

ScannerManager::~ScannerManager()
{
    //delete scanner;
}

void ScannerManager::setEnabled(bool enabled)
{
    scanningEnabled = enabled;
}

QString ScannerManager::portName()
{
    return scanner->portName();
}

void ScannerManager::onBarcode(QString barcode)
{
    if (scanningEnabled)
    {
        emit barcodeScanned(barcode);
    }
    else
    {
        qDebug() << __FUNCTION__ << "Scan attempt while disabled.";
    }
}
