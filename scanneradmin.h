#ifndef SCANNERADMIN_H
#define SCANNERADMIN_H

#include <QDialog>

namespace Ui {
class ScannerAdmin;
}

class ScannerAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit ScannerAdmin(QWidget *parent = 0);
    ~ScannerAdmin();

private:
    Ui::ScannerAdmin *ui;
};

#endif // SCANNERADMIN_H
