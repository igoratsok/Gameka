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

#include "GameData.h"

int GameData::SOFTWARE_CURRENT_VERSION = 0;
int GameData::MAGIC_NUMBER = 0xAFACABBE;
GameData *GameData::singleton = NULL;


GameData::GameData() {
	// TODO Auto-generated constructor stub
	arg1 = NULL;
	currentMap = NULL;
	nextMap = NULL;
	gameObjectsToCreate = new std::list<GameObjectCreationData*>();
	variableList = new std::vector<VariableData*>();

}

GameData::~GameData() {
	// TODO Auto-generated destructor stub
}

GameData *GameData::getInstance() {
	if(singleton == NULL) singleton = new GameData();

	return singleton;
}

void GameData::reorganizeVariableData() {
	int maiorId = 0;
	for(std::vector<VariableData*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
		VariableData *variableData = *it;

		if(variableData->id > maiorId) {
			maiorId = variableData->id;
		}
	}

	std::vector<VariableData*> *oVariableList = new std::vector<VariableData*>(maiorId + 1, (VariableData*) 0);

	for(std::vector<VariableData*>::iterator it = variableList->begin(); it != variableList->end(); ++it) {
		VariableData *variableData = *it;
		oVariableList->at(variableData->id) = variableData;

	}

	delete variableList;
	variableList = oVariableList;

	globalObject = new GameObject();
	globalObject->gameObjectInstance = new GameObjectInstance();
	globalObject->gameObjectInstance->gameObject = new GameObjectClass();
	globalObject->gameObjectInstance->gameObject->variableList = variableList;

	for(std::vector<GameObjectClass*>::iterator itobj = objectList->begin(); itobj != objectList->end(); ++itobj) {
		GameObjectClass *gameObject = *itobj;

		int maiorId = 0;
		for(std::vector<VariableData*>::iterator it = gameObject->variableList->begin(); it != gameObject->variableList->end(); ++it) {
			VariableData *variableData = *it;

			if(variableData->id > maiorId) {
				maiorId = variableData->id;
			}
		}

		std::vector<VariableData*> *oVariableList = new std::vector<VariableData*>(maiorId + 1, (VariableData*) 0);

		for(std::vector<VariableData*>::iterator it = gameObject->variableList->begin(); it != gameObject->variableList->end(); ++it) {
			VariableData *variableData = *it;
			oVariableList->at(variableData->id) = variableData;

		}

		delete gameObject->variableList;
		gameObject->variableList = oVariableList;

	}
}


void GameData::createObtainedItemsAndObjectsToBounceArrays() {
	int maiorIdItem = 0;

	for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
		GameObjectClass *object = *it;

		if(object->id > maiorIdItem) {
			maiorIdItem = object->id;
		}
	}

	for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
		GameObjectClass *object = *it;

		object->obtainedItems = new std::vector<bool>(maiorIdItem+1, false);

		object->arrayObjectsToBounce = new std::vector<bool>(maiorIdItem+1, false);
		for(std::list<GameObjectClass*>::iterator it = object->listObjectsToBounce.begin(); it != object->listObjectsToBounce.end(); ++it) {
			GameObjectClass *objectIt = *it;

			object->arrayObjectsToBounce->at(objectIt->id) = true;
		}

	}
}

bool GameData::preprocessPointers() {
	reorganizeVariableData();
	createObtainedItemsAndObjectsToBounceArrays();

	// percorrer todos os eventos globais computando os ponteiros dos objetos
	// previamente (de forma a economizar processamento ingame)
	preprocessProcedure(procedureGlobalStart);
	preprocessProcedure(procedureGlobalAlways);
	preprocessProcedure(procedureGlobalEnd);

	for(std::vector<ProcedureData*>::iterator it = procedureList->begin(); it != procedureList->end(); ++it) {
		ProcedureData *procedureData = *it;

		preprocessProcedure(procedureData);
	}

	for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
		GameObjectClass *gameObjectClass = *it;

		preprocessProcedure(gameObjectClass->procedureGlobalStart, gameObjectClass);
		preprocessProcedure(gameObjectClass->procedureGlobalAlways, gameObjectClass);
		preprocessProcedure(gameObjectClass->procedureGlobalEnd, gameObjectClass);

		for(std::vector<ProcedureData*>::iterator it2 = gameObjectClass->procedureList->begin(); it2 != gameObjectClass->procedureList->end(); ++it2) {
			ProcedureData *proceduredata = *it2;

			preprocessProcedure(proceduredata, gameObjectClass);
		}

		if(gameObjectClass->ativaEvento) {
			if(gameObjectClass->ativaEventoIdEvento  > 0) {
				gameObjectClass->ativaEventoProcedure = getProcedureById(gameObjectClass->ativaEventoIdEvento);
			} else {
				gameObjectClass->ativaEventoProcedure = getProcedureById(-gameObjectClass->ativaEventoIdEvento);
			}
		}

		if(gameObjectClass->incrementaVariavel) {
			if(gameObjectClass->incrementaVariavelIdVariavel > 0) {
				gameObjectClass->incrementaVariavelVariable = getVariableById(gameObjectClass->incrementaVariavelIdVariavel);
			} else {
				gameObjectClass->incrementaVariavelVariable = getVariableById(-gameObjectClass->incrementaVariavelIdVariavel);
			}
		}


	}

	preprocessItemLevelSkills();

	return true;
}

bool GameData::preprocessProcedure(ProcedureData *procedureData, GameObjectClass *gameObjectClass) {
	preprocessEventList(&procedureData->events, gameObjectClass);

	return true;
}

bool GameData::preprocessEventList(std::list<EventData*> *eventList, GameObjectClass *gameObjectClass) {
	for(std::list<EventData*>::iterator it = eventList->begin(); it != eventList->end(); ++it) {
		EventData *eventData = *it;

		preprocessEvent(eventData, gameObjectClass);

		preprocessEventList(&eventData->subEvents, gameObjectClass);
	}

	return true;
}

