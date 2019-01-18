#ifndef DISCONNECTED_H
#define DISCONNECTED_H

#include <QWidget>

namespace Ui {
class disconnected;
}

class disconnected : public QWidget
{
    Q_OBJECT

public:
    explicit disconnected(QWidget *parent = 0);
    ~disconnected();

private:
    Ui::disconnected *ui;
};

#endif // DISCONNECTED_H
