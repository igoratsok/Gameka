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



#include "configsobjphysicswidget.h"
#include "ui_configsobjphysicswidget.h"

ConfigsObjPhysicsWidget::ConfigsObjPhysicsWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsObjPhysicsWidget),
    optionsController(optionsController),
    gameObject(gameObject),
    currentListItem(currentListItem)
{
    ui->setupUi(this);

    switch(gameObject->type) {
    case GameObject::EIGHT_MOVEMENT_OBJECT:
        ui->gbPhysicsEightMovement->setEnabled(true);
        ui->gbPhysicsCarMovement->setVisible(false);
        ui->gbPhysicsBouncingBall->setVisible(false);
        ui->gbPhysicsMouseMovement->setVisible(false);
        ui->gbPhysicsPlatformer->setVisible(false);

        ui->comboTipoMovimento->setCurrentIndex(gameObject->tipoMovimento);

        ui->spinVx->setValue(gameObject->vx);
        ui->spinVy->setValue(gameObject->vy);
        ui->spinAx->setValue(gameObject->ax);
        ui->spinAy->setValue(gameObject->ay);
        ui->spinDax->setValue(gameObject->dax);
        ui->spinDay->setValue(gameObject->day);
        break;

    case GameObject::CAR_MOVEMENT_OBJECT:
        ui->gbPhysicsCarMovement->setEnabled(true);
        ui->gbPhysicsEightMovement->setVisible(false);
        ui->gbPhysicsBouncingBall->setVisible(false);
        ui->gbPhysicsMouseMovement->setVisible(false);
        ui->gbPhysicsPlatformer->setVisible(false);

        ui->comboTipoMovimento_2->setCurrentIndex(gameObject->tipoMovimento);
        ui->spinCarV->setValue(gameObject->vx);
        ui->spinCarA->setValue(gameObject->ax);
        ui->spinCarDA->setValue(gameObject->dax);
        ui->spinCarVA->setValue(gameObject->ay);
        break;

        /* Para o fighting movement, são utilizadas
           as mesmas físicas do platformer.         */

    case GameObject::FIGHTING_MOVEMENT_OBJECT:
        ui->gbPhysicsCarMovement->setVisible(false);
        ui->gbPhysicsEightMovement->setVisible(false);
        ui->gbPhysicsBouncingBall->setVisible(false);
        ui->gbPhysicsMouseMovement->setVisible(false);
        ui->gbPhysicsPlatformer->setEnabled(true);

        ui->comboTipoMovimentoPlatformer->setCurrentIndex(gameObject->tipoMovimento);
        ui->spinPlatformerV->setValue(gameObject->vx);
        ui->spinPlatformerA->setValue(gameObject->ax);
        ui->spinPlatformerG->setValue(gameObject->gravidade);
        ui->spinPlatformerIntensidadePulo->setValue(gameObject->intensidadePulo);

        break;

    case GameObject::PLATFORM_MOVEMENT_OBJECT:
        ui->gbPhysicsCarMovement->setVisible(false);
        ui->gbPhysicsEightMovement->setVisible(false);
        ui->gbPhysicsBouncingBall->setVisible(false);
        ui->gbPhysicsMouseMovement->setVisible(false);
        ui->gbPhysicsPlatformer->setEnabled(true);

        ui->comboTipoMovimentoPlatformer->setCurrentIndex(gameObject->tipoMovimento);
        ui->spinPlatformerV->setValue(gameObject->vx);
        ui->spinPlatformerA->setValue(gameObject->ax);
        ui->spinPlatformerG->setValue(gameObject->gravidade);
        ui->spinPlatformerIntensidadePulo->setValue(gameObject->intensidadePulo);

        break;

    case GameObject::MOUSE_MOVEMENT_OBJECT:
        ui->gbPhysicsCarMovement->setVisible(false);
        ui->gbPhysicsEightMovement->setVisible(false);
        ui->gbPhysicsBouncingBall->setVisible(false);
        ui->gbPhysicsMouseMovement->setEnabled(true);
        ui->gbPhysicsPlatformer->setVisible(false);

        ui->comboTipoMovimentoMouseObject->setCurrentIndex(gameObject->tipoMovimento);
        ui->comboFormaMovimentoMouseObject->setCurrentIndex(gameObject->formaMovimentoMouse);
        ui->spinMouseObjectV->setValue(gameObject->vx);
        ui->spinMouseObjectA->setValue(gameObject->ax);
        ui->spinMouseObjectDA->setValue(gameObject->dax);

        break;

    case GameObject::PONG_BALL_OBJECT:
        ui->gbPhysicsCarMovement->setVisible(false);
        ui->gbPhysicsEightMovement->setVisible(false);
        ui->gbPhysicsBouncingBall->setEnabled(true);
        ui->gbPhysicsMouseMovement->setVisible(false);
        ui->gbPhysicsPlatformer->setVisible(false);

        ui->spinBouncingBallVX->setValue(gameObject->vx);
        ui->spinBouncingBallVY->setValue(gameObject->vy);

        break;

    case GameObject::STATIC_OBJECT:
        ui->gbPhysicsCarMovement->setVisible(false);
        ui->gbPhysicsEightMovement->setVisible(false);
        ui->gbPhysicsBouncingBall->setVisible(false);
        ui->gbPhysicsMouseMovement->setVisible(false);
        ui->gbPhysicsPlatformer->setVisible(false);



        break;

    default:

        break;
    }

    /* resolve Collision */
    ui->checkBox->setChecked(gameObject->resolveCollision);


    populaComboObjectsToBounce();
    populaListaObjectsToBounce();

}