bool GameData::preprocessEvent(EventData *eventData, GameObjectClass *gameObjectClass) {
	eventData->object01 = searchGameObjectById(eventData->idObject01);
	eventData->object02 = searchGameObjectById(eventData->idObject02);



	if(!eventData->newEvent) {
		if(eventData->type == EventData::TYPE_ACTION) {
			switch(eventData->opcode) {
			case EventData::ACTION_SET_VALUE:
				eventData->execute = &Interpreter::setValue;
				break;
			case EventData::ACTION_ADD_VALUE:
				eventData->execute = &Interpreter::addValue;
				break;
			case EventData::ACTION_DIV_VALUE:
				eventData->execute = &Interpreter::divValue;
				break;
			case EventData::ACTION_MULT_VALUE:
				eventData->execute = &Interpreter::multValue;
				break;
			case EventData::ACTION_PLAY_MUSIC:
				eventData->execute = &Interpreter::playMusic;
				break;
			case EventData::ACTION_TOOGLE_PAUSE_MUSIC:
				eventData->execute = &Interpreter::pauseResumeMusic;
				break;
			case EventData::ACTION_STOP_MUSIC:
				eventData->execute = &Interpreter::stopMusic;
				break;
			case EventData::ACTION_PLAY_SOUND:
				eventData->execute = &Interpreter::playSound;
				break;
			case EventData::ACTION_TOGGLE_PAUSE_SOUND:
				eventData->execute = &Interpreter::pauseResumeSound;
				break;
			case EventData::ACTION_STOP_SOUND:
				eventData->execute = &Interpreter::stopSound;
				break;
			case EventData::ACTION_SET_MAP:
				eventData->execute = &Interpreter::changeMap;
				break;
			case EventData::ACTION_RESET_MAP:
				eventData->execute = &Interpreter::resetCurrentMap;
				break;
			case EventData::ACTION_CALL_PROCEDURE:
				eventData->execute = &Interpreter::callProcedure;

				if(eventData->value01 < 0) {
					eventData->procedureToCall = gameObjectClass->getProcedureById(-eventData->value01);
				} else {
					this->getProcedureById(eventData->value01);
				}

				break;
			case EventData::ACTION_RESET_MAP_TIMER:
				eventData->execute = &Interpreter::resetMapTimer;
				break;
			case EventData::ACTION_RESET_GAME_TIMER:
				eventData->execute = &Interpreter::resetGlobalTimer;
				break;
			case EventData::ACTION_PLATFORM_JUMP:
				eventData->execute = &Interpreter::plataformerJump;
				break;
			case EventData::ACTION_BOUNCE:
				eventData->execute = &Interpreter::bounce;
				break;
			case EventData::ACTION_BOOST:
				eventData->execute = &Interpreter::boost;
				break;
			case EventData::ACTION_THROW_OBJECT:
				eventData->execute = &Interpreter::throwObject;
				break;
			case EventData::ACTION_FOLLOW_OBJECT:
				eventData->execute = &Interpreter::followObject;
				break;
			case EventData::ACTION_UNFOLLOW_OBJECT:
				eventData->execute = &Interpreter::unfollowObject;
				break;
			case EventData::ACTION_NEXT_MAP:
				eventData->execute = &Interpreter::nextMap;
				break;
			}
		} else if(eventData->type == EventData::TYPE_CONDITION){
			switch(eventData->opcode) {
			case EventData::COND_EQUAL:
				eventData->execute = &Interpreter::equalThan;
				break;
			case EventData::COND_DIFFERENT:
				eventData->execute = &Interpreter::differentThan;
				break;
			case EventData::COND_LESS:
				eventData->execute = &Interpreter::lessThan;
				break;
			case EventData::COND_LESS_EQUAL:
				eventData->execute = &Interpreter::lessOrEqualThan;
				break;
			case EventData::COND_GREATER:
				eventData->execute = &Interpreter::greaterThan;
				break;
			case EventData::COND_GREATER_EQUAL:
				eventData->execute = &Interpreter::greaterOrEqualThan;
				break;
			case EventData::COND_DETECT_SIMPLE_COLLISION:
				eventData->execute = &Interpreter::collidesSimpleWith;
				break;
			case EventData::COND_DETECT_PIXEL_COLLISION:
				eventData->execute = &Interpreter::collidesPixelWith;
				break;
			case EventData::COND_BUTTON_DOWN:
				eventData->execute = &Interpreter::buttonDown;
				break;
			case EventData::COND_BUTTON_PRESSED:
				eventData->execute = &Interpreter::buttonInstantPress;
				break;
			case EventData::COND_MOUSE_BUTTON_DOWN:
				eventData->execute = &Interpreter::mouseDown;
				break;
			case EventData::COND_MOUSE_BUTTON_PRESSED:
				eventData->execute = &Interpreter::mouseInstantPress;
				break;
			case EventData::COND_IS_MUSIC_PLAYING:
				eventData->execute = &Interpreter::isMusicPlaying;
				break;
			case EventData::COND_IS_SOUND_PLAYING:
				eventData->execute = &Interpreter::isSoundPlaying;
				break;
			case EventData::COND_IS_CURRENT_MAP:
				eventData->execute = &Interpreter::isCurrentMap;
				break;
			case EventData::COND_IS_LEFT_SIDE:
				eventData->execute = &Interpreter::isObjectLeftSide;
				break;
			case EventData::COND_IS_UP_SIDE:
				eventData->execute = &Interpreter::isObjectUpSide;
				break;
			case EventData::COND_IS_RIGHT_SIDE:
				eventData->execute = &Interpreter::isObjectRightSide;
				break;
			case EventData::COND_IS_DOWN_SIDE:
				eventData->execute = &Interpreter::isObjectDownSide;
				break;
			case EventData::COND_EVERY_SECONDS:
				eventData->execute = &Interpreter::everySeconds;
				break;
			}
		} else if(eventData->type == EventData::TYPE_DIALOGUE) {
			eventData->execute = &Interpreter::executeDialogue;
		}


		if(eventData->valueType == Interpreter::VALUE_TYPE_VARIABLE) {
			if(eventData->value01 < 0) {
				eventData->variableValue = gameObjectClass->getVariableById(-eventData->value01);
				std::cout << "Varname: " << eventData->variableValue->name << std::endl;
			} else {
				eventData->variableValue = this->getVariableById(eventData->value01);

			}
		}
	}




	return true;
}

