#ifndef UPDATEMANAGERWINDOW_H
#define UPDATEMANAGERWINDOW_H

#include <QDialog>

#include "updatemanagercontroller.h"

class UpdateManagerController;

namespace Ui {
    class UpdateManagerWindow;
}

class UpdateManagerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateManagerWindow(UpdateManagerController *updateManagerController, QWidget *parent = 0);
    ~UpdateManagerWindow();

private:
    Ui::UpdateManagerWindow *ui;
    UpdateManagerController *updateManagerController;
};

#endif // UPDATEMANAGERWINDOW_H
