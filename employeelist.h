#ifndef EMPLOYEELIST_H
#define EMPLOYEELIST_H

#include <QDialog>


namespace Ui {
class employeelist;
}

class employeelist : public QDialog
{
    Q_OBJECT

public:
    explicit employeelist(QWidget *parent = 0);
    ~employeelist();
    bool grantuser();
    void loadEmployeeUserList();
    bool isEdit;


public slots:
    void on_selectEmployee();
    void on_selectUser();


private slots:
//    void on_tabWidget_currentChanged(int index);

//    void on_toolButton_clicked();

//    void on_toolButton_2_clicked();

//    void on_toolButton_4_clicked();
    void on_buttonBox_rejected();

    void on_btnGrantRevoke_clicked();

    void on_tabList_currentChanged(int index);


    void on_btnEdit_clicked();





    void on_btnNew_clicked();

    void on_buttonBox_accepted();

private:
    Ui::employeelist *ui;

};

#endif // EMPLOYEELIST_H
