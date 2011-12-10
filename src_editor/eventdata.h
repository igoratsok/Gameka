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


#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <string>
#include <list>
#include <sstream>

#include <QString>
#include <QIcon>

#include "eventcombodataprovider.h"
#include "gamedata.h"
#include "dialoguedata.h"
#include "eventseditorcontroller.h"

class EventComboDataProvider;
class GameData;
class DialogueData;
class EventsEditorController;

/**
 * @brief Entidade para representar os dados de um evento.
 *
 */
class EventData
{
public:
    /**
     * @brief Entidade para representar os dados de um evento.
     *
     */
    EventData();

    EventData* parent; /**< Condição pai, se houver. */

    bool newEvent; /**< Se é um novo evento. */
    int type; /**< Tipo do evento: \n
                    - 0: condição;
                    - 1: ação;
                    - 2: diálogo */
    int conditionType; /**< Tipo da condição (ainda não utilizado) */
    bool negate; /**< Se o teste da condição deve ser falso. */


    int opcode; /**< Código da operação (pode ser da ação ou condição) */
    int idObject01; /**< Identificador do objeto 01 */
    int instanceTypeObject01; /**< Tipo de instância do objeto 01: \n
                                    - -1: classe;
                                    - 0: instância this
                                    - 1..n instância de contexto */
    int idAssociatedVariable; /**< Identificador da variável associada. */
    int idObject02; /**< Identificador do objeto 02 */
    int instanceTypeObject02; /**< Tipo de instância do objeto 01: \n
                                    - -1: classe;
                                    - 0: instância this
                                    - 1..n instância de contexto */
    float value01; /**< Valor 01 */
    float value02; /**< Valor 02 (não utilizado ainda) */
    float value03; /**< Valor 03 (não utilizado ainda) */
    std::string expression; /**< Expressão (não utilizada ainda) */
    std::string stringValue; /**< Valor em string, usada para músicas/som */

    int valueType; /**< Tipo de valor: \n
                        - 0: número;
                        - 1: variável;
                        - 2: atributo de objeto;
                        - 3: especial;
                        - 4: objeto 02 */

    std::list<EventData*> subEvents; /**< Lista de eventos filhos. */

    EventComboDataProvider *eventComboDataProvider; /**< Provedor de dados para os combos. */

    /**
     * @brief Obtém string descritiva do evento.
     *
     * @param EventsEditorController
     * @param currentGameObject
     */
    QString getEventString(EventsEditorController *EventsEditorController, GameObject *currentGameObject);
    /**
     * @brief Obtém o ícone do evento.
     *
     */
    QIcon getEventIcon();
    /**
     * @brief Obtém o ícone do objeto 01.
     *
     */
    QIcon getObject01Icon();
    /**
     * @brief Obtém o ícone do objeto 02.
     *
     */
    QIcon getObject02Icon();

    /**
     * @brief Adiciona um evento filho.
     *
     * @param child
     */
    void addChild(EventData *child);


    /* pendentes de gravação */
    DialogueData *dialogueData; /**<  */


    static const int TYPE_CONDITION = 0; /**<  */
    static const int TYPE_ACTION = 1; /**<  */
    static const int TYPE_DIALOGUE = 2; /**<  */

    static const int VALUE_TYPE_NUMBER = 0; /**<  */
    static const int VALUE_TYPE_VARIABLE = 1; /**<  */
    static const int VALUE_TYPE_OBJECT_ATTRIBUTE = 2; /**<  */
    static const int VALUE_TYPE_SPECIAL = 3; /**<  */
    static const int VALUE_TYPE_OBJECT2 = 4; /**<  */

    static const int TYPE_CONDITION_IF = 0; /**<  */
    static const int TYPE_CONDITION_IF_ELSE = 1; /**<  */
    static const int TYPE_CONDITION_ELSE = 2; /**<  */
    static const int TYPE_CONDITION_WHILE = 3; /**<  */
    static const int TYPE_CONDITION_FOR = 4; /**<  */
};

#endif // EVENTDATA_H
