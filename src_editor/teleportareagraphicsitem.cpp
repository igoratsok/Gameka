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



#include "teleportareagraphicsitem.h"

TeleportAreaGraphicsItem::TeleportAreaGraphicsItem(MapEditorController *mapEditorController)
    : mapEditorController(mapEditorController)
{
    littleBoxAtTopLeft = NULL;
}

void TeleportAreaGraphicsItem::addLittleBoxAtTopLeftMarkToScene(QGraphicsScene *graphicsScene) {
    littleBoxAtTopLeft = graphicsScene->addRect(this->rect().x(), this->rect().y(), 15, 20, QPen(QColor(0, 0, 180, 255)), QBrush(QColor(0, 0, 255, 255)));
    std::cout << this->x() << std::endl;
    std::cout << this->y() << std::endl;


    rectText = new QGraphicsTextItem();
    rectText->setHtml(QString("<strong>T</strong>"));
    rectText->setPos(this->rect().x(), this->rect().y());
    rectText->setDefaultTextColor(QColor(255, 255, 255, 255));

    graphicsScene->addItem(rectText);



}

void TeleportAreaGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    QGraphicsRectItem::contextMenuEvent(event);

    QMenu menu;
    QAction *actionEdit = menu.addAction(QApplication::tr("Editar teletransporte"));
    QAction *actionRemove = menu.addAction(QApplication::tr("Remover teletransporte"));

    QAction *selectedAction = menu.exec(event->screenPos());

    if(selectedAction == actionEdit) {
        NewTeleportAreaDialog *newTeleportAreaDialog = new NewTeleportAreaDialog(mapEditorController, teleportArea);
        teleportArea = newTeleportAreaDialog->exec();

        delete newTeleportAreaDialog;
    } else if(selectedAction == actionRemove) {
        // TODO: melhorar isso aqui depois, ficou meio tosco
        if(MessageBoxes::showConfirmBox(std::string(QApplication::tr("Deseja mesmo remover?").toStdString().c_str()))) {
            GameData *gameData = GameData::getInstance();
            gameData->editingMap->teleportAreas->erase(
                    std::find(gameData->editingMap->teleportAreas->begin(),
                              gameData->editingMap->teleportAreas->end(),
                              teleportArea));


            delete this;
            delete littleBoxAtTopLeft;
            delete rectText;
        }

    }
}
