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



#include "configsobjectswidget.h"
#include "ui_configsobjectswidget.h"

ConfigsObjectsWidget::ConfigsObjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsObjectsWidget)
{
    ui->setupUi(this);

    specificWidget = NULL;

    specificWidget = new ConfigsObjGenericWidget(this);
    ui->scrollArea->setWidget(specificWidget);

    configsTabWidget = NULL;

    populaListaPersonagem();
}

ConfigsObjectsWidget::~ConfigsObjectsWidget()
{
    delete ui;
}

void ConfigsObjectsWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ConfigsObjectsWidget::on_pushButton_clicked()
{
    configsNewObjectWindow = new ConfigsNewObjectWindow(optionsController, this);
    configsNewObjectWindow->setModal(true);
    configsNewObjectWindow->setWindowTitle(QString("Novo objeto"));
    configsNewObjectWindow->show();
}

void ConfigsObjectsWidget::on_listPersonagem_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if(current != 0x0) {
        GameObject* currentObject;
        currentObject = (GameObject*) current->data(Qt::UserRole).value<void*>();

        if(currentObject != NULL) {
            specificWidget->removeAllWidgets();
            specificWidget->addWidgets(optionsController, currentObject, current);
        }



    }


}


void ConfigsObjectsWidget::setOptionsController(OptionsController *optionsController) {
    this->optionsController = optionsController;
}

void ConfigsObjectsWidget::populaListaPersonagem() {
    GameData *gameData;
    gameData = GameData::getInstance();

    std::vector<GameObject*>* objectList;

    objectList = optionsController->getObjectList();

    ui->listPersonagem->clear();

    QListWidgetItem *specialItem;

    specialItem = new QListWidgetItem();
    specialItem->setText(QString::fromUtf8("---Personagens---"));
    specialItem->setTextAlignment(Qt::AlignHCenter);
    specialItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->listPersonagem->addItem(specialItem);

    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject *gameObject;
        gameObject = *it;

        if(gameObject->type != GameObject::ITEM &&
                gameObject->type != GameObject::NPC &&
                gameObject->type != GameObject::INIMIGO &&
                gameObject->type != GameObject::STATIC_OBJECT) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(QString(gameObject->name.c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject));
            newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

            ui->listPersonagem->addItem(newItem);
        }


    }

    specialItem = new QListWidgetItem();
    specialItem->setText(QString::fromUtf8("---Itens---"));
    specialItem->setTextAlignment(Qt::AlignHCenter);
    specialItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->listPersonagem->addItem(specialItem);

    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject *gameObject;
        gameObject = *it;

        if(gameObject->type == GameObject::ITEM) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(QString(gameObject->name.c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject));
            newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

            ui->listPersonagem->addItem(newItem);
        }


    }

    specialItem = new QListWidgetItem();
    specialItem->setText(QString::fromUtf8("---NPC---"));
    specialItem->setTextAlignment(Qt::AlignHCenter);
    specialItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->listPersonagem->addItem(specialItem);

    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject *gameObject;
        gameObject = *it;

        if(gameObject->type == GameObject::NPC || gameObject->type == GameObject::INIMIGO) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(QString(gameObject->name.c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject));
            newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

            ui->listPersonagem->addItem(newItem);
        }


    }

    specialItem = new QListWidgetItem();
    specialItem->setText(QString::fromUtf8("---Estáticos---"));
    specialItem->setTextAlignment(Qt::AlignHCenter);
    specialItem->setData(Qt::UserRole, QVariant::fromValue((void*) NULL));

    ui->listPersonagem->addItem(specialItem);

    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject *gameObject;
        gameObject = *it;

        if(gameObject->type == GameObject::STATIC_OBJECT) {
            QListWidgetItem *newItem = new QListWidgetItem();
            newItem->setText(QString(gameObject->name.c_str()));
            newItem->setData(Qt::UserRole, QVariant::fromValue((void*) gameObject));
            newItem->setIcon(QIcon(QPixmap::fromImage(gameObject->getIconImage())));

            ui->listPersonagem->addItem(newItem);
        }


    }

}

void ConfigsObjectsWidget::selectObject(GameObject *gameObject) {
    int nro_elementos = ui->listPersonagem->count();

    for(int i = 0; i < nro_elementos; i++) {
        QListWidgetItem *item = ui->listPersonagem->item(i);
        GameObject *gameObjectItem = (GameObject*) item->data(Qt::UserRole).value<void*>();
        if(gameObjectItem != NULL) {
            if(gameObjectItem->id == gameObject->id) {
                ui->listPersonagem->setCurrentItem(item);
                on_listPersonagem_currentItemChanged(item, NULL);
                break;
            }
        }

    }
}

void ConfigsObjectsWidget::setConfigsTabWidget(ConfigsTabWidget *configsTabWidget) {
    this->configsTabWidget = configsTabWidget;
    this->specificWidget->setConfigsTabWidget(configsTabWidget);
}

void ConfigsObjectsWidget::on_pushButton_pressed()
{

}

void ConfigsObjectsWidget::on_removeObject_pressed()
{
    GameObject *currentObject = NULL;
    GameData *gameData = GameData::getInstance();
    if(ui->listPersonagem->currentItem() != NULL) {
        currentObject = (GameObject*) ui->listPersonagem->currentItem()->data(Qt::UserRole).value<void*>();
        if(currentObject != NULL) {
            if(MessageBoxes::showConfirmBox(std::string("Deseja realmente remover o objeto?"))) {
                if(!gameData->verifyObjectUsedById(currentObject->id)) {
                    this->optionsController->removeObject(currentObject);
                    ui->scrollArea->setWidget(NULL);
                    specificWidget->removeAllWidgets();
                } else {
                    MessageBoxes::showMessageBox(QString::fromUtf8("Não é possível remover o objeto, pois ele é utilizado em outro lugar."));
                }

            }


        }

    }

    populaListaPersonagem();
}
