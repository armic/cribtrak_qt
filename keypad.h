#ifndef KEYPAD_H
#define KEYPAD_H

#include <QApplication>
#include <QWidget>

class KeyPad : public QWidget
{
    Q_OBJECT
public:
    enum class KeyType{Alphabet, Numpad};

    explicit KeyPad(QWidget *parent = 0);
    explicit KeyPad(KeyType keyType, QWidget *parent = 0);

    void generateKeys(KeyType keyType);

signals:

public slots:
    void keyPress();
};

#endif // KEYPAD_H
