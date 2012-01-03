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

        pushSpecialComboData(&list, SDLK_UP, QApplication::tr("Cima").toStdString());
        pushSpecialComboData(&list, SDLK_RIGHT, QApplication::tr("Direita").toStdString());
        pushSpecialComboData(&list, SDLK_DOWN, QApplication::tr("Baixo").toStdString());
        pushSpecialComboData(&list, SDLK_LEFT, QApplication::tr("Esquerda").toStdString());

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

        pushSpecialComboData(&list, SDLK_RETURN, QApplication::tr("ENTER").toStdString());
        pushSpecialComboData(&list, SDLK_SPACE, QString::fromUtf8("ESPAÇO").toStdString());
        pushSpecialComboData(&list, SDLK_RSHIFT, QApplication::tr("SHIFT DIREITO").toStdString());
        pushSpecialComboData(&list, SDLK_LSHIFT, QApplication::tr("SHIFT ESQUERDO").toStdString());
        pushSpecialComboData(&list, SDLK_RCTRL, QApplication::tr("CTRL DIREITO").toStdString());
        pushSpecialComboData(&list, SDLK_LCTRL, QApplication::tr("CTRL ESQUERDO").toStdString());
        pushSpecialComboData(&list, SDLK_RALT, QApplication::tr("ALT DIREITO").toStdString());
        pushSpecialComboData(&list, SDLK_LALT, QApplication::tr("ALT ESQUERDO").toStdString());


        break;
    case EventAttributeData::COMBO_TYPE_MAP:

        foreach(Map *map, *mapList) {
            pushSpecialComboData(&list, map->id, map->mapName);
        }


        break;
    case EventAttributeData::COMBO_TYPE_MOUSE:
            pushSpecialComboData(&list, 1, QString::fromUtf8(QApplication::tr("Botão esquerdo").toStdString().c_str()).toStdString());
            pushSpecialComboData(&list, 3, QString::fromUtf8(QApplication::tr("Botão direito").toStdString().c_str()).toStdString());
            pushSpecialComboData(&list, 2, QString::fromUtf8(QApplication::tr("Botão do meio").toStdString().c_str()).toStdString());


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

    pushAttributeData(ATT_COLISION, QString::fromUtf8(QApplication::tr("Colisão").toStdString().c_str()), conds, actions,
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

    pushAttributeData(ATT_POSITION_X, QString::fromUtf8(QApplication::tr("Posição X").toStdString().c_str()), conds, actions,
                     true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_POSITION_Y, QString::fromUtf8(QApplication::tr("Posição Y").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_VELOCITY, QString::fromUtf8(QApplication::tr("Velocidade").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_VELOCITY_X, QString::fromUtf8(QApplication::tr("Velocidade X").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_VELOCITY_Y, QString::fromUtf8(QApplication::tr("Velocidade Y").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ACCELERATION, QString::fromUtf8(QApplication::tr("Aceleração").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ACCELERATION_X, QString::fromUtf8(QApplication::tr("Aceleração X").toStdString().c_str()),conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ACCELERATION_Y, QString::fromUtf8(QApplication::tr("Aceleração Y").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );

    pushAttributeData(ATT_GRAVITY, QString::fromUtf8(QApplication::tr("Gravidade").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_JUMP_INTENSITY, QString::fromUtf8(QApplication::tr("Intensidade do pulo").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_HP, QString::fromUtf8(QApplication::tr("HP (vida)").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_MP, QString::fromUtf8(QApplication::tr("MP (magia)").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ATK, QString::fromUtf8(QApplication::tr("Ataque").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_DEF, QString::fromUtf8(QApplication::tr("Defesa").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_INT, QString::fromUtf8(QApplication::tr("Inteligência").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_OBJECT_LEVEL, QString::fromUtf8(QApplication::tr("Nível").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );




    conds = new std::list<int>();
    conds->push_back((int)COND_EQUAL);
    conds->push_back((int)COND_DIFFERENT);

    pushAttributeData(ATT_DIRECTION, QString::fromUtf8(QApplication::tr("Direção").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );

    actions = new std::list<int>();
    actions->push_back((int)ACTION_SET_VALUE);

    pushAttributeData(ATT_ANIMATION, QString::fromUtf8(QApplication::tr("Animação").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );

    actions = new std::list<int>();
    actions->push_back((int)ACTION_SET_VALUE);
    actions->push_back((int)ACTION_ADD_VALUE);
    actions->push_back((int)ACTION_MULT_VALUE);
    actions->push_back((int)ACTION_DIV_VALUE);

    pushAttributeData(ATT_ROTATION, QString::fromUtf8(QApplication::tr("Rotação").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE );
    pushAttributeData(ATT_ZOOM, QString::fromUtf8(QApplication::tr("Zoom").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_BUTTON_PRESSED);
    conds->push_back((int)COND_BUTTON_DOWN);

    pushAttributeData(ATT_KEY, QString::fromUtf8(QApplication::tr("Teclado").toStdString().c_str()), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_KEY );

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_MOUSE_BUTTON_PRESSED);
    conds->push_back((int)COND_MOUSE_BUTTON_DOWN);

    pushAttributeData(ATT_MOUSE, QString::fromUtf8(QApplication::tr("Mouse").toStdString().c_str()), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_MOUSE );


    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_IS_MUSIC_PLAYING);
    actions->push_back((int)ACTION_PLAY_MUSIC);
    actions->push_back((int)ACTION_TOOGLE_PAUSE_MUSIC);
    actions->push_back((int)ACTION_STOP_MUSIC);

    pushAttributeData(ATT_MUSIC, QString::fromUtf8(QApplication::tr("Música").toStdString().c_str()), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_MUSIC );

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_IS_SOUND_PLAYING);
    actions->push_back((int)ACTION_PLAY_SOUND);
    actions->push_back((int)ACTION_TOGGLE_PAUSE_SOUND);
    actions->push_back((int)ACTION_STOP_SOUND);

    pushAttributeData(ATT_SOUND, QString::fromUtf8(QApplication::tr("Som").toStdString().c_str()), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_SOUND );

    actions = new std::list<int>();
    conds = new std::list<int>();

    conds->push_back((int)COND_IS_CURRENT_MAP);
    actions->push_back((int)ACTION_SET_MAP);
    actions->push_back((int)ACTION_RESET_MAP);
    actions->push_back((int)ACTION_NEXT_MAP);

    pushAttributeData(ATT_MAP, QString::fromUtf8(QApplication::tr("Mapa").toStdString().c_str()), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_MAP );

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_CALL_PROCEDURE);

    pushAttributeData(ATT_PROCEDURE, QString::fromUtf8(QApplication::tr("Procedimentos").toStdString().c_str()), conds, actions,
                      false, false, false, false, false, EventAttributeData::COMBO_TYPE_PROCEDURE );

    actions = new std::list<int>();
    conds = new std::list<int>();
    conds->push_back((int)COND_EVERY_SECONDS);
    actions->push_back((int)ACTION_RESET_MAP_TIMER);
    actions->push_back((int)ACTION_RESET_GAME_TIMER);

    pushAttributeData(ATT_TIMER, QString::fromUtf8(QApplication::tr("Tempo").toStdString().c_str()), conds, actions,
                      true, true, false, false, false, EventAttributeData::COMBO_TYPE_NONE);



    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_PLATFORM_JUMP);

    pushAttributeData(ATT_SPECIAL_PLATFORM_MOVEMENT, QString::fromUtf8(QApplication::tr("Especiais (Plataforma)").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_BOUNCE);
    actions->push_back((int)ACTION_BOOST);

    pushAttributeData(ATT_MOVEMENT, QString::fromUtf8(QApplication::tr("Movimentos Extras").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    conds->push_back((int)COND_EQUAL);
    conds->push_back((int)COND_DIFFERENT);
    conds->push_back((int)COND_LESS);
    conds->push_back((int)COND_LESS_EQUAL);
    conds->push_back((int)COND_GREATER);
    conds->push_back((int)COND_GREATER_EQUAL);

    pushAttributeData(ATT_INSTANCE_NUMBER, QString::fromUtf8(QApplication::tr("Número de objetos").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_THROW_OBJECT);

    pushAttributeData(ATT_THROWER, QString::fromUtf8(QApplication::tr("Atirar objetos").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    actions->push_back((int)ACTION_FOLLOW_OBJECT);
    actions->push_back((int)ACTION_UNFOLLOW_OBJECT);

    pushAttributeData(ATT_FOLLOWER, QString::fromUtf8(QApplication::tr("Seguir/Afastar").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    actions = new std::list<int>();
    conds = new std::list<int>();
    conds->push_back((int)COND_IS_LEFT_SIDE);
    conds->push_back((int)COND_IS_UP_SIDE);
    conds->push_back((int)COND_IS_RIGHT_SIDE);
    conds->push_back((int)COND_IS_DOWN_SIDE);

    pushAttributeData(ATT_SIDES, QString::fromUtf8(QApplication::tr("Canto da tela").toStdString().c_str()), conds, actions,
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

    pushAttributeData(ATT_GAME_TIMER, QString::fromUtf8(QApplication::tr("Timer global").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);
    pushAttributeData(ATT_MAP_TIMER, QString::fromUtf8(QApplication::tr("Timer do mapa").toStdString().c_str()), conds, actions,
                      true, true, true, false, true, EventAttributeData::COMBO_TYPE_NONE);

    pushConditionData(COND_EQUAL, QString::fromUtf8(QApplication::tr("Igual a").toStdString().c_str()));
    pushConditionData(COND_DIFFERENT, QString::fromUtf8(QApplication::tr("Diferente de").toStdString().c_str()));
    pushConditionData(COND_LESS, QString::fromUtf8(QApplication::tr("Menor que").toStdString().c_str()));
    pushConditionData(COND_LESS_EQUAL, QString::fromUtf8(QApplication::tr("Menor ou igual a").toStdString().c_str()));
    pushConditionData(COND_GREATER, QString::fromUtf8(QApplication::tr("Maior que").toStdString().c_str()));
    pushConditionData(COND_GREATER_EQUAL, QString::fromUtf8(QApplication::tr("Maior ou igual a").toStdString().c_str()));

    pushConditionData(COND_DETECT_SIMPLE_COLLISION, QString(QApplication::tr("Colide com").toStdString().c_str()));
    pushConditionData(COND_DETECT_PIXEL_COLLISION, QString(QApplication::tr("Colide (por pixel) com").toStdString().c_str()));

    pushConditionData(COND_BUTTON_PRESSED, QString::fromUtf8(QApplication::tr("Botão apertado").toStdString().c_str()));
    pushConditionData(COND_BUTTON_DOWN, QString::fromUtf8(QApplication::tr("Botão segurado").toStdString().c_str()));

    pushConditionData(COND_MOUSE_BUTTON_PRESSED, QString::fromUtf8(QApplication::tr("Mouse apertado").toStdString().c_str()));
    pushConditionData(COND_MOUSE_BUTTON_DOWN, QString::fromUtf8(QApplication::tr("Mouse segurado").toStdString().c_str()));

    pushConditionData(COND_IS_MUSIC_PLAYING, QString::fromUtf8(QApplication::tr("Existe música tocando?").toStdString().c_str()));
    pushConditionData(COND_IS_SOUND_PLAYING, QString::fromUtf8(QApplication::tr("Existe som tocando?").toStdString().c_str()));

    pushConditionData(COND_IS_CURRENT_MAP, QString::fromUtf8(QApplication::tr("É o mapa atual").toStdString().c_str()));

    pushConditionData(COND_EVERY_SECONDS, QString::fromUtf8(QApplication::tr("A cada __ segundos").toStdString().c_str()));

    pushConditionData(COND_IS_LEFT_SIDE, QString::fromUtf8(QApplication::tr("No canto esquerdo").toStdString().c_str()));
    pushConditionData(COND_IS_UP_SIDE, QString::fromUtf8(QApplication::tr("No canto de cima").toStdString().c_str()));
    pushConditionData(COND_IS_RIGHT_SIDE, QString::fromUtf8(QApplication::tr("No canto direito").toStdString().c_str()));
    pushConditionData(COND_IS_DOWN_SIDE, QString::fromUtf8(QApplication::tr("No canto debaixo").toStdString().c_str()));

    pushActionData(ACTION_SET_VALUE, QString::fromUtf8(QApplication::tr("Determina valor").toStdString().c_str()));
    pushActionData(ACTION_ADD_VALUE, QString::fromUtf8(QApplication::tr("Adiciona valor").toStdString().c_str()));
    pushActionData(ACTION_MULT_VALUE, QString::fromUtf8(QApplication::tr("Multiplica valor").toStdString().c_str()));
    pushActionData(ACTION_DIV_VALUE, QString::fromUtf8(QApplication::tr("Divide valor").toStdString().c_str()));
    pushActionData(ACTION_DIV_VALUE, QString::fromUtf8(QApplication::tr("Divide valor").toStdString().c_str()));

    pushActionData(ACTION_PLAY_MUSIC, QString::fromUtf8(QApplication::tr("Toca música").toStdString().c_str()));
    pushActionData(ACTION_TOOGLE_PAUSE_MUSIC, QString::fromUtf8(QApplication::tr("Pausa/resume música").toStdString().c_str()));
    pushActionData(ACTION_STOP_MUSIC, QString::fromUtf8(QApplication::tr("Para música").toStdString().c_str()));

    pushActionData(ACTION_PLAY_SOUND, QString::fromUtf8(QApplication::tr("Toca som").toStdString().c_str()));
    pushActionData(ACTION_TOGGLE_PAUSE_SOUND, QString::fromUtf8(QApplication::tr("Pausa/resume som").toStdString().c_str()));
    pushActionData(ACTION_STOP_SOUND, QString::fromUtf8(QApplication::tr("Para som").toStdString().c_str()));

    pushActionData(ACTION_SET_MAP, QString::fromUtf8(QApplication::tr("Pula para mapa").toStdString().c_str()));
    pushActionData(ACTION_RESET_MAP, QString::fromUtf8(QApplication::tr("Reseta mapa").toStdString().c_str()));

    pushActionData(ACTION_CALL_PROCEDURE, QString::fromUtf8(QApplication::tr("Chama procedimento").toStdString().c_str()));

    pushActionData(ACTION_RESET_MAP_TIMER, QString::fromUtf8(QApplication::tr("Reinicia timer do mapa").toStdString().c_str()));
    pushActionData(ACTION_RESET_GAME_TIMER, QString::fromUtf8(QApplication::tr("Reinicia timer do jogo").toStdString().c_str()));

    pushActionData(ACTION_PLATFORM_JUMP, QString::fromUtf8(QApplication::tr("Pula").toStdString().c_str()));

    pushActionData(ACTION_BOUNCE, QString::fromUtf8(QApplication::tr("Quica").toStdString().c_str()));

    pushActionData(ACTION_BOOST, QString::fromUtf8(QApplication::tr("Impulsiona").toStdString().c_str()));

    pushActionData(ACTION_THROW_OBJECT, QString::fromUtf8(QApplication::tr("Atira objeto na velocidade:").toStdString().c_str()));

    pushActionData(ACTION_FOLLOW_OBJECT, QString::fromUtf8(QApplication::tr("Segue objeto na velocidade:").toStdString().c_str()));
    pushActionData(ACTION_UNFOLLOW_OBJECT, QString::fromUtf8(QApplication::tr("Foge do objeto na velocidade:").toStdString().c_str()));

    pushActionData(ACTION_NEXT_MAP, QString::fromUtf8(QApplication::tr("Próximo mapa").toStdString().c_str()));

    GameObject *specialGameObject = new GameObject(-1);
    specialGameObject->specialIconPath = std::string(":/icones_editor_eventos/data/event_editor_icons/globe-icon.png");
    specialGameObject->name = std::string(QApplication::tr("Globais").toStdString().c_str());

    specialObjectList.push_back(specialGameObject);

    specialGameObject = new GameObject(-2);
    specialGameObject->specialIconPath = std::string(":/icones_editor_eventos/data/event_editor_icons/joystick-icon.png");
    specialGameObject->name = std::string(QApplication::tr("Controles").toStdString().c_str());

    specialObjectList.push_back(specialGameObject);

    specialGameObject = new GameObject(-3);
    specialGameObject->specialIconPath = std::string(":/icones_editor_eventos/data/event_editor_icons/clock-icon.png");
    specialGameObject->name = std::string(QApplication::tr("Tempo").toStdString().c_str());

    specialObjectList.push_back(specialGameObject);

    specialGameObject = new GameObject(-4);
    specialGameObject->specialIconPath = std::      string(":/icones_editor_eventos/data/event_editor_icons/music-icon.png");
    specialGameObject->name = QString::fromUtf8(QApplication::tr("Música/Som").toStdString().c_str()).toStdString();

    specialObjectList.push_back(specialGameObject);

}
