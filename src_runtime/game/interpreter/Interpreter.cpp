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

#include "Interpreter.h"

std::deque<ProcedureData*>* Interpreter::procedureDataStack = NULL;

#define SET_ACTION_VALUE GameObject *gameObject02;		\
switch(eventData->valueType) { 	\
		case VALUE_TYPE_NUMBER: 							\
			value = eventData->value01; 					\
			break; 											\
		case VALUE_TYPE_VARIABLE: 							\
			value = eventData->variableValue->value;		\
			break; 											\
		case VALUE_TYPE_OBJECT2: 							\
															\
			break; 											\
		case VALUE_TYPE_OBJECT_ATTRIBUTE: 					\
			switch(eventData->instanceTypeObject02) {			\
			case -1:													\
				if(eventData->object02 != NULL &&						\
						!eventData->object02->instances->empty()) {		\
					value = ((GameObject*) *eventData->					\
							object02->instances->begin())->				\
							getAttributeById(eventData->value01);		\
				} else {												\
					return false;										\
				}														\
				break;													\
			case 0:														\
				value = thisObject->getAttributeById(eventData->value01);							\
			default:													\
				gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2); \
				if(gameObject02 != NULL) {								\
					value = gameObject02->getAttributeById(eventData->value01); \
				} else {												\
					return false;										\
				}														\
				break;													\
			}												\
				break; 											\
		case VALUE_TYPE_SPECIAL:							\
															\
			break;											\
		}													\

#define SET_CONDITION_VALUE	switch(eventData->valueType) {  \
		case VALUE_TYPE_NUMBER: 							\
			value = eventData->value01;						\
			break; 											\
		case VALUE_TYPE_VARIABLE: 							\
		value = eventData->variableValue->value;			\
			break; 											\
		case VALUE_TYPE_OBJECT2: 							\
															\
			break; 											\
		case VALUE_TYPE_OBJECT_ATTRIBUTE: 					\
			switch(eventData->instanceTypeObject02) {			\
			case -1:											\
				value = eventData->value01;						\
				values = eventData->object02->instances;		\
				break;											\
			case 0:												\
				value = thisObject->getAttributeById(eventData->value01);						\
				break;											\
			default:											\
				gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2);	\
				if(gameObject02 != NULL) {						\
					value = gameObject02->getAttributeById(eventData->value01);	\
				} else {										\
					values = eventData->object02->instances;	\
				}												\
																\
				break;											\
			}													\
			break; 											\
		case VALUE_TYPE_SPECIAL:							\
															\
			break;											\
		}													\

Interpreter::Interpreter() {
	pairStack = new std::deque<std::vector<GameObject*> >();
	thisGameObject = NULL;

	if(Interpreter::procedureDataStack == NULL) {
		Interpreter::procedureDataStack = new std::deque<ProcedureData*>();
	}

}

Interpreter::Interpreter(GameObject *thisGameObject) :
	thisGameObject(thisGameObject) {
	pairStack = new std::deque<std::vector<GameObject*> >();
	currentPairList = NULL;
}

Interpreter::~Interpreter() {
	if(!currentPairList) {
		delete currentPairList;
	}

}

void Interpreter::executeProcedure(ProcedureData* procedureData, int dt) {
	for(std::deque<ProcedureData*>::iterator it = Interpreter::procedureDataStack->begin(); it != Interpreter::procedureDataStack->end(); ++it) {
		ProcedureData *procedureDataIt = *it;

		if(procedureDataIt == procedureData) {
			return;
		}
	}

	Interpreter::procedureDataStack->push_front(procedureData);

	std::list<EventData*>::iterator pit = procedureData->events.begin();
	std::list<EventData*>* currentEvent = &procedureData->events;
	PAIRLIST* pairList;



	currentPairList = NULL;


	while(true) {
		if(pit == currentEvent->end()) {
			if(iteratorStack.empty()) {
				break;
			} else {
				if(currentPairList == NULL || currentPairList->empty()) {
					currentEvent = eventStack.top();
					pit = iteratorStack.top();
					delete currentPairList;
					currentPairList = pairListStack.top();

					eventStack.pop();
					iteratorStack.pop();
					pairListStack.pop();
					pairStack->pop_front();
				} else {
					currentPairList->pop_front();

					pit = currentEvent->begin();

					if(currentPairList->empty()) {
						continue;
					} else {
						pairStack->pop_front();
						pairStack->push_front(*currentPairList->begin());
					}



				}


			}
		}

		EventData *eventData = *pit;

		if(eventData->execute != NULL) {
			if((pairList = eventData->execute(eventData, pairStack, thisGameObject, dt))) {
				pit++;
				iteratorStack.push(pit);
				eventStack.push(currentEvent);
				pairListStack.push(currentPairList);

				pit = eventData->subEvents.begin();
				currentEvent = &eventData->subEvents;
				currentPairList = pairList;

				pairStack->push_front(*currentPairList->begin());
			} else {
				pit++;
			}
		} else {
			pit++;
		}


	}


	Interpreter::procedureDataStack->pop_front();



}

