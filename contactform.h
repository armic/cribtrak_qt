#ifndef CONTACTFORM_H
#define CONTACTFORM_H

#include <QDialog>

#include "keypad.h"

namespace Ui {
class contactform;
}

class contactform : public QDialog
{
    Q_OBJECT

public:
    explicit contactform(QWidget *parent = 0);
    ~contactform();

private slots:
    void on_btnCancel_clicked();

    void on_btnSend_clicked();

private:
    Ui::contactform *ui;
    KeyPad* keybrd;
};

#endif // CONTACTFORM_H
