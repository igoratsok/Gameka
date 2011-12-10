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


#ifndef CONFIGSTABWINDOW_H
#define CONFIGSTABWINDOW_H

#include <QDialog>

#include "configstilesetwidget.h"
#include "configsobjectswidget.h"
#include "configsgeneralwidget.h"
#include "configsanimations.h"
#include "configsbackgrounds.h"
#include "eventswidget.h"

#include "gameobject.h"

#include "optionscontroller.h"
#include "eventseditorcontroller.h"

class ConfigsTilesetWidget;
class ConfigsObjectsWidget;
class ConfigsGeneralWidget;
class ConfigsAnimations;
class ConfigsBackgrounds;
class EventsWidget;

class GameObject;

class OptionsController;
class EventsEditorController;



namespace Ui {
    class ConfigsTabWindow;
}

/**
 * @brief Janela para comportar a ConfigsTabWidget.
 *
 * @see ConfigsTabWidget
 */
class ConfigsTabWindow : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Construtor
     *
     * @param optionsController
     * @param eventsEditorController
     * @param parent
     */
    ConfigsTabWindow(OptionsController *optionsController, EventsEditorController *eventsEditorController, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConfigsTabWindow();

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
     * @brief Obtém a aba de eventos.
     *
     */
    EventsWidget* getEventsTab();


    /**
     * @brief Seleciona um determinado objeto e mostra na tela de configurações gerais.
     *
     * @param gameObject ponteiro para o objeto
     */
    void selectObject(GameObject *gameObject);

protected:
    /**
     * @brief
     *
     * @param e
     */
    void changeEvent(QEvent *e);

private slots:
    /**
     * @brief
     *
     */
    void on_pushButton_pressed();

private:
    Ui::ConfigsTabWindow *ui; /**<  */

    OptionsController *optionsController; /**<  */
};

#endif // CONFIGSTABWINDOW_H

