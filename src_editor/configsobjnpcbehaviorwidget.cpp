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



#include "configsobjnpcbehaviorwidget.h"
#include "ui_configsobjnpcbehaviorwidget.h"

ConfigsObjNpcBehaviorWidget::ConfigsObjNpcBehaviorWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsObjNpcBehaviorWidget),
    optionsController(optionsController),
    gameObject(gameObject),
    currentListItem(currentListItem)
{
    ui->setupUi(this);
    ativaMudancaCombo = false;
    populaCampos();
    ativaMudancaCombo = true;

    if(gameObject->type == GameObject::NPC) {
        ui->groupBoxInimigo->setVisible(false);
    }
}

ConfigsObjNpcBehaviorWidget::~ConfigsObjNpcBehaviorWidget()
{
    delete ui;
}

void ConfigsObjNpcBehaviorWidget::populaCampos() {
    GameData *gameData = GameData::getInstance();

    ui->comboBoxFormaMovimentacaoNpc->setCurrentIndex(gameObject->formaMovimentacaoNpcItem);
    ui->spinBoxRaioMovimentacao->setValue(gameObject->raioMovimentacao);
    ui->checkBoxAtacaAtiraItemMagiaDirEstiver->setChecked(gameObject->atiraItemMaginaDirecaoEstiver);
    ui->checkBoxAtacaAtiraItemMagiaDirPers->setChecked(gameObject->atiraItemMagiaDirecaoPersonagem);
    ui->checkBoxAtacaEncostaNoPersonagem->setChecked(gameObject->atacaEncostaPersonagem);
    ui->checkBoxAtacaUsaEspada->setChecked(gameObject->atacaUsandoEspada);
    ui->checkBoxDerrotaAcertandoEspada->setChecked(gameObject->derrotaAcertandoEspadaSobreInimigo);
    ui->checkBoxDerrotaAtirandoItemMagia->setChecked(gameObject->derrotaAtirandoItemMagiaInimigo);
    ui->checkBoxDerrotaEncostandoInimigo->setChecked(gameObject->derrotaEncostandoInimigo);
    ui->checkBoxDerrotaPulandoSobre->setChecked(gameObject->derrotaPulandoSobreInimigo);

    ui->spinBoxDanoEncostaPersonagem->setValue(gameObject->atacaEncostaPersonagemDano);
    ui->spinBoxDanoUsaEspada->setValue(gameObject->atacaUsandoEspadaDano);

    ui->spinBoxVelocidadeMovimentacao->setValue(gameObject->vx);

    ui->checkBox->setChecked(gameObject->movimentaApenasDentroTela);

    std::vector<GameObject *> *gameObjectList;


    gameObjectList = optionsController->getObjectList();

    ui->comboBoxItemDirecaoEstiver->clear();
    ui->comboBoxItemDirecaoPersonagem->clear();
    ui->comboBoxItemEspada->clear();

    for(std::vector<GameObject*>::iterator it = gameObjectList->begin(); it != gameObjectList->end(); ++it) {
        GameObject *currentGameObject = *it;
        if(currentGameObject->type == GameObject::ITEM) {
            ui->comboBoxItemDirecaoEstiver->addItem(QIcon(QPixmap::fromImage(currentGameObject->getIconImage())), QString(currentGameObject->name.c_str()), QVariant(currentGameObject->id));
            ui->comboBoxItemDirecaoPersonagem->addItem(QIcon(QPixmap::fromImage(currentGameObject->getIconImage())), QString(currentGameObject->name.c_str()), QVariant(currentGameObject->id));
            ui->comboBoxItemEspada->addItem(QIcon(QPixmap::fromImage(currentGameObject->getIconImage())), QString(currentGameObject->name.c_str()), QVariant(currentGameObject->id));

            if(currentGameObject->id == gameObject->atiraItemMagiaDirecaoPersonagemIdItem) {
                ui->comboBoxItemDirecaoPersonagem->setCurrentIndex(ui->comboBoxItemDirecaoPersonagem->count() - 1);
            }

            if(currentGameObject->id == gameObject->atiraItemMaginaDirecaoEstiverIdItem) {
                ui->comboBoxItemDirecaoEstiver->setCurrentIndex(ui->comboBoxItemDirecaoEstiver->count() - 1);
            }

            if(currentGameObject->id == gameObject->espadaItemId) {
                ui->comboBoxItemEspada->setCurrentIndex(ui->comboBoxItemEspada->count() - 1);
            }
        }
    }

    if(gameObject->formaMovimentacaoNpcItem > 0) {
        ui->spinBoxVelocidadeMovimentacao->setEnabled(true);
        ui->spinBoxRaioMovimentacao->setEnabled(true);
        ui->checkBox->setEnabled(true);
    } else {
        ui->spinBoxVelocidadeMovimentacao->setEnabled(false);
        ui->spinBoxRaioMovimentacao->setEnabled(false);
        ui->checkBox->setEnabled(false);
    }

    ui->spinBoxPeriodicidade->setValue(gameObject->tempoAtaque);
    ui->spinBoxMagicCost->setValue(gameObject->magicCost);

    ui->spinBoxExperiencePoints->setValue(gameObject->experiencePoints);
    ui->spinBoxPontosDerrotar->setValue(gameObject->defeatPoints);



}


