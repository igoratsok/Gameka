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


#ifndef EVENTCOMBODATAPROVIDER_H
#define EVENTCOMBODATAPROVIDER_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <QString>
#include <QList>

#include "eventattributedata.h"
#include "gameobject.h"
#include "specialcombovaluedata.h"
#include "gamedata.h"
#include "map.h"
#include "eventseditorcontroller.h"

class EventAttributeData;
class GameObject;
class SpecialComboValueData;
class GameData;
class Map;
class EventsEditorController;

/**
 * @brief Fornece a janela de novo evento dados para as combos, como atributos e suas condições, além de dados
 * para saber o que habilitar ou não. É um singleton.
 *
 */
class EventComboDataProvider
{
public:

    /**
     * @brief Obtém isntância.
     *
     */
    static EventComboDataProvider* getInstance();

    /**
     * @brief Obtém um atributo por índice.
     *
     * @param index
     */
    EventAttributeData* getAttribute(int index);
    /**
     * @brief Obtém uma string de uma condição.
     *
     * @param index
     */
    QString getConditionString(int index);
    /**
     * @brief Obtém uma string de uma ação.
     *
     * @param index
     */
    QString getActionString(int index);
    /**
     * @brief Obtém a lista de objetos especiais. (Global, Timer, Música/Som, Joystick)
     *
     * @param eventType
     */
    std::list<GameObject*> getSpecialObjectList(int eventType);

    static const int COMBO_TYPE_NONE            = 0; /**<  */
    static const int COMBO_TYPE_KEY             = 4; /**<  */
    static const int COMBO_TYPE_MOUSE           = 5; /**<  */
    static const int COMBO_TYPE_MUSIC           = 6; /**<  */
    static const int COMBO_TYPE_SOUND           = 7; /**<  */
    static const int COMBO_TYPE_MAP             = 8; /**< */
    static const int COMBO_TYPE_PROCEDURE             = 9; /**<  */
    /**
     * @brief Obtém a lista de valores da combo para atributos especiais.
     *
     * @param eventsEditorController Controladora de editor de eventos
     * @param specialType Tipo especial: \n
                        - 0: nenhum;
                        - 4: tecla;
                        - 5: mouse;
                        - 6: música;
                        - 7: som;
                        - 8: mapa;
                        - 9: procedimento;
     * @param gameObject Objeto relacionado ao evento
     */
    std::list<SpecialComboValueData*> getSpecialComboValueList(EventsEditorController *eventsEditorController, int specialType, GameObject *gameObject);

    /**
     * @brief Se é uma ação excepcionalmente sem valor.
     *
     * @param action Identificador da ação.
     */
    bool isNoValueAction(int action);
    /**
     * @brief Se é uma  condição excepcionalmente sem valor.
     *
     * @param condition Identificador da condição.
     */
    bool isNoValueCondition(int condition);



    static const int ID_SPECIAL_GLOBAL =    -1; /**<  */
    static const int ID_SPECIAL_JOYSTICK =  -2; /**<  */
    static const int ID_SPECIAL_TIMER =     -3; /**<  */
    static const int ID_SPECIAL_MUSIC =     -4; /**<  */

    static const int ATT_POSITION_X =       0; /**<  */
    static const int ATT_POSITION_Y =       1; /**<  */
    static const int ATT_VELOCITY =         2; /**<  */
    static const int ATT_VELOCITY_X =       3; /**<  */
    static const int ATT_VELOCITY_Y =       4; /**<  */
    static const int ATT_ACCELERATION =     5; /**<  */
    static const int ATT_ACCELERATION_X =   6; /**<  */
    static const int ATT_ACCELERATION_Y =   7; /**<  */

    static const int ATT_GRAVITY =          8; /**<  */
    static const int ATT_JUMP_INTENSITY =   9; /**<  */
    static const int ATT_HP =               10; /**<  */
    static const int ATT_MP =               11; /**<  */
    static const int ATT_ATK =              12; /**<  */
    static const int ATT_DEF =              13; /**<  */
    static const int ATT_INT =              14; /**<  */

    static const int ATT_DIRECTION =        15; /**<  */
    static const int ATT_ANIMATION =        16; /**<  */
    static const int ATT_ROTATION =         17; /**<  */
    static const int ATT_ZOOM =             18; /**<  */

    static const int ATT_COLISION =         19; /**<  */

