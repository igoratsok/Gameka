#include "updatemanagercontroller.h"

UpdateManagerController::UpdateManagerController()
{
}

void UpdateManagerController::openUpdateManagerWindow() {
    updateManagerWindow = new UpdateManagerWindow(&manager, this);
    updateManagerWindow->show();

    QTimer::singleShot(0, updateManagerWindow, SLOT(downloadNextVersionXml()));

}



void UpdateManagerController::loadFilePairLists() {

}
