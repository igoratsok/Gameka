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



#include "easynewgameobjectdialog.h"
#include "ui_easynewgameobjectdialog.h"

EasyNewGameObjectDialog::EasyNewGameObjectDialog(OptionsController *OptionsController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EasyNewGameObjectDialog),
    optionsController(optionsController)
{
    ui->setupUi(this);

    populaCombosObjetos();
    habilitaCheckBoxes();


    gameObject = new GameObject();
    preencheComboMovementStyle();

    scene = new QGraphicsScene(this);
    item =
            new QGraphicsPixmapItem(QPixmap::fromImage(gameObject->getIconImage()));

    item->setPos(0, 0);

    scene->addItem(item);

    ui->graphicsView->setScene(scene);
}

EasyNewGameObjectDialog::~EasyNewGameObjectDialog()
{
    delete item;
    delete scene;
    delete ui;
}

GameObject* EasyNewGameObjectDialog::exec() {
    QDialog::exec();

    if(gameObject != NULL) {
        GameData *gameData = GameData::getInstance();

        gameObject->name = ui->lineEditName->text().toStdString();
        gameObject->type = ui->comboBoxType->currentIndex();

        switch(ui->comboBoxMovementType->currentIndex()) {
        case MOVEMENT_SSLOW:
            gameObject->vx = 7;
            gameObject->vy = 7;
            gameObject->ax = 10;
            gameObject->ay = 10;
            gameObject->dax = 10;
            gameObject->day = 10;
            break;
        case MOVEMENT_SLOW:
            gameObject->vx = 10;
            gameObject->vy = 10;
            gameObject->ax = 7;
            gameObject->ay = 7;
            gameObject->dax = 7;
            gameObject->day = 7;
            break;
        case MOVEMENT_FAST:
            gameObject->vx = 15;
            gameObject->vy = 15;
            gameObject->ax = 10;
            gameObject->ay = 10;
            gameObject->dax = 10;
            gameObject->day = 10;
            break;
        case MOVEMENT_FFAST:
            gameObject->vx = 20;
            gameObject->vy = 20;
            gameObject->ax = 15;
            gameObject->ay = 15;
            gameObject->dax = 15;
            gameObject->day = 15;
            break;
        case MOVEMENT_SFAST:
            gameObject->vx = 25;
            gameObject->vy = 25;
            gameObject->ax = 20;
            gameObject->ay = 20;
            gameObject->dax = 20;
            gameObject->day = 20;
            break;
        }

        gameObject->tipoMovimento = ui->comboBoxMovementStyle->currentIndex();

        if(ui->checkBoxDoubleJump->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_DOUBLE_JUMP;
            skillData->intensity = gameObject->intensidadePulo;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_DOUBLE_JUMP);
            skillData->skillObject = NULL;
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxFly->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_FLY;
            skillData->intensity = 3;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_FLY);
            skillData->skillObject = NULL;
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxGlide->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_GLIDE;
            skillData->intensity = 1;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_GLIDE);
            skillData->skillObject = NULL;
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxJump->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_JUMP;
            skillData->intensity = gameObject->intensidadePulo;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_JUMP);
            skillData->skillObject = NULL;
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxObjectThrow->isChecked()) {
            if(gameObject->type != GameObject::INIMIGO) {
                SkillData *skillData = new SkillData();
                skillData->id = Skill::SKILL_THROW_OBJECT;
                skillData->intensity = 2;
                skillData->magicCost = 0;
                skillData->level = -1;
                skillData->skill = gameData->skillList->at(Skill::SKILL_THROW_OBJECT);
                skillData->skillObject = (GameObject*)
                        ui->comboBoxObjectThrow->itemData(ui->comboBoxObjectThrow->currentIndex(), Qt::UserRole).value<void*>();
                skillData->skillProvider = NULL;

                gameObject->listaHabilidades.push_back(skillData);
            } else {
                gameObject->atiraItemMaginaDirecaoEstiver = true;
                gameObject->atiraItemMaginaDirecaoEstiverDano = 1;
                gameObject->atiraItemMaginaDirecaoEstiverIdItem = ((GameObject*)
                        ui->comboBoxObjectThrow->itemData(ui->comboBoxObjectThrow->currentIndex(), Qt::UserRole).value<void*>())->id;

            }

        }

        if(ui->checkBoxObjectThrowClick->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_THROW_OBJECT_CLICK;
            skillData->intensity = 2;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_THROW_OBJECT_CLICK);
            skillData->skillObject = (GameObject*)
                    ui->comboBoxObjectThrowClick->itemData(ui->comboBoxObjectThrowClick->currentIndex(), Qt::UserRole).value<void*>();
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxRun->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_RUN;
            skillData->intensity = 2;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_RUN);
            skillData->skillObject = NULL;
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxSwordUse->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_USE_SWORD;
            skillData->intensity = 2;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_USE_SWORD);
            skillData->skillObject = (GameObject*)
                    ui->comboBoxObjectThrowClick->itemData(ui->comboBoxObjectThrowClick->currentIndex(), Qt::UserRole).value<void*>();
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxWallKick->isChecked()) {
            SkillData *skillData = new SkillData();
            skillData->id = Skill::SKILL_WALL_KICK;
            skillData->intensity = 35;
            skillData->magicCost = 0;
            skillData->level = -1;
            skillData->skill = gameData->skillList->at(Skill::SKILL_WALL_KICK);
            skillData->skillObject = NULL;
            skillData->skillProvider = NULL;

            gameObject->listaHabilidades.push_back(skillData);
        }

        if(ui->checkBoxAttackedLeaning->isChecked()) {
            gameObject->derrotaEncostandoInimigo = true;
        } else {
            gameObject->derrotaEncostandoInimigo = false;
        }

        if(ui->checkBoxAttackLeaning->isChecked()) {
            gameObject->atacaEncostaPersonagem = true;
            gameObject->atacaEncostaPersonagemDano = 1;
            gameObject->tempoAtaque = 3;
        } else {
            gameObject->atacaEncostaPersonagem = false;
            gameObject->atacaEncostaPersonagemDano = 0;
        }
    }





    return gameObject;
}

