#include "updatemanagercontroller.h"

UpdateManagerController::UpdateManagerController()
{
}

void UpdateManagerController::openUpdateManagerWindow() {
    updateManagerWindow = new UpdateManagerWindow(this);
    updateManagerWindow->show();
}

void UpdateManagerController::loadFilePairLists() {

}
