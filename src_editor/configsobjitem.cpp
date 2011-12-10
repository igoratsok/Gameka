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



#include "configsobjitem.h"
#include "ui_configsobjitem.h"

ConfigsObjItem::ConfigsObjItem(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsObjItem),
    optionsController(optionsController),
    gameObject(gameObject),
    currentListItem(currentListItem)
{
    ui->setupUi(this);

    ui->checkBoxConcedeHabilidade->setVisible(false);
    ui->comboBoxConcedeHabilidade->setVisible(false);
    ui->radioButtonEnviaInventario->setVisible(false);

    ui->comboMovimentacaoItem->setVisible(false);
    ui->labelMovimentacao->setVisible(false);

    enableComboChange = false;

    populaComboEvents();
    populaComboVariables();
    populaCampos();

    enableComboChange = true;

    if((int) ui->comboBoxIncrementaVariavel->count() > 0) {
        gameObject->incrementaVariavelIdVariavel =
                ui->comboBoxIncrementaVariavel->itemData(ui->comboBoxIncrementaVariavel->currentIndex(), Qt::UserRole).toInt();
    }

    if((int) ui->comboBoxAtivaEvento->count() > 0) {
        gameObject->ativaEventoIdEvento =
                ui->comboBoxAtivaEvento->itemData(ui->comboBoxAtivaEvento->currentIndex(), Qt::UserRole).toInt();
    }



}

ConfigsObjItem::~ConfigsObjItem()
{
    delete ui;
}

void ConfigsObjItem::populaCampos() {
    ui->checkBoxAtivaEvento->setChecked(gameObject->ativaEvento);
    ui->checkBoxComportamentoDesapareceEncParedes->setChecked(gameObject->desapareceEncostarParede);
    ui->checkBoxComportamentoDesapareceEncPers->setChecked(gameObject->desapareceEncostarPersonagem);
    ui->checkBoxConcedePontos->setChecked(gameObject->concedePontos);
    ui->checkBoxGanhaPerdeMagia->setChecked(gameObject->ganhaPerdeMagia);
    ui->checkBoxGanhaPerdeVida->setChecked(gameObject->ganhaPerdeVida);
    ui->checkBoxIncrementaVariavel->setChecked(gameObject->incrementaVariavel);
    ui->checkBoxAtivaEvento->setChecked(gameObject->ativaEvento);
    ui->checkBoxConcedeHabilidade->setChecked(gameObject->concedeHabilidade);

    switch(gameObject->comportamentoEncostarPersonagem) {
    case 0:
        ui->radioButtonAtivaEfeitoImediatamente->setChecked(true);
        ui->radioButtonEnviaInventario->setChecked(false);
        break;
    case 1:
        ui->radioButtonAtivaEfeitoImediatamente->setChecked(false);
        ui->radioButtonEnviaInventario->setChecked(true);
        break;
    default:

        break;
    }

    ui->spinBoxConcedePontos->setValue(gameObject->concedePontosValor);
    ui->spinBoxGanhaPerdeMagia->setValue(gameObject->ganhaPerdeMagiaValor);
    ui->spinBoxGanhaPerdeVida->setValue(gameObject->ganhaPerdeVidaValor);
    ui->spinBoxIncrementaVariavel->setValue(gameObject->incrementaVariavelValor);

    ui->spinBoxConcedePontos->setEnabled(gameObject->concedePontos);
    ui->spinBoxGanhaPerdeMagia->setEnabled(gameObject->ganhaPerdeMagia);
    ui->spinBoxGanhaPerdeVida->setEnabled(gameObject->ganhaPerdeVida);
    ui->spinBoxIncrementaVariavel->setEnabled(gameObject->incrementaVariavel);

    ui->comboBoxAtivaEvento->setEnabled(gameObject->ativaEvento);
    ui->comboBoxConcedeHabilidade->setEnabled(gameObject->concedeHabilidade);
    ui->comboBoxIncrementaVariavel->setEnabled(gameObject->incrementaVariavel);


    ui->comboMovimentacaoItem->setCurrentIndex(gameObject->comportamentoEncostarPersonagem);

    /* TODO: popular combos da variavel, evento e habilidade, quando estiverem prontas*/

}

void ConfigsObjItem::populaComboEvents() {
    GameData *gameData = GameData::getInstance();

    ui->comboBoxAtivaEvento->clear();

    int i = 0;

    foreach(ProcedureData *procedureData, *gameData->procedureList) {
        std::stringstream ss;
        ss << "(Global) " << procedureData->name;


        ui->comboBoxAtivaEvento->addItem(QString(ss.str().c_str()), QVariant(procedureData->id));
        if(gameObject->ativaEventoIdEvento == procedureData->id) {
            ui->comboBoxAtivaEvento->setCurrentIndex(i);
        }
        i++;
    }

    foreach(ProcedureData *procedureData, *gameObject->procedureList) {
        std::stringstream ss;
        ss << "(" << gameObject->name << ") " << procedureData->name;

        ui->comboBoxAtivaEvento->addItem(QString(ss.str().c_str()), QVariant(-procedureData->id));

        if(gameObject->ativaEventoIdEvento == -procedureData->id) {
            ui->comboBoxAtivaEvento->setCurrentIndex(i);
        }
        i++;
    }
}

