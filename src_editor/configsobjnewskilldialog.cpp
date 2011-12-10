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



#include "configsobjnewskilldialog.h"
#include "ui_configsobjnewskilldialog.h"

ConfigsObjNewSkillDialog::ConfigsObjNewSkillDialog(OptionsController* optionsController, GameObject *gameObject, SkillData *skillData, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigsObjNewSkillDialog),
    gameObject(gameObject),
    optionsController(optionsController)
{
    ui->setupUi(this);

    populaComboHabilidades();
    populaComboObjetos();

    if(skillData) {
        this->skillData = skillData;
        preencheCampos(skillData);
    } else {
        this->skillData = new SkillData();
    }

    accepeted = false;


}

ConfigsObjNewSkillDialog::~ConfigsObjNewSkillDialog()
{
    delete ui;
}

void ConfigsObjNewSkillDialog::preencheCampos(SkillData *skillData) {
    if(skillData->skillObject != NULL) {

        if(skillData->skill != NULL) {
            int count_skill = ui->comboBoxSkill->count();
            for(int i = 0; i < count_skill; i++) {
                Skill *skill = (Skill*) ui->comboBoxSkill->itemData(i, Qt::UserRole).value<void*>();

                if(skill != NULL) {
                    if(skill->id == skillData->skill->id) {
                        ui->comboBoxSkill->setCurrentIndex(i);
                    }
                }


            }
        }

        if(skillData->skillObject != NULL) {
            int count_skill_object = ui->comboBoxSkillObject->count();
            for(int i = 0; i < count_skill_object; i++) {
                GameObject *gameObject = (GameObject*) ui->comboBoxSkillObject->itemData(i, Qt::UserRole).value<void*>();

                if(gameObject->id == skillData->skillObject->id) {
                    ui->comboBoxSkillObject->setCurrentIndex(i);
                }
            }
        }

        ui->checkBoxGetItem->setChecked(false);

        ui->checkBoxMagicAttack->setChecked(skillData->isMagical);

        if(skillData->skillProvider != NULL) {
            int count_skill_object = ui->comboBoxProviderObject->count();
            for(int i = 0; i < count_skill_object; i++) {
                GameObject *gameObject = (GameObject*) ui->comboBoxProviderObject->itemData(i, Qt::UserRole).value<void*>();

                if(gameObject->id == skillData->skillObject->id) {
                    ui->comboBoxProviderObject->setCurrentIndex(i);
                    ui->checkBoxAlways->setChecked(false);
                    ui->checkBoxGetItem->setChecked(true);
                }
            }
        }

        if(skillData->level > 0) {
            ui->spinBoxLevel->setValue(skillData->level);
            ui->checkBoxAlways->setChecked(false);
            ui->checkBoxLevel->setChecked(true);
        } else {
            ui->checkBoxLevel->setChecked(false);
        }

        ui->spinBoxIntensity->setValue(skillData->intensity);
        ui->spinBoxMagicCost->setValue(skillData->magicCost);

        ui->lineEditSound->setText(QString(skillData->sound.c_str()));

    }


}

void ConfigsObjNewSkillDialog::populaComboHabilidades() {
    GameData *gameData = GameData::getInstance();

    std::vector<Skill*> *skillList = gameData->skillList;

    ui->comboBoxSkill->clear();

    ui->comboBoxSkill->insertItem(ui->comboBoxSkill->count() + 1, QString("-- Escolha a habilidade --"), QVariant::fromValue((void*) NULL));

    for(std::vector<Skill*>::iterator it = skillList->begin(); it != skillList->end(); ++it) {
        Skill *skill = *it;

        if(skill->containsObjectType(gameObject->type)) {
            ui->comboBoxSkill->insertItem(ui->comboBoxSkill->count() + 1, QString(skill->name.c_str()), QVariant::fromValue((void*) skill));
        }

    }
}

void ConfigsObjNewSkillDialog::populaComboObjetos() {
    GameData *gameData = GameData::getInstance();

    std::vector<GameObject*> *objectList = optionsController->getObjectList();

    ui->comboBoxSkillObject->clear();

    for(std::vector<GameObject*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObject *gameObject = *it;

        if(gameObject->type == GameObject::ITEM) {
            ui->comboBoxSkillObject->insertItem(0, QIcon(QPixmap::fromImage(gameObject->getIconImage())), QString(gameObject->name.c_str()),
                                                QVariant::fromValue((void*) gameObject));
            ui->comboBoxProviderObject->insertItem(0, QIcon(QPixmap::fromImage(gameObject->getIconImage())), QString(gameObject->name.c_str()),
                                                QVariant::fromValue((void*) gameObject));
        }




    }

}