PAIRLIST* Interpreter::setValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01;

	if(eventData->object01 != NULL) {
		instances01 = eventData->object01->instances;


		GameObject *gameObject;
		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;
				float value = 0;
				SET_ACTION_VALUE;
				gameObject->setAttributeById(eventData->idAssociatedVariable, value);


			}

			return false;
			break;
		case 0:
			gameObject = thisObject;
			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			break;
		}

		if(gameObject != NULL) {
			float value = 0;
			SET_ACTION_VALUE;
			gameObject->setAttributeById(eventData->idAssociatedVariable, value);
		}
	} else {
		float value = 0;
		GameData *gameData = GameData::getInstance();
		SET_ACTION_VALUE;
		gameData->setAttributeById(eventData->idAssociatedVariable, value);
	}



	return false;
}

PAIRLIST* Interpreter::addValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {

	if(eventData->object01 != NULL) {
		std::list<GameObject*> *instances01 = eventData->object01->instances;

		GameObject *gameObject;
		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;
				float value = 0;
				SET_ACTION_VALUE;
				gameObject->setAttributeById(eventData->idAssociatedVariable, gameObject->getAttributeById(eventData->idAssociatedVariable) + value);
			}

			return false;
			break;
		case 0:
			gameObject = thisObject;
			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			break;
		}

		if(gameObject != NULL) {
			float value = 0;
			SET_ACTION_VALUE;
			gameObject->setAttributeById(eventData->idAssociatedVariable, gameObject->getAttributeById(eventData->idAssociatedVariable) + value);
		}
	} else {
		float value = 0;
		GameData *gameData = GameData::getInstance();
		SET_ACTION_VALUE;
		gameData->setAttributeById(eventData->idAssociatedVariable, gameData->getAttributeById(eventData->idAssociatedVariable) + value);
	}



	return false;
}


PAIRLIST* Interpreter::multValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {

	if(eventData->object01 != NULL) {
		std::list<GameObject*> *instances01 = eventData->object01->instances;

		GameObject *gameObject;
		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;
				float value = 0;
				SET_ACTION_VALUE;
				gameObject->setAttributeById(eventData->idAssociatedVariable, gameObject->getAttributeById(eventData->idAssociatedVariable) * value);
			}

			return false;
			break;
		case 0:
			gameObject = thisObject;
			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			break;
		}

		if(gameObject != NULL) {
			float value = 0;
			SET_ACTION_VALUE;
			gameObject->setAttributeById(eventData->idAssociatedVariable, gameObject->getAttributeById(eventData->idAssociatedVariable) * value);
		}

	} else {
		float value = 0;
		GameData *gameData = GameData::getInstance();
		SET_ACTION_VALUE;
		gameData->setAttributeById(eventData->idAssociatedVariable, gameData->getAttributeById(eventData->idAssociatedVariable) * value);
	}


	return false;

}

PAIRLIST* Interpreter::divValue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	if(eventData->object01 != NULL) {
		std::list<GameObject*> *instances01 = eventData->object01->instances;

		GameObject *gameObject;
		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;
				float value = 0;
				SET_ACTION_VALUE;
				gameObject->setAttributeById(eventData->idAssociatedVariable, gameObject->getAttributeById(eventData->idAssociatedVariable) / value);
			}

			return false;
			break;
		case 0:
			gameObject = thisObject;
			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			break;
		}

		if(gameObject != NULL) {
			float value = 0;
			SET_ACTION_VALUE;
			gameObject->setAttributeById(eventData->idAssociatedVariable, gameObject->getAttributeById(eventData->idAssociatedVariable) / value);
		}
	} else {
		float value = 0;
		GameData *gameData = GameData::getInstance();
		SET_ACTION_VALUE;
		gameData->setAttributeById(eventData->idAssociatedVariable, gameData->getAttributeById(eventData->idAssociatedVariable) / value);
	}



	return false;
}



PAIRLIST* Interpreter::playMusic(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	SoundManager *soundManager = SoundManager::getInstance();

	std::string diretorioMusic = std::string("musics/");
	diretorioMusic.append(eventData->stringValue.c_str());
	soundManager->playMusic(diretorioMusic, 2);


	return false;
}

PAIRLIST* Interpreter::pauseResumeMusic(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	SoundManager *soundManager = SoundManager::getInstance();

	soundManager->pauseResumeMusic();


	return false;
}


PAIRLIST* Interpreter::stopMusic(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	SoundManager *soundManager = SoundManager::getInstance();

	soundManager->stopMusic();


	return false;
}


PAIRLIST* Interpreter::changeMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	GameData *gameData = GameData::getInstance();

	gameData->nextMap = (int*) calloc(1, sizeof(int));
	*(gameData->nextMap) = eventData->value01;

	return false;
}


PAIRLIST* Interpreter::resetCurrentMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	GameData *gameData = GameData::getInstance();

	gameData->nextMap = (int*) calloc(1, sizeof(int));
	*(gameData->nextMap) = gameData->currentMap->key;

	return false;
}


