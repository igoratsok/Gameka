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


#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

#include <QDir>

#include "map.h"
#include "tileset.h"
#include "gameobject.h"
#include "titlescreendata.h"
#include "animationdata.h"
#include "background.h"
#include "skill.h"
#include "proceduredata.h"
#include "variabledata.h"
#include "eventdata.h"
#include "dialoguedata.h"


class Map;
class TileSet;
class GameObject;
class TitleScreenData;
class AnimationData;
class Background;
class Skill;
class ProcedureData;
class VariableData;
class EventData;
class DialogueData;


/**
 * @brief Entidade armazenadora de todas as outras entidades do jogo.
 *
 */
class GameData
{
public:

    /**
     * @brief
     *
     */
    virtual ~GameData();
    /**
     * @brief
     *
     */
    static GameData *getInstance();

    static int MAGIC_NUMBER; /**< Número mágico */
    static int SOFTWARE_CURRENT_VERSION;

    int version; /**< Versão. */

    std::string *gameName; /**< Nome do jogo. */
    int resWidth; /**< Largura da tela em píxeis. */
    int resHeight; /**< Altura da tela em píxeis. */

    static GameData *singleton; /**< Singleton da classe. */


    /* lista de tilesets */
    std::vector<TileSet*> *tileSetList; /**< Lista de tilesets. */
    /* lista de mapas */
    std::vector<Map*> *mapList; /**< Lista de mapas. */
    /* lista de objetos */
    std::vector<GameObject*> *objectList; /**< Lista de classes de objetos. */
    /* lista de animations */
    std::vector<AnimationData*> *animationDataList; /**< Lista de animações. */
    /* lista de backgrounds */
    std::vector<Background*> *backgroundList; /**< Lista de fundos. */
    /* lista de variáveis globais */
    std::vector<VariableData*> *variableList; /**< Lista de variáveis. */



    ProcedureData *procedureGlobalAlways; /**< Procedimento global "Sempre" */
    ProcedureData *procedureGlobalStart; /**< Procedimento global "No início" */
    ProcedureData *procedureGlobalEnd; /**< Procedimento global "No fim" */

    std::vector<ProcedureData*> *procedureList; /**< Lista de procedimentos */




    std::vector<Skill*> *skillList; /**< Lista de habilidades. */

    Map *editingMap; /**< Mapa em edição. */

    int idFirstMap; /**< Identificador do primeiro mapa. */

    TitleScreenData titleScreenData; /**< Dados da tela de título. */
    std::string optionsScreenFile; /**< Arquivo de fundo da tela de opções. */
    std::string gameoverScreenFile; /**< Arquivo de fundo da tela de Game Over */

    std::string titleScreenMusic; /**< Arquivo de música da tela de título. */
    int loopTitleScreenMusic; /**< Se a música da tela de título loopa. */
    std::string optionsScreenMusic; /**< Arquivo de música da tela de opções. */
    int loopOptionsScreenMusic; /**< Se a música da tela de opções loopa. */
    std::string gameOverScreenMusic; /**< Arquivo de música da tela de Game Over. */
    int loopGameOverScreenMusic; /**< Se a música da tela de Game Over loopa. */


    int deathAction; /**< Ação de morte: \n
                            - 0: Reseta mapa;
                            - 1: Reseta jogo; */
    int gameOverAction; /**< Ação de game over: \n
                            - 0: Reseta mapa;
                            - 1: Reseta jogo;
                            - 2: Desliga jogo; */
    bool looseLifes; /**< Se perde vidas. */
    int totalLives; /**< Quantas vidas tem. */

    /**
     * @brief Apaga dados do GameData
     *
     */
    void erase();




    /**
     * @brief Obtém o diretório do projeto.
     *
     */
    std::string getProjectDirectory();

    /**
     * @brief Adiciona um Tileset.
     *
     * @param tileSet
     */
    void addTileset(TileSet *tileSet);
    /**
     * @brief Adiciona uma animação.
     *
     * @param animationData
     */
    void addAnimation(AnimationData *animationData);
    /**
     * @brief Adiciona um Game Object.
     *
     * @param gameObject
     */
    void addGameObject(GameObject *gameObject);
    /**
     * @brief Adiciona um fundo.
     *
     * @param background
     */
    void addBackground(Background *background);
    /**
     * @brief Adiciona um procedimento.
     *
     * @param procedureData
     */
    void addProcedure(ProcedureData *procedureData);
    /**
     * @brief Adiciona uma variável.
     *
     * @param variableData
     */
    void addVariable(VariableData *variableData);

