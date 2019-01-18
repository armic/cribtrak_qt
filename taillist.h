#ifndef TAILLIST_H
#define TAILLIST_H

#include <QDialog>
#include <QtSql>


namespace Ui {
class taillist;
}

class taillist : public QDialog
{
    Q_OBJECT

public:
    explicit taillist(QWidget *parent = 0);
    ~taillist();
    void populatedataItem();

public slots:
    void editTail();
    void newTail();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::taillist *ui;
    QSqlQueryModel* taillistmodel;
};

#endif // TAILLIST_H
