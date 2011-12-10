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



#include "configsobjattributeswidget.h"
#include "ui_configsobjattributeswidget.h"

ConfigsObjAttributesWidget::ConfigsObjAttributesWidget(OptionsController *optionsController, GameObject *gameObject,QListWidgetItem *currentListItem, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsObjAttributesWidget),
    optionsController(optionsController),
    gameObject(gameObject),
    currentListItem(currentListItem)
{
    ui->setupUi(this);


    populaCampos();
    decideLevelEvolutionVisibility();
}

void ConfigsObjAttributesWidget::decideLevelEvolutionVisibility() {
    if(!ui->checkBoxLevelEvolution->isChecked()) {
        ui->labelEvoVelocity->setDisabled(true);
        ui->labelInitialLevel->setDisabled(true);
        ui->labelLabelAux->setDisabled(true);
        ui->labelmaxLevel->setDisabled(true);
        ui->spinBoxInitialLevel->setDisabled(true);
        ui->spinBoxMaxLevel->setDisabled(true);
        ui->horizontalSliderEvolutionVelocity->setDisabled(true);
    } else {
        ui->labelEvoVelocity->setDisabled(false);
        ui->labelInitialLevel->setDisabled(false);
        ui->labelLabelAux->setDisabled(false);
        ui->labelmaxLevel->setDisabled(false);
        ui->spinBoxInitialLevel->setDisabled(false);
        ui->spinBoxMaxLevel->setDisabled(false);
        ui->horizontalSliderEvolutionVelocity->setDisabled(false);
    }
}

void ConfigsObjAttributesWidget::populaCampos() {
    ui->spinBoxHp->setValue(gameObject->hp);
    ui->spinBoxMp->setValue(gameObject->mp);
    ui->spinBoxAtk->setValue(gameObject->atk);
    ui->spinBoxDef->setValue(gameObject->def);
    ui->spinBoxInitialLevel->setValue(gameObject->levelInicial);
    ui->spinBoxInt->setValue(gameObject->intelig);
    ui->spinBoxMaxLevel->setValue(gameObject->levelMax);

    ui->checkBoxLevelEvolution->setChecked(gameObject->evolucaoPorNivel);
    ui->horizontalSliderEvolutionVelocity->setValue(gameObject->velocidadeEvolucao);
    std::stringstream ss;
    ss << QString::fromUtf8("Velocidade de evolução: ").toStdString() << gameObject->velocidadeEvolucao;
    ui->labelEvoVelocity->setText(QString(ss.str().c_str()));

}

ConfigsObjAttributesWidget::~ConfigsObjAttributesWidget()
{
    delete ui;
}

void ConfigsObjAttributesWidget::on_checkBoxLevelEvolution_toggled(bool checked)
{
    gameObject->evolucaoPorNivel = checked;
    decideLevelEvolutionVisibility();
}




void ConfigsObjAttributesWidget::on_spinBoxHp_valueChanged(int value)
{
    gameObject->hp = value;
}

void ConfigsObjAttributesWidget::on_spinBoxMp_valueChanged(int value)
{
    gameObject->mp = value;
}

void ConfigsObjAttributesWidget::on_spinBoxAtk_valueChanged(int value)
{
    gameObject->atk = value;
}

void ConfigsObjAttributesWidget::on_spinBoxDef_valueChanged(int value)
{
    gameObject->def = value;
}

void ConfigsObjAttributesWidget::on_spinBoxInt_valueChanged(int value)
{
    gameObject->intelig = value;
}

void ConfigsObjAttributesWidget::on_spinBoxInitialLevel_valueChanged(int value)
{
    gameObject->levelInicial = value;
}

void ConfigsObjAttributesWidget::on_spinBoxMaxLevel_valueChanged(int value)
{
    gameObject->levelMax = value;
}

void ConfigsObjAttributesWidget::on_horizontalSliderEvolutionVelocity_valueChanged(int value)
{
    gameObject->velocidadeEvolucao = value;

    std::stringstream ss;
    ss << QString::fromUtf8("Velocidade de evolução: ").toStdString() << gameObject->velocidadeEvolucao;
    ui->labelEvoVelocity->setText(QString(ss.str().c_str()));
}
