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


#ifndef CONFIGSOBJNEWSKILLDIALOG_H
#define CONFIGSOBJNEWSKILLDIALOG_H

#include <QDialog>

#include "gamedata.h"
#include "skilldata.h"
#include "gameobject.h"
#include "messageboxes.h"
#include "soundpickerdialog.h"
#include "optionscontroller.h"

class GameData;
class SkillData;
class GameObject;
class MessageBoxes;
class SoundPickerDialog;
class OptionsController;

namespace Ui {
    class ConfigsObjNewSkillDialog;
}

/**
 * @brief Tela de edição de habilidades.
 *
 */
class ConfigsObjNewSkillDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param optionsController a controladora de opções
     * @param gameObject o objeto cuja habilidade está sendo adicionada/editada.
     * @param skillData
     * @param parent
     */
    explicit ConfigsObjNewSkillDialog(OptionsController* optionsController, GameObject *gameObject, SkillData *skillData = 0, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjNewSkillDialog();

    /**
     * @brief Executa a janela e retorna uma instância da SkillData criada/editada. Retorna NULL se cancelar.
     *
     */
    SkillData *exec();

private:
    /**
     * @brief Preeenche os campos da tela.
     *
     * @param skillData
     */
    void preencheCampos(SkillData *skillData);
    /**
     * @brief Popula as combos de objetos.
     *
     */
    void populaComboObjetos();
    /**
     * @brief Popula as combos de habilidades.
     *
     */
    void populaComboHabilidades();

    Ui::ConfigsObjNewSkillDialog *ui; /**<  */
    SkillData *skillData; /**<  */
    GameObject *gameObject; /**<  */
    OptionsController *optionsController; /**<  */
    bool accepeted; /**<  */

private slots:
    /**
     * @brief
     *
     */
    void on_buttonBox_rejected();
    /**
     * @brief
     *
     */
    void on_buttonBox_accepted();
    /**
     * @brief
     *
     */
    void on_checkBoxGetItem_released();
    /**
     * @brief
     *
     */
    void on_checkBoxAlways_released();
    /**
     * @brief
     *
     */
    void on_checkBoxLevel_released();
    /**
     * @brief
     *
     */
    void on_checkBoxGetItem_pressed();
    /**
     * @brief
     *
     */
    void on_checkBoxLevel_pressed();
    /**
     * @brief
     *
     */
    void on_checkBoxAlways_pressed();
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxGetItem_toggled(bool checked);
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxLevel_toggled(bool checked);
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxAlways_toggled(bool checked);
    /**
     * @brief
     *
     * @param index
     */
    void on_comboBoxSkill_currentIndexChanged(int index);
    /**
     * @brief
     *
     */
    void on_toolButtonSound_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonRemoveSound_pressed();
};

#endif // CONFIGSOBJNEWSKILLDIALOG_H