void EasyNewGameObjectDialog::populaCombosObjetos() {
    GameData *gameData = GameData::getInstance();

    ui->comboBoxObjectSword->clear();
    ui->comboBoxObjectThrow->clear();
    ui->comboBoxObjectThrowClick->clear();

    for(std::vector<GameObject*>::iterator it = optionsController->getObjectList()->begin(); it != optionsController->getObjectList()->end(); ++it) {
        GameObject *gameObject = *it;

        if(gameObject->type == GameObject::ITEM) {
            ui->comboBoxObjectSword->addItem(QIcon(QPixmap::fromImage(gameObject->getIconImage())), QString(gameObject->name.c_str()),
                                        QVariant::fromValue((void*) gameObject));

            ui->comboBoxObjectThrow->addItem(QIcon(QPixmap::fromImage(gameObject->getIconImage())), QString(gameObject->name.c_str()),
                                        QVariant::fromValue((void*) gameObject));

            ui->comboBoxObjectThrowClick->addItem(QIcon(QPixmap::fromImage(gameObject->getIconImage())), QString(gameObject->name.c_str()),
                                        QVariant::fromValue((void*) gameObject));
        }



    }
}

void EasyNewGameObjectDialog::habilitaCheckBoxes() {
    GameData *gameData = GameData::getInstance();

    std::vector<Skill*> *skillList = gameData->skillList;

    Skill *currentSkill;

    currentSkill = skillList->at(Skill::SKILL_DOUBLE_JUMP);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxDoubleJump->setEnabled(true);
    } else {
        ui->checkBoxDoubleJump->setEnabled(false);
        ui->checkBoxDoubleJump->setChecked(false);
    }

    currentSkill = skillList->at(Skill::SKILL_FLY);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxFly->setEnabled(true);
    } else {
        ui->checkBoxFly->setChecked(false);
        ui->checkBoxFly->setEnabled(false);
    }

    currentSkill = skillList->at(Skill::SKILL_GLIDE);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxGlide->setEnabled(true);
    } else {
        ui->checkBoxGlide->setEnabled(false);
        ui->checkBoxGlide->setChecked(false);
    }

    currentSkill = skillList->at(Skill::SKILL_JUMP);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxJump->setEnabled(true);
    } else {
        if(ui->comboBoxType->currentIndex() == GameObject::PLATFORM_MOVEMENT_OBJECT || GameObject::FIGHTING_MOVEMENT_OBJECT) {
            ui->checkBoxJump->setChecked(true);
        } else {
            ui->checkBoxJump->setChecked(false);
        }
        ui->checkBoxJump->setEnabled(false);
    }

    currentSkill = skillList->at(Skill::SKILL_RUN);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxRun->setEnabled(true);
    } else {
        ui->checkBoxRun->setEnabled(false);
        ui->checkBoxRun->setChecked(false);
    }

    currentSkill = skillList->at(Skill::SKILL_THROW_OBJECT);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()
            || ui->comboBoxType->currentIndex() == GameObject::INIMIGO) {
        ui->checkBoxObjectThrow->setEnabled(true);
        ui->comboBoxObjectThrow->setEnabled(true);
    } else {
        ui->checkBoxObjectThrow->setEnabled(false);
        ui->checkBoxObjectThrow->setChecked(false);
        ui->comboBoxObjectThrow->setEnabled(false);
    }

    currentSkill = skillList->at(Skill::SKILL_THROW_OBJECT_CLICK);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxObjectThrowClick->setEnabled(true);
        ui->comboBoxObjectThrowClick->setEnabled(true);
    } else {
        ui->checkBoxObjectThrowClick->setEnabled(false);
        ui->checkBoxObjectThrowClick->setChecked(false);
        ui->comboBoxObjectThrowClick->setEnabled(false);
    }

    currentSkill = skillList->at(Skill::SKILL_USE_SWORD);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxSwordUse->setEnabled(true);
        ui->comboBoxObjectSword->setEnabled(true);
    } else {
        ui->checkBoxSwordUse->setEnabled(false);
        ui->checkBoxSwordUse->setChecked(false);
        ui->comboBoxObjectSword->setEnabled(false);
    }

    currentSkill = skillList->at(Skill::SKILL_WALL_KICK);
    if(std::find(currentSkill->objectTypes.begin(), currentSkill->objectTypes.end(), ui->comboBoxType->currentIndex()) != currentSkill->objectTypes.end()) {
        ui->checkBoxWallKick->setEnabled(true);
    } else {
        ui->checkBoxWallKick->setEnabled(false);
        ui->checkBoxWallKick->setChecked(false);
    }

    if(ui->comboBoxType->currentIndex() == GameObject::INIMIGO) {
        ui->checkBoxAttackLeaning->setEnabled(true);
        ui->checkBoxAttackedLeaning->setEnabled(true);
    } else {
        ui->checkBoxAttackLeaning->setEnabled(false);
        ui->checkBoxAttackLeaning->setChecked(false);
        ui->checkBoxAttackedLeaning->setEnabled(false);
    }


}