void GameData::preprocessItemLevelSkills() {
	for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
		GameObjectClass *gameObjectClass = *it;

		for(std::vector<SkillData*>::iterator it2 = gameObjectClass->listaHabilidades.begin(); it2 != gameObjectClass->listaHabilidades.end(); ++it2) {
			SkillData *skillData = *it2;

			if(skillData->skillProvider != NULL) {
				skillData->skillProvider->itemSkills.push_back(make_pair(skillData->nroSkill, gameObjectClass));
			}

			if(skillData->level > 0) {
				gameObjectClass->levelSkills.push_back(make_pair(skillData->nroSkill, skillData->level));
			}
		}
	}
}

void GameData::freeGameObjectClassInstances() {
	for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
		GameObjectClass *gameObjectClass = *it;

		gameObjectClass->instances->clear();
	}
}

bool GameData::loadFile(std::string fileName) {
	FILE *fp;

	if(arg1 != NULL) {
		fp = fopen(std::string(arg1->c_str()).append(fileName.c_str()).c_str(), "rb");
	} else {
		fp = fopen(fileName.c_str(), "rb");
	}

	std::cout << fileName << std::endl;


	/* lendo o numero magico e verificando se de fato é um número mágico */
	int magic_number;
	fread(&magic_number, 1, sizeof(int), fp);

	if(magic_number != MAGIC_NUMBER) {
		return false;
	}

	fread(&version, 1, sizeof(int), fp);

	gameName = new std::string(loadString(fp));

	fread(&resWidth, 1, sizeof(int), fp);
	fread(&resHeight, 1, sizeof(int), fp);

	fread(&deathAction, 1, sizeof(int), fp);
	fread(&gameOverAction, 1, sizeof(int), fp);
	fread(&looseLifes, 1, sizeof(bool), fp);
	fread(&totalLives, 1, sizeof(int), fp);


	loadTileSetList(fp);
	loadAnimationDataList(fp);
	loadObjectList(fp);
	loadNpcObjectsToBounce(fp);
	loadObjectSkills(fp);
	loadBackgroundDataList(fp);
	loadMapList(fp);
	loadAllVariableLists(fp);
	loadAllEvents(fp);


	/*  lendo os nomes das imagens das telas principais */
	titleScreenFile = std::string(loadString(fp));
	optionsScreenFile = std::string(loadString(fp));
	gameoverScreenFile = std::string(loadString(fp));

	/* lendo os nomes das musicas das telas principais */
	titleScreenMusic = std::string(loadString(fp));
	optionsScreenMusic = std::string(loadString(fp));
	gameOverScreenMusic = std::string(loadString(fp));

	/* lendo a id do mapa inicial */
	fread(&idFirstMap, 1, sizeof(int), fp);

	fclose(fp);

	return true;
}

bool GameData::loadTileSetList(FILE *fp) {
    int num_tilesets;

    fread(&num_tilesets, 1, sizeof(int), fp);
    tileSetList = new std::vector<Tileset*>();

    int i;
    for(i = 0; i < num_tilesets; i++) {
    	Tileset *tileSet = new Tileset();

    	fread(&(tileSet->id), 1, sizeof(int), fp);

                tileSet->name = std::string(loadString(fp));
		tileSet->file = std::string(loadString(fp));

		fread(&(tileSet->width), 1, sizeof(int), fp);
		fread(&(tileSet->height), 1, sizeof(int), fp);

		fread(&(tileSet->maxX), 1, sizeof(int), fp);
		fread(&(tileSet->maxY), 1, sizeof(int), fp);

		fread(&(tileSet->tileSize), 1, sizeof(int), fp);

                ArrayCreator<int> *intArrayCreator = new ArrayCreator<int>();
                tileSet->collisionMatrix = intArrayCreator->createMatrix(tileSet->maxX, tileSet->maxY);

                int j, k;
		for(j = 0; j < tileSet->maxX; j++) {
			for(k = 0; k < tileSet->maxY; k++) {
				int valor;
				fread(&valor, 1, sizeof(int), fp);
				tileSet->collisionMatrix[j][k] = valor;
			}
		}


		tileSetList->push_back(tileSet);
    }

    return true;
}

