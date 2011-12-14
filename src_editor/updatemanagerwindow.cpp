#include "updatemanagerwindow.h"
#include "ui_updatemanagerwindow.h"

UpdateManagerWindow::UpdateManagerWindow(UpdateManagerController *updateManagerController, QWidget *parent) :
    updateManagerController(updateManagerController), QDialog(parent),
    ui(new Ui::UpdateManagerWindow)
{
    ui->setupUi(this);
}

UpdateManagerWindow::~UpdateManagerWindow()
{
    delete ui;
}
