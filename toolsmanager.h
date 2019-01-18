#ifndef TOOLSMANAGER_H
#define TOOLSMANAGER_H

#include <QDialog>

#include "datamanager.h"

namespace Ui {
class ToolsManager;
}

class ToolsManager : public QDialog
{
    Q_OBJECT

public:
    explicit ToolsManager(QWidget *parent = 0);
    ~ToolsManager();

    void onDrawerToolChanged(int dnum, int toolnum, int sts);
    void toolSelectionChanged(int drwnum, int toolnum);
    void onDrawerChanged(int drwnum, bool opened);


private:
    ToolData* currentToolData;
    Tool* currentToolDetail;
    bool currentToolPresent;
    QString currentUserId;
    QString currentUser;

    void newToolSelection(int drwnum, int toolnum);
    void updateToolDetailDisplay(int drwnum, int toolnum);
    void updateChanges();
    bool toolChanged();
    void clearToolDetailDisplay();
//    void updateToolDisplay(int drwnum, int toolnum);
    void toolReturned();
    void toolRemoved();

private slots:
    void reqCalibrationChange(int state);
    void removedChange(int state);
    void transferredChange(int state);



private:
    Ui::ToolsManager *ui;
};

#endif // TOOLSMANAGER_H