void ConfigsObjItem::populaComboVariables() {
    GameData *gameData = GameData::getInstance();

    ui->comboBoxIncrementaVariavel->clear();

    int i = 0;

    foreach(VariableData *variableData, *optionsController->getGlobalVariableDataList()) {
        std::stringstream ss;
        ss << "(Global) " << variableData->name;


        ui->comboBoxIncrementaVariavel->addItem(QString(ss.str().c_str()), QVariant(variableData->id));

        if(gameObject->incrementaVariavelIdVariavel == variableData->id) {
            ui->comboBoxIncrementaVariavel->setCurrentIndex(i);
        }
        i++;
    }

    foreach(VariableData *variableData, *gameObject->variableList) {
        std::stringstream ss;
        ss << "(" << gameObject->name << ") " << variableData->name;

        ui->comboBoxAtivaEvento->addItem(QString(ss.str().c_str()), QVariant(-variableData->id));

        if(gameObject->incrementaVariavelIdVariavel == -variableData->id) {
            ui->comboBoxIncrementaVariavel->setCurrentIndex(i);
        }
        i++;
    }
}

void ConfigsObjItem::on_checkBoxConcedePontos_toggled(bool checked)
{
    gameObject->concedePontos = checked;

   if(checked) {
       ui->spinBoxConcedePontos->setEnabled(true);
   } else {
       ui->spinBoxConcedePontos->setEnabled(false);
   }
}

void ConfigsObjItem::on_checkBoxGanhaPerdeVida_toggled(bool checked)
{
    gameObject->ganhaPerdeVida = checked;

    if(checked) {
        ui->spinBoxGanhaPerdeVida->setEnabled(true);
    } else {
        ui->spinBoxGanhaPerdeVida->setEnabled(false);
    }
}

void ConfigsObjItem::on_checkBoxGanhaPerdeMagia_toggled(bool checked)
{
    gameObject->ganhaPerdeMagia = checked;

    if(checked) {
        ui->spinBoxGanhaPerdeMagia->setEnabled(true);
    } else {
        ui->spinBoxGanhaPerdeMagia->setEnabled(false);
    }
}

void ConfigsObjItem::on_checkBoxIncrementaVariavel_toggled(bool checked)
{
    if(ui->comboBoxIncrementaVariavel->count() > 0) {
        gameObject->incrementaVariavel = checked;

        if(checked) {
            ui->spinBoxIncrementaVariavel->setEnabled(true);
            ui->comboBoxIncrementaVariavel->setEnabled(true);
        } else {
            ui->spinBoxIncrementaVariavel->setEnabled(false);
             ui->comboBoxIncrementaVariavel->setEnabled(false);
        }
    } else {
        ui->checkBoxIncrementaVariavel->setChecked(false);
        gameObject->incrementaVariavel = false;
    }

}

void ConfigsObjItem::on_checkBoxAtivaEvento_toggled(bool checked)
{
    if(ui->comboBoxAtivaEvento->count() > 0) {
        gameObject->ativaEvento = checked;

        if(checked) {
            ui->comboBoxAtivaEvento->setEnabled(true);
        } else {
            ui->comboBoxAtivaEvento->setEnabled(false);
        }
    } else {
        ui->checkBoxAtivaEvento->setChecked(false);
        gameObject->incrementaVariavel = false;
    }

}

void ConfigsObjItem::on_spinBoxConcedePontos_valueChanged(int value)
{
    gameObject->concedePontosValor = value;
}

void ConfigsObjItem::on_spinBoxGanhaPerdeVida_valueChanged(int value)
{
    gameObject->ganhaPerdeVidaValor = value;
}

void ConfigsObjItem::on_spinBoxGanhaPerdeMagia_valueChanged(int value)
{
    gameObject->ganhaPerdeMagiaValor = value;
}

void ConfigsObjItem::on_comboBoxIncrementaVariavel_currentIndexChanged(int index)
{
    if(enableComboChange) {
        gameObject->incrementaVariavelIdVariavel = ui->comboBoxIncrementaVariavel->itemData(index, Qt::UserRole).toInt();
    }

}

void ConfigsObjItem::on_spinBoxIncrementaVariavel_valueChanged(int value)
{
    gameObject->incrementaVariavelValor = value;
}

void ConfigsObjItem::on_comboBoxAtivaEvento_currentIndexChanged(int index)
{
    if(enableComboChange) {
        gameObject->ativaEventoIdEvento = ui->comboBoxAtivaEvento->itemData(index, Qt::UserRole).toInt();
    }

}

void ConfigsObjItem::on_radioButtonAtivaEfeitoImediatamente_toggled(bool checked)
{
    if(checked) {
        gameObject->comportamentoEncostarPersonagem = 0;
    }

}

void ConfigsObjItem::on_radioButtonEnviaInventario_toggled(bool checked)
{
    if(checked) {
        gameObject->comportamentoEncostarPersonagem = 1;
    }

}

void ConfigsObjItem::on_comboMovimentacaoItem_currentIndexChanged(int index)
{
    gameObject->formaMovimentacaoNpcItem = index;
}

void ConfigsObjItem::on_checkBoxComportamentoDesapareceEncPers_toggled(bool checked)
{
    gameObject->desapareceEncostarPersonagem = checked;
}

void ConfigsObjItem::on_checkBoxComportamentoDesapareceEncParedes_toggled(bool checked)
{
    gameObject->desapareceEncostarParede = checked;
}

void ConfigsObjItem::on_checkBoxConcedeHabilidade_toggled(bool checked)
{
    gameObject->concedeHabilidade = checked;

    if(checked) {
        ui->comboBoxConcedeHabilidade->setEnabled(true);
    } else {
        ui->comboBoxConcedeHabilidade->setEnabled(false);
    }
}

void ConfigsObjItem::on_comboBoxConcedeHabilidade_currentIndexChanged(int index)
{
    /* TODO quando habilidade estiverem prontas */
}