    /**
     * @brief Determina arquivo da tela de título.
     *
     * @param fileName
     */
    void setTitleScreenFile(std::string fileName);
    /**
     * @brief Determina arquivo da tela de opções.
     *
     * @param fileName
     */
    void setOptionsScreenFile(std::string fileName);
    /**
     * @brief Determina arquivo da tela de game over.
     *
     * @param fileName
     */
    void setGameOverScreenFile(std::string fileName);

    /**
     * @brief Procura Tileset pelo identificador.
     *
     * @param id
     */
    TileSet* searchTilesetById(int id);
    /**
     * @brief Procura objeto pelo identificador.
     *
     * @param id
     */
    GameObject* searchGameObjectById(int id);
    /**
     * @brief Procura animação pelo identificador.
     *
     * @param id
     */
    AnimationData* searchAnimationDataById(int id);
    /**
     * @brief Procura fundo pelo identificador.
     *
     * @param id
     */
    Background* searchBackgroundById(int id);
    /**
     * @brief Procura habilidade pelo identificador.
     *
     * @param id
     */
    Skill* searchSkillById(int id);
    /**
     * @brief Procura procedimento pelo identificador.
     *
     * @param id
     */
    ProcedureData* getProcedureById(int id);
    /**
     * @brief Procura variável pelo identificador.
     *
     * @param id
     */
    VariableData* getVariableById(int id);


    bool verifyObjectUsedById(int id);
    bool verifyObjectUsedAtEventsById(int id, std::list<EventData*> eventList);
    void removeObject(GameObject *gameObject);


    /**
     * @brief Verifica se um mapa está sendo utilizado.
     *
     * @return  true,   caso esteja sendo utilizado;
     *          false,  caso contrário.
     */
    bool verifyIfMapUsedById(int id);
    bool verifyIfMapUsedAtMapListById(int id, std::vector<Map*>* mapList);
    bool verifyIfMapUsedAtEventsById(int id, std::list<EventData*> eventList);
    void removeMap(int id, std::vector<Map*>* mapList = 0);


    /**
     * @brief Verifica se um Tileset foi usado. Retorna o mapa em que foi usado.
     *
     * @param id id do tileset.
     *
     * @return mapa em que o Tileset foi usado; NULL, cc.
     */
    Map* verifyTilesetUsed(int id);
    bool verifyTilesetUsedOnlyOne(int id);

    void removeTileset(TileSet *tileSet);

    GameObject* verifyAnimationUsed(int id);
    bool verifyAnimationUsedOnlyOnce(int id);

    void removeAnimation(AnimationData *animationData);

    bool verifyBackgroundUsed(int id);
    void removeBackground(Background *bg);

    /* os parametros abaixo nao devem ser gravados */
    std::string filePath; /**< Caminho do arquivo */
    /**
     * @brief
     *
     */
    int generateNewMapId();

    Map* searchAnyMap(std::vector<Map*> *mapList = 0);

    static const int DEATH_ACTION_RESET_MAP = 0; /**<  */
    static const int DEATH_ACTION_RESET_GAME = 1; /**< */
    static const int DEATH_ACTION_SHUTDOWN_GAME = 2; /**< */



    QString argv0;

private:
    /**
     * @brief
     *
     */
    GameData();

    /**
     * @brief Gera novo id para Tileset.
     *
     */
    int generateNewTilesetId();
    /**
     * @brief Gera novo id para animação.
     *
     */
    int generateNewAnimationId();
    /**
     * @brief Gera novo id para objeto.
     *
     */
    int generateNewGameObjectId();
    /**
     * @brief Gera novo id para fundo.
     *
     */
    int generateNewBackgroundId();
    /**
     * @brief Gera novo id para procedimento.
     *
     */
    int generateNewProcedureId();
    /**
     * @brief Gera novo id para variável.
     *
     */
    int generateNewVariableId();

    /**
     * @brief Gera novo id para mapa.
     *
     * @param mapList
     * @param id
     */
    int generateNewMapIdPercorreArvore(std::vector<Map*> *mapList, int id);



};

#endif // GAMEDATA_H
