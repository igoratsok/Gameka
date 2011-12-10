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



#include "eventseditorcontroller.h"

EventsEditorController::EventsEditorController()
{
    eventComboDataProvider = EventComboDataProvider::getInstance();
}

void EventsEditorController::setMainController(MainController *mainController)
{
    this->mainController = mainController;
}

void EventsEditorController::openNewConditionWindow(EventData *eventData, GameObject *gameObject = NULL) {
    NewEventDialog *newEventDialog = new NewEventDialog(this, eventData, gameObject, EventData::TYPE_CONDITION);
    newEventDialog->setWindowTitle(QString::fromUtf8("Nova condição"));
    newEventDialog->exec();

    delete newEventDialog;
}

void EventsEditorController::openNewActionWindow(EventData *eventData, GameObject *gameObject = NULL) {
    NewEventDialog *newEventDialog = new NewEventDialog(this, eventData, gameObject, EventData::TYPE_ACTION);
    newEventDialog->setWindowTitle(QString::fromUtf8("Nova ação"));
    newEventDialog->exec();

    delete newEventDialog;
}

void EventsEditorController::openEditEventWindow(EventData *eventData, GameObject *gameObject) {
    NewEventDialog *newEventDialog = new NewEventDialog(this, eventData, gameObject, eventData->type);
    newEventDialog->setWindowTitle(QString::fromUtf8("Nova ação"));
    newEventDialog->exec();

    delete newEventDialog;
}

void EventsEditorController::openNewDialogueDialog(EventData *eventData) {
    mainController->openNewDialogueDialog(eventData);
}


std::list<EventAttributeData*> EventsEditorController::getComboAttributes(GameObject *gameObject, int eventType) {
    std::list<EventAttributeData*> listAttributes;
    GameData *gameData = GameData::getInstance();
    EventAttributeData *variableGenericAttribute;
    EventAttributeData *variableAttribute;

    if(gameObject != NULL) {
        // lista de atributos comuns

        if(gameObject->type != GameObject::SPECIAL) {
            listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_POSITION_X));
            listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_POSITION_Y));


            listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_VELOCITY_X));
            listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_VELOCITY_Y));

            if(gameObject->type != GameObject::PONG_BALL_OBJECT) {
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_ACCELERATION_X));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_ACCELERATION_Y));
            }


            if(gameObject->type == GameObject::PLATFORM_MOVEMENT_OBJECT) {
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_GRAVITY));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_JUMP_INTENSITY));
            }


            if(gameObject->type != GameObject::NPC && gameObject->type != GameObject::ITEM &&
                    gameObject->type != GameObject::STATIC_OBJECT) {
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_HP));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_HP));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_ATK));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_DEF));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_INT));
            }


            //listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_DIRECTION));
            //listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_ANIMATION));
            //listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_ROTATION));
            //listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_ZOOM));

            if(gameObject->type == GameObject::PLATFORM_MOVEMENT_OBJECT && eventType == EventData::TYPE_ACTION) {
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_SPECIAL_PLATFORM_MOVEMENT));
            }

            if(eventType == EventData::TYPE_CONDITION) {
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_COLISION));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_SIDES));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_INSTANCE_NUMBER));
            } else {
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_MOVEMENT));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_THROWER));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_FOLLOWER));

            }

            if(gameObject->type != GameObject::ITEM && gameObject->type != GameObject::STATIC_OBJECT) {
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_OBJECT_LEVEL));
            }


            variableGenericAttribute = eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_VARIABLES);

            foreach(VariableData *variableData, *gameObject->variableList) {
                variableAttribute = new EventAttributeData(*variableGenericAttribute);

                variableAttribute->id += variableData->id;
                variableAttribute->name = variableData->name;

                listAttributes.push_back(variableAttribute);
            }




        } else {
            switch(gameObject->id) {
            case EventComboDataProvider::ID_SPECIAL_GLOBAL:
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_MAP));
                if(eventType == EventData::TYPE_ACTION) {
                    listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_PROCEDURE));
                }

                variableGenericAttribute = eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_VARIABLES);

                foreach(VariableData *variableData, *gameData->variableList) {
                    variableAttribute = new EventAttributeData(*variableGenericAttribute);

                    variableAttribute->id += variableData->id;
                    variableAttribute->name = variableData->name;

                    listAttributes.push_back(variableAttribute);
                }



                break;
            case EventComboDataProvider::ID_SPECIAL_JOYSTICK:
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_KEY));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_MOUSE));
                break;
            case EventComboDataProvider::ID_SPECIAL_MUSIC:
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_MUSIC));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_SOUND));
                break;
            case EventComboDataProvider::ID_SPECIAL_TIMER:
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_TIMER));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_GAME_TIMER));
                listAttributes.push_back(eventComboDataProvider->getAttribute(EventComboDataProvider::ATT_MAP_TIMER));
                break;
            }
        }







    }



    return listAttributes;
}