PAIRLIST* Interpreter::nextMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	GameData *gameData = GameData::getInstance();

	if(gameData->findNextMap(gameData->currentMap) != NULL) {
		gameData->nextMap = (int*) calloc(1, sizeof(int));
		*(gameData->nextMap) = gameData->findNextMap(gameData->currentMap)->key;
	}


	return false;
}

PAIRLIST* Interpreter::callProcedure(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	GameData *gameData = GameData::getInstance();

	Interpreter *interpreter = new Interpreter(thisObject);
	interpreter->executeProcedure(eventData->procedureToCall, dt);
	delete interpreter;

	return false;
}


PAIRLIST* Interpreter::resetMapTimer(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	TimerManager *timerManager = TimerManager::getInstance();
	float value;

	SET_ACTION_VALUE;
	timerManager->resetMapTimer(value*1000);

	return false;
}


PAIRLIST* Interpreter::resetGlobalTimer(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	TimerManager *timerManager = TimerManager::getInstance();
	float value;

	SET_ACTION_VALUE;
	timerManager->resetGlobalTimer(value*1000);

	return false;
}



PAIRLIST* Interpreter::playSound(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	SoundManager *soundManager = SoundManager::getInstance();

	std::string diretorioSound = std::string("sfx/");
	diretorioSound.append(eventData->stringValue.c_str());
	soundManager->playSound(diretorioSound, 1);


	return false;
}

PAIRLIST* Interpreter::pauseResumeSound(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	SoundManager *soundManager = SoundManager::getInstance();

	soundManager->pauseResumeSounds();


	return false;
}


PAIRLIST* Interpreter::stopSound(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	SoundManager *soundManager = SoundManager::getInstance();

	soundManager->stopSound();


	return false;
}


PAIRLIST* Interpreter::plataformerJump(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;

	GameObject *gameObject;
	switch(eventData->instanceTypeObject01) {
	case -1:
		for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
			gameObject = *it;
			float value = 0;
			SET_ACTION_VALUE;
			gameObject->velocity->y = -(float)value/29.0f;

		}

		return false;
		break;
	case 0:
		gameObject = thisObject;
		break;
	default:
		gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

		break;
	}

	if(gameObject != NULL) {
		float value = 0;
		SET_ACTION_VALUE;
		gameObject->velocity->y = -(float)value/29.0f;
	}


	return false;
}


PAIRLIST* Interpreter::bounce(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;

	GameObject *gameObject;
	switch(eventData->instanceTypeObject01) {
	case -1:
		for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
			gameObject = *it;

			gameObject->bounceEvent(dt);

		}

		return false;
		break;
	case 0:
		gameObject = thisObject;
		break;
	default:
		gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

		break;
	}

	if(gameObject != NULL) {
		gameObject->bounceEvent(dt);
	}


	return false;
}

PAIRLIST* Interpreter::boost(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;

	GameObject *gameObject;
	switch(eventData->instanceTypeObject01) {
	case -1:
		for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
			gameObject = *it;
			float value = 0;
			SET_ACTION_VALUE;
			gameObject->velocity->x = gameObject->lastDirection->x*value;
			gameObject->velocity->y = gameObject->lastDirection->y*value;

		}

		return false;
		break;
	case 0:
		gameObject = thisObject;
		break;
	default:
		gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

		break;
	}

	if(gameObject != NULL) {
		float value = 0;
		SET_ACTION_VALUE;
		gameObject->velocity->x = gameObject->lastDirection->x*value;
		gameObject->velocity->y = gameObject->lastDirection->y*value;
	}


	return false;
}





PAIRLIST* Interpreter::throwObject(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;
	GameData *gamedata = GameData::getInstance();

	GameObject *gameObject;
	switch(eventData->instanceTypeObject01) {
	case -1:
		for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
			gameObject = *it;
			float value = 0;
			SET_ACTION_VALUE;

			gamedata->gameObjectsToCreate->push_back(new GameObjectCreationData(gameObject, eventData->object02, value));
		}

		return false;
		break;
	case 0:
		gameObject = thisObject;
		break;
	default:
		gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

		break;
	}

	if(gameObject != NULL) {
		float value = 0;
		SET_ACTION_VALUE;

		gamedata->gameObjectsToCreate->push_back(new GameObjectCreationData(gameObject, eventData->object02, value));
	}


	return false;
}




