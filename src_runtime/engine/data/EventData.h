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
#include <algorithm>
#include <deque>

#include "DialogueData.h"
#include "ProcedureData.h"
#include "VariableData.h"
#include "GameObjectClass.h"
#include "GameData.h"
#include "GameObject.h"

class DialogueData;
class ProcedureData;
class VariableData;
class GameObjectClass;
class GameData;
class GameObject;
class GameObject;

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
	virtual ~EventData();

        EventData* parent;  /**< Condição pai, se houver. */

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

	unsigned long long int everyTimer;

        std::list<EventData*> subEvents;  /**< Lista de eventos filhos. */

	// exclusivos do runtime abaixo
        GameObjectClass *object01; /**< Ponteiro para a classe da classe do objeto 01. */
        GameObjectClass *object02; /**< Ponteiro para a classe da classe do objeto 01. */
        ProcedureData *procedureToCall; /**< Ponteiro para o procedimento a ser chamado,
                            se for uma chamada a procedimento. */
        VariableData *variableValue; /**< Ponteiro para a variável a ser usada, se aplicar. */

        DialogueData *dialogueData; /**< Ponteiro para o diálogo a ser mostrado, se aplicar. */

        /**
         * @brief Ponteiro para a função de executar.
         *
         * @param
         * @param
         * @param
         * @param dt
         */
        std::list<std::vector<GameObject*> >* (*execute)(EventData*, std::deque<std::vector<GameObject*> >*, GameObject*, int dt);

	static const int TYPE_CONDITION = 0;
	static const int TYPE_ACTION = 1;
	static const int TYPE_DIALOGUE = 2;



	static const int COND_EQUAL                 = 0;
	static const int COND_DIFFERENT             = 1;
	static const int COND_LESS                  = 2;
	static const int COND_LESS_EQUAL            = 3;
	static const int COND_GREATER               = 4;
	static const int COND_GREATER_EQUAL         = 5;

	static const int COND_DETECT_SIMPLE_COLLISION   = 6;
	static const int COND_DETECT_PIXEL_COLLISION    = 7;

	static const int COND_BUTTON_PRESSED        = 8;
	static const int COND_BUTTON_DOWN           = 9;
	static const int COND_MOUSE_BUTTON_PRESSED  = 10;
	static const int COND_MOUSE_BUTTON_DOWN     = 11;

	static const int COND_IS_MUSIC_PLAYING      = 12;
	static const int COND_IS_SOUND_PLAYING      = 13;

	static const int COND_IS_CURRENT_MAP        = 14;

	static const int COND_EVERY_SECONDS         = 15; // x (pendente)

	static const int COND_IS_LEFT_SIDE          = 16;
	static const int COND_IS_UP_SIDE            = 17;
	static const int COND_IS_RIGHT_SIDE         = 18;
	static const int COND_IS_DOWN_SIDE          = 19;



	static const int ACTION_SET_VALUE           = 0;
	static const int ACTION_ADD_VALUE           = 1;
	static const int ACTION_MULT_VALUE          = 2;
	static const int ACTION_DIV_VALUE           = 3;

	static const int ACTION_PLAY_MUSIC          = 4;
	static const int ACTION_TOOGLE_PAUSE_MUSIC  = 5;
	static const int ACTION_STOP_MUSIC          = 6;
	static const int ACTION_PLAY_SOUND          = 7;
	static const int ACTION_TOGGLE_PAUSE_SOUND  = 8;
	static const int ACTION_STOP_SOUND          = 9;

	static const int ACTION_SET_MAP             = 10;
	static const int ACTION_RESET_MAP           = 11;

	// fiz até aqui, a partir de agora fiz alguns (os com o //x)

	static const int ACTION_CALL_PROCEDURE      = 12;

	static const int ACTION_RESET_MAP_TIMER     = 13;
	static const int ACTION_RESET_GAME_TIMER    = 14;

	static const int ACTION_PLATFORM_JUMP       = 15; // x

	static const int ACTION_BOUNCE              = 16;
	static const int ACTION_BOOST               = 17;

	static const int ACTION_THROW_OBJECT               = 18;

	static const int ACTION_FOLLOW_OBJECT              = 19;
	static const int ACTION_UNFOLLOW_OBJECT             = 20;

	static const int ACTION_NEXT_MAP                    = 21;


protected:
private:
};

#endif // EVENTDATA_H
