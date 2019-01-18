#ifndef GUESTSCREEN_H
#define GUESTSCREEN_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QDateTime>
#include <QTimer>

#include "selecttail.h"

namespace Ui {
class GuestScreen;
}

class GuestScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GuestScreen(QWidget *parent = 0);
    ~GuestScreen();

    void setScreen();


    bool event(QEvent *event);

private slots:
    void on_switchButton_clicked();
    void toolButtonClicked();
    void deviceConnected();
    void deviceDisconnected();
    void rtsCheck();

    void on_toolFinderButton_clicked();

    void on_rtsButton_clicked();

public slots:
    void dateTime();

private:

    void setupScreen();
    void checkForTokenData(QEvent* event);
    void processToken();
    void invalidUserMessage();
    void addSelectTailWidget();

    quint64 readMemoryUsage();


    qint32 stateId;
    QString tokenString;
    bool enteringToken;
    bool waitingForReturn;

    SelectTail* selecttailDialog;
    QTimer *timer;
    QTimer *rtsTimer;   // Timer for release to service alert

    QWidget *tailWidget;

#define MAXTOKENLENGTH 20

private:
    Ui::GuestScreen *ui;


//protected:
//  void resizeEvent(QResizeEvent *re) {
//    pixmap  = pixmap.scaled(re->size(),Qt::KeepAspectRatioByExpanding);
//  }
//  void paintEvent(QPaintEvent *re) {
//    QPainter painter(this);
//    painter.drawPixmap(0,0,pixmap);
//  }
//private:
//  QPixmap pixmap;


};

#endif // GUESTSCREEN_H