bool GameData::loadMapList(FILE *fp) {
    mapList = new std::vector<Tilemap*>();

    int tamanhoMapList, i;
    int dummy;

    fread((&tamanhoMapList), 1, sizeof(int), fp);

    for(i = 0; i < tamanhoMapList; i++) {
    	Tilemap* map = new Tilemap();
    	int j, k, l;

    	int isFolder;

    	fread(&isFolder, 1, sizeof(int), fp);

    	if(isFolder) {
    		loadString(fp);
    		loadMapList(fp);
    	} else {
    		fread(&(map->key), 1, sizeof(int), fp);
			map->mapName = std::string(loadString(fp));

			fread(&(map->mapWidth), 1, sizeof(int), fp);
			fread(&(map->mapHeight), 1, sizeof(int), fp);
			fread(&(map->mapLayers), 1, sizeof(int), fp);

			int tileSetListSize;

			fread(&tileSetListSize, 1, sizeof(int), fp);


			map->tileSets = new std::vector<Tileset*>();

			for(j = 0; j < tileSetListSize; j++) {
				int id;

				fread(&id, 1, sizeof(int), fp);

				Tileset *tilesetItem = searchTilesetById(id);

				if(tilesetItem != NULL) {
					map->tileSets->push_back(tilesetItem);
				} else {
					printf("Erro na população dos tilesets de um mapa");
				   exit(1);
				}
			}

			/* ALTERACOES 22-FEV-2011 COMECAM AQUI */
			map->music = std::string(loadString(fp));
			map->sound = std::string(loadString(fp));

			std::cout << "String: " << map->music.c_str() << std::endl;

			fread(&map->loopMusic, 1, sizeof(int), fp);
			fread(&map->loopSound, 1, sizeof(int), fp);
			fread(&map->idFundo, 1, sizeof(int), fp);

			/* gravando as instancias de objetos */

			int nro_instancias;
			fread(&nro_instancias, 1, sizeof(int), fp);

			map->gameObjectInstances = new std::vector<GameObjectInstance*>();

			map->gameObjectInstances->clear();

			for(j = 0; j < nro_instancias; j++) {
				GameObjectInstance *gameObjectInstance = new GameObjectInstance();
				int gameObjectId;

				fread(&gameObjectInstance->id, 1, sizeof(unsigned int), fp);
				fread(&gameObjectId, 1,  sizeof(int), fp);
				gameObjectInstance->gameObject = searchGameObjectById(gameObjectId);

				if(gameObjectInstance->gameObject == NULL) {
					std::cout << "Problema com um GameObjectInstance. Abortando..." << std::endl;
					exit(1);
				}
				fread(&gameObjectInstance->x, 1,  sizeof(int), fp);
				fread(&gameObjectInstance->y, 1,  sizeof(int), fp);

				fread(&gameObjectInstance->nroEventos, 1,  sizeof(int), fp);
				fread(&gameObjectInstance->nroFalas, 1, sizeof(int), fp);

				fread(&gameObjectInstance->isCenter, 1, sizeof(bool), fp);
				fread(&gameObjectInstance->isMainObject, 1, sizeof(bool), fp);

				gameObjectInstance->dialogueData = loadDialogueData(fp);

				map->gameObjectInstances->push_back(gameObjectInstance);

			}


                        /* ALTERACOES 22-FEV-2011 TERMINAM AQUI */

                        ArrayCreator<Tile*> *arrayCreator = new ArrayCreator<Tile*>();
                        map->map = arrayCreator->createTensor(map->mapWidth, map->mapHeight, map->mapLayers);


			for(j = 0; j < map->mapWidth; j++) {
				for(k = 0; k < map->mapHeight; k++) {
					for(l = 0; l < map->mapLayers; l++) {
						int x, y;
						fread(&x, 1, sizeof(int), fp);
						fread(&y, 1, sizeof(int), fp);



						 int id;

						 fread(&id, 1, sizeof(int), fp);


						 if(id == -1) {
							map->map[j][k][l] = NULL;
						 } else {
							 Tileset* tilesetItem = searchTilesetById(id);

							 if(tilesetItem != NULL) {
								 Tile *tile = new Tile(x, y, tilesetItem->tileSize, tilesetItem->tileSize);
								 if(x < 0 || y < 0) {
									 tile->collisionType = Tile::COLLISION_PASS;
								 } else {
									 tile->collisionType = tilesetItem->collisionMatrix[x][y];
								 }

								 tile->tileset = tilesetItem;

								 map->tileWidth = tilesetItem->tileSize;
								 map->tileHeight = tilesetItem->tileSize;

								 tile->pos.x = j*map->tileWidth;
								 tile->pos.y = k*map->tileHeight;


								 map->map[j][k][l] = tile;
							 } else {
								 printf("Erro na obtenção de um tileset de um tile %d\n", id);
								 exit(1);
							 }
						 }
					}
				}
			}

			/* lendo teleport areas */
			int nro_teleport_areas;
			fread(&nro_teleport_areas, 1, sizeof(int), fp);

			map->teleportAreas = new std::vector<TeleportArea*>(nro_teleport_areas);

			for(j = 0; j < nro_teleport_areas; j++) {
				TeleportArea* teleportArea = new TeleportArea();

				fread(&teleportArea->id, 1, sizeof(int), fp);
				fread(&teleportArea->mapId, 1, sizeof(int), fp);
				fread(&teleportArea->mapPositionDetermined, 1, sizeof(bool), fp);
				fread(&teleportArea->mapPosX, 1, sizeof(int), fp);
				fread(&teleportArea->mapPosY, 1, sizeof(int), fp);
				fread(&teleportArea->rect.x, 1, sizeof(int), fp);
				fread(&teleportArea->rect.y, 1, sizeof(int), fp);
				fread(&teleportArea->rect.w, 1, sizeof(int), fp);
				fread(&teleportArea->rect.h, 1, sizeof(int), fp);
				fread(&teleportArea->showVictoryAnimation, 1, sizeof(bool), fp);

				map->teleportAreas->at(j) = teleportArea;

			}



			 /* carregando o fundo */
			int idBg;
			fread(&idBg, 1, sizeof(int), fp);

			if(idBg != -1) {
				map->background = searchBackgroundDataById(idBg);
				if(map->background == NULL) {
					printf("Erro na obtenção de um background de id %d\n", idBg);
					exit(1);
				}
			} else {
				map->background = NULL;
			}

			map->dialogueData = loadDialogueData(fp);

			if(map->tileWidth == 0) {
				map->tileWidth = 32;
			}

			if(map->tileHeight == 0) {
				map->tileHeight = 32;
			}

			mapList->push_back(map);



    	}


    }

    return true;
}

