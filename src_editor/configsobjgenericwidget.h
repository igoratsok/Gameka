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


#ifndef CONFIGSOBJGENERICWIDGET_H
#define CONFIGSOBJGENERICWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <stdlib.h>

#include "optionscontroller.h"
#include "gameobject.h"
#include "configsobjdadosgeraiswidget.h"
#include "configsobjhabilidadeswidget.h"
#include "configsobjphysicswidget.h"
#include "configsobjnpcbehaviorwidget.h"
#include "configsobjitem.h"
#include "configsobjattributeswidget.h"
#include "configstabwidget.h"

class OptionsController;
class GameObject;
class ConfigsObjDadosGeraisWidget;
class ConfigsObjHabilidadesWidget;
class ConfigsObjPhysicsWidget;
class ConfigsObjNpcBehaviorWidget;
class ConfigsObjAttributesWidget;
class ConfigsObjItem;
class ConfigsTabWidget;

namespace Ui {
    class ConfigsObjGenericWidget;
}

/**
 * @brief Widget de configuração dos objetos. Usado na aba de configurações de objetos,
 * ele mostra cada um dos grupos de configurações para um determinado o objeto.
 */
class ConfigsObjGenericWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    explicit ConfigsObjGenericWidget(QWidget *parent);
    /**
     * @brief
     *
     */
    ~ConfigsObjGenericWidget();



    /**
     * @brief Adiciona grupos de acordo com um objeto passado por parâmetro.
     *
     * @param optionsController controladora de opções.
     * @param gameObject objeto a ser editado.
     * @param currentListItem item da lista do objeto.
     */
    void addWidgets(OptionsController *optionsController,GameObject *gameObject, QListWidgetItem *currentListItem);
    /**
     * @brief Remove todos os grupos.
     *
     */
    void removeAllWidgets();

    /**
     * @brief Passa uma instância da ConfigsTabWidget.
     *
     * @param configsTabWidget
     */
    void setConfigsTabWidget(ConfigsTabWidget *configsTabWidget);

private:
    Ui::ConfigsObjGenericWidget *ui; /**<  */
    OptionsController *optionsController; /**<  */
    GameObject *gameObject; /**< */
    QListWidgetItem *currentListItem; /**< */
    QVBoxLayout *layout; /**< */
    QWidget *parent; /**< */
    ConfigsObjDadosGeraisWidget *configsObjDadosGeraisWidget; /**< */
    ConfigsObjAttributesWidget *configsObjAttributesWidget; /**<  */
    ConfigsObjNpcBehaviorWidget *configsObjBehaviorWidget; /**<  */
    ConfigsObjItem *configsObjItem; /**<  */
    ConfigsObjPhysicsWidget *configsObjPhysicsWidget; /**<  */
    ConfigsObjHabilidadesWidget *configsObjHabilidadesWidget; /**<  */

    ConfigsTabWidget *configsTabWidget; /**<  */

};

#endif // CONFIGSOBJGENERICWIDGET_H
