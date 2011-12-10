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


#ifndef TILESETSCENE_H
#define TILESETSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <math.h>

#include "tilesetgridvisual.h"
#include "tilesetdock.h"
#include "tileset.h"
#include "gamedata.h"

class TilesetDock;
class TileSet;
class GameData;
class TilesetLinesGenerator;

class TilesetGridVisual;

/**
 * @brief Cena do seletor de Tilesets. Permite pegar Tiles no seletor, contida
 * na TilesetDock. Para dispor os tiles na tela, usa um objeto da classe
 * TilesetGridVisual.
 *
 */
class TilesetScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param tilesetDock ponteiro para a TilesetDock.
     * @param tileset Tileset a ser mostrado no seletor.
     */
    TilesetScene(TilesetDock *tilesetDock, TileSet *tileset);

    QGraphicsRectItem *shape1, *shape2, *shape3, *shape4; /**< Retângulos para mostrar o TilesetSelecionado */

    int tileSize; /**< Tamanho do tile. */
    int iAnt, jAnt; /**< Posição que o mouse clica. Usado para calcular
                        a região selecionada do mouse. Não é atualizada
                        enquanto o mouse move segurado. */

    /* variaveis para desenho extensivel do shape */
    int iInicial, jInicial; /**< Posição que o mouse clica. Usado para
                                desenhar os retângulos. */


    TilesetDock *tilesetDock; /**<  */
    TilesetGridVisual *gridVisual; /**< Mostra os tiles na tela. */

    TileSet *tileSet; /**< Tileset sendo mostrado. */


    bool mousePressed; /**< Variável para o caso do mouse estar pressionado. */

    /**
     * @brief Evento que roda enquanto o mouse se move.
     *
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief Evento que roda quando o mouse é pressionado.
     *
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief Evento que roda quando o mouse é solto.
     *
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TILESETSCENE_H
