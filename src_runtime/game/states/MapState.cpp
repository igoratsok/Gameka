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

#include "MapState.h"

MapState::MapState(StateManager *stateManager) {
	playerData = NULL;
	objectFunctions = ObjectFunctions::getInstance();
	interpreter = new Interpreter();
	soundManager = SoundManager::getInstance();
	this->stateManager = stateManager;
	modalManager = new ModalStack();

}

MapState::~MapState() {
	// TODO Auto-generated destructor stub
}



void MapState::mountObjects() {
	mapObjects.clear();

	playerData = PlayerData::getInstance();



	std::vector<GameObjectInstance* > *gameObjectInstances;
	gameObjectInstances = map->gameObjectInstances;

	mainObject = NULL;

	for(std::vector<GameObjectInstance*>::iterator it = gameObjectInstances->begin(); it != gameObjectInstances->end(); ++it) {
		GameObjectInstance *gameObjectInstance = *it;


		GameObject *gameObject = NULL;


		switch(gameObjectInstance->gameObject->type) {
		case GameObjectClass::EIGHT_MOVEMENT_OBJECT:
			gameObject = (GameObject*) ObjectFactory::mountEightMovement(gameObjectInstance);
			break;
		case GameObjectClass::CAR_MOVEMENT_OBJECT:
			gameObject = (GameObject*) ObjectFactory::mountVehicleMovement(gameObjectInstance);
			break;
		case GameObjectClass::PLATFORM_MOVEMENT_OBJECT:
			gameObject = (GameObject*) ObjectFactory::mountPlatformerMovement(gameObjectInstance);
			break;
		case GameObjectClass::STATIC_OBJECT:
			gameObject = (GameObject*) ObjectFactory::mountStaticObject(gameObjectInstance);
			break;
		case GameObjectClass::FIGHTING_MOVEMENT_OBJECT:
			gameObject = (GameObject*) ObjectFactory::mountPlatformerMovement(gameObjectInstance);
			break;
		case GameObjectClass::PONG_BALL_OBJECT:
			gameObject = (GameObject*) ObjectFactory::mountBouncingBallObject(gameObjectInstance);
			break;
		case GameObjectClass::MOUSE_MOVEMENT_OBJECT:
			gameObject = (GameObject*) ObjectFactory::mountMouseFollowMovementObject(gameObjectInstance);
			break;
		case GameObjectClass::NPC:
			gameObject = (GameObject*) ObjectFactory::mountNpcMovementObject(gameObjectInstance);
			break;
		case GameObjectClass::INIMIGO:
			gameObject = (GameObject*) ObjectFactory::mountEnemyMovementObject(gameObjectInstance);
			break;
		case GameObjectClass::ITEM:
			gameObject = (GameObject*) ObjectFactory::mountItemMovementObject(gameObjectInstance);
			break;
		default:

			break;
		}

		pushObject(gameObject);

		gameObject->setTilemap(map);

		if(gameObjectInstance->isCenter) {
			gameObject->setCenter();
		}

		if(gameObjectInstance->isMainObject) {
			mainObject = gameObject;
			playerData->setPlayer(gameObject);
		}

		gameObject->setObjectList(&mapObjects);
		gameObject->setSpatialHashmap(spatialHashmap);
		gameObject->setModalManager(modalManager);


	}

	/* corrigindo se o usuário tiver marcado algum GameObject como o principal,
	 * marcar o primeiro Personagem
	 */
	if(mainObject == NULL) {
		for(std::list<GameObject*>::iterator it = mapObjects.begin(); it != mapObjects.end(); ++it) {
			GameObject *gameObject = *it;

			switch(gameObject->gameObjectInstance->gameObject->type) {
			case GameObjectClass::EIGHT_MOVEMENT_OBJECT:
			case GameObjectClass::CAR_MOVEMENT_OBJECT:
			case GameObjectClass::PLATFORM_MOVEMENT_OBJECT:
			case GameObjectClass::STATIC_OBJECT:
			case GameObjectClass::FIGHTING_MOVEMENT_OBJECT:
			case GameObjectClass::PONG_BALL_OBJECT:
			case GameObjectClass::MOUSE_MOVEMENT_OBJECT:
				mainObject = gameObject;
				playerData->setPlayer(gameObject);
				break;


			default:

				break;
			}

			if(mainObject != NULL) {
				break;
			}
		}
	}

	/* teletransporta o objeto principal para a posição
	 * do teletransporte, caso tenha sido especificada
	 */

	if(mainObject != NULL &&  playerData->getTeleportPosition() != NULL) {
		Vector2* teleportPosition = playerData->getTeleportPosition();
		mainObject->position->x = teleportPosition->x;
		mainObject->position->y = teleportPosition->y;

		playerData->freeTeleportPosition();
	}

}

