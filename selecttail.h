#ifndef SELECTTAIL_H
#define SELECTTAIL_H

//#include <QWidget>
#include <QDialog>
#include <QSqlQueryModel>
#include <QButtonGroup>
#include <QGridLayout>

#include "keypad.h"
#include "progressbar.h"



namespace Ui {
class SelectTail;
}

//class SelectTail : public QWidget
class SelectTail : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTail(QWidget *parent = 0);
    ~SelectTail();

    void setWidget();
    void refreshWidget();


public slots:
    void handleConfirmButton();
    void handleAdminButton();
    void handleCancelButton();


private:
    Ui::SelectTail *ui;
    void setupWidget();
    int setSpeedDialButton(QSqlQueryModel* model, QPushButton* button, QButtonGroup *group, int rows, int cnt);

    QButtonGroup *tailButtonGroup;
    bool useWorkOrder;
    bool useBatch;
    QString currentWorkOrder;
    QString currentBatch;
    KeyPad *keyBlock;
    QGridLayout* kbdLayout;
    QSqlQueryModel *currentTailModel;
    void displayErrorMessage(QString str);
    void clearErrorMessage();

    ProgressBar* progressBar;

    void handleCurrentTextChanged(const QString & text);
    void handleEditTextChanged(const QString & text);
    void handleHighlighted(const QString & text);
    void handleActivated(const QString & text);
    void handleButtonGroupClicked(int id);

    enum {noneSelected, comboSelected, speedDialSelected};
    int tailEntrySelected;

private slots:
    void handleProgressBarEnd();




};

#endif // SELECTTAIL_H
