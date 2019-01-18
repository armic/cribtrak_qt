#ifndef TOOLDETAIL_H
#define TOOLDETAIL_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>

#include "keypad.h"

namespace Ui {
class toolDetail;
}

class toolDetail : public QDialog
{
    Q_OBJECT

public:
    explicit toolDetail(QWidget *parent = 0);
    ~toolDetail();
    void setStockCode(const QString &stockCode);

private slots:
    void on_btnBox_accepted();

    void on_btnBox_rejected();

    void on_edtStockCode_textChanged(const QString &arg1);

    void on_edtDescription_textChanged(const QString &arg1);

    void on_cbIsKit_toggled(bool checked);

private:
    Ui::toolDetail *ui;
    QString m_stockCode;
    bool isEdit;
    KeyPad* keybrd;
};

#endif // TOOLDETAIL_H