void MapState::correctObjectPositions() {
	for(std::list<GameObject*>::iterator it = mapObjects.begin(); it != mapObjects.end(); ++it) {
		GameObject* gameObject = *it;

		Rect *objectRect = gameObject->sprite->getRectWithoutRot();

		while(gameObject->autoCollision && gameObject->testBoxCollisionTile(30) && gameObject->position->y - objectRect->h >= 0) {
			gameObject->position->y--;
		}

		delete objectRect;
	}
}

void MapState::checkMainObjectDefaultEvents() {
	/* verifica se o Main Object colide com algum teleportArea */
	for(std::vector<TeleportArea*>::iterator it = map->teleportAreas->begin(); it != map->teleportAreas->end(); ++it) {
		TeleportArea *teleportArea = *it;

		if(mainObject != NULL && mainObject->sprite != NULL
				&& mainObject->sprite->getRectWithoutRot()->intersectsWith(&teleportArea->rect)) {
			stateManager->setMapState(teleportArea->mapId);

			if(teleportArea->mapPositionDetermined) {
				playerData->setTeleportPosition(Vector2(teleportArea->mapPosX, teleportArea->mapPosY));
			}

		}
	}

}

void MapState::setLevel(int idLevel) {
	this->idLevel = idLevel;
}

void MapState::load() {
	GameData *gameData = GameData::getInstance();
	gameData->freeGameObjectClassInstances();


	mainObject = NULL;

	if(idLevel == -1) {
		idLevel = gameData->idFirstMap;
	}


	if(idLevel == 0) {
		map = gameData->mapList->at(0);
	} else {
		map = gameData->searchMapById(idLevel);
	}

	if(map == NULL) {
		std::cout << "Mapa " << idLevel << " não encontrado. Abortando..." << std::endl;
		exit(1);
	}

	gameData->currentMap = map;



	ScrollManager::getInstance()->setTilemap(map);

	spatialHashmap = new SpatialHashmap(map->mapWidth*map->tileWidth, map->mapHeight*map->tileHeight, 100);

	mountObjects();
	correctObjectPositions();

	playerData->setCurrentMap(map);


	if(map->background != NULL) {
		for(std::vector<BackgroundLayerData*>::iterator it = map->background->layerList->begin();
				it != map->background->layerList->end(); ++it) {
			BackgroundLayerData *bgLayerData = *it;

			BackgroundLayer *backgroundLayer = new BackgroundLayer(bgLayerData, mainObject);

			backgroundLayers.push_back(backgroundLayer);
		}
	}

	objectFunctions->setGameObjectList(&mapObjects);
	objectFunctions->setAddGameObjectList(&addMapObjects);

	backgroundMusic = NULL;
	if(!map->music.empty()) {
		std::string diretorioMusic = std::string("musics/");
		diretorioMusic.append(map->music.c_str());

		if(map->loopMusic) {
			soundManager->playMusic(diretorioMusic, 99);
		} else {
			soundManager->playMusic(diretorioMusic, 2);
		}

	}

	TimerManager::getInstance()->resetMapTimer(0);


	if(map->dialogueData != NULL) {
		modalManager->pushModal(new DialogueText(map->dialogueData, DialogueText::POS_DOWN));
	}



}

void MapState::unload() {
	for(std::list<GameObject*>::iterator it = mapObjects.begin(); it != mapObjects.end(); ++it) {
		GameObject *gameObject = *it;
		delete gameObject;
	}

	delete interpreter;
	delete spatialHashmap;

	for(std::list<BackgroundLayer*>::iterator it = backgroundLayers.begin(); it != backgroundLayers.end(); ++it) {
		BackgroundLayer *bgLayer = *it;
		delete bgLayer;
	}

	gameData->clearInstancesFromClasses();
}

void MapState::pushObject(GameObject *gameObject) {
	gameObject->gameObjectInstance->gameObject->instances->push_back(gameObject);
	gameObject->setObjectList(&mapObjects);
	gameObject->setSpatialHashmap(spatialHashmap);
	gameObject->setModalManager(modalManager);
	gameObject->setTilemap(map);
	mapObjects.push_back(gameObject);
}

