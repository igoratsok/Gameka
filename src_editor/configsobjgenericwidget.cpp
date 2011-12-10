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



#include "configsobjgenericwidget.h"
#include "ui_configsobjgenericwidget.h"

ConfigsObjGenericWidget::ConfigsObjGenericWidget(QWidget *parent) :
    QWidget(parent),
    gameObject(gameObject),
    optionsController(optionsController),
    currentListItem(currentListItem),
    ui(new Ui::ConfigsObjGenericWidget),
    parent(parent)
{
    ui->setupUi(this);

    layout = new QVBoxLayout(this);
    layout->setMargin(5);
    layout->setSpacing(0);

    configsObjDadosGeraisWidget = NULL;
    configsObjAttributesWidget = NULL;
    configsObjBehaviorWidget = NULL;
    configsObjItem = NULL;
    configsObjPhysicsWidget = NULL;
    configsObjHabilidadesWidget = NULL;

    configsTabWidget = NULL;


}

void ConfigsObjGenericWidget::addWidgets(OptionsController *optionsController,GameObject *gameObject, QListWidgetItem *currentListItem) {

    configsObjDadosGeraisWidget = new ConfigsObjDadosGeraisWidget(optionsController, gameObject, currentListItem, parent);
    layout->addWidget(configsObjDadosGeraisWidget);



    if(gameObject->type == GameObject::NPC ||
       gameObject->type == GameObject::INIMIGO) {
        configsObjBehaviorWidget = new ConfigsObjNpcBehaviorWidget(optionsController, gameObject, currentListItem, parent);
        layout->addWidget(configsObjBehaviorWidget);
    } else if(gameObject->type == GameObject::ITEM) {
        configsObjItem = new ConfigsObjItem(optionsController, gameObject, currentListItem, parent);
        layout->addWidget(configsObjItem);
    } else {
        configsObjPhysicsWidget = new ConfigsObjPhysicsWidget(optionsController, gameObject, currentListItem, parent);
        layout->addWidget(configsObjPhysicsWidget);
    }

    if(gameObject->type != GameObject::ITEM && gameObject->type != GameObject::NPC) {
        configsObjAttributesWidget = new ConfigsObjAttributesWidget(optionsController, gameObject, currentListItem, parent);
        layout->addWidget(configsObjAttributesWidget);
    }

    configsObjHabilidadesWidget = new ConfigsObjHabilidadesWidget(optionsController, gameObject, currentListItem, parent);
    configsObjHabilidadesWidget->setConfigsTabWidget(configsTabWidget);
    layout->addWidget(configsObjHabilidadesWidget);
}

void ConfigsObjGenericWidget::removeAllWidgets() {
    if(configsObjDadosGeraisWidget != NULL) {
        layout->removeWidget(configsObjDadosGeraisWidget);

        if(!configsObjDadosGeraisWidget->executandoTroca) {
            delete configsObjDadosGeraisWidget;
        } else {
            configsObjDadosGeraisWidget->setVisible(false);
        }

        configsObjDadosGeraisWidget = NULL;
    }


    if(configsObjAttributesWidget != NULL) {
        layout->removeWidget(configsObjAttributesWidget);

        delete configsObjAttributesWidget;
        configsObjAttributesWidget = NULL;
    }


    if(configsObjBehaviorWidget != NULL) {
        layout->removeWidget(configsObjBehaviorWidget);

        delete configsObjBehaviorWidget;
        configsObjBehaviorWidget = NULL;
    }

    if(configsObjItem != NULL) {
        layout->removeWidget(configsObjItem);

        delete configsObjItem;
        configsObjItem = NULL;
    }

    if(configsObjPhysicsWidget != NULL) {
        layout->removeWidget(configsObjPhysicsWidget);

        delete configsObjPhysicsWidget;
        configsObjPhysicsWidget = NULL;
    }


    if(configsObjHabilidadesWidget != NULL) {
        layout->removeWidget(configsObjHabilidadesWidget);

        delete configsObjHabilidadesWidget;
        configsObjHabilidadesWidget = NULL;
    }
}

ConfigsObjGenericWidget::~ConfigsObjGenericWidget()
{
    delete ui;
}

void ConfigsObjGenericWidget::setConfigsTabWidget(ConfigsTabWidget *configsTabWidget) {
    this->configsTabWidget = configsTabWidget;
}