void ConfigsObjNpcBehaviorWidget::on_comboBoxFormaMovimentacaoNpc_currentIndexChanged(int index)
{
    gameObject->formaMovimentacaoNpcItem = index;

    if(index > 0) {
        ui->spinBoxVelocidadeMovimentacao->setEnabled(true);
        ui->spinBoxRaioMovimentacao->setEnabled(true);
        ui->checkBox->setEnabled(true);
    } else {
        ui->spinBoxVelocidadeMovimentacao->setEnabled(false);
        ui->spinBoxRaioMovimentacao->setEnabled(false);
        ui->checkBox->setEnabled(false);
    }

}

void ConfigsObjNpcBehaviorWidget::on_checkBoxDerrotaEncostandoInimigo_toggled(bool checked)
{
    gameObject->derrotaEncostandoInimigo = checked;
}

void ConfigsObjNpcBehaviorWidget::on_checkBoxDerrotaAtirandoItemMagia_toggled(bool checked)
{
    gameObject->derrotaAtirandoItemMagiaInimigo = checked;
}

void ConfigsObjNpcBehaviorWidget::on_checkBoxDerrotaAcertandoEspada_toggled(bool checked)
{
    gameObject->derrotaAcertandoEspadaSobreInimigo = checked;
}

void ConfigsObjNpcBehaviorWidget::on_checkBoxDerrotaPulandoSobre_toggled(bool checked)
{
    gameObject->derrotaPulandoSobreInimigo = checked;
}

void ConfigsObjNpcBehaviorWidget::on_checkBoxAtacaEncostaNoPersonagem_toggled(bool checked)
{
    gameObject->atacaEncostaPersonagem = checked;
}

void ConfigsObjNpcBehaviorWidget::on_checkBoxAtacaUsaEspada_toggled(bool checked)
{
    gameObject->atacaUsandoEspada = checked;
}

void ConfigsObjNpcBehaviorWidget::on_checkBoxAtacaAtiraItemMagiaDirEstiver_toggled(bool checked)
{
    gameObject->atiraItemMaginaDirecaoEstiver = checked;
}

void ConfigsObjNpcBehaviorWidget::on_checkBoxAtacaAtiraItemMagiaDirPers_toggled(bool checked)
{
    gameObject->atiraItemMagiaDirecaoPersonagem = checked;
}

void ConfigsObjNpcBehaviorWidget::on_spinBoxDanoEncostaPersonagem_valueChanged(int value)
{
    gameObject->atacaEncostaPersonagemDano = value;
}

void ConfigsObjNpcBehaviorWidget::on_spinBoxDanoUsaEspada_valueChanged(int value)
{
    gameObject->atacaUsandoEspadaDano = value;
}

void ConfigsObjNpcBehaviorWidget::on_comboBoxItemDirecaoEstiver_currentIndexChanged(int index)
{
    if(ativaMudancaCombo) {
        gameObject->atiraItemMaginaDirecaoEstiverIdItem =
            ui->comboBoxItemDirecaoEstiver->itemData(index).toInt();
    }
}

void ConfigsObjNpcBehaviorWidget::on_comboBoxItemEspada_currentIndexChanged(int index)
{
    if(ativaMudancaCombo) {
        gameObject->espadaItemId =
            ui->comboBoxItemEspada->itemData(index).toInt();
    }
}

void ConfigsObjNpcBehaviorWidget::on_comboBoxItemDirecaoPersonagem_currentIndexChanged(int index)
{
    if(ativaMudancaCombo) {
        gameObject->atiraItemMagiaDirecaoPersonagemIdItem =
            ui->comboBoxItemDirecaoPersonagem->itemData(index).toInt();
    }

}

void ConfigsObjNpcBehaviorWidget::on_spinBoxVelocidadeMovimentacao_valueChanged(int value)
{
    gameObject->vx = value;
}

void ConfigsObjNpcBehaviorWidget::on_checkBox_toggled(bool checked)
{
    gameObject->movimentaApenasDentroTela = checked;
}

void ConfigsObjNpcBehaviorWidget::on_spinBoxRaioMovimentacao_valueChanged(int value)
{
    gameObject->raioMovimentacao = value;
}

void ConfigsObjNpcBehaviorWidget::on_spinBoxMagicCost_valueChanged(int value)
{
    gameObject->magicCost = value;
}


void ConfigsObjNpcBehaviorWidget::on_spinBoxPeriodicidade_valueChanged(double value)
{
    gameObject->tempoAtaque = value;
}

void ConfigsObjNpcBehaviorWidget::on_spinBoxExperiencePoints_valueChanged(int value)
{
    gameObject->experiencePoints = value;
}

void ConfigsObjNpcBehaviorWidget::on_spinBoxPontosDerrotar_valueChanged(int value)
{
    gameObject->defeatPoints = value;
}
