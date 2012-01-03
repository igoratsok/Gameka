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


#ifndef TELEPORTAREAGRAPHICSITEM_H
#define TELEPORTAREAGRAPHICSITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QApplication>

#include <iostream>

#include "teleportarea.h"
#include "newteleportareadialog.h"
#include "gamedata.h"
#include "messageboxes.h"
#include "mapeditorcontroller.h"

class TeleportArea;
class NewTeleportAreaDialog;
class GameData;
class MessageBoxes;
class MapEditorController;

/**
 * @brief Item gráfico para mostar uma área de teletransporte.
 *
 */
class TeleportAreaGraphicsItem : public QGraphicsRectItem
{
public:
    /**
     * @brief Construtor.
     *
     * @param mapEditorController A controladora do editor de mapas, para acessar a camada de negócio.
     */
    TeleportAreaGraphicsItem(MapEditorController *mapEditorController);
    /**
     * @brief Adiciona uma caixa com um "T" no canto esquerdo superior do quadrado.
     *
     * @param graphicsScene
     */
    void addLittleBoxAtTopLeftMarkToScene(QGraphicsScene *graphicsScene);

    QGraphicsRectItem *littleBoxAtTopLeft; /**< Caixinha com um "T" no canto  */
    QGraphicsTextItem *rectText; /**< Retângulo do texto ("T") */
    TeleportArea *teleportArea; /**< Área de teletransporte do item */
    MapEditorController *mapEditorController; /**< Controladora de editor de mapas. */

protected:
    /**
     * @brief Ativado ao clicar com o botão direito do mouse. Mostra so menus de editar e remover teletransporte.
     *
     * @param event
     */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // TELEPORTAREAGRAPHICSITEM_H
