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


#ifndef EVENTSEDITORCONTROLLER_H
#define EVENTSEDITORCONTROLLER_H

#include <list>

#include "maincontroller.h"

#include "gamedata.h"
#include "eventdata.h"
#include "neweventdialog.h"
#include "eventcombodataprovider.h"
#include "eventattributedata.h"
#include "gameobject.h"
#include "proceduredata.h"
#include "map.h"
#include "variabledata.h"
#include "specialcombovaluedata.h"

class MainController;

class GameData;
class EventData;
class NewEventDialog;
class EventComboDataProvider;
class EventAttributeData;
class GameObject;
class ProcedureData;
class Map;
class VariableData;
class SpecialComboValueData;

/**
 * @brief Controladora do editor de eventos. Contém funções quanto a camada de negócio no módulo
 * do editor de eventos.
 *
 */
class EventsEditorController
{
public:
    /**
     * @brief Construtor.
     *
     */
    EventsEditorController();

    /**
     * @brief Fornece ponteiro para a controladora principal.
     *
     * @param
     */
    void setMainController(MainController*);
    /**
     * @brief Abre uma janela de nova condição.
     *
     * @param eventData Evento a ser criado.
     * @param gameObject Objeto do evento (pode ser NULL, se for global)
     */
    void openNewConditionWindow(EventData *eventData, GameObject *gameObject);
    /**
     * @brief Abre uma janela de nova ação.
     *
     * @param eventData Evento a ser criado.
     * @param gameObject Objeto do evento (pode ser NULL, se for global)
     */
    void openNewActionWindow(EventData *eventData, GameObject *gameObject);
    /**
     * @brief Abre janela de editar evento.
     *
     * @param eventData Evento a ser editado.
     * @param gameObject Objeto do evento (pode ser NULL, se for global)
     */
    void openEditEventWindow(EventData *eventData, GameObject *gameObject);
    /**
     * @brief Abre uma jenela de novo diálogo.
     *
     * @param eventData
     */
    void openNewDialogueDialog(EventData *eventData);

    /**
     * @brief Adiciona um procedimento global no projeto.
     *
     */
    ProcedureData* addProcedure();
    /**
     * @brief Adiciona um procedimento a um objeto.
     *
     * @param gameObject O objeto a adicionar o procedimento.
     */
    ProcedureData* addProcedure(GameObject *gameObject);
    /**
     * @brief Adiciona um procedimento a um mapa.
     *
     * @param map Mapa no qual o procedimento será adicionado.
     */
    ProcedureData* addProcedure(Map *map);

    /**
     * @brief Obtém a combo de atributos de um objeto.
     *
     * @param gameObject
     * @param eventType
     */
    std::list<EventAttributeData*> getComboAttributes(GameObject *gameObject, int eventType);
    /**
     * @brief Obtém a string de uma condição.
     *
     * @param index
     */
    QString getComboConditionString(int index);
    /**
     * @brief Obtém a string de uma ação.
     *
     * @param index
     */
    QString getComboActionString(int index);
    /**
     * @brief Obtém os objetos de contexto de um evento.
     *
     * @param eventData
     */
    std::vector<GameObject*> getContextObjects(EventData *eventData);
    /**
     * @brief Obtém os objetos especiais.
     *
     * @param eventType
     */
    std::list<GameObject*> getSpecialGameObjects(int eventType);
    /**
     * @brief Obtém os valores dos combos de atributos especiais.
     *
     * @param specialType
     * @param gameObject
     *
     * @see SpecialComboValueData
     */
    std::list<SpecialComboValueData*> getSpecialComboValueList(int specialType, GameObject *gameObject);

    /**
     * @brief Obtém a lista de objetos.
     *
     */
    std::vector<GameObject*>* getObjectList();
    /**
     * @brief Obtém a lista de Tilesets.
     *
     */
    std::vector<TileSet*>* getTilesetList();
    /**
     * @brief Obtém a lista de mapas.
     *
     */
    std::vector<Map*>* getMaplist();
    /**
     * @brief Obtém a lista de animações.
     *
     */
    std::vector<AnimationData*>* getAnimationDataList();
    /**
     * @brief Obtém a lista de variáveis.
     *
     */
    std::vector<VariableData*>* getGlobalVariableDataList();
    /**
     * @brief Obtém a lista de procedimentos.
     *
     */
    std::vector<ProcedureData*>* getGlobalProcedureList();

    /**
     * @brief Verifica se uma ação é especificamente sem valor.
     *
     * @param action
     */
    bool isNoValueAction(int action);
    /**
     * @brief Verifica se uma condição é especificamente sem valor.
     *
     * @param condition
     */
    bool isNoValueCondition(int condition);




private:
    /**
     * @brief Adiciona um procedimento em um objeto ou mapa.
     *
     * @param gameObject Objeto a ser adicionado, pode ser NULL se for mapa ou global.
     * @param map Objeto a ser adicionado, pode ser NULL se for mapa ou global.
     */
    ProcedureData* addProcedure(GameObject *gameObject, Map *map);


    MainController *mainController; /**< */
    EventComboDataProvider *eventComboDataProvider; /**<  */
};

#endif // EVENTSEDITORCONTROLLER_H