void EasyNewGameObjectDialog::preencheComboMovementStyle() {
    switch(ui->comboBoxType->currentIndex()) {
    case GameObject::EIGHT_MOVEMENT_OBJECT:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(false);
        break;
    case GameObject::CAR_MOVEMENT_OBJECT:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(false);
        ui->comboBoxMovementType->setEnabled(true);
        break;
    case GameObject::PLATFORM_MOVEMENT_OBJECT:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(false);
        ui->comboBoxMovementType->setEnabled(true);
        break;
    case GameObject::FIGHTING_MOVEMENT_OBJECT:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(false);
        ui->comboBoxMovementType->setEnabled(true);
        break;
    case GameObject::PONG_BALL_OBJECT:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(false);
        ui->comboBoxMovementType->setEnabled(true);
        break;
    case GameObject::MOUSE_MOVEMENT_OBJECT:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(true);
        ui->comboBoxMovementType->setEnabled(true);

        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Sempre na posição do mouse").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Sempre na posição do mouse quando clicar").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Sempre segue o mouse").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Segue o mouse quando clicar").toStdString().c_str()));
        ui->comboBoxMovementStyle->setCurrentIndex(2);
        break;
    case GameObject::STATIC_OBJECT:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(false);
        ui->comboBoxMovementType->setEnabled(false);
        break;
    case GameObject::NPC:

    case GameObject::INIMIGO:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(true);
        ui->comboBoxMovementType->setEnabled(true);
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Parado").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Segue personagem").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Foge do personagem").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Move esquerda/direita").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Move cima/baixo").toStdString().c_str()));
        ui->comboBoxMovementStyle->addItem(QString::fromUtf8(tr("Movimento circular").toStdString().c_str()));
        break;
    case GameObject::ITEM:
        ui->comboBoxMovementStyle->clear();
        ui->comboBoxMovementStyle->setEnabled(false);
        ui->comboBoxMovementType->setEnabled(false);
        break;
    }
}

void EasyNewGameObjectDialog::on_comboBoxType_currentIndexChanged(int index)
{
    habilitaCheckBoxes();
    preencheComboMovementStyle();
}

void EasyNewGameObjectDialog::on_buttonBox_accepted()
{
    if(ui->lineEditName->text().isEmpty()) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Erro: O objeto precisa ter um nome!").toStdString().c_str()));
        return;
    }

    if(ui->checkBoxObjectThrow->isChecked() && ui->comboBoxObjectThrow->count() == 0) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Erro: é necessário escolher um ítem para marcar a opção de atirar objeto.").toStdString().c_str()));
        return;
    }

    if(ui->checkBoxObjectThrowClick->isChecked() && ui->comboBoxObjectThrowClick->count() == 0) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Erro: é necessário escolher um ítem para marcar a opção de atirar objeto com clique.").toStdString().c_str()));
        return;
    }

    if(ui->checkBoxSwordUse->isChecked() && ui->comboBoxObjectSword->count() == 0) {
        MessageBoxes::showMessageBox(QString::fromUtf8(tr("Erro: é necessário escolher um ítem para marcar a opção de atirar objeto com clique.").toStdString().c_str()));
        return;
    }




    accept();
}

void EasyNewGameObjectDialog::on_buttonBox_rejected()
{
    delete gameObject;
    gameObject = NULL;

    reject();
}

void EasyNewGameObjectDialog::on_pushButtonEditGraphics_pressed()
{
    ConfigsObjAnimationChooserWindow *configsObjAnimationChooserWindow =
            new ConfigsObjAnimationChooserWindow(optionsController,
                                                       gameObject,
                                                       NULL,
                                                       this);

    configsObjAnimationChooserWindow->setWindowTitle(tr("Graficos do objeto").toStdString().c_str());

    configsObjAnimationChooserWindow->exec();

    delete configsObjAnimationChooserWindow;


    scene->removeItem(item);

    delete item;

    item =
            new QGraphicsPixmapItem(QPixmap::fromImage(gameObject->getIconImage()));

    item->setPos(0, 0);

    scene->addItem(item);
}