PAIRLIST* Interpreter::followObject(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;

	GameObject *gameObject;
	switch(eventData->instanceTypeObject01) {
	case -1:
		for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
			gameObject = *it;
			float value = 0;
			SET_ACTION_VALUE;

			switch(eventData->instanceTypeObject02) {
			case -1:
				if(eventData->object02 != NULL &&
						!eventData->object02->instances->empty()) {
					gameObject02 = ((GameObject*) *eventData->
							object02->instances->begin());
				} else {
					return false;
				}
				break;
			case 0:
				gameObject02 = thisObject;
			default:
				gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2);

				if(gameObject02 == NULL) {
					return false;
				}
				break;
			}

			gameObject->follow(gameObject02->getCenter(), dt, value);

		}

		return false;
		break;
	case 0:
		gameObject = thisObject;
		break;
	default:
		gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

		break;
	}

	if(gameObject != NULL) {
		float value = 0;
		SET_ACTION_VALUE;

		switch(eventData->instanceTypeObject02) {
		case -1:
			if(eventData->object02 != NULL &&
					!eventData->object02->instances->empty()) {
				gameObject02 = ((GameObject*) *eventData->
						object02->instances->begin());
			} else {
				return false;
			}
			break;
		case 0:
			gameObject02 = thisObject;
		default:
			gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2);

			if(gameObject02 == NULL) {
				return false;
			}
			break;
		}

		gameObject->follow(gameObject02->getCenter(), dt, value);
	}


	return false;
}


PAIRLIST* Interpreter::unfollowObject(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;

	GameObject *gameObject;
	switch(eventData->instanceTypeObject01) {
	case -1:
		for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
			gameObject = *it;
			float value = 0;
			SET_ACTION_VALUE;

			switch(eventData->instanceTypeObject02) {
			case -1:
				if(eventData->object02 != NULL &&
						!eventData->object02->instances->empty()) {
					gameObject02 = ((GameObject*) *eventData->
							object02->instances->begin());
				} else {
					return false;
				}
				break;
			case 0:
				gameObject02 = thisObject;
			default:
				gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2);

				if(gameObject02 == NULL) {
					return false;
				}
				break;
			}

			gameObject->moveAway(gameObject02->getCenter(), dt, value);

		}

		return false;
		break;
	case 0:
		gameObject = thisObject;
		break;
	default:
		gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

		break;
	}

	if(gameObject != NULL) {
		float value = 0;
		SET_ACTION_VALUE;

		switch(eventData->instanceTypeObject02) {
		case -1:
			if(eventData->object02 != NULL &&
					!eventData->object02->instances->empty()) {
				gameObject02 = ((GameObject*) *eventData->
						object02->instances->begin());
			} else {
				return false;
			}
			break;
		case 0:
			gameObject02 = thisObject;
		default:
			gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2);

			if(gameObject02 == NULL) {
				return false;
			}
			break;
		}

		gameObject->moveAway(gameObject02->getCenter(), dt, value);
	}


	return false;
}



PAIRLIST* Interpreter::equalThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {

	PAIRLIST *pairList;
	pairList = new PAIRLIST();

	GameObject *gameObject;
	std::list<GameObject*> *values;
	float value;
	GameObject *gameObject02 = NULL;


	if(eventData->idAssociatedVariable == GameObject::ATT_INSTANCE_NUMBER) {
		values = NULL;

		SET_CONDITION_VALUE;

		equalThanTest(values, value, NULL, eventData->object01->instances->size(), eventData, gameObject02, pairList);

	} else {
		if(eventData->object01 != NULL) {
			std::list<GameObject*> *instances01 = eventData->object01->instances;

			switch(eventData->instanceTypeObject01) {
			case -1:
				for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
					gameObject = *it;

					values = NULL;

					SET_CONDITION_VALUE;

					equalThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);


				}
				break;
			case 0:
				gameObject = thisObject;

				values = NULL;

				SET_CONDITION_VALUE;

				equalThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

				break;
			default:
				gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

				values = NULL;

				SET_CONDITION_VALUE;

				equalThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);
				break;
			}

		} else {
			GameData *gameData = GameData::getInstance();
			values = NULL;

			SET_CONDITION_VALUE;

			equalThanTest(values, value, gameData->globalObject, gameData->globalObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

		}
	}





	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}


}

// gameObject->getAttributeById(eventData->idAssociatedVariable)

void Interpreter::equalThanTest(std::list<GameObject*> *values, float value,
		GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList) {
	if(values == NULL) {
		if((obj1Value == value) != eventData->negate) {
			std::vector<GameObject*> pair = std::vector<GameObject*>(2);
			pair[0] = gameObject;
			pair[1] = gameObject02;
			pairList->push_back(pair);
		}
	} else {
		for(std::list<GameObject*>::iterator it = values->begin(); it != values->end(); ++it) {
			GameObject *gameObject02 = *it;

			if((obj1Value == gameObject02->getAttributeById(value)) != eventData->negate) {
				std::vector<GameObject*> pair = std::vector<GameObject*>(2);
				pair[0] = gameObject;
				pair[1] = gameObject02;
				pairList->push_back(pair);
			}
		}
	}
}




