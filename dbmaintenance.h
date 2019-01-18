#ifndef DBMAINTENANCE_H
#define DBMAINTENANCE_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class dbMaintenance;
}

class dbMaintenance : public QDialog
{
    Q_OBJECT

public:
    explicit dbMaintenance(QWidget *parent = 0);
    ~dbMaintenance();

    void setup();


private slots:
    void on_btnOK_clicked();

    void on_btnCheckTables_clicked();

    void on_btnAnalyze_clicked();

    void on_btnOptimized_clicked();

    void on_btnrepair_clicked();

private:
    Ui::dbMaintenance *ui;
};

#endif // DBMAINTENANCE_H
