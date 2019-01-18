#include "keypad.h"
#include "vkey.h"
#include <vector>
#include <QHBoxLayout>
#include <QString>
#include <QEvent>
#include <QKeyEvent>
#include <QtDebug>


KeyPad::KeyPad(QWidget *parent) : QWidget(parent)
{
    generateKeys(KeyType::Alphabet);
}

KeyPad::KeyPad(KeyPad::KeyType keyType, QWidget *parent) : QWidget(parent)
{
    generateKeys(keyType);
}

void KeyPad::generateKeys(KeyPad::KeyType keyType)
{
    std::vector<QString> rows;
    if (keyType == KeyType::Alphabet) {
        rows = {"1234567890()-⌫", "QWERTYUIOP[]{}", "ASDFGHJKL.,:;'\"@", "ZXCVBNM<>/ "};
    }
    else if (keyType == KeyType::Numpad) {
        rows = {"789", "456", "123", "0"};
    }

    QVBoxLayout *mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    foreach (QString row, rows) {
        QHBoxLayout *currentLayout = new QHBoxLayout();
        currentLayout->addStretch();
        mainLayout->addLayout(currentLayout);
        for (int i = 0; i < row.length(); ++i) {
            VKey *key = new VKey(row.at(i), this);
            currentLayout->addWidget(key);
            connect(key, SIGNAL(clicked()), this, SLOT(keyPress()));
        }
        currentLayout->addStretch();
    }
}

void KeyPad::keyPress()
{
    VKey *key = qobject_cast<VKey *>(sender());
    //QString val = key->text();
    if (key->text() == static_cast<QString>("⌫"))
    {
        qApp->postEvent(QApplication::focusWidget(), new QKeyEvent (QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier));
        qApp->postEvent(QApplication::focusWidget(), new QKeyEvent (QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier));
    }
    else
    {
        qApp->postEvent(QApplication::focusWidget(), new QKeyEvent (QEvent::KeyPress, Qt::Key_unknown, Qt::NoModifier, key->text()));
        qApp->postEvent(QApplication::focusWidget(), new QKeyEvent (QEvent::KeyRelease, Qt::Key_unknown, Qt::NoModifier, key->text()));
    }
    qDebug() << "KeyPad::keyPress " << key->text();
}