PAIRLIST* Interpreter::greaterThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	PAIRLIST *pairList;
	pairList = new PAIRLIST();

	GameObject *gameObject;
	std::list<GameObject*> *values;
	float value;
	GameObject *gameObject02 = NULL;


	if(eventData->idAssociatedVariable == GameObject::ATT_INSTANCE_NUMBER) {
		values = NULL;

		SET_CONDITION_VALUE;

		greaterThanTest(values, value, NULL, eventData->object01->instances->size(), eventData, gameObject02, pairList);

	} else {
		if(eventData->object01 != NULL) {
			std::list<GameObject*> *instances01 = eventData->object01->instances;

			switch(eventData->instanceTypeObject01) {
			case -1:
				for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
					gameObject = *it;

					values = NULL;

					SET_CONDITION_VALUE;

					greaterThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);


				}
				break;
			case 0:
				gameObject = thisObject;

				values = NULL;

				SET_CONDITION_VALUE;

				greaterThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

				break;
			default:
				gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

				values = NULL;

				SET_CONDITION_VALUE;

				greaterThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);
				break;
			}

		} else {
			GameData *gameData = GameData::getInstance();
			values = NULL;

			SET_CONDITION_VALUE;

			greaterThanTest(values, value, gameData->globalObject, gameData->globalObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

		}

	}


	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}

}

void Interpreter::greaterThanTest(std::list<GameObject*> *values, float value,
		GameObject *gameObject, float obj1Value,  EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList) {
	if(values == NULL) {

		if((obj1Value > value) != eventData->negate) {
			std::vector<GameObject*> pair = std::vector<GameObject*>(2);
			pair[0] = gameObject;
			pair[1] = gameObject02;
			pairList->push_back(pair);
		}
	} else {
		for(std::list<GameObject*>::iterator it = values->begin(); it != values->end(); ++it) {
			GameObject *gameObject02 = *it;

			if((obj1Value > gameObject02->getAttributeById(value)) != eventData->negate) {
				std::vector<GameObject*> pair = std::vector<GameObject*>(2);
				pair[0] = gameObject;
				pair[1] = gameObject02;
				pairList->push_back(pair);
			}
		}
	}
}



PAIRLIST* Interpreter::lessThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	PAIRLIST *pairList;
	pairList = new PAIRLIST();

	GameObject *gameObject;
	std::list<GameObject*> *values;
	float value;
	GameObject *gameObject02 = NULL;

	if(eventData->idAssociatedVariable == GameObject::ATT_INSTANCE_NUMBER) {
		values = NULL;

		SET_CONDITION_VALUE;

		lessThanTest(values, value, NULL, eventData->object01->instances->size(), eventData, gameObject02, pairList);

	} else {
		if(eventData->object01 != NULL) {
			std::list<GameObject*> *instances01 = eventData->object01->instances;

			switch(eventData->instanceTypeObject01) {
			case -1:
				for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
					gameObject = *it;

					values = NULL;

					SET_CONDITION_VALUE;

					lessThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);


				}
				break;
			case 0:
				gameObject = thisObject;

				values = NULL;

				SET_CONDITION_VALUE;

				lessThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

				break;
			default:
				gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

				values = NULL;

				SET_CONDITION_VALUE;

				lessThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);
				break;
			}

		} else {
			GameData *gameData = GameData::getInstance();
			values = NULL;

			SET_CONDITION_VALUE;

			lessThanTest(values, value, gameData->globalObject, gameData->globalObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

		}

	}


	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}

}

void Interpreter::lessThanTest(std::list<GameObject*> *values, float value,
		GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList) {
	if(values == NULL) {
		if((obj1Value < value) != eventData->negate) {
			std::vector<GameObject*> pair = std::vector<GameObject*>(2);
			pair[0] = gameObject;
			pair[1] = gameObject02;
			pairList->push_back(pair);
		}
	} else {
		for(std::list<GameObject*>::iterator it = values->begin(); it != values->end(); ++it) {
			GameObject *gameObject02 = *it;

			if((obj1Value < gameObject02->getAttributeById(value)) != eventData->negate) {
				std::vector<GameObject*> pair = std::vector<GameObject*>(2);
				pair[0] = gameObject;
				pair[1] = gameObject02;
				pairList->push_back(pair);
			}
		}
	}
}


PAIRLIST* Interpreter::lessOrEqualThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	PAIRLIST *pairList;
	pairList = new PAIRLIST();

	GameObject *gameObject;
	std::list<GameObject*> *values;
	float value;
	GameObject *gameObject02 = NULL;


	if(eventData->idAssociatedVariable == GameObject::ATT_INSTANCE_NUMBER) {
		values = NULL;

		SET_CONDITION_VALUE;

		lessOrEqualThanTest(values, value, NULL, eventData->object01->instances->size(), eventData, gameObject02, pairList);

	} else {
		if(eventData->object01 != NULL) {
			std::list<GameObject*> *instances01 = eventData->object01->instances;

			switch(eventData->instanceTypeObject01) {
			case -1:
				for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
					gameObject = *it;

					values = NULL;

					SET_CONDITION_VALUE;

					lessOrEqualThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);


				}
				break;
			case 0:
				gameObject = thisObject;

				values = NULL;

				SET_CONDITION_VALUE;

				lessOrEqualThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

				break;
			default:
				gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

				values = NULL;

				SET_CONDITION_VALUE;

				lessOrEqualThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);
				break;
			}

		} else {
			GameData *gameData = GameData::getInstance();
			values = NULL;

			SET_CONDITION_VALUE;

			lessOrEqualThanTest(values, value, gameData->globalObject, gameData->globalObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

		}

	}


	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}

}

