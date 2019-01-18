#ifndef TOOLOUTFORM_H
#define TOOLOUTFORM_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTimer>

namespace Ui {
class toolOutForm;
}

class toolOutForm : public QDialog
{
    Q_OBJECT

public:
    explicit toolOutForm(QWidget *parent = 0, bool rts = false);
    ~toolOutForm();
    bool rtsOnly;

private slots:
    void on_brnClose_clicked();

private:
    Ui::toolOutForm *ui;
     QTimer *timer;
};

#endif // TOOLOUTFORM_H

