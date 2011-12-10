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



#include "eventcombodataprovider.h"

EventComboDataProvider* EventComboDataProvider::singleton = NULL;


EventComboDataProvider* EventComboDataProvider::getInstance() {
    if(singleton == NULL) {
        singleton = new EventComboDataProvider();
    }

    return singleton;
}

EventAttributeData* EventComboDataProvider::getAttribute(int index) {
    std::map<int, EventAttributeData*>::iterator it = eventMap.find(index);
    if(it != eventMap.end()) {
        return it->second;
    } else {
        return NULL;
    }
}

QString EventComboDataProvider::getConditionString(int index) {
    std::map<int, std::string>::iterator it = conditionMap.find(index);
    if(it != conditionMap.end()) {
        return QString(it->second.c_str());
    } else {
        return NULL;
    }
}

QString EventComboDataProvider::getActionString(int index) {
    std::map<int, std::string>::iterator it = actionMap.find(index);
    if(it != conditionMap.end()) {
        return QString(it->second.c_str());
    } else {
        return NULL;
    }
}

std::list<GameObject*> EventComboDataProvider::getSpecialObjectList(int eventType) {
    std::list<GameObject*> specialObjectListFiltered;

    foreach(GameObject *gameObject, specialObjectList) {
        if(eventType == EventData::TYPE_ACTION) {
            if(gameObject->id == ID_SPECIAL_GLOBAL || gameObject->id == ID_SPECIAL_TIMER || gameObject->id ==  ID_SPECIAL_MUSIC) {
                specialObjectListFiltered.push_back(gameObject);
            }
        } else {
            specialObjectListFiltered.push_back(gameObject);
        }
    }

    return specialObjectListFiltered;
}
std::list<SpecialComboValueData*> EventComboDataProvider::getSpecialComboValueList(EventsEditorController *eventsEditorController, int specialType, GameObject *gameObject) {
    std::list<SpecialComboValueData*> list;
    GameData *gameData = GameData::getInstance();

    std::vector<Map*> *mapList = eventsEditorController->getMaplist();

    QDir *dir;
    QStringList files;
    QStringList filters;

    switch(specialType) {
    case EventAttributeData::COMBO_TYPE_KEY:

        pushSpecialComboData(&list, SDLK_UP, "Cima");
        pushSpecialComboData(&list, SDLK_RIGHT, "Direita");
        pushSpecialComboData(&list, SDLK_DOWN, "Baixo");
        pushSpecialComboData(&list, SDLK_LEFT, "Esquerda");

        pushSpecialComboData(&list, SDLK_a, "A");
        pushSpecialComboData(&list, SDLK_b, "B");
        pushSpecialComboData(&list, SDLK_c, "C");
        pushSpecialComboData(&list, SDLK_d, "D");
        pushSpecialComboData(&list, SDLK_e, "E");
        pushSpecialComboData(&list, SDLK_f, "F");
        pushSpecialComboData(&list, SDLK_g, "G");
        pushSpecialComboData(&list, SDLK_h, "H");
        pushSpecialComboData(&list, SDLK_i, "I");
        pushSpecialComboData(&list, SDLK_j, "J");
        pushSpecialComboData(&list, SDLK_k, "K");
        pushSpecialComboData(&list, SDLK_l, "L");
        pushSpecialComboData(&list, SDLK_m, "M");
        pushSpecialComboData(&list, SDLK_n, "N");
        pushSpecialComboData(&list, SDLK_o, "O");
        pushSpecialComboData(&list, SDLK_p, "P");
        pushSpecialComboData(&list, SDLK_q, "Q");
        pushSpecialComboData(&list, SDLK_r, "R");
        pushSpecialComboData(&list, SDLK_s, "S");
        pushSpecialComboData(&list, SDLK_t, "T");
        pushSpecialComboData(&list, SDLK_u, "U");
        pushSpecialComboData(&list, SDLK_v, "V");
        pushSpecialComboData(&list, SDLK_w, "W");
        pushSpecialComboData(&list, SDLK_x, "X");
        pushSpecialComboData(&list, SDLK_y, "Y");
        pushSpecialComboData(&list, SDLK_z, "Z");

        pushSpecialComboData(&list, SDLK_RETURN, "ENTER");
        pushSpecialComboData(&list, SDLK_SPACE, QString::fromUtf8("ESPAÇO").toStdString());
        pushSpecialComboData(&list, SDLK_RSHIFT, "SHIFT DIREITO");
        pushSpecialComboData(&list, SDLK_LSHIFT, "SHIFT ESQUERDO");
        pushSpecialComboData(&list, SDLK_RCTRL, "CTRL DIREITO");
        pushSpecialComboData(&list, SDLK_LCTRL, "CTRL ESQUERDO");
        pushSpecialComboData(&list, SDLK_RALT, "ALT DIREITO");
        pushSpecialComboData(&list, SDLK_LALT, "ALT ESQUERDO");


        break;
    case EventAttributeData::COMBO_TYPE_MAP:

        foreach(Map *map, *mapList) {
            pushSpecialComboData(&list, map->id, map->mapName);
        }


        break;
    case EventAttributeData::COMBO_TYPE_MOUSE:
            pushSpecialComboData(&list, 1, QString::fromUtf8("Botão esquerdo").toStdString());
            pushSpecialComboData(&list, 3, QString::fromUtf8("Botão direito").toStdString());
            pushSpecialComboData(&list, 2, QString::fromUtf8("Botão do meio").toStdString());


        break;
    case EventAttributeData::COMBO_TYPE_MUSIC:
        dir = new QDir(gameData->getProjectDirectory().append("/musics/").c_str());
        filters.clear();
        filters << "*.wav" << "*.mp3";
        std::cout << gameData->getProjectDirectory().append("/musics/");


        dir->setNameFilters(filters);

        files = dir->entryList();



        for(QStringList::Iterator it = files.begin(); it != files.end(); ++it) {
            pushSpecialComboData(&list, 0, ((QString)*it).toStdString());
        }
        break;
    case EventAttributeData::COMBO_TYPE_SOUND:    
        dir = new QDir(gameData->getProjectDirectory().append("/sfx/").c_str());
        filters.clear();
        filters << "*.wav" << "*.mp3";
        std::cout << gameData->getProjectDirectory().append("/sfx/");


        dir->setNameFilters(filters);

        files = dir->entryList();



        for(QStringList::Iterator it = files.begin(); it != files.end(); ++it) {
            pushSpecialComboData(&list, 0, ((QString)*it).toStdString());
        }
        break;
    case EventAttributeData::COMBO_TYPE_PROCEDURE:

        foreach(ProcedureData *procedureData, *gameData->procedureList) {
            std::stringstream ss;

            ss << "Global - " << procedureData->name;

            pushSpecialComboData(&list, procedureData->id, ss.str());
        }

        if(gameObject != NULL) {
           foreach(ProcedureData *procedureData, *gameObject->procedureList) {
               std::stringstream ss;

               ss << gameObject->name << " - " << procedureData->name;

               pushSpecialComboData(&list, -procedureData->id, ss.str());
           }
        }


        break;
    }

    return list;
}