bool GameData::loadObjectList(FILE *fp) {
	objectList = new std::vector<GameObjectClass*>();

	int nro_objetos;
	fread(&nro_objetos, 1, sizeof(int), fp);
	for(int i = 0; i < nro_objetos; i++) {
		GameObjectClass *gameObject = new GameObjectClass();

		fread(&gameObject->id, 1, sizeof(int), fp);
		gameObject->name = std::string(loadString(fp));
		fread(&gameObject->type, 1, sizeof(int), fp);

		fread(&gameObject->isObjetoUnico, 1, sizeof(bool), fp);
		fread(&gameObject->formaGrafica, 1, sizeof(int), fp);
		fread(&gameObject->tipoMovimento, 1, sizeof(int), fp);

		gameObject->soundDamage = std::string(loadString(fp));
		gameObject->soundSpecial = std::string(loadString(fp));

		fread(&gameObject->isDraggable, 1, sizeof(bool), fp);

		fread(&gameObject->formaMovimentoMouse, 1, sizeof(int), fp);
		fread(&gameObject->vx, 1, sizeof(int), fp);
		fread(&gameObject->vy, 1, sizeof(int), fp);
		fread(&gameObject->ax, 1, sizeof(int), fp);
		fread(&gameObject->ay, 1, sizeof(int), fp);
		fread(&gameObject->dax, 1, sizeof(int), fp);
		fread(&gameObject->day, 1, sizeof(int), fp);
		fread(&gameObject->gravidade, 1, sizeof(int), fp);
		fread(&gameObject->intensidadePulo, 1, sizeof(int), fp);
		fread(&gameObject->evolucaoPorNivel, 1, sizeof(int), fp);

		fread(&gameObject->hp, 1, sizeof(int), fp);
		fread(&gameObject->mp, 1, sizeof(int), fp);
		fread(&gameObject->atk, 1, sizeof(int), fp);
		fread(&gameObject->def, 1, sizeof(int), fp);
		fread(&gameObject->intelig, 1, sizeof(int), fp);
		fread(&gameObject->levelInicial, 1, sizeof(int), fp);
		fread(&gameObject->levelMax, 1, sizeof(int), fp);
		fread(&gameObject->velocidadeEvolucao, 1, sizeof(int), fp);
		fread(&gameObject->resolveCollision, 1, sizeof(int), fp);

		gameObject->currentLevel = gameObject->levelInicial;
		std::cout << "currlevel: " << gameObject->currentLevel << std::endl;


		if(gameObject->type == GameObjectClass::INIMIGO || gameObject->type == GameObjectClass::NPC ||
		   gameObject->type == GameObjectClass::ITEM) {
			fread(&gameObject->formaMovimentacaoNpcItem, 1, sizeof(int), fp);
			fread(&gameObject->movimentaApenasDentroTela, 1, sizeof(bool), fp);
			fread(&gameObject->raioMovimentacao, 1, sizeof(int), fp);

			if(gameObject->type == GameObjectClass::INIMIGO) {

				fread(&gameObject->derrotaEncostandoInimigo, 1, sizeof(bool), fp);
				fread(&gameObject->derrotaAtirandoItemMagiaInimigo, 1, sizeof(bool), fp);
				fread(&gameObject->derrotaAcertandoEspadaSobreInimigo, 1, sizeof(bool), fp);
				fread(&gameObject->derrotaPulandoSobreInimigo, 1, sizeof(bool), fp);
				fread(&gameObject->atacaEncostaPersonagem, 1, sizeof(bool), fp);
				fread(&gameObject->atacaEncostaPersonagemDano, 1, sizeof(int), fp);
				fread(&gameObject->atacaUsandoEspada, 1, sizeof(bool), fp);
				fread(&gameObject->espadaItemId, 1, sizeof(int), fp);
				fread(&gameObject->atacaUsandoEspadaDano, 1, sizeof(int), fp);

				fread(&gameObject->atiraItemMaginaDirecaoEstiver, 1, sizeof(bool), fp);
				fread(&gameObject->atiraItemMaginaDirecaoEstiverIdItem, 1, sizeof(int), fp);
				fread(&gameObject->atiraItemMaginaDirecaoEstiverDano, 1, sizeof(int), fp);

				fread(&gameObject->atiraItemMagiaDirecaoPersonagem, 1, sizeof(bool), fp);
				fread(&gameObject->atiraItemMagiaDirecaoPersonagemIdItem, 1, sizeof(int), fp);
				fread(&gameObject->atiraItemMagiaDirecaoPersonagemDano, 1, sizeof(int), fp);

				fread(&gameObject->tempoAtaque, 1, sizeof(float), fp);
				fread(&gameObject->magicCost, 1, sizeof(int), fp);

				fread(&gameObject->experiencePoints, 1, sizeof(int), fp);
				fread(&gameObject->defeatPoints, 1, sizeof(int), fp);

			} else if(gameObject->type == GameObjectClass::NPC) {
				fread(&gameObject->nroFalas, 1, sizeof(int), fp);
			} else if(gameObject->type == GameObjectClass::ITEM) {
				fread(&gameObject->concedePontos, 1, sizeof(bool), fp);
				fread(&gameObject->concedePontosValor, 1, sizeof(int), fp);
				fread(&gameObject->ganhaPerdeVida, 1, sizeof(bool), fp);
				fread(&gameObject->ganhaPerdeVidaValor, 1, sizeof(int), fp);
				fread(&gameObject->ganhaPerdeMagia, 1, sizeof(bool), fp);
				fread(&gameObject->ganhaPerdeMagiaValor, 1, sizeof(int), fp);
				fread(&gameObject->incrementaVariavel, 1, sizeof(bool), fp);
				fread(&gameObject->incrementaVariavelIdVariavel, 1, sizeof(int), fp);
				fread(&gameObject->incrementaVariavelValor, 1, sizeof(int), fp);
				fread(&gameObject->ativaEvento, 1, sizeof(bool), fp);
				fread(&gameObject->ativaEventoIdEvento, 1, sizeof(int), fp);
				fread(&gameObject->concedeHabilidade, 1, sizeof(bool), fp);
				fread(&gameObject->concedeHabilidadeIdHabilidade, 1, sizeof(int), fp);

				fread(&gameObject->comportamentoEncostarPersonagem, 1, sizeof(int), fp);
				fread(&gameObject->desapareceEncostarPersonagem, 1, sizeof(bool), fp);
				fread(&gameObject->desapareceEncostarParede, 1, sizeof(bool), fp);
			}
		}



		fread(&gameObject->possuiEventos, 1, sizeof(bool), fp);

		int nro_gameobject_animations;
		fread(&nro_gameobject_animations, 1, sizeof(int), fp);

		gameObject->gameObjectAnimations = new std::vector<GameObjectAnimation*>();

		gameObject->gameObjectAnimations->clear();

		for(int j = 0; j < nro_gameobject_animations; j++) {
			GameObjectAnimation *gameObjectAnimation = new GameObjectAnimation();

			fread(&gameObjectAnimation->id, 1, sizeof(int), fp);
			fread(&gameObjectAnimation->type, 1, sizeof(int), fp);

			fread(&gameObjectAnimation->numDirectionFactor, 1, sizeof(int), fp);

			int nro_types;
			fread(&nro_types, 1, sizeof(int), fp);

			for(int k = 0; k < nro_types; k++) {
				int valor_type;
				fread(&valor_type, 1, sizeof(int), fp);

				gameObjectAnimation->types->at(k) = valor_type;
			}


			int nro_horizontal_inverts;
			fread(&nro_horizontal_inverts, 1, sizeof(int), fp);

			for(int k = 0; k < nro_horizontal_inverts; k++) {
				bool valor_horinv;
				fread(&valor_horinv, 1, sizeof(bool), fp);
				gameObjectAnimation->horizontalInvert.at(k) = valor_horinv;
			}

			int nro_vertical_inverts;
			fread(&nro_vertical_inverts, 1, sizeof(int), fp);

			for(int k = 0; k < nro_vertical_inverts; k++) {
				bool valor_verinv;
				fread(&valor_verinv, 1, sizeof(bool), fp);
				gameObjectAnimation->verticalInvert.at(k) = valor_verinv;
			}

			int nro_adjustments;
			fread(&nro_adjustments, 1, sizeof(int), fp);

			for(int k = 0; k < nro_adjustments; k++) {
				Vector2 point;
				int x, y;
				fread(&x, 1, sizeof(int), fp);
				fread(&y, 1, sizeof(int), fp);
				point.x = x;
				point.y = y;

				gameObjectAnimation->adjustments.at(k) = point;
			}



			gameObjectAnimation->name = std::string(loadString(fp));

			int nro_sprites = gameObjectAnimation->sprites->size();
			fread(&nro_sprites, 1, sizeof(int), fp);

			for(int k = 0; k < nro_sprites; k++) {
				SpriteRepresentation *sprite = new SpriteRepresentation();

				fread(&sprite->id, 1, sizeof(int), fp);
				fread(&sprite->direction, 1, sizeof(int), fp);

                fread(&sprite->activated, 1, sizeof(bool), fp);
                fread(&sprite->hascolorkey, 1, sizeof(bool), fp);
                fread(&sprite->r_colorkey, 1, sizeof(int), fp);
                fread(&sprite->g_colorkey, 1, sizeof(int), fp);
                fread(&sprite->b_colorkey, 1, sizeof(int), fp);


				sprite->spriteFileName = std::string(loadString(fp));

				gameObjectAnimation->sprites->at(k) = sprite;
			}

			int nro_animations;
			fread(&nro_animations, 1, sizeof(int), fp);


			for(int k = 0; k < nro_animations; k++) {
				int animationDataId;
				fread(&animationDataId, 1, sizeof(int), fp);

				if(animationDataId != -1) {
					gameObjectAnimation->animations->at(k) = searchAnimationDataById(animationDataId);

					if(gameObjectAnimation->animations->at(k) == NULL) {
						std::cout << "Problema com leitura de um animationData de um object" << std::endl;
					}
				}

			}



			// TODO: fazer loop leitura de animations quando estiverem prontas

			gameObject->gameObjectAnimations->push_back(gameObjectAnimation);
		}

		objectList->push_back(gameObject);
	}



	return true;
}


