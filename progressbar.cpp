
#include <QDebug>
#include <QSettings>

#include "progressbar.h"


//
//  constructor with timer values in parameters
//
ProgressBar::ProgressBar(int timerLth, QProgressBar *barInst, QObject *parent) : QObject(parent)
{

    init(timerLth, barInst);

}



//
//  overloaded constructor with timer values from ini file
//  the values will be taken from the [ProgressTimers] section
//
ProgressBar::ProgressBar(QString timerLth, QProgressBar *barInst, QObject *parent) : QObject(parent)
{

    // Get timer values from ini file
    QSettings settings("trak.ini", QSettings::IniFormat);
    settings.beginGroup("System");
    int tmr = settings.value(timerLth, 30).toInt();
    settings.endGroup();

    init(tmr, barInst);

}

//
//  init only called by the constructors
//
void ProgressBar::init(int timerLth, QProgressBar *barInst)
{

    maxSeconds = timerLth;
    barInstance = barInst;
    timer = new QTimer(this);
    if (maxSeconds > 0)
    {
        barInstance->setMaximum(maxSeconds);
        connect(timer, &QTimer::timeout, this, &ProgressBar::handleProgressTimer);
    }

}





void ProgressBar::start()
{
    // set progress bar
    barInstance->setValue(0);
    if (maxSeconds > 0)
        timer->start(1000);
    barInstance->setStyleSheet(barInstance->property("defaultStyleSheet").toString() +
    " QProgressBar::chunk { background:  rgb(0, 120, 215); }"
    "QProgressBar {border: 0px solid grey; border-radius: 5px; background-color: black; } ");

}




void ProgressBar::start(int newtime)
{
    qDebug() << __FUNCTION__;
    maxSeconds = newtime;
    // set progress bar
    barInstance->setValue(0);
    if (maxSeconds > 0)
    {
        barInstance->setMaximum(maxSeconds);
        timer->start(1000);
    }
    barInstance->setStyleSheet(barInstance->property("defaultStyleSheet").toString() +
    " QProgressBar::chunk { background:  rgb(0, 120, 215); }"
    "QProgressBar {border: 0px solid grey; border-radius: 5px; background-color: black; } ");

}





void ProgressBar::stop()
{
    timer->stop();
}



void ProgressBar::handleProgressTimer()
{
    int value = barInstance->value();
    if (value >= maxSeconds)
    {
        // holt bar
        stop();
        emit progressBarTimeout();
        return;
    }
    if (value > (maxSeconds-3))
    {
        barInstance->setStyleSheet(barInstance->property("defaultStyleSheet").toString() +
        " QProgressBar::chunk { background: red; }"
        "QProgressBar {border: 0px solid grey; border-radius: 5px; background-color: black; } ");
    }
    barInstance->setValue(value+1);

}