void ConfigsObjPhysicsWidget::populaListaObjectsToBounce() {
    ui->listWidgetObjectsToBounce->clear();


    foreach(GameObject *gameObjectIt, gameObject->listObjectsToBounce) {
        QListWidgetItem *newItem = new QListWidgetItem(QIcon(QPixmap::fromImage(gameObjectIt->getIconImage())), QString(gameObjectIt->name.c_str()));
        newItem->setData(Qt::UserRole, QVariant::fromValue((void*) gameObjectIt));
        ui->listWidgetObjectsToBounce->addItem(newItem);
    }
}

ConfigsObjPhysicsWidget::~ConfigsObjPhysicsWidget()
{
    delete ui;
}

void ConfigsObjPhysicsWidget::populaComboObjectsToBounce() {
    ui->comboBoxObjectsToBounce->clear();
    GameData *gameData = GameData::getInstance();

    foreach(GameObject *gameObjectIt, *optionsController->getObjectList()) {
        if(gameObjectIt != gameObject) {
            ui->comboBoxObjectsToBounce->addItem(QIcon(QPixmap::fromImage(gameObjectIt->getIconImage())), QString(gameObjectIt->name.c_str()), QVariant::fromValue((void*) gameObjectIt));
        }
    }


}

void ConfigsObjPhysicsWidget::on_comboTipoMovimento_currentIndexChanged(int index)
{
    gameObject->tipoMovimento = index;
}

void ConfigsObjPhysicsWidget::on_spinVx_valueChanged(double value)
{
    gameObject->vx = value;
}

void ConfigsObjPhysicsWidget::on_spinVy_valueChanged(double value)
{
    gameObject->vy = value;
}

void ConfigsObjPhysicsWidget::on_spinAx_valueChanged(double value)
{
    gameObject->ax = value;
}

void ConfigsObjPhysicsWidget::on_spinAy_valueChanged(double value)
{
    gameObject->ay = value;
}

void ConfigsObjPhysicsWidget::on_spinDax_valueChanged(double value)
{
    gameObject->dax = value;
}

void ConfigsObjPhysicsWidget::on_spinDay_valueChanged(double value)
{
    gameObject->day = value;
}