bool GameData::loadNpcObjectsToBounce(FILE *fp) {
    for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObjectClass *gameObject = *it;

        if(gameObject->type == GameObjectClass::PONG_BALL_OBJECT) {
            int gameObjectsToAddCount;
            fread(&gameObjectsToAddCount, 1, sizeof(int), fp);

            for(int j = 0; j < gameObjectsToAddCount; j++) {
                int idGameObjectToAdd;
                fread(&idGameObjectToAdd, 1, sizeof(int), fp);
                GameObjectClass *gameObjectIt = searchGameObjectById(idGameObjectToAdd);

                if(gameObjectIt != NULL) {
                    gameObject->listObjectsToBounce.push_back(gameObjectIt);
                } else {
                    printf("Erro na obtenção de um objeto de id: %d\n", idGameObjectToAdd);
                    exit(1);
                }
            }
        }
    }
}


bool GameData::loadObjectSkills(FILE *fp) {
	for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
		GameObjectClass *gameObject = *it;

		int nroListaHabilidades;

                fread(&nroListaHabilidades, 1, sizeof(int), fp);

		for(int j = 0; j < nroListaHabilidades; j++) {
			SkillData* skillData = new SkillData();

			fread(&skillData->id, 1, sizeof(int), fp);
			fread(&skillData->intensity, 1, sizeof(int), fp);
			fread(&skillData->magicCost, 1, sizeof(int), fp);
			fread(&skillData->level, 1, sizeof(int), fp);


			int idSkill;
			fread(&skillData->nroSkill, 1, sizeof(int), fp);

			fread(&skillData->isMagical, 1, sizeof(int), fp);

			skillData->sound = std::string(loadString(fp));

			int idSkillData;
			fread(&idSkillData, 1, sizeof(int), fp);
			int idSkillProvider;
			fread(&idSkillProvider, 1, sizeof(int), fp);

			if(idSkillData == -1) {
				skillData->skillObject = NULL;
			} else {
				skillData->skillObject = searchGameObjectById(idSkillData);
				if(skillData->skillObject == NULL) {
					printf("Erro na obtenção de um objeto (skillObject) de id: %d\n", idSkillData);
					exit(1);
				}
			}


			if(idSkillProvider == -1) {
				skillData->skillProvider = NULL;
			} else {
				skillData->skillProvider = searchGameObjectById(idSkillProvider);
				if(skillData->skillProvider == NULL) {
					printf("Erro na obtenção de um objeto (skillProvider) de id: %d\n", idSkillProvider);
					exit(1);
				}
			}

			gameObject->listaHabilidades.push_back(skillData);



		}
	}

	return true;
}

