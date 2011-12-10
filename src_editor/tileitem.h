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


#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsRectItem>
#include <QImage>
#include <QPainter>


#include "tilemapgridvisual.h"
#include "tileset.h"
#include "gamedata.h"

class TilemapGridVisual;
class TileSet;
class GameData;

/**
 * @brief Item visual de um Tile, a ser mostrado em uma cena.
 *
 */
class TileItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param mapGridVisual gridvisual do mapa.
     * @param i Coluna do tile.
     * @param j Linha do tile.
     */
    TileItem(TilemapGridVisual *mapGridVisual, int i, int j);
    /**
     * @brief  Construtor.
     *
     * @param image A imagem do Tile.
     * @param size Tamanho do Tile.
     * @param i Coluna do Tile.
     * @param j Linha do Tile.
     */
    TileItem(QImage *image, int size, int i, int j);

    /**
     * @brief Muda a posição e Tileset do Tile.
     *
     * @param i Coluna
     * @param j Linha
     * @param tileset Tileset
     */
    void updateTile(int i, int j, TileSet *tileset);

    /**
     * @brief Muda o Tileset do Tile.
     *
     * @param tileset o novo Tileset.
     */
    void updateTileset(TileSet *tileset);

    /**
     * @brief Se está visível.
     *
     */
    bool isVisible();
    /**
     * @brief Verifica visibilidade.
     *
     * @param visibility
     */
    void setVisible(bool visibility);

private:
    QImage *image; /**< Imagem do Tileset do Tile; */
    int size, i, j; /**<  */
    bool visible; /**<  */

    bool existance; /**<  */

    float imageScale; /**<  */

protected:
    /**
     * @brief Pinta o Tile.
     *
     * @param
     * @param option
     * @param widget
     */
    void paint( QPainter *, const QStyleOptionGraphicsItem *option, QWidget *widget );

};

#endif // TILEITEM_H