void MapState::removeObject(std::list<GameObject*>::iterator it) {
    GameObject *gameObject = *it;
    mapObjects.erase(it);



    gameObject->gameObjectInstance->gameObject->instances->remove(gameObject);
}

int MapState::update(int dt) {
	if(modalManager->modalActivated()) {
		if(modalManager->update(dt) == 1) {
			modalManager->popModal();
		}
	} else {
		spatialHashmap->clearBuckets();

		for(std::list<GameObject*>::iterator it = mapObjects.begin(); it != mapObjects.end(); ++it) {
			GameObject *gameObject = *it;
			spatialHashmap->registerObject(gameObject);
		}



		for(std::list<GameObject*>::iterator it = mapObjects.begin(); it != mapObjects.end(); ++it) {
			GameObject *gameObject = *it;
			int result = gameObject->update(dt);
			objectFunctions->processSkills(gameObject);


			if(result == -1) {
				std::list<GameObject*>::iterator it_aux = it;
				if(it == mapObjects.begin()) {
					it++;
				} else {
					it--;
				}

				if(gameObject == playerData->getPlayer()) {
					if(gameData->deathAction == GameData::DEATH_ACTION_RESET_MAP) {
						if(gameData->looseLifes) {
							playerData->addLives(-1);
						}
						stateManager->setMapState(map->key);
						playerData->resetHp();

						if(playerData->getLives() == 0) {
							stateManager->setGameOverState(map->key);
						}
						break;

					} else {
						stateManager->resetGame();
						break;
					}
				} else {
					removeObject(it_aux);
				}


			}
		}

		if(!gameData->gameObjectsToCreate->empty()) {
			for(std::list<GameObjectCreationData*>::iterator it = gameData->gameObjectsToCreate->begin(); it != gameData->gameObjectsToCreate->end(); ++it) {
				GameObjectCreationData *gocd = *it;

				objectFunctions->throwObject(gocd->thrower, gocd->throwable, gocd->throwIntensity, 0);

				delete gocd;
			}

			gameData->gameObjectsToCreate->clear();
		}


		while(!gameData->dialogueDatasToAdd.empty()) {
			modalManager->pushModal(new DialogueText(gameData->dialogueDatasToAdd.top(), DialogueText::POS_DOWN));
			gameData->dialogueDatasToAdd.pop();
		}




		checkMainObjectDefaultEvents();

		for(std::list<BackgroundLayer*>::iterator it = backgroundLayers.begin(); it != backgroundLayers.end(); ++it) {
			BackgroundLayer *backgroundLayer = *it;

			backgroundLayer->update(dt);
		}

		if(!addMapObjects.empty()) {
			for(std::vector<GameObject*>::iterator it = addMapObjects.begin(); it != addMapObjects.end(); ++it) {
				GameObject *gameObject = *it;

				pushObject(gameObject);
			}

			addMapObjects.clear();
		}

		interpreter->executeProcedure(gameData->procedureGlobalAlways, dt);

		if(gameData->nextMap != NULL) {
			int nextMap = *(gameData->nextMap);
			gameData->nextMap = NULL;
			stateManager->setMapState(nextMap);
		}
	}



	//std::cout << "dt: " << 1000/dt << std::endl;

	return 0;
}

void MapState::render(Screen *screen) {
	for(std::list<BackgroundLayer*>::iterator it = backgroundLayers.begin(); it != backgroundLayers.end(); ++it) {
		BackgroundLayer *backgroundLayer = *it;

		backgroundLayer->render(screen);
	}

	map->render(screen);

	std::list<GameObject*> zObjects;


	for(std::list<GameObject*>::iterator it = mapObjects.begin(); it != mapObjects.end(); ++it) {
		GameObject *gameObject = *it;
		if(gameObject->position->z == 0) {
			gameObject->render(screen);
		} else {
			zObjects.push_back(gameObject);
		}



	}

	// desenha os objetos que estiverem em z > 0 depois, para aparecerem acima dos outros

	for(std::list<GameObject*>::iterator it = zObjects.begin(); it != zObjects.end(); ++it) {
		GameObject *gameObject = *it;
		gameObject->render(screen);
	}


	if(playerData != NULL) {
		playerData->renderHud(screen);
	}

	modalManager->render(screen);
}