QString EventsEditorController::getComboConditionString(int index) {
    return eventComboDataProvider->getConditionString(index);
}

QString EventsEditorController::getComboActionString(int index) {
    return eventComboDataProvider->getActionString(index);
}


ProcedureData* EventsEditorController::addProcedure(GameObject *gameObject, Map *map) {
    ProcedureData *procedureData;

    if(gameObject == NULL) {
        GameData *gameData = GameData::getInstance();

        procedureData = new ProcedureData();

        gameData->addProcedure(procedureData);
    } else {
        procedureData = new ProcedureData();

        gameObject->addProcedure(procedureData);

    }

    return procedureData;
}

ProcedureData* EventsEditorController::addProcedure() {
    addProcedure(NULL, NULL);
}

ProcedureData* EventsEditorController::addProcedure(GameObject *gameObject) {
    addProcedure(gameObject, NULL);
}

ProcedureData* EventsEditorController::addProcedure(Map *map) {
    addProcedure(NULL, map);
}

std::vector<GameObject*> EventsEditorController::getContextObjects(EventData *eventData) {
    std::vector<GameObject*> objectList;

    EventData *parent;
    parent = eventData->parent;
    while(parent != NULL) {
        GameData *gameData = GameData::getInstance();

        GameObject *gameObject01 = gameData->searchGameObjectById(parent->idObject01);

        objectList.push_back(gameObject01);

        if(parent->idObject02 != -1) {
            GameObject *gameObject02 = gameData->searchGameObjectById(parent->idObject02);;
            objectList.push_back(gameObject02);
        } else {
            objectList.push_back(NULL);
        }

        parent = parent->parent;


    }

    return objectList;
}

std::list<GameObject*> EventsEditorController::getSpecialGameObjects(int eventType) {
    return eventComboDataProvider->getSpecialObjectList(eventType);
}

std::list<SpecialComboValueData*> EventsEditorController::getSpecialComboValueList(int specialType, GameObject *gameObject) {
    return eventComboDataProvider->getSpecialComboValueList(this, specialType, gameObject);
}

bool EventsEditorController::isNoValueAction(int action) {
    return eventComboDataProvider->isNoValueAction(action);
}

bool EventsEditorController::isNoValueCondition(int condition) {
    return eventComboDataProvider->isNoValueCondition(condition);
}


std::vector<GameObject*>* EventsEditorController::getObjectList() {
    GameData *gameData = GameData::getInstance();

    return gameData->objectList;
}

std::vector<TileSet*>* EventsEditorController::getTilesetList() {
    GameData *gameData = GameData::getInstance();

    return gameData->tileSetList;
}

std::vector<Map*>* EventsEditorController::getMaplist() {
    GameData *gameData = GameData::getInstance();

    return gameData->mapList;
}

std::vector<AnimationData*>* EventsEditorController::getAnimationDataList() {
    GameData *gameData = GameData::getInstance();

    return gameData->animationDataList;
}


std::vector<VariableData*>* EventsEditorController::getGlobalVariableDataList() {
    GameData *gameData = GameData::getInstance();

    return gameData->variableList;
}

