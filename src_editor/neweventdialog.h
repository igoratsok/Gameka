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


#ifndef NEWEVENTDIALOG_H
#define NEWEVENTDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <sstream>

#include "gamedata.h"
#include "gameobject.h"
#include "eventseditorcontroller.h"
#include "eventattributedata.h"
#include "messageboxes.h"
#include "eventdata.h"

class GameData;
class GameObject;
class EventsEditorController;
class EventAttributeData;
class MessageBoxes;
class EventData;

namespace Ui {
    class NewEventDialog;
}

/**
 * @brief Janela de novo evento. Pode ser uma condição ou uma ação.
 *
 */
class NewEventDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param eventsEditorController controlador do editor de eventos.
     * @param eventData EventData que está sendo editado.
     * @param gameObject GameObject a que pertence o GameData. Se for NULL significa que é um evento global.
     * @param type Tipo: \n
                - 0: condição;
                - 1: ação;
     * @param conditionType Tipo da condição: ainda não implementado.
     * @param parent
     */
    explicit NewEventDialog(EventsEditorController *eventsEditorController, EventData *eventData, GameObject *gameObject, int type, int conditionType = 0, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~NewEventDialog();

    /**
     * @brief Popula as listas de objetos.
     *
     */
    void populaListaObjects();
    /**
     * @brief Popula as combos de atributos com os atributos com os atributos do objeto selecionado.
     *
     */
    void populaComboAtributos();
    /**
     * @brief Popula a combo de condições com base no atributo selecionado, se o evento for uma condição.
     *
     */
    void populaComboConditions();
    /**
     * @brief Popula a combo de ações com base no atributo selecionado, se o evento for uma ação.
     *
     */
    void populaComboActions();
    /**
     * @brief Habilita o grupo de valores.
     *
     */
    void habilitaGroupValues();
    /**
     * @brief Popula a combo de variáveis com as variáveis globais e do objeto (se for um evento de objeto).
     *
     */
    void populaComboVariables();
    /**
     * @brief Popula combo de valores especiais.
     *
     * @param type
     *
     * @see SpecialComboValueData
     */
    void populaComboSpecial(int type);

    /**
     * @brief Popula combo de atributos do objeto 02 selecionado.
     *
     */
    void populaComboAtributosObject02();

    /**
     * @brief Preenche os campos.
     *
     */
    void preencheCampos();

    /**
     * @brief Libera espaço dos attributesData obtidos.
     *
     */
    void freeAttributeData();

private slots:
    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidgetObject1_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

    /**
     * @brief
     *
     * @param index
     */
    void on_comboBoxAttrib_currentIndexChanged(int index);

    /**
     * @brief
     *
     * @param index
     */
    void on_comboBoxCondit_currentIndexChanged(int index);

    /**
     * @brief
     *
     * @param current
     * @param previous
     */
    void on_listWidgetObject2_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);

    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxNumber_toggled(bool checked);

    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxVariable_toggled(bool checked);

    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxFieldObject02_toggled(bool checked);

    /**
     * @brief Ao aceitar, coloca todos os valores na EventData adequadamente a aceita.
     *
     */
    void on_buttonBox_2_accepted();

    /**
     * @brief
     *
     */
    void on_buttonBox_2_rejected();

    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxNegate_toggled(bool checked);

private:
    Ui::NewEventDialog *ui; /**<  */
    EventsEditorController *eventsEditorController; /**<  */
    EventData *eventData; /**<  */
    GameObject *gameObject; /**<  */
    int type; /**<  Tipo: \n
                - 0: condição;
                - 1: ação; */
    int conditionType; /**< Tipo da condição. Ainda não implementado. */
};

#endif // NEWEVENTDIALOG_H

