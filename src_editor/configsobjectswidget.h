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


#ifndef CONFIGSOBJECTSWIDGET_H
#define CONFIGSOBJECTSWIDGET_H

#include <QWidget>
#include <vector>
#include <QListWidgetItem>

#include "optionscontroller.h"
#include "configsnewobjectwindow.h"
#include "gamedata.h"
#include "gameobject.h"
#include "configsobjgenericwidget.h"
#include "configstabwidget.h"
#include "messageboxes.h"

class ConfigsNewObjectWindow;
class OptionsController;
class GameData;
class GameObject;
class ConfigsObjGenericWidget;
class ConfigsTabWidget;
class MessageBoxes;


namespace Ui {
    class ConfigsObjectsWidget;
}

/**
 * @brief Aba de configurações de objetos.
 *
 */
class ConfigsObjectsWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    ConfigsObjectsWidget(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsObjectsWidget();

    /**
     * @brief Fornece a controladora de opções para chamadas na camada de negócio.
     *
     * @param optionsController controladora de opções.
     */
    void setOptionsController(OptionsController *optionsController);
    /**
     * @brief Popula a lista de objetos.
     *
     */
    void populaListaPersonagem();

    /**
     * @brief Seleciona um determinado objeto.
     *
     * @param gameObject objeto a ser selecionado.
     */
    void selectObject(GameObject *gameObject);
    /**
     * @brief Passa uma isntância da ConfigsTabWidget.
     *
     * @param configsTabWidget
     */
    void setConfigsTabWidget(ConfigsTabWidget *configsTabWidget);




protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::ConfigsObjectsWidget *ui; /**<  */
    ConfigsObjGenericWidget *specificWidget; /**< O widget contendo as configurações do objeto escolhido na lista. */
    ConfigsNewObjectWindow *configsNewObjectWindow; /**<  */
    OptionsController *optionsController; /**<  */
    ConfigsTabWidget *configsTabWidget; /**<  */

private slots:
    /**
     * @brief Evento ativado quando um item da lista de objetos é escolhido.
     * Isto irá adicionar todos os widgets de configuração necessários
     * para a edição do personagem, no lado direito da tela (em specificWidget).
     *
     * @param current
     * @param previous
     */
    void on_listPersonagem_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    /**
     * @brief
     *
     */
    void on_pushButton_clicked();
    /**
     * @brief
     *
     */
    void on_pushButton_pressed();
    void on_removeObject_pressed();
};

#endif // CONFIGSOBJECTSWIDGET_H

