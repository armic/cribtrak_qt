#ifndef CABTOOLDETAIL_H
#define CABTOOLDETAIL_H

#include <QDialog>
#include <QSqlQuery>

#include "keypad.h"

namespace Ui {
class cabtooldetail;
}

class cabtooldetail : public QDialog
{
    Q_OBJECT

public:
    explicit cabtooldetail(QWidget *parent = 0);
    ~cabtooldetail();
    void loadDialog(const int DrawerNum, int ToolNum);

private slots:
    void on_btnBox_accepted();

    void on_btnBox_rejected();

    void on_chkCalibration_toggled(bool checked);

private:
    Ui::cabtooldetail *ui;
    KeyPad* keybrd;
};

#endif // CABTOOLDETAIL_H
