#ifndef UPDATEMANAGERCONTROLLER_H
#define UPDATEMANAGERCONTROLLER_H

#include <QList>

#include "updatefilepair.h"
#include "updatemanagerwindow.h"

class UpdateFilePair;
class UpdateManagerWindow;

class UpdateManagerController
{
public:
    UpdateManagerController();


    void openUpdateManagerWindow();
    void loadFilePairLists();

    QList<UpdateFilePair> filePairList;
    UpdateManagerWindow *updateManagerWindow;
};

#endif // UPDATEMANAGERCONTROLLER_H
