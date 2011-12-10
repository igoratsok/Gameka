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


#ifndef CONFIGSTABWIDGET_H
#define CONFIGSTABWIDGET_H

#include <QTabWidget>


#include "optionscontroller.h"
#include "configstilesetwidget.h"
#include "configsobjectswidget.h"
#include "configsgeneralwidget.h"
#include "configsanimations.h"
#include "configsbackgrounds.h"
#include "eventswidget.h"

class OptionsController;
class ConfigsTilesetWidget;
class ConfigsObjectsWidget;
class ConfigsGeneralWidget;
class ConfigsAnimations;
class ConfigsBackgrounds;
class EventsWidget;

namespace Ui {
    class ConfigsTabWidget;
}

/**
 * @brief Widget contendo a tela de condigurações gerais e todas as abas correspondentes.
 *
 */
class ConfigsTabWidget : public QTabWidget {
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param parent
     */
    ConfigsTabWidget(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsTabWidget();

    /**
     * @brief Fornecimento da controladora de opções para chamadas na camada de negócio.
     *
     * @param optionsController a controladora de opções.
     */
    void setOptionsController(OptionsController *optionsController);

    /**
     * @brief Obtém a aba de tilesets.
     *
     */
    ConfigsTilesetWidget* getTilesetTab();

    /**
     * @brief Obtém a aba de objetos.
     *
     */
    ConfigsObjectsWidget* getObjectTab();

    /**
     * @brief Obtém a aba de dados gerais.
     *
     */
    ConfigsGeneralWidget* getDadosGeraisTab();

    /**
     * @brief Obtém a aba de animações.
     *
     */
    ConfigsAnimations* getAnimationsTab();

    /**
     * @brief Obtém a aba de fundos.
     *
     */
    ConfigsBackgrounds* getBackgroundsTab();

    /**
     * @brief Obtém a aba de
     *
     */
    EventsWidget* getEventsTab();

    /**
     * @brief Seleciona um determinado objeto e mostra na tela de configurações gerais.
     *
     * @param gameObject ponteiro para o objeto
     */
    void selectObject(GameObject *gameObject);
    /**
     * @brief Seleciona um determinado objeto e mostra na tela de configurações gerais.
     *
     * @param idObject identificador do objeto
     */
    void selectObjectEvent(int idObject);

protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private:
    Ui::ConfigsTabWidget *ui; /**<  */

    OptionsController *optionsController; /**<  */
};

#endif // CONFIGSTABWIDGET_H
