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


#ifndef TilesetGridVisual_H
#define TilesetGridVisual_H

#include <math.h>
#include <stdio.h>
#include <boost/multi_array.hpp>

#include "tileitem.h"
#include "tilesetlinesgenerator.h"

class TileItem;
class TilesetLinesGenerator;

using namespace boost;

/**
 * @brief Conjunto de itens visuais para mostrar tiles de um Tileset em uma cena.
 *
 */
class TilesetGridVisual
{
public:
    /**
     * @brief Construtor.
     *
     * @param scene A cena na qual serão mostrados os tiles.
     * @param image A imagem do Tileset que contém os tiles.
     * @param tileSize O tamanho do tile.
     */
    TilesetGridVisual(QGraphicsScene *scene, QImage *image, int tileSize);

    /**
     * @brief Adiciona os tilesets na cena especificada no construtor.
     *
     */
    void addTilesToScene();


    QImage *image; /**< Imagem da Tileset. */
    int tileSize; /**< Tamanho da Tileset. */
    int width; /**< Largura da Tileset em número de blocos. */
    int height; /**< Altura da Tileset em número de blocos. */
    QGraphicsScene *scene; /**< Cena onde serão colocados dos tiles. */
    TilesetLinesGenerator *linesGenerator; /**< Gerador de linhas. */

    multi_array<TileItem*, 2> tileArray; /**< Array com os itens visuais de cada tile. */


};

#endif // TilesetGridVisual_H
