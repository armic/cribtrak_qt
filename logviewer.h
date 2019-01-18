#ifndef LOGVIEWER_H
#define LOGVIEWER_H

#include <QDialog>
#include <QDate>

namespace Ui {
class logViewer;
}

class logViewer : public QDialog
{
    Q_OBJECT

public:
    explicit logViewer(QWidget *parent = 0);
    ~logViewer();

private slots:
    void on_btnClose_clicked();

private:
    Ui::logViewer *ui;
};

#endif // LOGVIEWER_H
