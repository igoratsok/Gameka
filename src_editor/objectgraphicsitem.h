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


#ifndef OBJECTGRAPHICSITEM_H
#define OBJECTGRAPHICSITEM_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include <QMenu>
#include <QAction>
#include <QStaticText>

#include <stdlib.h>
#include <vector>

#include "gameobject.h"
#include "gameobjectinstance.h"
#include "gamedata.h"
#include "messageboxes.h"
#include "mapeditorcontroller.h"
#include "newdialoguedialog.h"


class GameObject;
class GameObjectInstance;
class GameData;
class MessageBoxes;
class MapEditorController;
class NewDialogueDialog;

/**
 * @brief Item visual de um objeto. Utilizado no TilemapScene.
 *
 */
class ObjectGraphicsItem : public QGraphicsRectItem
{
public:
    /**
     * @brief Construtor.
     *
     * @param gameObjectInstance A instância do objeto relacionada.
     * @param mapGameObjectInstances Todas as instâncias de objeto do mapa;
     * @param mapEditorController A controladora do editor de mapas, utilizada para chamadas na camada de negócio;
     */
    ObjectGraphicsItem(GameObjectInstance *gameObjectInstance,
                       std::vector<GameObjectInstance*> *mapGameObjectInstances,
                       MapEditorController *mapEditorController);



    /**
     * @brief Determina visibilidade.
     *
     * @param visible
     */
    void setVisible(bool visible);
    /**
     * @brief Determina efeito de colorização.
     *
     * @param value
     */
    void setColorizeEffect(bool value);
    /**
     * @brief Atualiza posição da entidade com base na posição do item. Usado quando o objeto se move.
     *
     */
    void updateObjectInstancePosition();

    QGraphicsColorizeEffect *colorizeEffect; /**< Efeito de colorização aplicado quando objetos são selecionados. */

private:
    QImage *image; /**< Imagem do objeto. */
    bool visible; /**< Visibilidade */
    float width, height; /**<  */
    GameObjectInstance *gameObjectInstance; /**< Instância do objeto. */
    std::vector<GameObjectInstance*> *mapGameObjectInstances; /**< Todas instâncias do mapa. */
    MapEditorController *mapEditorController; /**< Controladora do editor de mapas. */


protected:
    /**
     * @brief Pinta o objeto.
     *
     * @param
     * @param option
     * @param widget
     */
    void paint( QPainter *, const QStyleOptionGraphicsItem *option, QWidget *widget );
    /**
     * @brief Evento ao se soltar o mapa: atualiza a posição da entidade do objeto com base na posição do item.
     *
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief Ativado ao pressionar com o botão esquerdo do mouse no objeto. Mostra menus para determinar o objeto,
     * como objeto central, principal, editar e remover.
     *
     * @param event
     */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // OBJECTGRAPHICSITEM_H
