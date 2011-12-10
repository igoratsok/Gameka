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


#ifndef CONFIGSOBJNPCBEHAVIORWIDGET_H
#define CONFIGSOBJNPCBEHAVIORWIDGET_H

#include <QWidget>
#include <vector>

#include "optionscontroller.h"
#include "gameobject.h"
#include "gamedata.h"
#include "gameobject.h"

class OptionsController;
class GameObject;
class GameData;
class GameObject;

namespace Ui {
    class ConfigsObjNpcBehaviorWidget;
}

/**
 * @brief Grupo de comportamento de NPCs das configurações de objetos.
 *
 */
class ConfigsObjNpcBehaviorWidget : public QWidget
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
    explicit ConfigsObjNpcBehaviorWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjNpcBehaviorWidget();



    /**
     * @brief Popula os campos da tela.
     *
     */
    void populaCampos();



private:
    Ui::ConfigsObjNpcBehaviorWidget *ui; /**<  */
    OptionsController *optionsController; /**<  */
    GameObject *gameObject; /**<  */
    QListWidgetItem *currentListItem; /**<  */
    bool ativaMudancaCombo; /**<  */

private slots:
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinBoxPeriodicidade_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxMagicCost_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxItemEspada_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxRaioMovimentacao_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBox_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxVelocidadeMovimentacao_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxItemDirecaoPersonagem_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxItemDirecaoEstiver_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxDanoUsaEspada_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxDanoEncostaPersonagem_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxAtacaAtiraItemMagiaDirPers_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxAtacaAtiraItemMagiaDirEstiver_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxAtacaUsaEspada_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxAtacaEncostaNoPersonagem_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxDerrotaPulandoSobre_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxDerrotaAcertandoEspada_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxDerrotaAtirandoItemMagia_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxDerrotaEncostandoInimigo_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxFormaMovimentacaoNpc_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxExperiencePoints_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxPontosDerrotar_valueChanged(int );
};

#endif // CONFIGSOBJNPCBEHAVIORWIDGET_H