SkillData* ConfigsObjNewSkillDialog::exec() {
    QDialog::exec();


    if(this->accepeted) {


        skillData->intensity = ui->spinBoxIntensity->value();
        skillData->magicCost = ui->spinBoxMagicCost->value();
        if(ui->checkBoxLevel->isChecked()) {
            skillData->level = ui->spinBoxLevel->value();
        } else {
            skillData->level = -1;
        }
        skillData->skill = (Skill*) ui->comboBoxSkill->itemData(ui->comboBoxSkill->currentIndex(), Qt::UserRole).value<void*>();
        if(skillData->skill->hasObject) {
            skillData->skillObject = (GameObject*) ui->comboBoxSkillObject->itemData(ui->comboBoxSkillObject->currentIndex(), Qt::UserRole).value<void*>();
        } else {
            skillData->skillObject = NULL;
        }

        if(ui->checkBoxGetItem->isChecked()) {
            skillData->skillProvider = (GameObject*) ui->comboBoxProviderObject->itemData(ui->comboBoxProviderObject->currentIndex(), Qt::UserRole).value<void*>();
        } else {
            skillData->skillProvider = NULL;
        }

        skillData->isMagical = ui->checkBoxMagicAttack->isChecked();

        skillData->sound = ui->lineEditSound->text().toStdString();


        return skillData;
    } else {
        return NULL;
    }

}

void ConfigsObjNewSkillDialog::on_comboBoxSkill_currentIndexChanged(int index)
{
    Skill *skill = (Skill*) ui->comboBoxSkill->itemData(index, Qt::UserRole).value<void*>();

    if(skill != NULL) {
        ui->spinBoxIntensity->setEnabled(skill->hasIntensity);
        ui->comboBoxSkillObject->setEnabled(skill->hasObject);
        ui->groupBoxObtain->setEnabled(true);
        ui->spinBoxMagicCost->setEnabled(true);
    } else {
        ui->spinBoxIntensity->setEnabled(false);
        ui->comboBoxSkillObject->setEnabled(false);
        ui->groupBoxObtain->setEnabled(false);
        ui->spinBoxMagicCost->setEnabled(false);
    }


}

void ConfigsObjNewSkillDialog::on_checkBoxAlways_toggled(bool checked)
{

}

void ConfigsObjNewSkillDialog::on_checkBoxLevel_toggled(bool checked)
{
    ui->spinBoxLevel->setEnabled(checked);
}

void ConfigsObjNewSkillDialog::on_checkBoxGetItem_toggled(bool checked)
{
    ui->comboBoxProviderObject->setEnabled(checked);
}

void ConfigsObjNewSkillDialog::on_checkBoxAlways_pressed()
{

}

void ConfigsObjNewSkillDialog::on_checkBoxLevel_pressed()
{

}

void ConfigsObjNewSkillDialog::on_checkBoxGetItem_pressed()
{

}

void ConfigsObjNewSkillDialog::on_checkBoxAlways_released()
{
    if(ui->checkBoxAlways->isChecked()) {
        ui->checkBoxLevel->setChecked(false);
        ui->checkBoxGetItem->setChecked(false);
    } else {
        ui->checkBoxAlways->setChecked(true);
    }
}

void ConfigsObjNewSkillDialog::on_checkBoxLevel_released()
{
    if(ui->checkBoxLevel->isChecked()) {
        ui->checkBoxAlways->setChecked(false);
    } else {
        if(!ui->checkBoxGetItem->isChecked()) {
            ui->checkBoxAlways->setChecked(true);
        }
    }
}



void ConfigsObjNewSkillDialog::on_checkBoxGetItem_released()
{
    if(ui->comboBoxProviderObject->count() == 0) {
        MessageBoxes::showMessageBox(QString::fromUtf8("Nío existem itens para serem escolhidos."));
        ui->checkBoxGetItem->setChecked(false);
    }

    if(ui->checkBoxGetItem->isChecked()) {
        ui->checkBoxAlways->setChecked(false);
    } else {
        if(!ui->checkBoxLevel->isChecked()) {
            ui->checkBoxAlways->setChecked(true);
        }
    }
}


void ConfigsObjNewSkillDialog::on_buttonBox_accepted()
{
    Skill *skill = (Skill*) ui->comboBoxSkill->itemData(ui->comboBoxSkill->currentIndex(), Qt::UserRole).value<void*>();

    if(skill == NULL) {
        MessageBoxes::showMessageBox(QString::fromUtf8("Selecione uma habilidade."));
        return;
    }


    if(skill->hasObject) {
        if(((GameObject*) ui->comboBoxSkillObject->itemData(ui->comboBoxSkillObject->currentIndex(), Qt::UserRole).value<void*>()) == NULL) {
            MessageBoxes::showMessageBox(QString::fromUtf8("Um objeto deve ser selecionado."));
            return;
        }

    }

    accepeted = true;
    accept();
}


void ConfigsObjNewSkillDialog::on_buttonBox_rejected()
{
    accepeted = false;
    reject();
}

void ConfigsObjNewSkillDialog::on_toolButtonSound_pressed()
{
    SoundPickerDialog *soundPickerDialog = new SoundPickerDialog(SoundPickerDialog::SOM, this);
    soundPickerDialog->setWindowTitle(QString::fromUtf8("Som"));
    soundPickerDialog->exec();

    if(soundPickerDialog->okPressed()) {
        ui->lineEditSound->setText(QString(soundPickerDialog->getSelectedFile().c_str()));
    }


    delete soundPickerDialog;
}

void ConfigsObjNewSkillDialog::on_toolButtonRemoveSound_pressed()
{
    ui->lineEditSound->setText(QString(""));
}