    static const int ATT_KEY =              20; /**<  */
    static const int ATT_MOUSE =            21; /**<  */

    static const int ATT_SOUND =            22; /**<  */
    static const int ATT_MUSIC =            23; /**<  */

    static const int ATT_MAP =              24; /**<  */

    static const int ATT_PROCEDURE =        25; /**<  */

    static const int ATT_TIMER =                    26; /**<  */

    static const int ATT_SPECIAL_BOUNCING_BALL =    27; // não implementado /**< TODO  */
    static const int ATT_SPECIAL_EIGHT_MOVEMENT =   28; // não implementado /**<  TODO */
    static const int ATT_SPECIAL_PLATFORM_MOVEMENT =    29; /**<  */

    static const int ATT_MOVEMENT                     =   30; /**<  */

    static const int ATT_INSTANCE_NUMBER              =   31; /**<  */

    static const int ATT_THROWER                      =   32; /**<  */

    static const int ATT_FOLLOWER                     =   33; /**<  */

    static const int ATT_SIDES                        =   34; /**<  */

    static const int ATT_GAME_TIMER                     = 35; /**<  */
    static const int ATT_MAP_TIMER                      = 36; /**<  */

    static const int ATT_OBJECT_LEVEL                   = 37; /**<  */


    static const int ATT_VARIABLES                    =  300; /**<  */

    // adicionar: pontuação




    static const int COND_EQUAL                 = 0; /**<  */
    static const int COND_DIFFERENT             = 1; /**<  */
    static const int COND_LESS                  = 2; /**<  */
    static const int COND_LESS_EQUAL            = 3; /**<  */
    static const int COND_GREATER               = 4; /**<  */
    static const int COND_GREATER_EQUAL         = 5; /**<  */

    static const int COND_DETECT_SIMPLE_COLLISION   = 6; /**<  */
    static const int COND_DETECT_PIXEL_COLLISION    = 7; /**<  */

    static const int COND_BUTTON_PRESSED        = 8; /**<  */
    static const int COND_BUTTON_DOWN           = 9; /**<  */
    static const int COND_MOUSE_BUTTON_PRESSED  = 10; /**<  */
    static const int COND_MOUSE_BUTTON_DOWN     = 11; /**<  */

    static const int COND_IS_MUSIC_PLAYING      = 12; /**<  */
    static const int COND_IS_SOUND_PLAYING      = 13; /**<  */

    static const int COND_IS_CURRENT_MAP        = 14; /**<  */

    static const int COND_EVERY_SECONDS         = 15; /**<  */

    static const int COND_IS_LEFT_SIDE          = 16; /**<  */
    static const int COND_IS_UP_SIDE            = 17; /**<  */
    static const int COND_IS_RIGHT_SIDE         = 18; /**<  */
    static const int COND_IS_DOWN_SIDE          = 19; /**<  */



    static const int ACTION_SET_VALUE           = 0; /**<  */
    static const int ACTION_ADD_VALUE           = 1; /**<  */
    static const int ACTION_MULT_VALUE          = 2; /**<  */
    static const int ACTION_DIV_VALUE           = 3; /**<  */

    static const int ACTION_PLAY_MUSIC          = 4; /**<  */
    static const int ACTION_TOOGLE_PAUSE_MUSIC  = 5; /**<  */
    static const int ACTION_STOP_MUSIC          = 6; /**<  */
    static const int ACTION_PLAY_SOUND          = 7; /**<  */
    static const int ACTION_TOGGLE_PAUSE_SOUND  = 8; /**<  */
    static const int ACTION_STOP_SOUND          = 9; /**<  */

    static const int ACTION_SET_MAP             = 10; /**<  */
    static const int ACTION_RESET_MAP           = 11; /**<  */

    static const int ACTION_CALL_PROCEDURE      = 12; /**<  */

    static const int ACTION_RESET_MAP_TIMER     = 13; /**<  */
    static const int ACTION_RESET_GAME_TIMER    = 14; /**<  */

    static const int ACTION_PLATFORM_JUMP       = 15; /**<  */

    static const int ACTION_BOUNCE              = 16; /**<  */
    static const int ACTION_BOOST               = 17; /**<  */

    static const int ACTION_THROW_OBJECT               = 18; /**<  */

