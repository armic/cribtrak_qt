#ifndef SCANNERMANAGER_H
#define SCANNERMANAGER_H

// Isolates the low-level scanner details from the rest of the system.

#include <QObject>
#include "barcodescanner.h"

class ScannerManager : public QObject
{
    Q_OBJECT
public:
    explicit ScannerManager(QObject *parent = nullptr);
    ~ScannerManager();

    void setEnabled(bool enabled = true);
    QString portName();

#ifdef TRAK_TESTKEYS
    void emitScanSignal(QString barcode)
    {
        //emit barcodeScanned(barcode);
        onBarcode(barcode);
    }
#endif

signals:
void barcodeScanned(QString barcode);

public slots:
void onBarcode(QString barcode);

private:
BarcodeScanner *scanner;
bool scanningEnabled;

};

#endif // SCANNERMANAGER_H
