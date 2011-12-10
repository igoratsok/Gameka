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


#ifndef TilemapGridVisual_H
#define TilemapGridVisual_H

#include <QImage>
#include <QGraphicsScene>

#include <stdio.h>
#include <stdlib.h>

#include <boost/multi_array.hpp>

#include "tileitem.h"
#include "tilesetlinesgenerator.h"
#include "tilesetdock.h"
#include "gamedata.h"
#include "tileset.h"

class TilesetDock;
class TileItem;
class GameData;
class TileSet;

using namespace boost;

/**
 * @brief Conjunto de itens visuais para mostrar tiles de um mapa em uma cena.
 * O mapa atual a ser desenhado é pego na classe GameData.
 */
class TilemapGridVisual
{
public:
    /**
     * @brief Construtor.
     *
     * @param scene A cena onde irão aparecer os tiles.
     * @param image A imagem do Tileset
     * @param tileSize Tamanho de cada Tile.
     * @param width Largura em número de blocos.
     * @param height Altura em número de blocos.
     * @param layers Número de camadas
     */
    TilemapGridVisual(QGraphicsScene *scene, QImage *image,
                    int tileSize, int width, int height, int layers);

    /**
     * @brief Adiciona os tiles na cena especificada no construtor.
     *
     */
    void addTilesToScene();

    /**
     * @brief Troca um Tile de uma célula.
     *
     * @param i Coluna do tile.
     * @param j Linha do tile.
     * @param tileI Novo valor i da célula.
     * @param tileJ Novo valor j da célula.
     * @param layer Número da camada.
     * @param tileset Tileset da célula.
     */
    void changeTile(int i, int j, int tileI, int tileJ, int layer, TileSet *tileset);

    /**
     * @brief Se está visível.
     *
     */
    bool isVisible();
    /**
     * @brief Determina visibilidade de todos tiles.
     *
     * @param visibility visiblidade de todos tiles.
     */
    void setVisible(bool visibility);

    /**
     * @brief Determina opacidade dos tiles.
     *
     * @param opacity
     */
    void setOpacity(float opacity);
    /**
     * @brief Expande as camadas (verifica o número de camadas do mapa sendo editado no GameData).
     *
     */
    void expandLayer();

    /**
     * @brief Determina o zoom. Ainda não funciona bem.
     *
     * @param zoom
     */
    void setZoom(int zoom);

    /**
     * @brief Obtém o número de camadas.
     *
     */
    int getLayerCount();


    QImage *image; /**< Image do Tileset. */
    int tileSize, width, height; /**<  */
    QGraphicsScene *scene; /**< Cena. */


    multi_array<TileItem*, 3> tileMap; /**< Itens visuais dos Tiles. */

    TilesetLinesGenerator *linesGenerator; /**< Gerador de linhas. */
    TilesetDock *tilesetDock; /**< Ponteiro para a dock de tilesets. */
private:
    bool visible; /**< Se está visível. */
    int layers; /**< Número de camadas. */
};

#endif // TilemapGridVisual_H
