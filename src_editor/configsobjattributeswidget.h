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


#ifndef CONFIGSOBJATTRIBUTESWIDGET_H
#define CONFIGSOBJATTRIBUTESWIDGET_H

#include <QWidget>
#include <sstream>
#include <string>

#include "optionscontroller.h"
#include "gameobject.h"

class OptionsController;
class GameObject;


namespace Ui {
    class ConfigsObjAttributesWidget;
}

/**
 * @brief Grupo de "Atributos" das configurações de um objeto. Contém
 * edições como vida, magia, defesa, ataque e inteligência,
 * além de configurações de nível.
 *
 */
class ConfigsObjAttributesWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param optionsController controladora de opções.
     * @param gameObject objeto sendo editado.
     * @param currentListItem item do objeto sendo editado.
     * @param parent
     */
    explicit ConfigsObjAttributesWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjAttributesWidget();



    /**
     * @brief Decide visibilidade da parte de evolução por nível.
     *
     */
    void decideLevelEvolutionVisibility();
    /**
     * @brief Popula os campos.
     *
     */
    void populaCampos();

private:
    Ui::ConfigsObjAttributesWidget *ui; /**<  */
    OptionsController *optionsController; /**<  */
    GameObject *gameObject; /**<  */
    QListWidgetItem *currentListItem; /**<  */

private slots:
    /**
     * @brief
     *
     * @param value
     */
    void on_horizontalSliderEvolutionVelocity_valueChanged(int value);

    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxMaxLevel_valueChanged(int );

    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxInitialLevel_valueChanged(int );

    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxInt_valueChanged(int );

    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxDef_valueChanged(int );

    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxAtk_valueChanged(int );

    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxMp_valueChanged(int );

    /**
     * @brief
     *
     * @param int
     */
    void on_spinBoxHp_valueChanged(int );

    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxLevelEvolution_toggled(bool checked);
};

#endif // CONFIGSOBJATTRIBUTESWIDGET_H