bool EventComboDataProvider::isNoValueAction(int action) {
    switch(action) {
    case ACTION_TOOGLE_PAUSE_MUSIC:
        return true;
        break;
    case ACTION_STOP_MUSIC:
        return true;
        break;
    case ACTION_TOGGLE_PAUSE_SOUND:
        return true;
        break;
    case ACTION_STOP_SOUND:
        return true;
        break;
    case ACTION_RESET_MAP:
        return true;
    case ACTION_BOUNCE:
        return true;
        break;
    case ACTION_NEXT_MAP:
        return true;
        break;

    }


    return false;
}

bool EventComboDataProvider::isNoValueCondition(int condition) {
    switch(condition) {
    case COND_IS_MUSIC_PLAYING:
        return true;
        break;
    case COND_IS_SOUND_PLAYING:
        return true;
        break;

    }

    return false;
}

void EventComboDataProvider::pushAttributeData(int id, QString name, std::list<int> *conditions, std::list<int> *actions,
                                               bool showNumberValueCombo, bool showVariableValueCombo,
                                               bool showObjectFieldCombo, bool showDirectionInput,
                                               bool showObject02, int specialComboType) {

    EventAttributeData *eventAttributeData = new EventAttributeData();

    std::cout << "EAD size:" << sizeof(*eventAttributeData) << std::endl;



    eventAttributeData->name = std::string(name.toStdString().c_str());
    eventAttributeData->conditions = conditions;
    eventAttributeData->actions = actions;
    eventAttributeData->id = id;
    eventAttributeData->showNumberValueCombo = showNumberValueCombo;
    eventAttributeData->showVariableValueCombo = showVariableValueCombo;
    eventAttributeData->showObjectFieldCombo = showObjectFieldCombo;
    eventAttributeData->showObject02 = showObject02;
    eventAttributeData->showDirectionInput = showDirectionInput;
    eventAttributeData->specialComboType = specialComboType;




    eventMap.insert(std::pair<int, EventAttributeData*>(id, eventAttributeData));
}

