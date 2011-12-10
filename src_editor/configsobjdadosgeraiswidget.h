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


#ifndef CONFIGSOBJDADOSGERAISWIDGET_H
#define CONFIGSOBJDADOSGERAISWIDGET_H

#include <QWidget>

#include "optionscontroller.h"
#include "gameobject.h"
#include "messageboxes.h"

#include "configsobjanimationchooserwindow.h"

class OptionsController;
class MessageBoxes;
class GameObject;
class ConfigsObjAnimationChooserWindow;

namespace Ui {
    class ConfigsObjDadosGeraisWidget;
}

/**
 * @brief Grupo de "Dados Gerais" das configurações de um objeto.
 *
 */
class ConfigsObjDadosGeraisWidget : public QWidget
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
    explicit ConfigsObjDadosGeraisWidget(OptionsController *optionsController, GameObject *gameObject, QListWidgetItem *currentListItem, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjDadosGeraisWidget();

    bool executandoTroca; /**< Mecanismo para troca de tipo de objeto. */

private:
    Ui::ConfigsObjDadosGeraisWidget *ui; /**<  */
    OptionsController *optionsController; /**<  */
    GameObject *gameObject; /**<  */
    QListWidgetItem *currentListItem; /**<  */
    QGraphicsPixmapItem *item; /**<  */
    QGraphicsScene *scene; /**<  */
    bool ativaTrocaCombos; /**< Mecanismo para troca de combos só após tudo ter sido preenchido. */

private slots:
    /**
     * @brief
     *
     */
    void on_botaoEditarFormaGrafica_clicked();
    /**
     * @brief
     *
     * @param index
     */
    void on_comboFormaGrafica_currentIndexChanged(int index);
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxObjUnico_toggled(bool checked);
    /**
     * @brief
     *
     * @param QString
     */
    void on_editNome_textChanged(QString );
    /**
     * @brief
     *
     * @param checked
     */
    void on_checkBoxDrag_toggled(bool checked);
    /**
     * @brief
     *
     * @param index
     */
    void on_comboTipo_currentIndexChanged(int index);
};

#endif // CONFIGSOBJDADOSGERAISWIDGET_H


