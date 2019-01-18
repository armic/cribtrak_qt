#ifndef ACCESSDENIED_H
#define ACCESSDENIED_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class accessdenied;
}

class accessdenied : public QDialog
{
    Q_OBJECT

public:
    explicit accessdenied(QWidget *parent = 0);
    ~accessdenied();

private slots:
    void closeMessage();

private:
    Ui::accessdenied *ui;
    QTimer *timer;

};

#endif // ACCESSDENIED_H
