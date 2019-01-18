#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QObject>
#include <QtWidgets>
#include <QMainWindow>
#include <QMessageBox>

#include "guestscreen.h"
#include "userscreen.h"
#include "adminscreen.h"
#include "toolsmanager.h"



class MainView : public QWidget
//class MainView : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);

//    void addToolStatusButton();
    void userButton();
    void processSwitchClicked();
    void setGuestScreen();
    void setUserScreen();
    void setAdminScreen();
//    void setUserDrawerOpenedView(int dnum, DrawerList* list);
//    void setUserDrawerClosedView(int dnum);
    void backToGuestMode();
    void updateToolStatusView(int dnum, int toolnum, bool out, DrawerList* list);
//    void updateToolDetailView(int drwnum, int toolnum, bool out);
//    void buildUserDrawerScenes();

    // tools manager
    void setToolServiceScreen();
    ToolsManager* toolsManager;


    QWidget* window;
    QVBoxLayout* mainWindowLayout;
    ToolData* currentToolDetail;

protected:

//    void keyPressEvent(QKeyEvent* event);



public:
    UserScreen* userScreenInstance;


private:
    GuestScreen* guestScreenInstance;
    QStackedWidget* stackedWidget;
    adminscreen* adminScreenInstance;

signals:
    void changeToolService(ToolData* tool);

private  slots:
    void toolServiceableBtnPressed();

};


//
//  message box class with timeout
//

class MyMessageBox : public QMessageBox
{

    Q_OBJECT

public:
    void setTimeoutValue(int time);
    virtual int exec();

private:
    int timeout;

};




#endif // MAINVIEW_H
