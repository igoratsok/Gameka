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


#ifndef CONFIGSOBJPHYSICSWIDGET_H
#define CONFIGSOBJPHYSICSWIDGET_H

#include <QWidget>
#include <list>

#include "optionscontroller.h"
#include "gameobject.h"



class OptionsController;
class GameObject;

namespace Ui {
    class ConfigsObjPhysicsWidget;
}

/**
 * @brief Grupo de "Física" das configurações de objetos.
 *
 */
class ConfigsObjPhysicsWidget : public QWidget
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
    explicit ConfigsObjPhysicsWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjPhysicsWidget();

    /**
     * @brief Popula combo de objetos que rebatem um BouncingBall.
     *
     */
    void populaComboObjectsToBounce();

    /**
     * @brief Popula lista de objetos que foram adicionados para rebater uma BouncingBall.
     *
     */
    void populaListaObjectsToBounce();


private:
    Ui::ConfigsObjPhysicsWidget *ui; /**<  */
    OptionsController *optionsController; /**<  */
    GameObject *gameObject; /**<  */
    QListWidgetItem *currentListItem; /**<  */

private slots:
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinCarVA_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param checked
     */
    void on_checkBox_toggled(bool checked);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinMouseObjectDA_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinMouseObjectA_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinMouseObjectV_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboFormaMovimentoMouseObject_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboTipoMovimentoMouseObject_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinBouncingBallVY_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinBouncingBallVX_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinPlatformerIntensidadePulo_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinPlatformerG_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinPlatformerA_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinPlatformerV_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboTipoMovimentoPlatformer_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinCarDA_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinCarA_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinCarV_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboTipoMovimento_2_currentIndexChanged(int index);
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinDay_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinDax_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinAy_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinAx_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinVy_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param double
     */
    void on_spinVx_valueChanged(double );
    /**
     * @brief Evento de atualização de valor.
     *
     * @param index
     */
    void on_comboTipoMovimento_currentIndexChanged(int index);

    /**
     * @brief Evento de atualização de valor.
     *
     */
    void on_pushButtonAddObjectsToBounce_pressed();

    /**
     * @brief Evento de atualização de valor.
     *
     */
    void on_pushButtonRemoveObjectsToBounce_pressed();
};

#endif // CONFIGSOBJPHYSICSWIDGET_H



