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
#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <stdio.h>
#include "SDL.h"
#include "SDL/SDL_image.h"
#include <vector>

#include "CommonTypes.h"

#include "GameData.h"
#include "Tileset.h"
#include "Tile.h"
#include "Screen.h"
#include "ScrollManager.h"
#include "Line.h"
#include "GameObjectInstance.h"
#include "BackgroundData.h"
#include "DialogueData.h"
#include "TeleportArea.h"


class GameData;
class Tileset;
class Tile;
class Screen;
class ScrollManager;
class Line;
class GameObjectInstance;
class BackgroundData;
class DialogueData;
class TeleportArea;


using namespace std;


/**
 * @brief Classe representando um mapa genérico, que é
 * uma matriz de tiles.
 *
 */
class Tilemap {
public:
        /**
         * @brief Construtor.
         *
         * @param mapId Passa o identificador do mapa.
         */
        Tilemap(int mapId);
        /**
         * @brief
         *
         */
        virtual ~Tilemap();

        /**
         * @brief
         *
         */
        Tilemap();

        /**
         * @brief Renderiza o mapa na tela.
         *
         * @param screen
         */
        void render(Screen* screen);

        /**
         * @brief Obtém um Tile por um índice.
         *
         * @param j Coluna
         * @param i Linha
         * @param z Camada
         */
        Tile* getTilesetByIndex(int j, int i, int z);
        /**
         * @brief Obtém um Tile por uma posição.
         *
         * @param x Posição X
         * @param y Posição Y
         * @param z Posição Z
         */
        Tile* getTilesetByPosition(commtypes::real x, commtypes::real y, commtypes::real z);

        /**
         * @brief Se ocorre colisão em um Tile de bloco em uma posição.
         *
         * @param type
         * @param x
         * @param y
         *
         * @return Tile* Retorna: \n
                        - O Tile colidido, se houver colisão;
                        - NULL, se não houver colisão.
         */
        Tile* isTilesetColisionBlockByPosition(int type, commtypes::real x, commtypes::real y);

        SDL_Surface *tilesetSurface; /**< SDL_Surface */

        Tileset *tileset; /**< Tileset do mapa (se for único). */
        GameData *gameData; /**< GameData */
        ScrollManager *scrollManager; /**<  */
        std::string mapName; /**< Nome do mapa. */
        int tileWidth, tileHeight, nx, ny, mapWidth, mapHeight, mapLayers, key; /**<  */
        Tile**** map; /**< Array de Tiles do mapa, a ser desenhado. */

        std::vector<Tileset*> *tileSets; /**< Lista de Tilesets do mapa. */
        std::vector<GameObjectInstance*> *gameObjectInstances; /**< Instâncias de objetos do mapa. */

        SDL_Rect renderRect; /**<  O retângulo de renderização de cada Tile. */

        BackgroundData *background; /**< Fundo. */

        std::string music; /**< Arquivo da música de fundo. */
        std::string sound; /**< Arquivo do som de fundo. */
        int loopMusic; /**< Se a música repete. */
        int loopSound; /**< Se o som repete. */
        int idFundo; /**< Identificador do fundo do mapa. */

        std::vector<TeleportArea*>* teleportAreas; /**< Áreas de teletransporte. */

        DialogueData *dialogueData; /**< Diálogo no início do mapa. */
};

#endif /* TILEMAP_H_ */
