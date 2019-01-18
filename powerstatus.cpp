#include "powerstatus.h"
#include <QTimer>
#include <QDebug>

#ifdef WIN32
    #include <Windows.h>
#endif

/*PowerStatus::PowerStatus(QObject *parent) : QObject(parent)
{
    qDebug() << "Initial constructor";
    PowerStatus(1000, parent);
}*/

PowerStatus::PowerStatus(QObject *parent, int timeout) : QObject(parent)
{
    powerConnected_ = powerConnected();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkPower()));
    timer->start(timeout);
}

bool PowerStatus::powerConnected()
{
#ifdef WIN32
    SYSTEM_POWER_STATUS sps;
    GetSystemPowerStatus(&sps);
    if (sps.ACLineStatus == 1)
    {
        return true;
    }
#endif

    return false;
}

void PowerStatus::checkPower()
{
    bool prevPowerConnected = powerConnected_;
    powerConnected_ = powerConnected();
    if (prevPowerConnected != powerConnected_)
    {
        // Power status changed.
        qDebug() << "Power Changed";
        emit powerConnectionChanged(powerConnected_);
    }
    else
    {
        qDebug() << "Power Unchanged";
    }
}
