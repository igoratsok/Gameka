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



#include "eventdata.h"

EventData::EventData()
{
    newEvent = true;
    eventComboDataProvider = EventComboDataProvider::getInstance();
    parent = NULL;
    dialogueData = NULL;

    negate = false;
}


QString EventData::getEventString(EventsEditorController *eventsEditorController, GameObject *currentGameObject) {
    if(newEvent) {
        return QString(QApplication::tr("< Novo evento >").toStdString().c_str());
    } else {
        if(type == TYPE_CONDITION || type == TYPE_ACTION) {
            GameData *gameData = GameData::getInstance();
            std::stringstream ss;

            GameObject *gameObject01 = gameData->searchGameObjectById(idObject01);

            if(gameObject01 || idObject01 == EventComboDataProvider::ID_SPECIAL_GLOBAL) {
                if(idObject01 != EventComboDataProvider::ID_SPECIAL_GLOBAL) {
                    ss << gameObject01->name;

                    ss << ".";
                } else {
                    ss << QApplication::tr("Global.").toStdString();
                }


                if(idAssociatedVariable < 300) {
                    ss << eventComboDataProvider->getAttribute(idAssociatedVariable)->name << ": ";
                } else {
                    if(currentGameObject != NULL) {
                        ss << currentGameObject->getVariableById(idAssociatedVariable - 300)->name << ": ";
                    } else {
                        ss << gameData->getVariableById(idAssociatedVariable - 300)->name << ": ";
                    }
                }

            }


            if(negate) {
                ss << QString::fromUtf8(QApplication::tr(" NÃO ").toStdString().c_str()).toStdString();
            }


            if(type == TYPE_CONDITION) {
                ss << eventComboDataProvider->getConditionString(opcode).toStdString();
            } else {
                ss << eventComboDataProvider->getActionString(opcode).toStdString();
            }




            ss << " : ";


            GameObject *gameObject02;

            std::list<SpecialComboValueData*> listSpecialCombo;

            switch(valueType) {
            case VALUE_TYPE_NUMBER:
                ss << value01;
                break;
            case VALUE_TYPE_VARIABLE:
                if(value01 < 0) {
                    ss << currentGameObject->name << "." << currentGameObject->getVariableById(-value01)->name;
                } else {
                    ss << QApplication::tr("Global.").toStdString() << gameData->getVariableById(value01)->name;
                }
                break;
            case VALUE_TYPE_OBJECT_ATTRIBUTE:
                if(idObject02 != -1) {
                    gameObject02 = gameData->searchGameObjectById(idObject02);
                    ss << gameObject02->name << "." << eventComboDataProvider->getAttribute(value01)->name;
                }

                break;
            case VALUE_TYPE_SPECIAL:
                switch(idAssociatedVariable) {
                case EventComboDataProvider::ATT_KEY:
                    listSpecialCombo = eventsEditorController->getSpecialComboValueList(EventAttributeData::COMBO_TYPE_KEY, NULL);

                    foreach(SpecialComboValueData *specialComboValue, listSpecialCombo) {
                        if(specialComboValue->code == value01) {
                            ss << specialComboValue->string;
                            break;
                        }
                    }

                    break;
                case EventComboDataProvider::ATT_MOUSE:
                    listSpecialCombo = eventsEditorController->getSpecialComboValueList(EventAttributeData::COMBO_TYPE_MOUSE, NULL);

                    foreach(SpecialComboValueData *specialComboValue, listSpecialCombo) {
                        if(specialComboValue->code == value01) {
                            ss << specialComboValue->string;
                            break;
                        }
                    }
                    break;
                case EventComboDataProvider::ATT_MAP:
                    if(type == TYPE_ACTION && (opcode == EventComboDataProvider::ACTION_SET_MAP) || type == TYPE_CONDITION) {
                        listSpecialCombo = eventsEditorController->getSpecialComboValueList(EventAttributeData::COMBO_TYPE_MAP, NULL);

                        foreach(SpecialComboValueData *specialComboValue, listSpecialCombo) {
                            if(specialComboValue->code = value01) {
                                ss << specialComboValue->string;
                                break;
                            }
                        }
                    }

                    break;
                case EventComboDataProvider::ATT_MUSIC:
                    if(type == TYPE_ACTION && opcode == EventComboDataProvider::ACTION_PLAY_MUSIC) {
                        ss << stringValue;
                    }

                    break;
                case EventComboDataProvider::ATT_SOUND:
                    if(type == TYPE_ACTION && opcode == EventComboDataProvider::ACTION_PLAY_SOUND) {
                        ss << stringValue;
                    }
                    break;
                case EventComboDataProvider::ATT_PROCEDURE:
                    if(value01 < 0) {
                        if(currentGameObject != NULL) {
                            ss << currentGameObject->name << " - " << currentGameObject->getProcedureById(-value01)->name;
                        }
                    } else {
                        ss << gameData->getProcedureById(value01)->name;
                    }


                    break;

                default:
                    ss << "x";
                    break;
                }

                break;
            case VALUE_TYPE_OBJECT2:
                if(idObject02 != -1) {
                    gameObject02 = gameData->searchGameObjectById(idObject02);
                    ss << gameObject02->name;
                }

                break;
            }



            return QString(ss.str().c_str());
        } else {
            return QString::fromUtf8(QApplication::tr("Mostra diálogo").toStdString().c_str());
        }

    }
}

QIcon EventData::getEventIcon() {
    if(newEvent) {
        return QIcon(":/icones_editor_eventos/data/event_editor_icons/new_event_icon.png");
    } else {
        if(type == TYPE_CONDITION) {
            return QIcon(":/icones_editor_eventos/data/event_editor_icons/condition_icon.png");
        } else {
            return QIcon(":/icones_editor_eventos/data/event_editor_icons/action_icon.png");
        }

    }

}

QIcon EventData::getObject01Icon() {
    if(newEvent) {
        return QIcon("");
    } else {
        GameData *gameData = GameData::getInstance();

        if(idObject01 > 0) {
            GameObject *gameObject01 = gameData->searchGameObjectById(idObject01);

            if(gameObject01) {
                return QIcon(QPixmap::fromImage(gameObject01->getIconImage()));
            } else {
                return QIcon("");
            }
        } else {
            std::list<GameObject*> specialObjects = eventComboDataProvider->getSpecialObjectList(type);

            foreach(GameObject *gameObject, specialObjects) {
                if(gameObject->id == idObject01) {
                    return QIcon(QPixmap::fromImage(gameObject->getIconImage()));
                }
            }

            return QIcon("");


        }


    }

    return QIcon("");
}

QIcon EventData::getObject02Icon() {
    if(newEvent) {
        return QIcon("");
    } else {
        GameData *gameData = GameData::getInstance();

        if(idObject02 != -1) {
            GameObject *gameObject02 = gameData->searchGameObjectById(idObject02);

            if(gameObject02) {
                return QIcon(QPixmap::fromImage(gameObject02->getIconImage()));
            }
        } else {
            return QIcon("");
        }


    }
}

void EventData::addChild(EventData *child) {
    child->parent = this;
    subEvents.push_back(child);

}
