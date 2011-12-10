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


#ifndef TILESET_H
#define TILESET_H

#include <string>
#include <QImage>
#include <boost/multi_array.hpp>

#include "gamedata.h"

class GameData;

#define NO_COLLISION        0
#define BLOCK_COLLISION     1
#define PIXEL_COLLISION     2
#define LAYER_UP            3

using namespace boost;

/**
 * @brief Entidade para guardar dados sobre o Tileset.
 *
 */
class TileSet
{
public:
    /**
     * @brief Construtor sem nada.
     *
     */
    TileSet();
    /**
     * @brief Construtor.
     *
     * @param file o caminho para o arquivo do Tileset.
     * @param tileSize o tamanho de cada Tile.
     */
    TileSet(std::string file, int tileSize);

    /**
     * @brief Determina um valor para o mapa de colisão em uma determinada
     * célula.
     *
     * @param tileI coluna
     * @param tileJ linha
     * @param collisionType tipo de colisão: \n
                                - 0 (NO_COLLISION): não tem colisão;
                                - 1 (BLOCK_COLLISION): colisão bloqueada
     */
    void setCollision(int tileI, int tileJ, int collisionType);

    /**
     * @brief Recarrega a imagem do Tileset.
     *
     */
    void reloadTilesetImage();

    /**
     * @brief Calcula e aloca espaço para a matriz de colisão.
     *
     */
    void calculateCollisionMatrix();

    QImage* getTilesetAlphaImage(bool reset = false);


    QImage *tilesetImage; /**<  */

    multi_array<int, 2> collisionMatrix; /**< Matriz de colisão do Tileset. */
    std::string file; /**< Nome do arquivo. */
    std::string name; /**< Nome do Tileset. */
    int tileSize; /**< Tamanho de cada Tile. */
    int width; /**< Largura em número de blocos. */
    int height; /**<  Altura em número de blocos. */
    int maxX; /**<  Largura em número de blocos (na visualização). */
    int maxY; /**<  Altura em número de blocos (na visualização). */
    int id; /**< Número identificador do Tileset. */


    int hasColorKey; /**< Se tem colorkey. */
    int colorkey_r; /**< Intensidade de vermelho da colorkey. */
    int colorkey_g; /**< Intensidade de verde na colorkey. */
    int colorkey_b; /**< Intensidade de azul na colorkey. */




};

#endif // TILESET_H
