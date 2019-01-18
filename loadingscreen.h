#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include <QDialog>

namespace Ui {
class loadingscreen;
}

class loadingscreen : public QDialog
{
    Q_OBJECT

public:
    explicit loadingscreen(QWidget *parent = 0);
    ~loadingscreen();

private:
    Ui::loadingscreen *ui;
};

#endif // LOADINGSCREEN_H
