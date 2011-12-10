/***********************************************

Gameka: A game development tool for non-programmers
Copyright (C) 2011 Igor Augusto de Faria Costa

This software is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

************************************************/



#include "newteleportareadialog.h"
#include "ui_newteleportareadialog.h"

NewTeleportAreaDialog::NewTeleportAreaDialog(MapEditorController *mapEditorController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTeleportAreaDialog),
    mapEditorController(mapEditorController)
{
    ui->setupUi(this);
    ui->checkBoxMostraAnimVit->setVisible(false);
    teleportArea = new TeleportArea();
    populaComboMapa();
}

NewTeleportAreaDialog::NewTeleportAreaDialog(MapEditorController *mapEditorController, TeleportArea *teleportArea, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::NewTeleportAreaDialog),
        teleportArea(teleportArea),
        mapEditorController(mapEditorController)
{
    ui->setupUi(this);
    populaComboMapa();

    int i;
    for(i = 0; i < ui->comboMap->count(); i++) {
        int id = ui->comboMap->itemData(i).toInt();
        if(id == teleportArea->mapId) {
            ui->comboMap->setCurrentIndex(i);
            break;
        }
    }

    ui->checkBoxMostraAnimVit->setChecked(teleportArea->showVictoryAnimation);

    if(teleportArea->mapPositionDetermined) {
        std::stringstream ss1, ss2;
        ss1 << teleportArea->x;
        ss2 << teleportArea->y;


        ui->lineEditPosX->setText(QString(ss1.str().c_str()));
        ui->lineEditPosY->setText(QString(ss2.str().c_str()));
    }
}

NewTeleportAreaDialog::~NewTeleportAreaDialog()
{
    delete ui;
}

void NewTeleportAreaDialog::populaComboMapa() {
    GameData *gameData = GameData::getInstance();

    ui->comboMap->clear();
    populaComboMapaPercorreArvore(mapEditorController->getMaplist(), std::string(""));
}

void NewTeleportAreaDialog::populaComboMapaPercorreArvore(std::vector<Map*> *mapList, std::string prefix) {
    for(std::vector<Map*>::iterator it = mapList->begin(); it != mapList->end(); ++it) {
        Map* map = *it;
        if(map->isFolder()) {
            populaComboMapaPercorreArvore(map->filhos, std::string(prefix.c_str()).append(map->mapName).append(" > "));
        } else {
            ui->comboMap->addItem(QString(prefix.c_str()).append(map->mapName.c_str()), QVariant(map->id));
            std::cout << "map-key: " << map->id << std::endl;
        }
    }
}

TeleportArea* NewTeleportAreaDialog::exec() {
    if(QDialog::exec()) {
        teleportArea->id = 0;
        teleportArea->mapId = ui->comboMap->itemData(ui->comboMap->currentIndex()).toInt();
        if(ui->lineEditPosX->text().isEmpty()) {
            teleportArea->mapPosX = 0;
        } else {
            teleportArea->mapPosX = ui->lineEditPosX->text().toInt();
        }

        if(ui->lineEditPosY->text().isEmpty()) {
            teleportArea->mapPosY = 0;
        } else {
            teleportArea->mapPosY = ui->lineEditPosY->text().toInt();
        }

        if(ui->lineEditPosX->text().isEmpty() &&
           ui->lineEditPosY->text().isEmpty()) {
            teleportArea->mapPositionDetermined = false;
        } else {
            teleportArea->mapPositionDetermined = true;
        }

        teleportArea->showVictoryAnimation = ui->checkBoxMostraAnimVit->isChecked();

        return teleportArea;
    }

    return NULL;






}
