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


#ifndef MAP_H
#define MAP_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <boost/multi_array.hpp>
#include <boost/multi_array/iterator.hpp>
#include <stdio.h>

#include <vector>

#include "point.h"
#include "tileset.h"
#include "gameobject.h"
#include "gameobjectinstance.h"
#include "teleportarea.h"
#include "background.h"
#include "dialoguedata.h"

class Point;
class TileSet;
class GameObject;
class GameObjectInstance;
class TeleportArea;
class Background;

using namespace boost;

/**
 * @brief Entidade para guardar informações acerca de um mapa.
 * Pode também representar uma pasta de mapas.
 *
 */
class Map
{
public:
    /**
     * @brief Construtor.
     *
     */
    Map();
    /**
     * @brief Construtor.
     *
     * @param mapName Nome do mapa.
     * @param width Largura em número de blocos.
     * @param height Altura em número de blocos.
     * @param layers Número de camadas.
     */
    Map(std::string mapName, int width, int height, int layers);
    /**
     * @brief Construtor para criar uma pasta.
     *
     * @param folderName Nome das pasta.
     * @param mapasFilhos
     */
    Map(std::string folderName, std::vector<Map *> *mapasFilhos);

    /**
     * @brief Extende o mapa em uma largura, altura e camadas.
     *
     * @param width Largura em número de blocos.
     * @param height Altura em número de blocos.
     * @param layers Número de camadas
     */
    void extent(int width, int height, int layers);
    /**
     * @brief Extenda as camadas dos mapas.
     *
     * @param layers Número de camadas
     */
    void extent(int layers);
    /**
     * @brief Determina o Tile.
     *
     * @param i Coluna do mapa;
     * @param j linha do mapa;
     * @param layer Camada do mapa;
     * @param xvalue Valor i do Tileset;
     * @param yvalue Valor j do tileset;
     */
    void setTile(int i, int j, int layer, int xvalue, int yvalue);
    /**
     * @brief Se é uma pasta, ou seja, se tem filhos.
     *
     */
    bool isFolder();

    /**
     * @brief Verifica se uma camada está preenchida.
     *
     * @param layer
     */
    bool verifyLayerFilled(int layer);

    std::vector<Map *> *filhos; /**< Filhos de uma "pasta". Se tiver filhos, é um mapa. */

    std::string mapName; /**< Nome do mapa. */
    int id; /**< Identificador do mapa. */

    multi_array<Point, 3> map; /**< Matriz do mapa propriamente dita. */
    std::vector<TileSet *> *tileSets; /**< Tilesets do mapa. */
    std::vector<GameObject *> *gameObjects; /**< Objetos do mapa (não é mais utilizado). */

    int width, height, layers; /**<  */


    std::string music; /**< Nome do arquivo da música do mapa. */
    std::string sound; /**< Nome do arquivo do som do mapa. */
    int loopMusic; /**< Se a música entra em loop. */
    int loopSound; /**< Se o som entra em loop. */
    int idFundo; /**< Identificador do fundo. */
    std::vector<GameObjectInstance *> *gameObjectInstances; /**< Instâncias de objetos no mapa. */



    std::vector<TeleportArea*> *teleportAreas; /**< Áreas de teletransporte. */


    Background *background; /**< Fundos. */


    DialogueData *dialogueData; /**< Diálogo inicial. */



};

#endif // MAP_H