void Interpreter::lessOrEqualThanTest(std::list<GameObject*> *values, float value,
		GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList) {
	if(values == NULL) {
		if((obj1Value <= value) != eventData->negate) {
			std::vector<GameObject*> pair = std::vector<GameObject*>(2);
			pair[0] = gameObject;
			pair[1] = gameObject02;
			pairList->push_back(pair);
		}
	} else {
		for(std::list<GameObject*>::iterator it = values->begin(); it != values->end(); ++it) {
			GameObject *gameObject02 = *it;

			if((obj1Value <= gameObject02->getAttributeById(value)) != eventData->negate) {
				std::vector<GameObject*> pair = std::vector<GameObject*>(2);
				pair[0] = gameObject;
				pair[1] = gameObject02;
				pairList->push_back(pair);
			}
		}
	}
}



PAIRLIST* Interpreter::greaterOrEqualThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	PAIRLIST *pairList;
	pairList = new PAIRLIST();

	GameObject *gameObject;
	std::list<GameObject*> *values;
	float value;
	GameObject *gameObject02 = NULL;


	if(eventData->idAssociatedVariable == GameObject::ATT_INSTANCE_NUMBER) {
		values = NULL;

		SET_CONDITION_VALUE;

		greaterOrEqualThanTest(values, value, NULL, eventData->object01->instances->size(), eventData, gameObject02, pairList);

	} else {
		if(eventData->object01 != NULL) {
			std::list<GameObject*> *instances01 = eventData->object01->instances;

			switch(eventData->instanceTypeObject01) {
			case -1:
				for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
					gameObject = *it;

					values = NULL;

					SET_CONDITION_VALUE;

					greaterOrEqualThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);


				}
				break;
			case 0:
				gameObject = thisObject;

				values = NULL;

				SET_CONDITION_VALUE;

				greaterOrEqualThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

				break;
			default:
				gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

				values = NULL;

				SET_CONDITION_VALUE;

				greaterOrEqualThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);
				break;
			}

		} else {
			GameData *gameData = GameData::getInstance();
			values = NULL;

			SET_CONDITION_VALUE;

			greaterOrEqualThanTest(values, value, gameData->globalObject, gameData->globalObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

		}

	}

	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}
}

void Interpreter::greaterOrEqualThanTest(std::list<GameObject*> *values, float value,
		GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList) {
	if(values == NULL) {
		if((obj1Value >= value) != eventData->negate) {
			std::vector<GameObject*> pair = std::vector<GameObject*>(2);
			pair[0] = gameObject;
			pair[1] = gameObject02;
			pairList->push_back(pair);
		}
	} else {
		for(std::list<GameObject*>::iterator it = values->begin(); it != values->end(); ++it) {
			GameObject *gameObject02 = *it;

			if((obj1Value >= gameObject02->getAttributeById(value)) != eventData->negate) {
				std::vector<GameObject*> pair = std::vector<GameObject*>(2);
				pair[0] = gameObject;
				pair[1] = gameObject02;
				pairList->push_back(pair);
			}
		}
	}
}



PAIRLIST* Interpreter::differentThan(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	PAIRLIST *pairList;
	pairList = new PAIRLIST();

	GameObject *gameObject;
	std::list<GameObject*> *values;
	float value;
	GameObject *gameObject02 = NULL;


	if(eventData->idAssociatedVariable == GameObject::ATT_INSTANCE_NUMBER) {
		values = NULL;

		SET_CONDITION_VALUE;

		differentThanTest(values, value, NULL, eventData->object01->instances->size(), eventData, gameObject02, pairList);

	} else {
		if(eventData->object01 != NULL) {
			std::list<GameObject*> *instances01 = eventData->object01->instances;

			switch(eventData->instanceTypeObject01) {
			case -1:
				for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
					gameObject = *it;

					values = NULL;

					SET_CONDITION_VALUE;

					differentThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);


				}
				break;
			case 0:
				gameObject = thisObject;

				values = NULL;

				SET_CONDITION_VALUE;

				differentThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

				break;
			default:
				gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

				values = NULL;

				SET_CONDITION_VALUE;

				differentThanTest(values, value, gameObject, gameObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);
				break;
			}

		} else {
			GameData *gameData = GameData::getInstance();
			values = NULL;

			SET_CONDITION_VALUE;

			differentThanTest(values, value, gameData->globalObject, gameData->globalObject->getAttributeById(eventData->idAssociatedVariable), eventData, gameObject02, pairList);

		}

	}



	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}
}

