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

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <list>
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Tileset.h"
#include "Tilemap.h"
#include "GameObjectClass.h"
#include "SpriteRepresentation.h"
#include "AnimationData.h"
#include "BackgroundData.h"
#include "ProcedureData.h"
#include "VariableData.h"
#include "EventData.h"
#include "GameObjectCreationData.h"
#include "DialogueData.h"
#include "Interpreter.h"
#include "ArrayCreator.h"

class Tileset;
class Tilemap;
class GameObjectClass;
class SpriteRepresentation;
class AnimationData;
class BackgroundData;
class ProcedureData;
class VariableData;
class EventData;
class GameObjectCreationData;
class DialogueData;
class Interpreter;

using namespace std;

/**
 * Dados do jogo.
 */


/**
 * @brief Entidade armazenadora de todas as outras entidades do jogo. Uma documentação mais completa
 * da classe se localiza na documentação do Módulo Editor.
 *
 */
class GameData {
public:
    GameData();
    virtual ~GameData();
    static GameData *getInstance();

    /**
     * @brief Reorganiza dados de variáveis.
     *
     */
    void reorganizeVariableData();

    /**
     * @brief Cria o array dos ítens obtidos de cada um dos objetos.
     *
     */
    void createObtainedItemsAndObjectsToBounceArrays();


    /**
     * @brief Pre-processa ponteiros.
     *
     */
    bool preprocessPointers();

    /**
     * @brief Pre-processa pronteiros da lista de eventos.
     *
     * @param eventList
     * @param gameObjectClass
     */
    bool preprocessEventList(std::list<EventData*> *eventList, GameObjectClass *gameObjectClass = NULL);

    /**
     * @brief Pre-processa ponteiros de procedimentos.
     *
     * @param procedureData
     * @param gameObjectClass
     */
    bool preprocessProcedure(ProcedureData *procedureData, GameObjectClass *gameObjectClass = NULL);

    /**
     * @brief  Preprocessa ponteiros de eventos eventos.
     *
     * @param eventData
     * @param gameObjectClass
     */
    bool preprocessEvent(EventData *eventData, GameObjectClass *gameObjectClass = NULL);


    /**
     * @brief Preprocessa lista de habilidades de itens e níveis de objetos.
     *
     */
    void preprocessItemLevelSkills();


    /**
     * @brief Apaga as listas de instâncias de objetos nas GameObjectClass.
     *
     */
    void freeGameObjectClassInstances();

    bool loadFile(std::string fileName);
    bool loadTileSetList(FILE *fp);
    bool loadMapList(FILE *fp);
    bool loadObjectList(FILE *fp);
    bool loadNpcObjectsToBounce(FILE *fp);
    bool loadObjectSkills(FILE *fp);

    char* loadString(FILE *fp);

    SDL_Surface* loadIMG(std::string file);

    Tilemap* findNextMap(Tilemap *currentMap);

    void clearInstancesFromClasses();

    static int MAGIC_NUMBER;
    static int SOFTWARE_CURRENT_VERSION;

    int version;

    string *gameName;
    int resWidth, resHeight;

    Tilemap* currentMap;
    std::list<GameObjectCreationData*> *gameObjectsToCreate;

    int* nextMap;


    int deathAction;
    int gameOverAction;
    bool looseLifes;
    int totalLives;


    ProcedureData *procedureGlobalAlways;
    ProcedureData *procedureGlobalStart;
    ProcedureData *procedureGlobalEnd;

    std::vector<ProcedureData*> *procedureList;

    std::vector<Tileset*> *tileSetList;
    std::vector<Tilemap*> *mapList;
    std::vector<GameObjectClass*> *objectList;
    std::vector<AnimationData*> *animationDataList;
    std::vector<BackgroundData*> *backgroundList;
    std::vector<VariableData*> *variableList;

    GameObject *globalObject;

    std::string *arg1;

    std::string titleScreenFile;
    std::string optionsScreenFile;
    std::string gameoverScreenFile;

    std::string titleScreenMusic;
    int loopTitleScreenMusic;
    std::string optionsScreenMusic;
    int loopOptionsScreenMusic;
    std::string gameOverScreenMusic;
    int loopGameOverScreenMusic;

    int idFirstMap;

    Tileset* searchTilesetById(int id);
    GameObjectClass* searchGameObjectById(int id);
    Tilemap* searchMapById(int id);
    AnimationData* searchAnimationDataById(int id);
    BackgroundData* searchBackgroundDataById(int id);
    ProcedureData* getProcedureById(int id);
    VariableData* getVariableById(int id);



    void setAttributeById(int id, float value);
    float getAttributeById(int id);

    bool loadAnimationDataList(FILE *fp);

    bool loadBackgroundDataList(FILE *fp);

    std::vector<ProcedureData*>* loadProcedureList(FILE *fp);
    ProcedureData *loadProcedure(FILE *fp);
    bool loadAllEvents(FILE *fp);
    std::list<EventData*> loadEventList(FILE *fp);
    VariableData* loadVariable(FILE *fp);
    bool loadAllVariableLists(FILE *fp);

    DialogueData *loadDialogueData(FILE *fp);

    std::stack<DialogueData*> dialogueDatasToAdd;

    static const int DEATH_ACTION_RESET_MAP = 0;
    static const int DEATH_ACTION_RESET_GAME = 1;
    static const int DEATH_ACTION_SHUTDOWN_GAME = 2;


    static GameData *singleton; /**< TODO */
};

#endif /* GAMEDATA_H_ */
