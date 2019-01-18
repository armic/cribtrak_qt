#ifndef POWERSTATUS_H
#define POWERSTATUS_H

#include <QObject>

class PowerStatus : public QObject
{
    Q_OBJECT
public:
    //explicit PowerStatus(QObject *parent = 0);
    explicit PowerStatus(QObject *parent = 0, int timeout = 1000);
    bool powerConnected();

private:
    bool powerConnected_;
    int timeout;

signals:
    void powerConnectionChanged(bool mainsPower);

public slots:
    void checkPower();
};

#endif // POWERSTATUS_H
