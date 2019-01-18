#ifndef OPENALARMMESSAGE_H
#define OPENALARMMESSAGE_H

#include <QDialog>
#include <QSound>


namespace Ui {
class openalarmmessage;
}

class openalarmmessage : public QDialog
{
    Q_OBJECT

public:
    explicit openalarmmessage(QWidget *parent = 0);
    ~openalarmmessage();

private:
    Ui::openalarmmessage *ui;
};

#endif // OPENALARMMESSAGE_H
