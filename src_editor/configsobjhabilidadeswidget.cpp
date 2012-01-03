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



#include "configsobjhabilidadeswidget.h"
#include "ui_configsobjhabilidadeswidget.h"

ConfigsObjHabilidadesWidget::ConfigsObjHabilidadesWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigsObjHabilidadesWidget),
    optionsController(optionsController),
    gameObject(gameObject),
    currentListItem(currentListItem)
{
    ui->setupUi(this);


    if(gameObject->type == GameObject::ITEM ||
       gameObject->type == GameObject::NPC |
       gameObject->type == GameObject::INIMIGO ||
       gameObject->type == GameObject::STATIC_OBJECT) {
        ui->groupBoxHabilidades->setVisible(false);
    } else {
        ui->groupBoxHabilidades->setVisible(true);
    }

    switch(gameObject->type) {
    case GameObject::ITEM:
        ui->labelSpecialSound->setText(QString::fromUtf8(tr("Som ao pegar ítem: ").toStdString().c_str()));
        break;
    case GameObject::PLATFORM_MOVEMENT_OBJECT:
        ui->labelSpecialSound->setText(QString::fromUtf8(tr("Som ao pular: ").toStdString().c_str()));
        break;
    case GameObject::PONG_BALL_OBJECT:
        ui->labelSpecialSound->setText(QString::fromUtf8(tr("Som ao pegar ítem: ").toStdString().c_str()));
        break;

    default:
        ui->labelSpecialSound->setVisible(false);
        ui->lineEditSpecialSound->setVisible(false);
        ui->toolButtonSpecialSound->setVisible(false);
        ui->toolButtonRemoveSpecialSound->setVisible(false);
        break;
    }

    ui->lineEditDamageSound->setText(QString(gameObject->soundDamage.c_str()));
    ui->lineEditSpecialSound->setText(QString(gameObject->soundSpecial.c_str()));


    populaListaSkills();
}

ConfigsObjHabilidadesWidget::~ConfigsObjHabilidadesWidget()
{
    delete ui;
}

void ConfigsObjHabilidadesWidget::populaListaSkills() {
    ui->treeWidgetSkills->clear();

    for(std::vector<SkillData*>::iterator it = gameObject->listaHabilidades.begin(); it != gameObject->listaHabilidades.end(); ++it) {
        SkillData* skillData = *it;


        std::stringstream ss1, ss2;
        ss1.str("");
        ss1 << skillData->intensity;

        ss2.str("");
        if(skillData->level > 0) {
            ss2 << skillData->level;
        } else {
            ss2 << "-";
        }


        QTreeWidgetItem *treeItem = new QTreeWidgetItem(QStringList()
                                                    << QString(skillData->skill->name.c_str())
                                                    << QString(ss1.str().c_str())
                                                    << QString(ss2.str().c_str()));

        treeItem->setData(0, Qt::UserRole, QVariant::fromValue((void*) skillData));


        ui->treeWidgetSkills->insertTopLevelItem(0, treeItem);
    }
}

void ConfigsObjHabilidadesWidget::on_comboEvoNivel_currentIndexChanged(int index)
{
    gameObject->evolucaoPorNivel = !index;

}

void ConfigsObjHabilidadesWidget::on_botaoOpcoes_clicked()
{

}

void ConfigsObjHabilidadesWidget::on_botaoAddHabilidade_clicked()
{

}

void ConfigsObjHabilidadesWidget::on_botaoEditorEventos_clicked()
{

}

void ConfigsObjHabilidadesWidget::on_botaoAddHabilidade_pressed()
{
    SkillData *skillData;

    ConfigsObjNewSkillDialog *configsObjNewSkillDialog;
    configsObjNewSkillDialog = new ConfigsObjNewSkillDialog(optionsController, gameObject);
    configsObjNewSkillDialog->setWindowTitle(tr("Nova habilidade"));

    skillData = configsObjNewSkillDialog->exec();

    if(skillData != NULL) {
        optionsController->addObjectSkill(gameObject, skillData);
        populaListaSkills();
    }
}

void ConfigsObjHabilidadesWidget::on_listHabilidades_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{

}

void ConfigsObjHabilidadesWidget::on_pushButtonRemove_pressed()
{
    if(ui->treeWidgetSkills->currentItem() != NULL) {
        SkillData* skillData = (SkillData*) ui->treeWidgetSkills->currentItem()->data(0, Qt::UserRole).value<void*>();

        if(skillData != NULL) {
            optionsController->removeObjectSkill(gameObject, skillData);
            populaListaSkills();
        }

    }

}


void ConfigsObjHabilidadesWidget::on_pushButtonEdit_pressed()
{

    if(ui->treeWidgetSkills->currentItem() != NULL) {
        SkillData* skillData = (SkillData*) ui->treeWidgetSkills->currentItem()->data(0, Qt::UserRole).value<void*>();

        if(skillData != NULL) {
            ConfigsObjNewSkillDialog *configsObjNewSkillDialog;
            configsObjNewSkillDialog = new ConfigsObjNewSkillDialog(optionsController, gameObject, skillData);
            configsObjNewSkillDialog->setWindowTitle(tr("Nova habilidade"));

            configsObjNewSkillDialog->exec();

            populaListaSkills();
        }

    }


}


void ConfigsObjHabilidadesWidget::setConfigsTabWidget(ConfigsTabWidget *configsTabWidget) {
    this->configsTabWidget = configsTabWidget;
}

void ConfigsObjHabilidadesWidget::on_botaoEditorEventos_pressed()
{
    configsTabWidget->selectObjectEvent(gameObject->id);
}

void ConfigsObjHabilidadesWidget::on_toolButtonDamageSound_pressed()
{
    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::SOM, this);
    soundPickerDialog->setWindowTitle(QString::fromUtf8(tr("Som ao levar dano").toStdString().c_str()));
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->lineEditDamageSound->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
        gameObject->soundDamage = std::string(soundPickerDialog->getSelectedFile().c_str());
    }


    delete soundPickerDialog;
}

void ConfigsObjHabilidadesWidget::on_toolButtonSpecialSound_pressed()
{
    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::SOM, this);
    soundPickerDialog->setWindowTitle(ui->labelSpecialSound->text());
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->lineEditSpecialSound->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
        gameObject->soundSpecial = std::string(soundPickerDialog->getSelectedFile().c_str());
    }


    delete soundPickerDialog;
}

void ConfigsObjHabilidadesWidget::on_toolButtonRemoveDamageSound_pressed()
{
    ui->lineEditDamageSound->setText(QString(""));
    gameObject->soundDamage = std::string("");
}

void ConfigsObjHabilidadesWidget::on_toolButtonRemoveSpecialSound_pressed()
{
    ui->lineEditSpecialSound->setText(QString(""));
    gameObject->soundSpecial = std::string("");
}
