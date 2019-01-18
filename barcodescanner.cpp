#include "barcodescanner.h"
#include <QDebug>

BarcodeScanner::BarcodeScanner(QObject *parent) : QObject(parent)
{
    connectScanner();
}

BarcodeScanner::~BarcodeScanner()
{
    delete serialPort;
}

void BarcodeScanner::handleReadyRead()
{
    readData.append(serialPort->readAll());

    if (readData.endsWith('\r'))
    {
        QString barcode = readData;
        readData.clear();
        qDebug() << "Scanned barcode" << QString::fromLatin1(barcode.toLatin1().toHex());

        // Ignore first and last digits, and the 0x0d character at the end.
        //emit barcodeScanned(barcode.mid(1, barcode.length() - 3));

        // Ignore the trailing 0x0d character.
        emit barcodeScanned(barcode.left(barcode.length() - 1));
    }
}

void BarcodeScanner::handleError(QSerialPort::SerialPortError error)
{
    //qWarning() << "Serial port error: " << serialPort->errorString();
    // NOTE: Need to test what happens when scanner is unplugged during operation.
    // This handler should be reached.
    // Should clear readData variable and reconnect.
    // One problem is that the logs show this warning every connection!
    // Will the above reconnection procedure result in an endless loop?
}

void BarcodeScanner::reconnectScanner()
{
    connectScanner();
}

QString BarcodeScanner::portName()
{
    return serialPort->portName();
}

void BarcodeScanner::connectScanner()
{
    QString port;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        //qDebug() << info;
        if (info.description() == "Barcode Scanner")
        {
            port = info.portName();
            qDebug() << __FUNCTION__ << "Scanner port:" << port;
        }
    }

    serialPort = new QSerialPort();
    serialPort->setPortName(port);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    connect(serialPort, &QSerialPort::readyRead, this, &BarcodeScanner::handleReadyRead);
    connect(serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error), this, &BarcodeScanner::handleError);

    if (!serialPort->open(QIODevice::ReadOnly)) {
        //qWarning() << __FUNCTION__ << "Failed to open serial port" << serialPort->portName() << serialPort->errorString();
        //qDebug() << __FUNCTION__ << "Trying again in 1 second.";
        QTimer::singleShot(1000, this, SLOT(reconnectScanner()));
    }
    else
    {
        qDebug() << __FUNCTION__ << "Serial port connection established.";
    }

}
