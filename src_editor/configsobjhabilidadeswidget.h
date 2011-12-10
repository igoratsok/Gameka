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


#ifndef CONFIGSOBJHABILIDADESWIDGET_H
#define CONFIGSOBJHABILIDADESWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTreeWidgetItem>

#include <sstream>

#include "optionscontroller.h"
#include "gameobject.h"
#include "configsobjnewskilldialog.h"
#include "skilldata.h"
#include "configstabwidget.h"
#include "soundpickerdialog.h"

class OptionsController;
class GameObject;
class ConfigsObjNewSkillDialog;
class SkillData;
class ConfigsTabWidget;
class SoundPickerDialog;

namespace Ui {
    class ConfigsObjHabilidadesWidget;
}

/**
 * @brief Grupo de "Habilidades" das configurações de objetos.
 *
 */
class ConfigsObjHabilidadesWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param optionsController controladora de opções.
     * @param gameObject objeto sendo editado.
     * @param currentListItem item da lista do objeto sendo editado.
     * @param parent
     */
    explicit ConfigsObjHabilidadesWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjHabilidadesWidget();

    /**
     * @brief Passa uma instância da ConfigsTabWidget.
     *
     * @param configsTabWidget
     */
    void setConfigsTabWidget(ConfigsTabWidget *configsTabWidget);

private:
    Ui::ConfigsObjHabilidadesWidget *ui; /**<  */

    OptionsController *optionsController; /**< */
    GameObject *gameObject; /**<  */
    QListWidgetItem *currentListItem; /**<  */
    ConfigsTabWidget *configsTabWidget; /**< */

    /**
     * @brief Popula a lista de habilidades.
     *
     */
    void populaListaSkills();

private slots:
    /**
     * @brief Evento para editar uma habilidade da lista. Chamado ao pressionar botão "Editar".
     *
     */
    void on_pushButtonEdit_pressed();
    /**
     * @brief Evento para remover uma habilidade da lista. Chamado ao pressionar botão "Remover".
     *
     */
    void on_pushButtonRemove_pressed();

    /**
     * @brief Evento ao escolher um item da lista de habilidades.
     *
     * @param current
     * @param previous
     */
    void on_listHabilidades_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

    /**
     * @briefonar".
     *
     */
    void on_botaoAddHabilidade_pressed();
    /**
     * @brief
     *
     */
    void on_botaoEditorEventos_clicked();
    /**
     * @brief Evento para adicionar uma habilidade da lista. Chamado ao pressionar botão "Adicionar".
     *
     */
    void on_botaoAddHabilidade_clicked();
    /**
     * @brief
     *
     */
    void on_botaoOpcoes_clicked();
    /**
     * @brief
     *
     * @param index
     */
    void on_comboEvoNivel_currentIndexChanged(int index);
    /**
     * @brief
     *
     */
    void on_botaoEditorEventos_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonDamageSound_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonSpecialSound_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonRemoveDamageSound_pressed();
    /**
     * @brief
     *
     */
    void on_toolButtonRemoveSpecialSound_pressed();
};

#endif // CONFIGSOBJHABILIDADESWIDGET_H





