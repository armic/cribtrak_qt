#ifndef BARCODESCANNER_H
#define BARCODESCANNER_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

class BarcodeScanner : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeScanner(QObject *parent = nullptr);
    ~BarcodeScanner();

signals:
void barcodeScanned(QString barcode);

public slots:
void handleReadyRead();
void handleError(QSerialPort::SerialPortError error);
void reconnectScanner();
QString portName();

private:
QSerialPort *serialPort;
QByteArray  readData;
QTimer timer;

void connectScanner();
};

#endif // BARCODESCANNER_H
