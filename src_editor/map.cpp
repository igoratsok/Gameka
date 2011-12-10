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



#include "map.h"

Map::Map() {
    filhos = NULL;

    tileSets = new std::vector<TileSet*>();
    gameObjects = new std::vector<GameObject*>();
    gameObjectInstances = new std::vector<GameObjectInstance*>();
    teleportAreas = new std::vector<TeleportArea*>();

    music = std::string("");
    sound = std::string("");

    loopMusic = -1;
    loopSound = -1;

    background = NULL;

    width = 25;
    height = 18;

    dialogueData = NULL;
}

Map::Map(std::string mapName, int width, int height, int layers)
{
    int i, j, z;

    /* inicializando os parâmetros */
    this->mapName = mapName;
    this->width = width;
    this->height = height;
    this->layers = layers;


    /* determinando o tamanho do mapa */
    map.resize(boost::extents[width][height][layers]);

    /* inicializando a matriz com as posicoes 0 */
    for(i = 0; i < width; i++)
        for(j = 0; j < height; j++)
            for(z = 0; z < layers;  z++) {
                 map[i][j][z].x = -1;
                 map[i][j][z].y = -1;
                 map[i][j][z].z = NULL;
    }


    filhos = NULL;

    tileSets = new std::vector<TileSet*>();
    gameObjects = new std::vector<GameObject*>();
    gameObjectInstances = new std::vector<GameObjectInstance*>();
    teleportAreas = new std::vector<TeleportArea*>();

    music = std::string("");
    sound = std::string("");

    loopMusic = -1;
    loopSound = -1;

    background = NULL;


}

bool Map::isFolder() {
    return (filhos != NULL);
}

Map::Map(std::string folderName, std::vector<Map* > *mapasFilhos) {
    this->mapName = folderName;
    this->filhos = mapasFilhos;
}

void Map::extent(int layers) {
    this->layers = layers;
    map.resize(boost::extents[width][height][layers]);
}

void Map::extent(int width, int height, int layers) {
    this->layers = layers;
    this->width = width;
    this->height = height;

    map.resize(boost::extents[width][height][layers]);
}

void Map::setTile(int i, int j, int layer, int xvalue, int yvalue) {
    map[i][j][layer].x = xvalue;
    map[i][j][layer].y = yvalue;
}

bool Map::verifyLayerFilled(int layer) {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            if(map[i][j][layer].z != NULL) {
                return true;
            }
        }

    }

    return false;


}
