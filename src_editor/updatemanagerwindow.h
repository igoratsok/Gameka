#ifndef UPDATEMANAGERWINDOW_H
#define UPDATEMANAGERWINDOW_H

#include <QDialog>

#include <QtNetwork/QNetworkAccessManager>

#include "updatemanagercontroller.h"

class UpdateManagerController;

namespace Ui {
    class UpdateManagerWindow;
}

class UpdateManagerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateManagerWindow(QNetworkAccessManager *manager, UpdateManagerController *updateManagerController, QWidget *parent = 0);
    ~UpdateManagerWindow();

private:
    Ui::UpdateManagerWindow *ui;
    UpdateManagerController *updateManagerController;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

private slots:
    void downloadNextVersionXml();
    void downloadFinished();
};

#endif // UPDATEMANAGERWINDOW_H