void Interpreter::differentThanTest(std::list<GameObject*> *values, float value,
		GameObject *gameObject, float obj1Value, EventData *eventData, GameObject *gameObject02, PAIRLIST *pairList) {
	if(values == NULL) {
		if((obj1Value != value) != eventData->negate) {
			std::vector<GameObject*> pair = std::vector<GameObject*>(2);
			pair[0] = gameObject;
			pair[1] = gameObject02;
			pairList->push_back(pair);
		}
	} else {
		for(std::list<GameObject*>::iterator it = values->begin(); it != values->end(); ++it) {
			GameObject *gameObject02 = *it;

			if((obj1Value != gameObject02->getAttributeById(value)) != eventData->negate) {
				std::vector<GameObject*> pair = std::vector<GameObject*>(2);
				pair[0] = gameObject;
				pair[1] = gameObject02;
				pairList->push_back(pair);
			}
		}
	}
}



PAIRLIST* Interpreter::collidesSimpleWith(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;
	PAIRLIST *pairList;

	pairList = new PAIRLIST();

	GameObject *gameObject02 = NULL;



	for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
		GameObject *gameObject = *it;


		std::list<GameObject*> *gameObject2List;
		GameObject *gameObject02 = NULL;

		switch(eventData->instanceTypeObject02) {
		case -1:
			gameObject2List = eventData->object02->instances;
			break;
		case 0:
			gameObject02 = thisObject;
			break;
		default:
			gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2);
			break;
		}

		if(!gameObject2List->empty()) {
			for(std::list<GameObject*>::iterator it2 = gameObject2List->begin(); it2 != gameObject2List->end(); ++it2) {
				GameObject *gameObject02 = *it2;

				if((gameObject02->collidesWith(gameObject)) != eventData->negate) {
					std::vector<GameObject*> pair = std::vector<GameObject*>(2);
					pair[0] = gameObject;
					pair[1] = gameObject02;
					pairList->push_back(pair);
				}

			}
		} else {
			if(gameObject02 != NULL) {
				if((gameObject02->collidesWith(gameObject)) != eventData->negate) {
					std::vector<GameObject*> pair = std::vector<GameObject*>(2);
					pair[0] = gameObject;
					pair[1] = gameObject02;
					pairList->push_back(pair);
				}
			} else {
				return false;
			}
		}







	}

	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}

}


PAIRLIST* Interpreter::collidesPixelWith(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;
	PAIRLIST *pairList;

	pairList = new PAIRLIST();

	GameObject *gameObject02 = NULL;



	for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
		GameObject *gameObject = *it;


		std::list<GameObject*> *gameObject2List;
		GameObject *gameObject02;

		switch(eventData->instanceTypeObject02) {
		case -1:
			gameObject2List = eventData->object02->instances;
			break;
		case 0:
			gameObject02 = thisObject;
			break;
		default:
			gameObject02 = pairStack->at((eventData->instanceTypeObject02 - 1)/2).at((eventData->instanceTypeObject02 - 1)%2);
			break;
		}

		if(!gameObject2List->empty()) {
			for(std::list<GameObject*>::iterator it2 = gameObject2List->begin(); it2 != gameObject2List->end(); ++it2) {
				GameObject *gameObject02 = *it2;

				if((gameObject02->collidesPixelWith(gameObject)) != eventData->negate) {
					std::vector<GameObject*> pair = std::vector<GameObject*>(2);
					pair[0] = gameObject;
					pair[1] = gameObject02;
					pairList->push_back(pair);
				}

			}
		} else {
			if(gameObject02 != NULL) {
				if((gameObject02->collidesPixelWith(gameObject)) != eventData->negate) {
					std::vector<GameObject*> pair = std::vector<GameObject*>(2);
					pair[0] = gameObject;
					pair[1] = gameObject02;
					pairList->push_back(pair);
				}
			} else {
				return false;
			}
		}







	}

	if(pairList->empty()) {
		delete pairList;
		return NULL;
	} else {
		return pairList;
	}

}

PAIRLIST* Interpreter::buttonDown(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	InputManager *inputManager = InputManager::getInstance();

	PAIRLIST* pairList;

	pairList = new PAIRLIST();


	if((inputManager->isKeyDown(eventData->value01)) != eventData->negate) {
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}

}

PAIRLIST* Interpreter::buttonInstantPress(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	InputManager *inputManager = InputManager::getInstance();

	PAIRLIST* pairList;

	pairList = new PAIRLIST();


	if((inputManager->isKeyPressed(eventData->value01)) != eventData->negate) {
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}

}


PAIRLIST* Interpreter::mouseDown(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	InputManager *inputManager = InputManager::getInstance();

	PAIRLIST* pairList;

	pairList = new PAIRLIST();


	if((inputManager->isMouseDown(eventData->value01)) != eventData->negate) {
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}

}


PAIRLIST* Interpreter::mouseInstantPress(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	InputManager *inputManager = InputManager::getInstance();

	PAIRLIST* pairList;

	pairList = new PAIRLIST();


	if((inputManager->isMousePressed(eventData->value01)) != eventData->negate) {
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}

}

