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


#ifndef POINT_H
#define POINT_H

#include "tileset.h"

class TileSet;

/**
 * @brief Representação de um ponto. O eixo "z" é um ponteiro para um Tileset.
 *
 */
class Point
{
public:
    /**
     * @brief Construtor.
     *
     */
    Point();

    /**
     * @brief Construtor com x e y determinados.
     *
     * @param x Posição X;
     * @param y Posição Y;
     */
    Point(int x, int y);

    int x, y; /**<  */
    TileSet* z; /**<  */
};

#endif // POINT_H
