#ifndef TAILDETAIL_H
#define TAILDETAIL_H

#include <QDialog>
#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QMessageBox>

#include "keypad.h"

namespace Ui {
class taildetail;
}

class taildetail : public QDialog
{
    Q_OBJECT

public:
    explicit taildetail(QWidget *parent = 0);
    ~taildetail();
    void setEditMode(const QString tailNumber);
    QString m_tailNumber;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_edtTailNumber_textChanged(const QString &arg1);

    void on_edtDescription_textChanged(const QString &arg1);

private:
    Ui::taildetail *ui;
    KeyPad* keybrd;

    bool editMode;

};

#endif // TAILDETAIL_H
