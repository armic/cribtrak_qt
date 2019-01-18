#ifndef TOOLADMIN_H
#define TOOLADMIN_H

#include <QDialog>
#include <QtSql>

#include "keypad.h"

#include "multicolumnsortfilterproxymodel.h"

namespace Ui {
class tooladmin;
}

class tooladmin : public QDialog
{
    Q_OBJECT

public:
    explicit tooladmin(QWidget *parent = 0);
    ~tooladmin();
    void populateTooldataItem();
    void populateCribTooldataItem();

private slots:
    void on_btnNew_clicked();

    void on_btnEdit_clicked();

    void on_btnDelete_clicked();

    void on_btnImport_clicked();

    void on_tabList_currentChanged(int index);

    void onBarcodeScanned(QString barcode);

    void on_filterEdit_textChanged(const QString &arg1);

    void on_btnexport_clicked();

    void on_closeButton_clicked();

private:
    Ui::tooladmin *ui;
    QSqlQueryModel* toollistmodel;
    QSqlQueryModel* cribtoollistmodel;

    // Filtering
    MultiColumnSortFilterProxyModel *allToolsProxyModel;
    MultiColumnSortFilterProxyModel *cribToolsProxyModel;
    QSortFilterProxyModel *cribToolsConsumableProxyModel;

    KeyPad *keyPad;
    //QString csvRemoveQuotes(QString str);
    //QStringList parseCsvLine(QString line);
};

#endif // TOOLADMIN_H
