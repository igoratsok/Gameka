#include "updatemanagerwindow.h"
#include "ui_updatemanagerwindow.h"

UpdateManagerWindow::UpdateManagerWindow(QNetworkAccessManager *manager, UpdateManagerController *updateManagerController, QWidget *parent) :
    updateManagerController(updateManagerController), QDialog(parent),
    ui(new Ui::UpdateManagerWindow)
{
    ui->setupUi(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished()));
    this->manager = manager;
}

UpdateManagerWindow::~UpdateManagerWindow()
{
    delete ui;
}

void UpdateManagerWindow::downloadFinished() {
    if(reply->error() == QNetworkReply::NoError) {
        std::cout << "OK!" << " " << reply->isReadable() << " " << std::endl;
        QFile file("update.xml");
        file.open(QIODevice::WriteOnly);

        file.write(reply->readAll());
        file.close();
    } else {
        std::cout << "BAD BAD!" << std::endl;
    }
}

void UpdateManagerWindow::downloadNextVersionXml() {
    QString gamekaUpdateURL = "http://www.gameka.com.br/updates/";

    gamekaUpdateURL.append(QString("update").append(QString::number(GameData::SOFTWARE_CURRENT_VERSION+1).append(".xml")));
    QUrl url = QUrl(gamekaUpdateURL);
    QNetworkRequest networkRequest(url);
    reply = manager->get(networkRequest);



}
