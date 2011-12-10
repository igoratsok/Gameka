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



#include "newmapwindowobjectwidget.h"
#include "ui_newmapwindowobjectwidget.h"

NewMapWindowObjectWidget::NewMapWindowObjectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewMapWindowObjectWidget)
{
    ui->setupUi(this);
}

NewMapWindowObjectWidget::~NewMapWindowObjectWidget()
{
    delete ui;
}

void NewMapWindowObjectWidget::populaListaObjetosDisponiveis() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<GameObject*> *objectList;

    objectList = gameData->objectList;

    ui->listObjectsDispon->clear();

    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject *gameObject = *it;

        if(std::find(map->gameObjects->begin(), map->gameObjects->end(), gameObject) == map->gameObjects->end()) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(QString(gameObject->name.c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject));
            newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));
            ui->listObjectsDispon->addItem(newItem);
        }
    }
}

void NewMapWindowObjectWidget::populaListObjetosEscolhidos() {
    std::vector<GameObject*> *objectList;

    objectList = map->gameObjects;

    ui->listObjectsEscolhidas->clear();

    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject* gameObject = *it;

        QListWidgetItem *newItem = new QListWidgetItem();
        newItem->setText(QString(gameObject->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject));
        newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));
        ui->listObjectsEscolhidas->addItem(newItem);
    }
}

void NewMapWindowObjectWidget::on_pushButton_clicked()
{
    QListWidgetItem* currentItem = ui->listObjectsDispon->currentItem();

    if(currentItem != NULL) {
        GameObject* gameObject;
        gameObject = (GameObject*) currentItem->data(Qt::UserRole).value<void*>();
        map->gameObjects->push_back(gameObject);

        populaListaObjetosDisponiveis();
        populaListObjetosEscolhidos();
    }
}
