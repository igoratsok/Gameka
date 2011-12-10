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


#ifndef CONFIGSOBJITEM_H
#define CONFIGSOBJITEM_H

#include <QWidget>
#include <sstream>

#include "optionscontroller.h"
#include "gameobject.h"

class OptionsController;
class GameObject;


namespace Ui {
    class ConfigsObjItem;
}

/**
 * @brief Grupo "Item" de configurações de objetos.
 *
 */
class ConfigsObjItem : public QWidget
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
    explicit ConfigsObjItem(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjItem();

    /**
     * @brief Popula campos.
     *
     */
    void populaCampos();
    /**
     * @brief Popula combos de eventos.
     *
     */
    void populaComboEvents();
    /**
     * @brief Popula combos de variáveis.
     *
     */
    void populaComboVariables();





private:
    Ui::ConfigsObjItem *ui; /**<  */
    OptionsController *optionsController; /**< */
    GameObject *gameObject; /**< TODO */
    QListWidgetItem *currentListItem; /**<  */

    bool enableComboChange; /**<  */


private slots:
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxConcedeHabilidade_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxConcedeHabilidade_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxComportamentoDesapareceEncParedes_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxComportamentoDesapareceEncPers_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboMovimentacaoItem_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_radioButtonEnviaInventario_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_radioButtonAtivaEfeitoImediatamente_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxAtivaEvento_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxIncrementaVariavel_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboBoxIncrementaVariavel_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxGanhaPerdeMagia_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxGanhaPerdeVida_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param int
     */
    void on_spinBoxConcedePontos_valueChanged(int );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxAtivaEvento_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxIncrementaVariavel_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxGanhaPerdeMagia_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxGanhaPerdeVida_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBoxConcedePontos_toggled(bool checked);
};

#endif // CONFIGSOBJITEM_H
