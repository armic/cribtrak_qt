#include "maincontroller.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setStyleSheet ("QCheckBox::indicator:unchecked {image: url(:/images/images/unchecked_t_25x25.png);} "
                         "QCheckBox::indicator:checked {image:   url(:/images/images/checked_t_25x25.png);} "
                         "QCheckBox::indicator:checked:disabled {image:   url(:/images/images/checked_greyed_25x25.png);} "
                         "QCheckBox::indicator:unchecked:disabled {image:   url(:/images/images/unchecked_greyed_25x25.png);} "
                         "QCheckBox::indicator {width: 40px; height: 40px;}");

//    // splashscreen display
//    QSplashScreen* splash = new QSplashScreen;
//    splash->setPixmap(QPixmap(":images/images/splash.png"));
//    splash->show();

//    Qt::Alignment topLeft = Qt::AlignLeft | Qt::AlignTop;
//    splash->showMessage("Initialising Main Controller", topLeft, Qt::white);
    MainController w;

//    splash->close();
//    delete(splash);

    // install the main event filter
    //a.installEventFilter(new mainEventFilter());
    return a.exec();
}