PAIRLIST* Interpreter::isCurrentMap(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	InputManager *inputManager = InputManager::getInstance();

	PAIRLIST* pairList;

	pairList = new PAIRLIST();

	GameData *gameData = GameData::getInstance();

	Tilemap *valueMap = gameData->searchMapById(eventData->value01);

	if((valueMap == gameData->currentMap) != eventData->negate) {
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}

}

PAIRLIST* Interpreter::isObjectLeftSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;
		PAIRLIST *pairList;

		pairList = new PAIRLIST();

		GameObject *gameObject;
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);



		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;

				if((gameObject->isInMapLeftSide()) != eventData->negate) {
					pair[0] = gameObject;
					pair[1] = NULL;
					pairList->push_back(pair);

				}


			}
			break;
		case 0:
			gameObject = thisObject;

			if((gameObject->isInMapLeftSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			if((gameObject->isInMapLeftSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		}


		if(pairList->empty()) {
			delete pairList;
			return NULL;
		} else {
			return pairList;
		}


}


PAIRLIST* Interpreter::isObjectUpSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;
		PAIRLIST *pairList;

		pairList = new PAIRLIST();

		GameObject *gameObject;
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);



		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;

				if((gameObject->isInMapUpSide()) != eventData->negate) {
					pair[0] = gameObject;
					pair[1] = NULL;
					pairList->push_back(pair);

				}


			}
			break;
		case 0:
			gameObject = thisObject;

			if((gameObject->isInMapUpSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			if((gameObject->isInMapUpSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		}


		if(pairList->empty()) {
			delete pairList;
			return NULL;
		} else {
			return pairList;
		}


}


PAIRLIST* Interpreter::isObjectRightSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;
		PAIRLIST *pairList;

		pairList = new PAIRLIST();

		GameObject *gameObject;
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);



		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;

				if((gameObject->isInMapRightSide()) != eventData->negate) {
					pair[0] = gameObject;
					pair[1] = NULL;
					pairList->push_back(pair);

				}


			}
			break;
		case 0:
			gameObject = thisObject;

			if((gameObject->isInMapRightSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			if((gameObject->isInMapRightSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		}


		if(pairList->empty()) {
			delete pairList;
			return NULL;
		} else {
			return pairList;
		}


}


PAIRLIST* Interpreter::isObjectDownSide(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	std::list<GameObject*> *instances01 = eventData->object01->instances;
		PAIRLIST *pairList;

		pairList = new PAIRLIST();

		GameObject *gameObject;
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);



		switch(eventData->instanceTypeObject01) {
		case -1:
			for(std::list<GameObject*>::iterator it = instances01->begin(); it != instances01->end(); ++it) {
				gameObject = *it;

				if((gameObject->isInMapDownSide()) != eventData->negate) {
					pair[0] = gameObject;
					pair[1] = NULL;
					pairList->push_back(pair);

				}


			}
			break;
		case 0:
			gameObject = thisObject;

			if((gameObject->isInMapDownSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		default:
			gameObject = pairStack->at((eventData->instanceTypeObject01 - 1)/2).at((eventData->instanceTypeObject01 - 1)%2);

			if((gameObject->isInMapDownSide()) != eventData->negate) {
				pair[0] = gameObject;
				pair[1] = NULL;
				pairList->push_back(pair);

				return pairList;
			}


			break;
		}


		if(pairList->empty()) {
			delete pairList;
			return NULL;
		} else {
			return pairList;
		}


}

PAIRLIST* Interpreter::isSoundPlaying(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	InputManager *inputManager = InputManager::getInstance();

	PAIRLIST* pairList;

	pairList = new PAIRLIST();

	SoundManager *soundManager = SoundManager::getInstance();



	if((soundManager->isSoundPlaying()) != eventData->negate) {
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}

}


PAIRLIST* Interpreter::isMusicPlaying(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	InputManager *inputManager = InputManager::getInstance();

	PAIRLIST* pairList;

	pairList = new PAIRLIST();

	SoundManager *soundManager = SoundManager::getInstance();



	if((soundManager->isMusicPlaying()) != eventData->negate) {
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}

}

PAIRLIST* Interpreter::everySeconds(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	float value;
	GameObject *gameObject02 = NULL;
	PAIRLIST* pairList;
	std::list<GameObject*> *values;

	eventData->everyTimer += dt;

	SET_CONDITION_VALUE;


	if(eventData->everyTimer > value) {
		eventData->everyTimer = 0;
		std::vector<GameObject*> pair = std::vector<GameObject*>(2);

		pair[0] = NULL;
		pair[1] = NULL;
		pairList->push_back(pair);

		return pairList;
	} else {
		return NULL;
	}
}

PAIRLIST* Interpreter::executeDialogue(EventData *eventData, std::deque<std::vector<GameObject*> > *pairStack, GameObject *thisObject, int dt) {
	GameData *gameData = GameData::getInstance();

	gameData->dialogueDatasToAdd.push(eventData->dialogueData);

	return NULL;
}

