#ifndef TOOLFINDER_H
#define TOOLFINDER_H

#include <QWidget>
//#include <QSortFilterProxyModel>
#include "multicolumnsortfilterproxymodel.h"
#include "keypad.h"

namespace Ui {
class ToolFinder;
}

class ToolFinder : public QWidget
{
    Q_OBJECT

public:
    explicit ToolFinder(QWidget *parent = 0);
    ~ToolFinder();

private slots:
    void on_filterLineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::ToolFinder *ui;
    MultiColumnSortFilterProxyModel *filterProxy;

    KeyPad *keypad;
};

#endif // TOOLFINDER_H