void ConfigsObjPhysicsWidget::on_comboTipoMovimento_2_currentIndexChanged(int index)
{
    gameObject->tipoMovimento = index;
}



void ConfigsObjPhysicsWidget::on_spinCarV_valueChanged(double value)
{
    gameObject->vx = value;
}

void ConfigsObjPhysicsWidget::on_spinCarA_valueChanged(double value)
{
    gameObject->ax = value;
}

void ConfigsObjPhysicsWidget::on_spinCarDA_valueChanged(double value)
{
    gameObject->dax = value;
}



void ConfigsObjPhysicsWidget::on_comboTipoMovimentoPlatformer_currentIndexChanged(int index)
{
    gameObject->tipoMovimento = index;
}

void ConfigsObjPhysicsWidget::on_spinPlatformerV_valueChanged(double value)
{
    gameObject->vx = value;
}

void ConfigsObjPhysicsWidget::on_spinPlatformerA_valueChanged(double value)
{
    gameObject->ax = value;
}

void ConfigsObjPhysicsWidget::on_spinPlatformerG_valueChanged(double value)
{
    gameObject->gravidade = value;
}

void ConfigsObjPhysicsWidget::on_spinPlatformerIntensidadePulo_valueChanged(double value)
{
    gameObject->intensidadePulo = value;
}

void ConfigsObjPhysicsWidget::on_spinBouncingBallVX_valueChanged(double value)
{
    gameObject->vx = value;
}

void ConfigsObjPhysicsWidget::on_spinBouncingBallVY_valueChanged(double value)
{
    gameObject->vy = value;
}

void ConfigsObjPhysicsWidget::on_comboTipoMovimentoMouseObject_currentIndexChanged(int index)
{
    gameObject->tipoMovimento = index;
}

void ConfigsObjPhysicsWidget::on_comboFormaMovimentoMouseObject_currentIndexChanged(int index)
{
    gameObject->formaMovimentoMouse = index;
}

void ConfigsObjPhysicsWidget::on_spinMouseObjectV_valueChanged(double value)
{
    gameObject->vx = value;
}

void ConfigsObjPhysicsWidget::on_spinMouseObjectA_valueChanged(double value)
{
    gameObject->ax = value;
}

void ConfigsObjPhysicsWidget::on_spinMouseObjectDA_valueChanged(double value)
{
    gameObject->dax = value;
}

void ConfigsObjPhysicsWidget::on_checkBox_toggled(bool checked)
{
    gameObject->resolveCollision = checked;
}

void ConfigsObjPhysicsWidget::on_spinCarVA_valueChanged(double value)
{
    gameObject->ay = value;
}

void ConfigsObjPhysicsWidget::on_pushButtonAddObjectsToBounce_pressed()
{
    if(ui->comboBoxObjectsToBounce->count() > 0) {
        GameObject* gameObjectIt = (GameObject*) ui->comboBoxObjectsToBounce->itemData(ui->comboBoxObjectsToBounce->currentIndex(), Qt::UserRole).value<void*>();
        if(std::find(gameObject->listObjectsToBounce.begin(), gameObject->listObjectsToBounce.end(), gameObjectIt) == gameObject->listObjectsToBounce.end()) {
            gameObject->listObjectsToBounce.push_back(gameObjectIt);
        }

        populaListaObjectsToBounce();
    }

}

void ConfigsObjPhysicsWidget::on_pushButtonRemoveObjectsToBounce_pressed()
{
    if(ui->listWidgetObjectsToBounce->currentItem() != NULL) {
        GameObject* gameObjectIt = (GameObject*) ui->listWidgetObjectsToBounce->currentItem()->data(Qt::UserRole).value<void*>();

        std::list<GameObject*>::iterator it = std::find(gameObject->listObjectsToBounce.begin(), gameObject->listObjectsToBounce.end(), gameObjectIt);

        if(it != gameObject->listObjectsToBounce.end()) {
            gameObject->listObjectsToBounce.erase(it);
        }
    }

    populaListaObjectsToBounce();

}