void EventComboDataProvider::pushConditionData(int id, QString name) {
    conditionMap.insert(std::pair<int, std::string>(id, name.toStdString()));
}

void EventComboDataProvider::pushActionData(int id, QString name) {
    actionMap.insert(std::pair<int, std::string>(id, name.toStdString()));
}

void EventComboDataProvider::pushSpecialComboData(std::list<SpecialComboValueData *> *list, int code, std::string string) {
    SpecialComboValueData *specialComboValueData = new SpecialComboValueData();
    specialComboValueData->code = code;
    specialComboValueData->string = string;

    list->push_back(specialComboValueData);
}



EventComboDataProvider::EventComboDataProvider()
{


    std::list<int> *actions;
    std::list<int> *conds;

    actions = new std::list<int>();

    conds = new std::list<int>();
    conds->push_back((int)COND_DETECT_SIMPLE_COLLISION);
    conds->push_back((int)COND_DETECT_PIXEL_COLLISION);

    actions = new std::list<int>();

    pushAttributeData(ATT_COLISION, QString::fromUtf8("Colisão"), conds, actions,
                      false, false, false, false, true, false);


    conds = new std::list<int>();
    conds->push_back((int)COND_EQUAL);
    conds->push_back((int)COND_DIFFERENT);
    conds->push_back((int)COND_LESS);
    conds->push_back((int)COND_LESS_EQUAL);
    conds->push_back((int)COND_GREATER);
    conds->push_back((int)COND_GREATER_EQUAL);


    actions = new std::list<int>();
    actions->push_back((int)ACTION_SET_VALUE);
    actions->push_back((int)ACTION_ADD_VALUE);
    actions->push_back((int)ACTION_MULT_VALUE);
    actions->push_back((int)ACTION_DIV_VALUE);



    pushAttributeData(ATT_VARIABLES, QString::fromUtf8("[[VariableName]]"), conds, actions,
                     true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );

    pushAttributeData(ATT_POSITION_X, QString::fromUtf8("Posição X"), conds, actions,
                     true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_POSITION_Y, QString::fromUtf8("Posição Y"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_VELOCITY, QString::fromUtf8("Velocidade"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_VELOCITY_X, QString::fromUtf8("Velocidade X"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_VELOCITY_Y, QString::fromUtf8("Velocidade Y"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ACCELERATION, QString::fromUtf8("Aceleração"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ACCELERATION_X, QString::fromUtf8("Aceleração X"),conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ACCELERATION_Y, QString::fromUtf8("Aceleração Y"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );

    pushAttributeData(ATT_GRAVITY, QString::fromUtf8("Gravidade"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_JUMP_INTENSITY, QString::fromUtf8("Intensidade do pulo"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_HP, QString::fromUtf8("HP (vida)"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_MP, QString::fromUtf8("MP (magia)"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ATK, QString::fromUtf8("Ataque"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_DEF, QString::fromUtf8("Defesa"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_INT, QString::fromUtf8("Inteligência"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_OBJECT_LEVEL, QString::fromUtf8("Nível"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );




    conds = new std::list<int>();
    conds->push_back((int)COND_EQUAL);
    conds->push_back((int)COND_DIFFERENT);

    pushAttributeData(ATT_DIRECTION, QString::fromUtf8("Direção"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );

    actions = new std::list<int>();
    actions->push_back((int)ACTION_SET_VALUE);

    pushAttributeData(ATT_ANIMATION, QString::fromUtf8("Animação"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );

    actions = new std::list<int>();
    actions->push_back((int)ACTION_SET_VALUE);
    actions->push_back((int)ACTION_ADD_VALUE);
    actions->push_back((int)ACTION_MULT_VALUE);
    actions->push_back((int)ACTION_DIV_VALUE);

    pushAttributeData(ATT_ROTATION, QString::fromUtf8("Rotação"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ZOOM, QString::fromUtf8("Zoom"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_BUTTON_PRESSED);
    conds->push_back((int)COND_BUTTON_DOWN);

    pushAttributeData(ATT_KEY, QString::fromUtf8("Teclado"), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_KEY );

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_MOUSE_BUTTON_PRESSED);
    conds->push_back((int)COND_MOUSE_BUTTON_DOWN);

    pushAttributeData(ATT_MOUSE, QString::fromUtf8("Mouse"), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_MOUSE );


    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_IS_MUSIC_PLAYING);
    actions->push_back((int)ACTION_PLAY_MUSIC);
    actions->push_back((int)ACTION_TOOGLE_PAUSE_MUSIC);
    actions->push_back((int)ACTION_STOP_MUSIC);

    pushAttributeData(ATT_MUSIC, QString::fromUtf8("Música"), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_MUSIC );

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_IS_SOUND_PLAYING);
    actions->push_back((int)ACTION_PLAY_SOUND);
    actions->push_back((int)ACTION_TOGGLE_PAUSE_SOUND);
    actions->push_back((int)ACTION_STOP_SOUND);

    pushAttributeData(ATT_SOUND, QString::fromUtf8("Som"), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_SOUND );

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_IS_CURRENT_MAP);
    actions->push_back((int)ACTION_SET_MAP);
    actions->push_back((int)ACTION_RESET_MAP);
    actions->push_back((int)ACTION_NEXT_MAP);

    pushAttributeData(ATT_MAP, QString::fromUtf8("Mapa"), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_MAP );

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_CALL_PROCEDURE);

    pushAttributeData(ATT_PROCEDURE, QString::fromUtf8("Procedimentos"), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_PROCEDURE );

    actions = new std::list<int>();
    conds = new std::list<int>();
    conds->push_back((int)COND_EVERY_SECONDS);
    actions->push_back((int)ACTION_RESET_MAP_TIMER);
    actions->push_back((int)ACTION_RESET_GAME_TIMER);

    pushAttributeData(ATT_TIMER, QString::fromUtf8("Tempo"), conds, actions,
                      true, true, false, false, false, EventAttributeData::COMBO_TYPE_NONE);



    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_PLATFORM_JUMP);

    pushAttributeData(ATT_SPECIAL_PLATFORM_MOVEMENT, QString::fromUtf8("Especiais (Plataforma)"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_BOUNCE);
    actions->push_back((int)ACTION_BOOST);

    pushAttributeData(ATT_MOVEMENT, QString::fromUtf8("Movimentos Extras"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    conds->push_back((int)COND_EQUAL);
    conds->push_back((int)COND_DIFFERENT);
    conds->push_back((int)COND_LESS);
    conds->push_back((int)COND_LESS_EQUAL);
    conds->push_back((int)COND_GREATER);
    conds->push_back((int)COND_GREATER_EQUAL);

    pushAttributeData(ATT_INSTANCE_NUMBER, QString::fromUtf8("Número de objetos"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_THROW_OBJECT);

    pushAttributeData(ATT_THROWER, QString::fromUtf8("Atirar objetos"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_FOLLOW_OBJECT);
    actions->push_back((int)ACTION_UNFOLLOW_OBJECT);

    pushAttributeData(ATT_FOLLOWER, QString::fromUtf8("Seguir/Afastar"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    conds->push_back((int)COND_IS_LEFT_SIDE);
    conds->push_back((int)COND_IS_UP_SIDE);
    conds->push_back((int)COND_IS_RIGHT_SIDE);
    conds->push_back((int)COND_IS_DOWN_SIDE);

    pushAttributeData(ATT_SIDES, QString::fromUtf8("Canto da tela"), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_NONE);



    actions = new std::list<int>();
    actions->push_back((int) ACTION_SET_VALUE);
    conds = new std::list<int>();
    conds->push_back((int)COND_EQUAL);
    conds->push_back((int)COND_DIFFERENT);
    conds->push_back((int)COND_LESS);
    conds->push_back((int)COND_LESS_EQUAL);
    conds->push_back((int)COND_GREATER);
    conds->push_back((int)COND_GREATER_EQUAL);

    pushAttributeData(ATT_GAME_TIMER, QString::fromUtf8("Timer global"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);
    pushAttributeData(ATT_MAP_TIMER, QString::fromUtf8("Timer do mapa"), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    pushConditionData(COND_EQUAL, QString::fromUtf8("Igual a"));
    pushConditionData(COND_DIFFERENT, QString::fromUtf8("Diferente de"));
    pushConditionData(COND_LESS, QString::fromUtf8("Menor que"));
    pushConditionData(COND_LESS_EQUAL, QString::fromUtf8("Menor ou igual a"));
    pushConditionData(COND_GREATER, QString::fromUtf8("Maior que"));
    pushConditionData(COND_GREATER_EQUAL, QString::fromUtf8("Maior ou igual a"));

    pushConditionData(COND_DETECT_SIMPLE_COLLISION, QString("Colide com"));
    pushConditionData(COND_DETECT_PIXEL_COLLISION, QString("Colide (por pixel) com"));

    pushConditionData(COND_BUTTON_PRESSED, QString::fromUtf8("Botão apertado"));
    pushConditionData(COND_BUTTON_DOWN, QString::fromUtf8("Botão segurado"));

    pushConditionData(COND_MOUSE_BUTTON_PRESSED, QString::fromUtf8("Mouse apertado"));
    pushConditionData(COND_MOUSE_BUTTON_DOWN, QString::fromUtf8("Mouse segurado"));

    pushConditionData(COND_IS_MUSIC_PLAYING, QString::fromUtf8("Existe música tocando?"));
    pushConditionData(COND_IS_SOUND_PLAYING, QString::fromUtf8("Existe som tocando?"));

    pushConditionData(COND_IS_CURRENT_MAP, QString::fromUtf8("É o mapa atual"));

    pushConditionData(COND_EVERY_SECONDS, QString::fromUtf8("A cada __ segundos"));

    pushConditionData(COND_IS_LEFT_SIDE, QString::fromUtf8("No canto esquerdo"));
    pushConditionData(COND_IS_UP_SIDE, QString::fromUtf8("No canto de cima"));
    pushConditionData(COND_IS_RIGHT_SIDE, QString::fromUtf8("No canto direito"));
    pushConditionData(COND_IS_DOWN_SIDE, QString::fromUtf8("No canto debaixo"));

    pushActionData(ACTION_SET_VALUE, QString::fromUtf8("Determina valor"));
    pushActionData(ACTION_ADD_VALUE, QString::fromUtf8("Adiciona valor"));
    pushActionData(ACTION_MULT_VALUE, QString::fromUtf8("Multiplica valor"));
    pushActionData(ACTION_DIV_VALUE, QString::fromUtf8("Divide valor"));
    pushActionData(ACTION_DIV_VALUE, QString::fromUtf8("Divide valor"));

    pushActionData(ACTION_PLAY_MUSIC, QString::fromUtf8("Toca música"));
    pushActionData(ACTION_TOOGLE_PAUSE_MUSIC, QString::fromUtf8("Pausa/resume música"));
    pushActionData(ACTION_STOP_MUSIC, QString::fromUtf8("Para música"));

    pushActionData(ACTION_PLAY_SOUND, QString::fromUtf8("Toca som"));
    pushActionData(ACTION_TOGGLE_PAUSE_SOUND, QString::fromUtf8("Pausa/resume som"));
    pushActionData(ACTION_STOP_SOUND, QString::fromUtf8("Para som"));

    pushActionData(ACTION_SET_MAP, QString::fromUtf8("Pula para mapa"));
    pushActionData(ACTION_RESET_MAP, QString::fromUtf8("Reseta mapa"));

    pushActionData(ACTION_CALL_PROCEDURE, QString::fromUtf8("Chama procedimento"));

    pushActionData(ACTION_RESET_MAP_TIMER, QString::fromUtf8("Reinicia timer do mapa"));
    pushActionData(ACTION_RESET_GAME_TIMER, QString::fromUtf8("Reinicia timer do jogo"));

    pushActionData(ACTION_PLATFORM_JUMP, QString::fromUtf8("Pula"));

    pushActionData(ACTION_BOUNCE, QString::fromUtf8("Quica"));

    pushActionData(ACTION_BOOST, QString::fromUtf8("Impulsiona"));

    pushActionData(ACTION_THROW_OBJECT, QString::fromUtf8("Atira objeto na velocidade:"));

    pushActionData(ACTION_FOLLOW_OBJECT, QString::fromUtf8("Segue objeto na velocidade:"));
    pushActionData(ACTION_UNFOLLOW_OBJECT, QString::fromUtf8("Foge do objeto na velocidade:"));

    pushActionData(ACTION_NEXT_MAP, QString::fromUtf8("Próximo mapa"));

    GameObject *specialGameObject = new GameObject(-1);
    specialGameObject->specialIconPath = std::string(":/icones_editor_eventos/data/event_editor_icons/globe-icon.png");
    specialGameObject->name = std::string("Globais");

    specialObjectList.push_back(specialGameObject);

    specialGameObject = new GameObject(-2);
    specialGameObject->specialIconPath = std::string(":/icones_editor_eventos/data/event_editor_icons/joystick-icon.png");
    specialGameObject->name = std::string("Controles");

    specialObjectList.push_back(specialGameObject);

    specialGameObject = new GameObject(-3);
    specialGameObject->specialIconPath = std::string(":/icones_editor_eventos/data/event_editor_icons/clock-icon.png");
    specialGameObject->name = std::string("Tempo");

    specialObjectList.push_back(specialGameObject);

    specialGameObject = new GameObject(-4);
    specialGameObject->specialIconPath = std::      string(":/icones_editor_eventos/data/event_editor_icons/music-icon.png");
    specialGameObject->name = QString::fromUtf8("Música/Som").toStdString();

    specialObjectList.push_back(specialGameObject);

}
