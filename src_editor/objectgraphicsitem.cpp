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



#include "objectgraphicsitem.h"

ObjectGraphicsItem::ObjectGraphicsItem(GameObjectInstance *gameObjectInstance,
                                       std::vector<GameObjectInstance *> *mapGameObjectInstances,
                                       MapEditorController *mapEditorController)
{
    this->gameObjectInstance = gameObjectInstance;
    this->image = new QImage(gameObjectInstance->gameObject->getIconImage());
    this->width = image->width();
    this->height = image->height();
    this->setRect(0, 0, width, height);
    this->mapGameObjectInstances = mapGameObjectInstances;
    this->mapEditorController = mapEditorController;

    colorizeEffect = new QGraphicsColorizeEffect();
    colorizeEffect->setColor(QColor(255, 255, 255, 255));
    colorizeEffect->setStrength(0.2);
    colorizeEffect->setEnabled(false);

    setGraphicsEffect(colorizeEffect);
}

void ObjectGraphicsItem::setVisible(bool visible) {
    this->visible = visible;
}

void ObjectGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(QRectF(0, 0, width, height), *image, QRectF(0, 0,  width, height), NULL);


    if(gameObjectInstance->isCenter) {
        painter->setPen(QPen(QColor(0, 255, 0, 220)));
        painter->drawRect(QRect(0, 0, width, height));
        painter->setBrush(QBrush(QColor(0, 255, 0, 180)));
        painter->drawRect(QRect(width - 10, 0, 10, 15));
        painter->setPen(QPen(QColor(0, 0, 0)));
        painter->drawStaticText(width - 10, 0, QStaticText(QString("C")));
    }

    if(gameObjectInstance->isMainObject) {
        painter->setBrush(QBrush(QColor(0, 0, 0, 0)));
        painter->setPen(QPen(QColor(255, 0, 0, 220)));
        painter->drawRect(QRect(0, 0, width, height));
        painter->setBrush(QBrush(QColor(255, 0, 0, 180)));
        painter->drawRect(QRect(0, 0, 10, 15));
        painter->setPen(QPen(QColor(255, 255, 255)));
        painter->drawStaticText(0, 0, QStaticText(QString("P")));
    }




}

void ObjectGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mouseReleaseEvent(event);

    gameObjectInstance->x = this->pos().x();
    gameObjectInstance->y = this->pos().y();
}

void ObjectGraphicsItem::updateObjectInstancePosition() {
    gameObjectInstance->x = this->pos().x();
    gameObjectInstance->y = this->pos().y();
}

void ObjectGraphicsItem::setColorizeEffect(bool value) {
    if(value) {
        colorizeEffect->setEnabled(true);
    } else {
        colorizeEffect->setEnabled(false);
    }
}

void ObjectGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    QMenu menu;
    QAction *mainObjectAction = menu.addAction("Objeto Principal");
    QAction *cameraCenterAction = menu.addAction("Centro da camera");
    menu.addSeparator();
    QAction *dialogueAction = NULL;
    if(gameObjectInstance->gameObject->type == GameObject::NPC) {
        dialogueAction = menu.addAction(QString::fromUtf8("Editar diálogos"));
        menu.addSeparator();
    }

    QAction *editarPropriedadesAction = menu.addAction("Editar propriedades");
    QAction *removeAction = menu.addAction("Remover");


    mainObjectAction->setCheckable(true);
    mainObjectAction->setChecked(gameObjectInstance->isMainObject);
    cameraCenterAction->setCheckable(true);
    cameraCenterAction->setChecked(gameObjectInstance->isCenter);


    QAction *selectedAction = menu.exec(event->screenPos());

    if(selectedAction == mainObjectAction) {
        gameObjectInstance->isMainObject = !gameObjectInstance->isMainObject;

        scene()->update();
        this->update();


        for(std::vector<GameObjectInstance*>::iterator it = mapGameObjectInstances->begin();
                           it != mapGameObjectInstances->end(); ++it) {
            GameObjectInstance *currentGameObjectInstance = *it;
            if(currentGameObjectInstance != gameObjectInstance) {
                currentGameObjectInstance->isMainObject = false;
            }
        }
    } else if(selectedAction == cameraCenterAction) {
        gameObjectInstance->isCenter = !gameObjectInstance->isCenter;

        scene()->update();
        this->update();

        for(std::vector<GameObjectInstance*>::iterator it = mapGameObjectInstances->begin();
                           it != mapGameObjectInstances->end(); ++it) {
            GameObjectInstance *currentGameObjectInstance = *it;
            if(currentGameObjectInstance != gameObjectInstance) {
                currentGameObjectInstance->isCenter = false;
            }


        }
    } else if(selectedAction == removeAction) {
        if(MessageBoxes::showConfirmBox(std::string("Deseja mesmo remover?"))) {
            GameData *gameData = GameData::getInstance();
            gameData->editingMap->gameObjectInstances->erase(
                    std::find(gameData->editingMap->gameObjectInstances->begin(),
                              gameData->editingMap->gameObjectInstances->end(),
                              gameObjectInstance));
            /* TODO: se for objeto principal, transferir */

            delete this;
        }


    } else if(selectedAction == editarPropriedadesAction) {
        mapEditorController->openConfigsTabWindow(gameObjectInstance->gameObject);
    } else if(gameObjectInstance->gameObject->type == GameObject::NPC && selectedAction == dialogueAction) {
        mapEditorController->openNewDialogueDialog(gameObjectInstance);
    }
}
