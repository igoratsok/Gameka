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

#ifndef TILESET_H_
#define TILESET_H_

#include <string>
#include "SDL.h"
#include "SDL/SDL_image.h"
#include <stdio.h>

#include "GameData.h"

class GameData;

/**
 * @brief Classe de Tileset. Responsável por armazenar
 * dados de um tileset bem como
 *
 */
class Tileset {
public:
        /**
         * @brief Construtor.
         *
         */
        Tileset();
        /**
         * @brief
         *
         */
        virtual ~Tileset();



        int** collisionMatrix; /**< Matriz de colisão. */
        std::string file; /**< Nome do arquivo. */
        std::string name; /**< Nome do Tileset. */
        int tileSize; /**< Tamanho do Tile. */
        int width; /**< Largura em número de blocos. */
        int height; /**< Altura em número de blocos. */
        int maxX; /**< Largura em número de blocos (para uso no Editor). */
        int maxY; /**< Altura em número de blocos (para uso no Editor). */
        int id; /**< Número identificador do Tileset. */

        /**
         * @brief Obtém a SDL_Surface do Tileset.
         *
         */
        SDL_Surface* getTilesetSurface();

private:
        SDL_Surface *tilesetSurface; /**< A SDL_Surface do Tileset. */
};

#endif /* TILESET_H_ */