    static const int ACTION_FOLLOW_OBJECT              = 19; /**<  */
    static const int ACTION_UNFOLLOW_OBJECT             = 20; /**<  */

    static const int ACTION_NEXT_MAP                    = 21; /**<  */

    static const int SDLK_UP	= 273; /**<  */
    static const int SDLK_DOWN  = 274; /**<  */
    static const int SDLK_RIGHT	= 275; /**<  */
    static const int SDLK_LEFT	= 276; /**<  */

    static const int SDLK_a			= 97; /**<  */
    static const int SDLK_b			= 98; /**<  */
    static const int SDLK_c			= 99; /**<  */
    static const int SDLK_d			= 100; /**<  */
    static const int SDLK_e			= 101; /**<  */
    static const int SDLK_f			= 102; /**<  */
    static const int SDLK_g			= 103; /**<  */
    static const int SDLK_h			= 104; /**<  */
    static const int SDLK_i			= 105; /**<  */
    static const int SDLK_j			= 106; /**<  */
    static const int SDLK_k			= 107; /**<  */
    static const int SDLK_l			= 108; /**<  */
    static const int SDLK_m			= 109; /**<  */
    static const int SDLK_n			= 110; /**<  */
    static const int SDLK_o			= 111; /**<  */
    static const int SDLK_p			= 112; /**<  */
    static const int SDLK_q			= 113; /**<  */
    static const int SDLK_r			= 114; /**<  */
    static const int SDLK_s			= 115; /**<  */
    static const int SDLK_t			= 116; /**<  */
    static const int SDLK_u			= 117; /**<  */
    static const int SDLK_v			= 118; /**<  */
    static const int SDLK_w			= 119; /**<  */
    static const int SDLK_x			= 120; /**<  */
    static const int SDLK_y			= 121; /**<  */
    static const int SDLK_z			= 122; /**<  */

    static const int SDLK_ESCAPE		= 27; /**<  */
    static const int SDLK_RETURN		= 13; /**<  */
    static const int SDLK_SPACE                 = 32; /**<  */
    static const int SDLK_RSHIFT		= 303; /**<  */
    static const int SDLK_LSHIFT		= 304; /**<  */
    static const int SDLK_RCTRL                 = 305; /**<  */
    static const int SDLK_LCTRL                 = 306; /**<  */
    static const int SDLK_RALT                  = 307; /**<  */
    static const int SDLK_LALT                  = 308; /**<  */



private:
    /**
     * @brief Construtor.
     *
     */
    EventComboDataProvider();
    /**
     * @brief Adiciona na lista um dado de atributo.
     *
     * @param id Identificador.
     * @param name Nome.
     * @param conditions Lista de condições.
     * @param actions Lista de ações.
     * @param showNumberValueCombo Se mostra o valor de número;
     * @param showVariableValueCombo Se mostra o valor de variável;
     * @param showObjectFieldCombo Se mostra o valor de objeto;
     * @param showDirectionInput Se mostra o input de direção;
     * @param showObject02 Se mostra a lista de objetos 02.
     * @param specialComboType Se mostra o combo de tipo especial.
     */
    void pushAttributeData(int id, QString name, std::list<int> *conditions, std::list<int> *actions,
                           bool showNumberValueCombo, bool showVariableValueCombo,
                           bool showObjectFieldCombo, bool showDirectionInput,
                           bool showObject02, int specialComboType);
    /**
     * @brief Adiciona dados de uma condição.
     *
     * @param id Identificador.
     * @param name Nome;
     */
    void pushConditionData(int id, QString name);
    /**
     * @brief Adiciona dados de uma ação.
     *
     * @param id Identificador
     * @param name Nome
     */
    void pushActionData(int id, QString name);

    /**
     * @brief Adiciona um dado deu ma combo especial.
     *
     * @param list Lista de dados.
     * @param code Código
     * @param string texto
     *
     * @ver SpecialComboValueData
     */
    void pushSpecialComboData(std::list<SpecialComboValueData*> *list, int code, std::string string);

    std::map<int, EventAttributeData*> eventMap; /**<  */
    std::map<int, std::string> conditionMap; /**<  */
    std::map<int, std::string> actionMap; /**<  */

    std::list<GameObject*> specialObjectList; /**<  */

    static EventComboDataProvider *singleton; /**<  */

};

#endif // EVENTCOMBODATAPROVIDER_H
