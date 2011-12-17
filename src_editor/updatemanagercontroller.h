#ifndef UPDATEMANAGERCONTROLLER_H
#define UPDATEMANAGERCONTROLLER_H

#include <QObject>
#include <QList>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QTimer>

#include "gamedata.h"
#include "updatefilepair.h"
#include "updatemanagerwindow.h"

class GameData;
class UpdateFilePair;
class UpdateManagerWindow;

class UpdateManagerController : public QObject
{
public:
    UpdateManagerController();


    void openUpdateManagerWindow();

    void loadFilePairLists();

    QList<UpdateFilePair> filePairList;
    UpdateManagerWindow *updateManagerWindow;
    QNetworkAccessManager manager;





};

#endif // UPDATEMANAGERCONTROLLER_H