char* GameData::loadString(FILE *fp) {
    char* string;
    int tamanho;

    fread(&tamanho, 1, sizeof(int), fp);
    string = (char*) calloc(tamanho + 1, sizeof(char));

    string[tamanho] = '\0';


    if(tamanho > 0) {
    	fread(string, sizeof(char), tamanho, fp);
    }



    return string;

}

Tileset* GameData::searchTilesetById(int id) {
    for(std::vector<Tileset*>::iterator it = tileSetList->begin(); it != tileSetList->end(); ++it) {
        Tileset *tileset = *it;

        if(tileset->id == id) {
            return tileset;
        }
    }

    return NULL;
}

GameObjectClass* GameData::searchGameObjectById(int id) {
    for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObjectClass *gameObject = *it;

        if(gameObject->id == id) {
            return gameObject;
        }
    }

    return NULL;
}

Tilemap* GameData::searchMapById(int id) {
	for(std::vector<Tilemap*>::iterator it = mapList->begin(); it != mapList->end(); ++it) {
		Tilemap *map = *it;

		if(map->key == id) {
			return map;
		}
	}

	return NULL;
}

AnimationData* GameData::searchAnimationDataById(int id) {
    for(std::vector<AnimationData*>::iterator it = animationDataList->begin(); it != animationDataList->end(); ++it) {
        AnimationData *animationData = *it;

        if(animationData->id == id) {
            return animationData;
        }
    }

    return NULL;
}

BackgroundData* GameData::searchBackgroundDataById(int id) {
    for(std::vector<BackgroundData*>::iterator it = backgroundList->begin(); it != backgroundList->end(); ++it) {
        BackgroundData *backgroundData = *it;

        if(backgroundData->id == id) {
            return backgroundData;
        }
    }

    return NULL;
}


ProcedureData* GameData::getProcedureById(int id) {
	for(std::vector<ProcedureData*>::iterator it = procedureList->begin(); it != procedureList->end(); ++it) {
		ProcedureData *procedureData = *it;

		if(procedureData->id == id) {
			return procedureData;
		}
	}

	return NULL;
}

VariableData* GameData::getVariableById(int id) {
	return variableList->at(id);
}


void GameData::setAttributeById(int id, float value) {
	globalObject->setAttributeById(id, value);
	//variableList->at(id - 300)->value;
}

float GameData::getAttributeById(int id) {
	return globalObject->getAttributeById(id);
	//return variableList->at(id - 300)->value;
}

SDL_Surface* GameData::loadIMG(std::string file) {
	//printf("arg1: %s\n", arg1->append(file.c_str()).c_str());

	//return IMG_Load(file.c_str());

	if(arg1 == NULL) {
		return IMG_Load(file.c_str());
	} else {
		std::cout << "arg1: " << std::string(arg1->c_str()).append(file.c_str()).c_str() << std::endl;
		return IMG_Load(std::string(arg1->c_str()).append(file.c_str()).c_str());
	}

}

Tilemap* GameData::findNextMap(Tilemap *currentMap) {
	for(std::vector<Tilemap*>::iterator it = mapList->begin(); it != mapList->end(); ++it) {
		Tilemap* map = *it;

		if(map->key == currentMap->key) {
			it++;

			if(it != mapList->end()) {
				return *it;
			} else {
				return NULL;
			}
		}


	}

	return NULL;
}


void GameData::clearInstancesFromClasses() {
	for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
		GameObjectClass *gameObjectClass = *it;

		gameObjectClass->instances->clear();
	}
}




bool GameData::loadAnimationDataList(FILE *fp) {
    int tamanhoLista;

    fread(&tamanhoLista, 1, sizeof(int), fp);

    animationDataList = new std::vector<AnimationData*>();

    for(int i = 0; i < tamanhoLista; i++) {
        AnimationData *animationData = new AnimationData();

        fread(&animationData->id, 1, sizeof(int), fp);

        animationData->fileName = std::string(loadString(fp));
        animationData->name = std::string(loadString(fp));

        fread(&animationData->colorkey_b, 1, sizeof(int), fp);
        fread(&animationData->colorkey_g, 1, sizeof(int), fp);
        fread(&animationData->colorkey_r, 1, sizeof(int), fp);

        fread(&animationData->frameLoop, 1, sizeof(int), fp);
        fread(&animationData->hasColorkey, 1, sizeof(bool), fp);
        fread(&animationData->hasLoop, 1, sizeof(bool), fp);
        fread(&animationData->horizontalFrameNumber, 1, sizeof(int), fp);
        fread(&animationData->horizontalSpacing, 1, sizeof(int), fp);
        fread(&animationData->order, 1, sizeof(int), fp);
        fread(&animationData->velocity, 1, sizeof(int), fp);
        fread(&animationData->verticalFrameNumber, 1, sizeof(int), fp);
        fread(&animationData->verticalSpacing, 1, sizeof(int), fp);

        fread(&animationData->startX, 1, sizeof(int), fp);
        fread(&animationData->startY, 1, sizeof(int), fp);
        fread(&animationData->endX, 1, sizeof(int), fp);
        fread(&animationData->endY, 1, sizeof(int), fp);

        animationDataList->push_back(animationData);


    }

    return true;
}

