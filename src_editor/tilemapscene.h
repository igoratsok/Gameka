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


#ifndef TILEMAPSCENE_H
#define TILEMAPSCENE_H

#include <QGraphicsScene>
#include <QAbstractGraphicsShapeItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QAction>
#include <QMenu>
#include <QKeyEvent>
#include <math.h>


#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "tilemapgridvisual.h"
#include "mapeditorcontroller.h"
#include "tileset.h"
#include "gameobject.h"
#include "gamedata.h"
#include "objectgraphicsitem.h"
#include "newteleportareadialog.h"
#include "neweventareadialog.h"
#include "teleportarea.h"
#include "teleportareagraphicsitem.h"

class TilemapGridVisual;
class MapEditorController;
class Tileset;
class GameData;
class GameObject;
class ObjectGraphicsItem;
class NewTeleportAreaDialog;
class NewEventAreaDialog;
class TeleportArea;
class TeleportAreaGraphicsItem;


/**
 * @brief Cena que mostra e permite a edição dos Tilesets.
 *
 */
class TilemapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief Construtor.
     *
     * @param tileSize tamanho do Tile.
     * @param width largura em número de blocos.
     * @param height altura em número de blocos.
     * @param layers camadas.
     * @param mapEditorController controladora do editor de mapas.
     */
    TilemapScene(int tileSize, int width, int height, int layers, MapEditorController *mapEditorController);

    QGraphicsRectItem *shape1, *shape2; /**< Retângulos para mostrar seleção. */
    QGraphicsRectItem *objectSelectionShape; /**< Seleção de objetos. */
    QGraphicsRectItem *layerRect; /**< Retângulo branco para deixar os layers de baixo menos visíveis. */

    QPointF objectSelectionStartPosition, objectSelectionEndPosition; /**<  */
    QPointF squareCircleDrawStartPosition, squareCircleDrawEndPosition; /**<  */
    QPointF squareCopyDrawStartPosition, squareCopyDrawEndPosition; /**< */


    /**
     * @brief Desenha (adiciona o item) o retângulo de seleção.
     *
     */
    void drawObjectSelectionRectangle();

    /**
     * @brief Tira o efeito de colorização dos itens selecionados.
     *
     */
    void cleanColorizeSelectedItems();

    /**
     * @brief Aplica um efeito de colorização nos itens selecionados.
     *
     */
    void colorizeSelectedItems();

    /**
     * @brief Evento ao mover o mouse. Tem comportamento baseado no modo de edição selecionado.
     *
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Evento ao pressionar o mouse. Tem comportamento baseado no modo de edição selecionado.
     *
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Evento ao soltar o mouse. Tem comportamento baseado no modo de edição selecionado.
     *
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Evento executado quando move a rodinha do mouse. Nada acontece, por enquanto.
     *
     * @param event
     */
    void wheelEvent(QGraphicsSceneWheelEvent *event);

    /**
     * @brief Muda o tile de uma célula do mapa, no visual apenas.
     *
     * @param i Coluna do Tile.
     * @param j Linha do Tile.
     * @param tileI Novo valor i do Tile.
     * @param tileJ Novo valor j do Tile.
     * @param layer Camada do Tile.
     * @param tileSet Tileset do Tile.
     */
    void changeTile(int i, int j, int tileI, int tileJ, int layer, TileSet *tileSet);

    /**
     * @brief Determina o tamanho do retângulo de seleção. Ele irá aumentar de tamanho de acordo
     * com o número de Tiles selecionados no Seletor de Tilesets, pra indicar o espaço onde serão preenchidos.
     * Também irá aumentar ao usar o modo de pintura de retângulos.
     *
     * @param di número de blocos na horizontal
     * @param dj número de blocos na vertical
     */
    void setSelectionRectangleSize(int di, int dj);

    /**
     * @brief Desenha (insere o item na tela) o objeto selecionado no Seletor de Objetos na posição do cursor.
     * O objetivo é mostrar uma prévie do objeto no cenário, onde ele seria posicionado.
     *
     */
    void setCurrentObjectAtCursor();

    /**
     * @brief Determina o modo do editor.
     *
     * @param mode modo a ser determinado.
     */
    void setEditorMode(int mode);
    /**
     * @brief Determina a camada sendo editada.
     *
     * @param layer
     */
    void setEditionLayer(int layer);

    /**
     * @brief Determina o zoom da camada. Ainda não está funcionando direito.
     *
     * @param zoom
     */
    void setZoom(int zoom);

    TilemapGridVisual *mapGridVisual; /**<  Tiles do mapa mostrados no cenário. */
    MapEditorController *mapEditorController; /**< Controladora do editor de mapas. */
    QGraphicsPixmapItem *currentObjectItem; /**< Item do objeto atual selecionado no Seletor de Objetos. */
    bool mousePressed; /**< Booleano para indicar se o mouse está pressionado. */
    bool rightMousePressed; /**< Booleano para indicar que o botão direito do mouse está pressionado. */

    int tileSize; /**< Tamanho do tile. */


    std::vector<GameObjectInstance*> *gameObjectInstances; /**< Ponteiro para instâncias de objetos no cenário. */
    std::vector<TeleportAreaGraphicsItem*> *teleportAreaGraphicsItems; /**< Pointeiro para áreas de teletransporte no cenário. */



};

#endif // TILEMAPSCENE_H
