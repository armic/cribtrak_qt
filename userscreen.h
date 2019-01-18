#ifndef USERSCREEN_H
#define USERSCREEN_H

#include <QWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QSoundEffect>

#include "datamanager.h"
#include "progressbar.h"
//#include "cabinetmanager.h"
#include "openalarmmessage.h"

//#define TRAK_TESTKEYS

class DrawerScene;

namespace Ui {
class UserScreen;
}

class UserScreen : public QWidget
{
    Q_OBJECT

public:
    explicit UserScreen(QWidget *parent = 0);
    ~UserScreen();

    bool event(QEvent *event);
    void setupScreen();
    void setScreen();
//    void setDrawerClosedView();
//    void setDrawerOpenView(int dnum, DrawerList* list);
//    void updateToolDisplay(int dnum, DrawerList* list);
//    void updateToolDetail(QString stockcode, QString desc, int toolnum, ToolStates status, QString user);
//    void clearToolDetail();

//    void userBalanceDisplay();
//    void updateUserBalanceDisplay();
    QGridLayout* userBalanceLayout;
//    void clearUserBalanceDisplay();

//    //DrawerScene *scene;
//    QGraphicsScene* currentScene;
//    // scene graphics
//    QGraphicsScene* sceneArray[MaxDrawers];
//    void buildDrawerScenes();
//    QGraphicsScene* buildDrawerScene(int drwnum, DrawerList* drawer);
//    void updateDrawerScene(int drwnum, DrawerList* drawer);
//    void clearCurrentSelection();

    void cancelProgressBarTimer();
    void startProgressBarTimer();

    // NOTE: Testing function.
    void toolIssued(QString description);
    void toolReturned(QString description, bool consumable = false);
    void showError(QString errorString);
    void showConsumableScreen(const QString description, const int numOut, const int numAvailable, const bool returnable);
    void showKitScreen(int kitCount);

    void setUserNumToolsOut(int num);


private slots:
    void handleProgressBarEnd();
//    void deviceConnected();
//    void deviceDisconnected();
//    void toolSelectionChanged();
//    void resizeEvent(QResizeEvent *event);
    void dateTime();


    void on_logoutButton_clicked();

    void on_dismissErrorButton_clicked();

    void on_consumableIssuingButton_toggled(bool checked);

    void on_consumableReturningButton_toggled(bool checked);

    void on_stackedWidget_currentChanged(int arg1);

    void on_issueConsumablesButton_clicked();

    void on_kitCancelButton_clicked();

    void on_kitOKButton_clicked();

    void on_consumableCountSpinBox_valueChanged(int arg1);

    void on_consumableUsedButton_toggled(bool checked);

    void on_unserviceableButton_clicked();

    void on_consumableUnusedButton_toggled(bool checked);

    void onReturnToReadyScan();

private:
    Ui::UserScreen *ui;

//    UserDrawerClosed* userDrawerClosedInst;
//    UserDrawerOpen* userDrawerOpenInst;
    QVBoxLayout* mainWindowLayout;
    QStackedWidget* stackedWidget;

//    void setDrawerStatusIndicators();
//    void setDrawerStatusIndicator(int drwnum, int drwsts);

    ProgressBar* progressBar;
//    void drawerOpenAlarmOn();
//    void drawerOpenAlarmOff();
//    QSoundEffect* drawerOpenAlarm;
//    openalarmmessage *drawerOpenMsg;

//    void toolDetailDisplay();
    QGridLayout* toolDetailLayout;
    QLabel* value0;
    QLabel* value1;
    QLabel* value2;
    QLabel* value3;
    QPushButton* serviceableBtn;

    QTimer *timer;
    QTimer *issuedTimer;

    void flipHorizontal(QGraphicsSvgItem *toolitem);
    void flipVertical(QGraphicsSvgItem *toolitem);

    // Needed for spinbox when switching between issue and return in consumable page.
    int maxConsumableReturn;    // Number of consumables of selected type issued to current user.
    int maxConsumableIssue;     // Number of consumables of selected type available.


public:
    // colours of tool states
    //static const QColor toolInColour = QColor(40, 200, 40);
    static const QColor toolInColour;
    static const QColor toolOutColour;
    static const QColor toolOtherUserColour;
    static const QColor toolMissingColour;
    static const QColor toolUnserviceableColour;
    static const QColor toolTransferredColour;

    QColor getToolStatusColour(ToolStates state);


    enum {STOCKCODE, DESC, TOOLNUM, STATE, DRAWERNUM};

public:
    void createWrongUserReturnMsg();
    void displayWrongUserRetrunMsg(int dnum, int toolnum, QString toolname, int action);
    void clearWrongUserRetrunMsg();
    QLabel* illegalReturnMsg;

    // tool service changes in user view
public:
//    void toolServiceChange();
//    void updateToolServiceChange(bool disable, int currentService);
//    void disableToolServiceChange();
public slots:
    void toolServiceBtnClicked();
signals:
    void toolServiceableBtn();
    void consumableIssueSelected(int num);
    void consumableReturnSelected(int num, bool used);

    void kitIssueCancelled();
    void kitIssueOK();

    void toolMarkedUnserviceable();


public:
//    QPoint toolManagerAnchor();

};





//#include <QGraphicsScene>
//#include <QtSvg>

//#include <memory>


//class DrawerScene : public QGraphicsScene
//{
//public:
//    DrawerScene();
//    DrawerScene(DrawerList *drawer);

//    void setDrawer(DrawerList *drawer);

//private:
//    std::unique_ptr<QSvgRenderer> renderer; // Each scene has its own renderer. Bad.
//};


#endif // USERSCREEN_H