bool GameData::loadBackgroundDataList(FILE *fp) {
	int tamanhoLista;


	fread(&tamanhoLista, 1, sizeof(int), fp);
	backgroundList = new std::vector<BackgroundData*>();

	for(int i = 0; i < tamanhoLista; i++) {
		BackgroundData *bg = new BackgroundData();

		fread(&bg->id, 1, sizeof(int), fp);
		bg->name = std::string(loadString(fp));

		int tamanho_layer_list;
		fread(&tamanho_layer_list, 1, sizeof(int), fp);

		for(int j = 0; j < tamanho_layer_list; j++) {
			BackgroundLayerData *bgLayer = new BackgroundLayerData();

			bgLayer->fileName = std::string(loadString(fp));

			fread(&bgLayer->behavior, 1, sizeof(int), fp);
			fread(&bgLayer->displacementX, 1, sizeof(int), fp);
			fread(&bgLayer->displacementY, 1, sizeof(int), fp);
			fread(&bgLayer->repeatsHorizontally, 1, sizeof(int), fp);
			fread(&bgLayer->repeatsVertically, 1, sizeof(int), fp);
			fread(&bgLayer->vx, 1, sizeof(int), fp);
			fread(&bgLayer->vy, 1, sizeof(int), fp);

			bg->layerList->push_back(bgLayer);
		}

		backgroundList->push_back(bg);


	}

	return true;
}



bool GameData::loadAllEvents(FILE *fp) {
    procedureGlobalAlways = loadProcedure(fp);
    procedureGlobalStart = loadProcedure(fp);
    procedureGlobalEnd = loadProcedure(fp);

    procedureList = loadProcedureList(fp);


    for(std::vector<GameObjectClass*>::iterator it = objectList->begin(); it != objectList->end(); ++it) {
        GameObjectClass* gameObject = *it;

        gameObject->procedureGlobalAlways = loadProcedure(fp);
        gameObject->procedureGlobalStart = loadProcedure(fp);
        gameObject->procedureGlobalEnd = loadProcedure(fp);

        gameObject->procedureList = loadProcedureList(fp);
    }

    return true;
}


std::vector<ProcedureData*>* GameData::loadProcedureList(FILE *fp) {
    int sizeProcedureList;
    std::vector<ProcedureData*>* procedureList = new std::vector<ProcedureData*>();

    fread(&sizeProcedureList, 1, sizeof(int), fp);

    for(int i = 0; i < sizeProcedureList; i++) {
        procedureList->push_back(loadProcedure(fp));
    }


    return procedureList;
}


ProcedureData* GameData::loadProcedure(FILE *fp) {
    ProcedureData *procedureData = new ProcedureData();

    fread(&procedureData->id, 1, sizeof(int), fp);
    procedureData->name = std::string(loadString(fp));
    fread(&procedureData->nameEditable, 1, sizeof(int), fp);

    procedureData->events = loadEventList(fp);

    return procedureData;
}




std::list<EventData*> GameData::loadEventList(FILE *fp) {
    int eventListSize;
    std::list<EventData*> eventListFunction;

    fread(&eventListSize, 1, sizeof(int), fp);

    for(int i = 0; i < eventListSize; i++) {
        EventData *eventData = new EventData();

        fread(&eventData->newEvent, 1, sizeof(int), fp);
        if(!eventData->newEvent) {
            fread(&eventData->type, 1, sizeof(int), fp);
            fread(&eventData->conditionType, 1, sizeof(int), fp);
            fread(&eventData->negate, 1, sizeof(bool), fp);

            fread(&eventData->opcode, 1, sizeof(int), fp);
            fread(&eventData->idAssociatedVariable, 1, sizeof(int), fp);
            fread(&eventData->idObject01, 1, sizeof(int), fp);
            fread(&eventData->instanceTypeObject01, 1, sizeof(int), fp);
            fread(&eventData->idObject02, 1, sizeof(int), fp);
            fread(&eventData->instanceTypeObject02, 1, sizeof(int), fp);
            fread(&eventData->valueType, 1, sizeof(int), fp);
            fread(&eventData->value01, 1, sizeof(int), fp);
            eventData->stringValue = std::string(loadString(fp));

            eventData->dialogueData = loadDialogueData(fp);

            eventData->subEvents = loadEventList(fp);

        }

        eventListFunction.push_back(eventData);
    }

    return eventListFunction;
}

VariableData* GameData::loadVariable(FILE *fp) {
    VariableData *variable = new VariableData();

    fread(&variable->id, 1, sizeof(int), fp);
    variable->name = std::string(loadString(fp));
    fread(&variable->type, 1, sizeof(int), fp);
    fread(&variable->value, 1, sizeof(float), fp);

    return variable;
}


bool GameData::loadAllVariableLists(FILE *fp) {

    // lendo as variáveis globais
    int count_n_variables;
    fread(&count_n_variables, 1, sizeof(int), fp);


    for(int i = 0; i < count_n_variables; i++) {
        variableList->push_back(loadVariable(fp));
    }

    // lendos as variáveis dos objetos
    for(std::vector<GameObjectClass*>::iterator it1 = objectList->begin(); it1 != objectList->end(); ++it1) {
        GameObjectClass *gameObject = *it1;

        fread(&count_n_variables, 1, sizeof(int), fp);

        for(int i = 0; i < count_n_variables; i++) {
            gameObject->variableList->push_back(loadVariable(fp));
        }

    }
    return true;
}


DialogueData* GameData::loadDialogueData(FILE *fp) {
    bool dialogueDataNotExists;
    fread(&dialogueDataNotExists, 1, sizeof(bool), fp);

    DialogueData *dialogueData;

    if(dialogueDataNotExists) {
        return NULL;
    } else {
        dialogueData = new DialogueData();

        int itemNumber;
        fread(&itemNumber, 1, sizeof(int), fp);

        for(int i = 0; i < itemNumber; i++) {
            DialogueItemData *dialogueItemData = new DialogueItemData();

            fread(&dialogueItemData->type, 1, sizeof(int), fp);
            if(dialogueItemData->type == DialogueItemData::TYPE_MESSAGE) {
                dialogueItemData->message = std::string(loadString(fp));
                dialogueItemData->associatedImage = std::string(loadString(fp));
                fread(&dialogueItemData->associatedImageAtCenter, 1, sizeof(bool), fp);
            } else {
                fread(&dialogueItemData->procedureId, 1, sizeof(bool), fp);
            }

            dialogueData->dialogueItems.push_back(dialogueItemData);
        }
    }

    return dialogueData;
}
