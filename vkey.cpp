#include "vkey.h"
//#include <QtTest/QTest>


VKey::VKey(const QString &text, QWidget *parent) : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    //setStyleSheet("font: 75 24pt; border: 2px solid grey; border-radius: 4px; background-color: #f8f8f8;");
    //setStyleSheet("font: 75 18pt; border: 2px solid grey; border-radius: 4px; background-color: #f8f8f8;");
    setStyleSheet("font: 75 18pt; border: 2px solid grey; border-radius: 4px; color: #f8f8f8; background-color: #000000");
    setText(text);
}
