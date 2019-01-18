#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QObject>
#include <QProgressBar>
#include <QTimer>

class ProgressBar : public QObject
{
    Q_OBJECT
public:
    explicit ProgressBar(int timerLth, QProgressBar* barInst, QObject *parent = 0);
    explicit ProgressBar(QString timerLth, QProgressBar *barInst, QObject *parent = 0);

    void start();
    void start(int newtime);
    void stop();

private:
    void init(int timerLth, QProgressBar *barInst);

    int maxSeconds;
    QProgressBar* barInstance;
    QTimer* timer;

signals:
    void progressBarTimeout();

public slots:
    void handleProgressTimer();

};

#endif // PROGRESSBAR_H
