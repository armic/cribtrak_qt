#ifndef CUSTOMERSETTINGS_H
#define CUSTOMERSETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QSettings>

#include "keypad.h"


namespace Ui {
class CustomerSettings;
}

class CustomerSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerSettings(QWidget *parent = 0);
    ~CustomerSettings();

    void setup();
    void loadSettings();
    void saveSettings();



private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

//    void on_edtTailDescription_textChanged();

    void on_btnLoadLogo_clicked();

private:
    Ui::CustomerSettings *ui;
    KeyPad* keybrd;
};

#endif // CUSTOMERSETTINGS_H
