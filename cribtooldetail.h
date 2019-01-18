#ifndef CRIBTOOLDETAIL_H
#define CRIBTOOLDETAIL_H

#include <QDialog>

#include "keypad.h"

namespace Ui {
class CribToolDetail;
}

class CribToolDetail : public QDialog
{
    Q_OBJECT

public:
    explicit CribToolDetail(QWidget *parent = 0);
    ~CribToolDetail();

    void setNewMode();
    void setEditMode(int toolId);

    void setup();

private slots:
    void on_barcodeLineEdit_textChanged(const QString &arg1);

    void on_toolComboBox_currentIndexChanged(int index);

    void on_kitCheckBox_toggled(bool checked);

    void on_consumableCheckBox_toggled(bool checked);

    void on_requiresCalibrationCheckBox_toggled(bool checked);

    void on_cancelButton_clicked();

    void on_saveButton_clicked();

    void onBarcodeScanned(QString barcode);

    void on_newLocationButton_clicked();

private:
    Ui::CribToolDetail *ui;
    KeyPad* keybrd;
    bool editMode;
    int toolId;
    int getToolIndex(int toolId);
    QString currentBarcode;
};

#endif // CRIBTOOLDETAIL_H
