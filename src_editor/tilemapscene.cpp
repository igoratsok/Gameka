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



#include "tilemapscene.h"

TilemapScene::TilemapScene(int size, int width,
                           int height, int layers, MapEditorController *mapEditorController) : QGraphicsScene(),
    tileSize(size)
{
    GameData *gameData = GameData::getInstance();
    this->mapEditorController = mapEditorController;

    setSceneRect(0, 0, size*width, size*height);
    mapGridVisual = new TilemapGridVisual(this, new QImage("tile_example.png"), size, width, height, layers);
    //gridView->addTilesToScene();

    //shape = addRect(3, 3, size-6, size-6, QPen(), QBrush(QColor(0, 0, 255, 255), Qt::SolidPattern));
    shape1 = addRect(3, 3, size-6, size-6, QPen(QColor(255, 255, 255, 255)));
    shape2 = addRect(2, 2, size-4, size-4, QPen());


    shape1->setOpacity(1);




    currentObjectItem = NULL;



    shape1->setZValue(30);
    shape2->setZValue(30);
    mousePressed = false;
    rightMousePressed = false;


    setEditorMode(mapEditorController->editorMode);

    /* carregando objetos para a tela */
    gameObjectInstances = gameData->editingMap->gameObjectInstances;
    for(std::vector<GameObjectInstance*>::iterator it = gameObjectInstances->begin(); it != gameObjectInstances->end(); ++it) {
        GameObjectInstance *gameObjectInstance = *it;

        ObjectGraphicsItem *item = new ObjectGraphicsItem(gameObjectInstance, gameObjectInstances, mapEditorController);
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        item->setZValue(35);
        item->setPos(gameObjectInstance->x, gameObjectInstance->y);
        this->addItem(item);
    }

    objectSelectionShape = NULL;

    teleportAreaGraphicsItems = new std::vector<TeleportAreaGraphicsItem*>();
    std::vector<TeleportArea*> *teleportAreas = gameData->editingMap->teleportAreas;
    for(std::vector<TeleportArea*>::iterator it = teleportAreas->begin(); it != teleportAreas->end(); ++it) {
        TeleportArea *teleportArea = *it;

        TeleportAreaGraphicsItem *teleportAreaGraphicsItem;
        teleportAreaGraphicsItem = new TeleportAreaGraphicsItem(mapEditorController);
        teleportAreaGraphicsItem->setRect(teleportArea->x, teleportArea->y, teleportArea->w, teleportArea->h);
        teleportAreaGraphicsItem->setPen(QPen(QColor(0, 0, 255, 255)));
        teleportAreaGraphicsItem->setBrush(QBrush(QColor(0, 0, 255, 30)));

        addItem(teleportAreaGraphicsItem);

        teleportAreaGraphicsItem->addLittleBoxAtTopLeftMarkToScene(this);

        teleportAreaGraphicsItem->teleportArea = teleportArea;

        teleportAreaGraphicsItems->push_back(teleportAreaGraphicsItem);

    }

    layerRect = new QGraphicsRectItem(QRectF(0, 0, width*size, height*size), 0, this);
    layerRect->setBrush(QBrush(QColor(255, 255, 255, 150)));
    layerRect->setZValue(-1);
    addItem(layerRect);
}


void TilemapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);


    int i, j;

    if(mapEditorController->editorMode == MapEditorController::MODE_MAP && event->button() == Qt::LeftButton) {

        switch(mapEditorController->drawMode) {
        case MapEditorController::DRAW_MODE_PAINT:
        case MapEditorController::DRAW_MODE_ERASER:
        case MapEditorController::DRAW_MODE_PENCIL:
            mousePressed = true;
            if(mapEditorController->editorMode == MapEditorController::MODE_MAP) {

                i = floor(event->scenePos().x()/tileSize);
                j = floor(event->scenePos().y()/tileSize);

                mapEditorController->iClick = i;
                mapEditorController->jClick = j;

                if(i < 0) {
                    i = 0;
                }

                if(j < 0) {
                    j = 0;
                }

                mapEditorController->changeTile(i, j);
                break;
            }
        case MapEditorController::DRAW_MODE_SQUARE:
            i = floor(event->scenePos().x()/tileSize);
            j = floor(event->scenePos().y()/tileSize);

            mapEditorController->iClick = i;
            mapEditorController->jClick = j;

            if(i < 0) {
                i = 0;
            }

            if(j < 0) {
                j = 0;
            }

            squareCircleDrawStartPosition = event->scenePos();
            mousePressed = true;

            break;

        }



    } else if(mapEditorController->editorMode == MapEditorController::MODE_OBJECT ||
              mapEditorController->editorMode == MapEditorController::MODE_EVENT ) {
        GameData *gameData = GameData::getInstance();

        if(event->button() == Qt::LeftButton) {
            mousePressed = true;
        }


        if(event->button() == Qt::LeftButton || event->button() == Qt::MiddleButton) {
            /* TODO: este código é provisório, colocar o código de adicionar objeto AQUI */
            GameObject *selectedObject;
            if((selectedObject = mapEditorController->getSelectedObject()) != NULL) {
                GameObjectInstance* gameObjectInstance;
                gameObjectInstance = new GameObjectInstance(selectedObject);


                gameObjectInstance->x = (int) currentObjectItem->pos().x();
                gameObjectInstance->y = (int) currentObjectItem->pos().y();

                mapEditorController->addGameObjectInstanceToEditingMap(gameObjectInstance);

                ObjectGraphicsItem *item = new ObjectGraphicsItem(gameObjectInstance, gameObjectInstances, mapEditorController);
                item->setFlag(QGraphicsItem::ItemIsMovable);
                item->setFlag(QGraphicsItem::ItemIsSelectable);
                item->setZValue(30);
                item->setPos(currentObjectItem->pos());
                this->addItem(item);

                if(event->button() == Qt::LeftButton) {
                    mapEditorController->unSelectObject();
                    setCurrentObjectAtCursor();
                }



            }

            if(event->button() == Qt::LeftButton) {
                objectSelectionStartPosition = event->scenePos();
                objectSelectionEndPosition = event->scenePos();
                if(objectSelectionShape != NULL) {
                    objectSelectionShape->setVisible(false);
                }
            }
        }







    }

    if(event->button() == Qt::RightButton && mapEditorController->editorMode == MapEditorController::MODE_MAP) {
        rightMousePressed = true;

        squareCircleDrawStartPosition = event->scenePos();
    }

    cleanColorizeSelectedItems();
    colorizeSelectedItems();
}







void TilemapScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    int mousePosX, mousePosY;

    mousePosX = floor(event->scenePos().x());
    mousePosY = floor(event->scenePos().y());

    std::stringstream ss;
    ss << std::string("X: ") << mousePosX << std::string(" Y: ") << mousePosY;

    mapEditorController->setStatusBarText(QString(ss.str().c_str()));


    if(mapEditorController->editorMode == MapEditorController::MODE_MAP) {
        shape1->setPos(floor(event->scenePos().x()/tileSize)*tileSize, floor(event->scenePos().y()/tileSize)*tileSize);
        shape2->setPos(shape1->pos());

        int i, j;

        switch(mapEditorController->drawMode) {
        case MapEditorController::DRAW_MODE_PAINT:
        case MapEditorController::DRAW_MODE_ERASER:
        case MapEditorController::DRAW_MODE_PENCIL:

            if(mousePressed) {
                i = floor(event->scenePos().x()/tileSize);
                j = floor(event->scenePos().y()/tileSize);

                if(i < 0) {
                    i = 0;
                }

                if(j < 0) {
                    j = 0;
                }

                mapEditorController->changeTile(i, j);
            }
            break;
        case MapEditorController::DRAW_MODE_SQUARE:
            if(mousePressed) {
                i = floor(event->scenePos().x()/tileSize);
                j = floor(event->scenePos().y()/tileSize);

                int iInicial = squareCircleDrawStartPosition.x()/tileSize;
                int jInicial = squareCircleDrawStartPosition.y()/tileSize;
                int iStart, jStart;
                int diff_i, diff_j;

                if(i < 0) i = 0;
                if(j < 0) j = 0;

                if(i > (mapGridVisual->width-1)) {
                    i = mapGridVisual->width-1;
                }
                if(j > (mapGridVisual->height-1)) {
                    j = mapGridVisual->height-1;
                }

                diff_i = (i - iInicial);
                diff_j = (j - jInicial);

                if(diff_i < 0) {
                    iStart = iInicial + diff_i;
                } else {
                    iStart = iInicial;
                }

                if(diff_j < 0) {
                    jStart = jInicial + diff_j;
                } else {
                    jStart = jInicial;
                }

                setSelectionRectangleSize((abs(diff_i)), (abs(diff_j)));
                shape1->setPos(iStart*tileSize, jStart*tileSize);
                shape2->setPos(iStart*tileSize, jStart*tileSize);
            }



            break;

        }

        if(rightMousePressed) {
            i = floor(event->scenePos().x()/tileSize);
            j = floor(event->scenePos().y()/tileSize);

            int iInicial = squareCircleDrawStartPosition.x()/tileSize;
            int jInicial = squareCircleDrawStartPosition.y()/tileSize;
            int iStart, jStart;
            int diff_i, diff_j;

            if(i < 0) i = 0;
            if(j < 0) j = 0;

            if(i > (mapGridVisual->width-1)) {
                i = mapGridVisual->width-1;
            }
            if(j > (mapGridVisual->height-1)) {
                j = mapGridVisual->height-1;
            }

            diff_i = (i - iInicial);
            diff_j = (j - jInicial);

            if(diff_i < 0) {
                iStart = iInicial + diff_i;
            } else {
                iStart = iInicial;
            }

            if(diff_j < 0) {
                jStart = jInicial + diff_j;
            } else {
                jStart = jInicial;
            }

            setSelectionRectangleSize((abs(diff_i)), (abs(diff_j)));
            shape1->setPos(iStart*tileSize, jStart*tileSize);
            shape2->setPos(iStart*tileSize, jStart*tileSize);
        }



    } else if(mapEditorController->editorMode == MapEditorController::MODE_OBJECT ||
              mapEditorController->editorMode == MapEditorController::MODE_EVENT) {
        if(currentObjectItem != NULL) {
            QPointF currentObjectItemPos = event->scenePos();

            currentObjectItemPos.setX(currentObjectItemPos.x() - currentObjectItem->boundingRect().width()/2);
            currentObjectItemPos.setY(currentObjectItemPos.y() - currentObjectItem->boundingRect().height()/2);
            currentObjectItem->setPos(currentObjectItemPos);
        }

        if(mousePressed) {
            objectSelectionEndPosition = event->scenePos();
            drawObjectSelectionRectangle();
        }



    }


}

void TilemapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);



    if(event->button() == Qt::LeftButton) {
        mousePressed = false;
        mapEditorController->pushUndoChangesCommand();
    } else if(event->button() == Qt::RightButton && mapEditorController->editorMode == MapEditorController::MODE_MAP) {
        rightMousePressed = false;

        squareCircleDrawEndPosition = event->scenePos();

        mapEditorController->setCopyArray(squareCircleDrawStartPosition.x()/tileSize, squareCircleDrawStartPosition.y()/tileSize,
                                         squareCircleDrawEndPosition.x()/tileSize, squareCircleDrawEndPosition.y()/tileSize);

        int i, j;
        i = floor(event->scenePos().x()/tileSize);
        j = floor(event->scenePos().y()/tileSize);

        if(i < 0) {
            i = 0;
        }

        if(j < 0) {
            j = 0;
        }

    }

    if(mapEditorController->editorMode == MapEditorController::MODE_OBJECT) {
        if(event->button() == Qt::LeftButton) {

            // verifica quais os itens que deverao ser selecionados
            float xmin = std::min(objectSelectionStartPosition.x(), objectSelectionEndPosition.x());
            float ymin = std::min(objectSelectionStartPosition.y(), objectSelectionEndPosition.y());
            float xmax = std::max(objectSelectionStartPosition.x(), objectSelectionEndPosition.x());
            float ymax = std::max(objectSelectionStartPosition.y(), objectSelectionEndPosition.y());


            if(objectSelectionShape != NULL) {
                objectSelectionShape->setVisible(false);
            }


            if(selectedItems().empty()) {
                QList<QGraphicsItem*> toSelectItemList = items(xmin, ymin, xmax-xmin, ymax-ymin);

                for(QList<QGraphicsItem*>::iterator it = toSelectItemList.begin(); it != toSelectItemList.end(); ++it) {
                    QGraphicsItem *qGraphicsItem = *it;

                    if(typeid(*qGraphicsItem) == typeid(ObjectGraphicsItem)) {
                        qGraphicsItem->setSelected(true);

                    }
                }
            }

            QList<QGraphicsItem*> selectedItemList = selectedItems();

            for(QList<QGraphicsItem*>::iterator it = selectedItemList.begin(); it != selectedItemList.end(); ++it) {
                QGraphicsItem *qGraphicsItem = *it;

                if(typeid(*qGraphicsItem) == typeid(ObjectGraphicsItem)) {
                    ObjectGraphicsItem *objGraphicsItem = (ObjectGraphicsItem*) qGraphicsItem;
                    objGraphicsItem->updateObjectInstancePosition();
                }
            }


            cleanColorizeSelectedItems();
            colorizeSelectedItems();
        }
    } else if(mapEditorController->editorMode == MapEditorController::MODE_EVENT) {
        if(event->button() == Qt::LeftButton) {
            QMenu menu;
            QAction *newTeleportAction = menu.addAction(tr("Novo teletransporte"));
            //QAction *newEventAction = menu.addAction(tr("Novo evento"));

            QAction *selectedAction = menu.exec(event->screenPos());

            /*if(selectedAction == newEventAction) {
                NewEventAreaDialog *newEventAreaDialog = new NewEventAreaDialog();
                newEventAreaDialog->setWindowTitle(QString("Novo evento"));
                newEventAreaDialog->exec();
            } else
            */if(selectedAction == newTeleportAction) {
                GameData *gameData = GameData::getInstance();
                TeleportArea *newTeleportArea;
                NewTeleportAreaDialog *newTeleportAreaDialog = new NewTeleportAreaDialog(mapEditorController);
                newTeleportAreaDialog->setWindowTitle(QString(tr("Novo teletransporte")));
                newTeleportArea = newTeleportAreaDialog->exec();

                delete newTeleportAreaDialog;

                if(newTeleportArea != NULL) {
                    float xmin = std::min(objectSelectionStartPosition.x(), objectSelectionEndPosition.x());
                    float ymin = std::min(objectSelectionStartPosition.y(), objectSelectionEndPosition.y());
                    float xmax = std::max(objectSelectionStartPosition.x(), objectSelectionEndPosition.x());
                    float ymax = std::max(objectSelectionStartPosition.y(), objectSelectionEndPosition.y());

                    newTeleportArea->x = xmin;
                    newTeleportArea->y = ymin;
                    newTeleportArea->w = xmax - xmin;
                    newTeleportArea->h = ymax - ymin;

                    if(newTeleportArea->w < 30) {
                        newTeleportArea->w = 30;
                    }

                    if(newTeleportArea->h < 30) {
                        newTeleportArea->h = 30;
                    }

                    gameData->editingMap->teleportAreas->push_back(newTeleportArea);

                    TeleportAreaGraphicsItem *teleportAreaGraphicsItem;
                    teleportAreaGraphicsItem = new TeleportAreaGraphicsItem(mapEditorController);
                    teleportAreaGraphicsItem->setRect(xmin, ymin, newTeleportArea->w, newTeleportArea->h);
                    teleportAreaGraphicsItem->setPen(QPen(QColor(0, 0, 255, 255)));
                    teleportAreaGraphicsItem->setBrush(QBrush(QColor(0, 0, 255, 30)));

                    addItem(teleportAreaGraphicsItem);

                    teleportAreaGraphicsItem->addLittleBoxAtTopLeftMarkToScene(this);

                    teleportAreaGraphicsItem->teleportArea = newTeleportArea;

                    teleportAreaGraphicsItems->push_back(teleportAreaGraphicsItem);
                }




            }

            if(objectSelectionShape != NULL) {
                objectSelectionShape->setVisible(false);
            }
        }

    } else if(mapEditorController->editorMode == MapEditorController::MODE_MAP) {
        switch(mapEditorController->drawMode) {
        case MapEditorController::DRAW_MODE_PAINT:
        case MapEditorController::DRAW_MODE_ERASER:
        case MapEditorController::DRAW_MODE_PENCIL:

            break;
        case MapEditorController::DRAW_MODE_SQUARE:
            if(event->button() == Qt::LeftButton) {
                squareCircleDrawEndPosition = event->scenePos();

                mapEditorController->changeTiles(squareCircleDrawStartPosition.x()/tileSize, squareCircleDrawStartPosition.y()/tileSize,
                                                 squareCircleDrawEndPosition.x()/tileSize, squareCircleDrawEndPosition.y()/tileSize);

                int i, j;
                i = floor(event->scenePos().x()/tileSize);
                j = floor(event->scenePos().y()/tileSize);

                if(i < 0) {
                    i = 0;
                }

                if(j < 0) {
                    j = 0;
                }

                setSelectionRectangleSize(0, 0);

                shape1->setPos(i*tileSize, j*tileSize);
                break;
            }


        }
    }




}

void TilemapScene::drawObjectSelectionRectangle() {
    float w, h, xmin, ymin;

    if(objectSelectionShape != NULL) {
        removeItem(objectSelectionShape);
    }

    w = (objectSelectionStartPosition.x() - objectSelectionEndPosition.x());
    h = (objectSelectionStartPosition.y() - objectSelectionEndPosition.y());

    xmin = (objectSelectionStartPosition.x());
    ymin = (objectSelectionStartPosition.y());


    if(w > 0) {
        xmin -= w;
    }

    if(h > 0) {
        ymin -= h;
    }


    w = fabs(w);
    h = fabs(h);

    objectSelectionShape = addRect(xmin, ymin, w, h, QPen(QColor(0, 30, 0, 255)), QBrush(QColor(0, 70, 0, 30)));
    objectSelectionShape->setZValue(50);

    if(selectedItems().empty()) {
        objectSelectionShape->setVisible(true);
    } else {
        objectSelectionShape->setVisible(false);
    }
}

void TilemapScene::changeTile(int i, int j, int tileI, int tileJ, int layer, TileSet* tileset) {
    mapGridVisual->changeTile(i, j, tileI, tileJ, layer, tileset);
}

void TilemapScene::wheelEvent(QGraphicsSceneWheelEvent *event) {
    update();
}

void TilemapScene::setSelectionRectangleSize(int di, int dj) {
    removeItem(shape1);
    removeItem(shape2);

    printf("di: %d\n", di);

    shape1 = addRect(3, 3, (di+1)*mapGridVisual->tileSize-6, (dj+1)*mapGridVisual->tileSize-6, QPen(QColor(255, 255, 255, 255)));
    shape2 = addRect(2, 2, (di+1)*mapGridVisual->tileSize-4, (dj+1)*mapGridVisual->tileSize-4, QPen());

    shape1->setOpacity(1);

    shape1->setZValue(30);
    shape2->setZValue(30);
}

void TilemapScene::setCurrentObjectAtCursor() {
    if(currentObjectItem != NULL) {
        this->removeItem(currentObjectItem);
        delete currentObjectItem;
    }

    if(mapEditorController->getSelectedObject() != NULL) {
        QPixmap *currentObjectImage;
        currentObjectImage = new QPixmap(QPixmap::fromImage(mapEditorController->getSelectedObject()->getIconImage()));
        currentObjectItem = new QGraphicsPixmapItem(*currentObjectImage);
        currentObjectItem->setOpacity(0.5);
        currentObjectItem->setPos(-1000, -1000);
        this->addItem(currentObjectItem);
    } else {
        currentObjectItem = NULL;
    }
}

void TilemapScene::setEditorMode(int mode) {
    if(mode == MapEditorController::MODE_MAP) {
        if(shape1 != NULL) {
            shape1->setVisible(false);
        }

        if(shape2 != NULL) {
            shape2->setVisible(false);
        }

        if(currentObjectItem != NULL) {
            currentObjectItem->setVisible(false);
        }
        //mapGridVisual->setOpacity(1.0f);

    } else if(mode == MapEditorController::MODE_OBJECT) {
        if(shape1 != NULL) {
            shape1->setVisible(false);
        }

        if(shape2 != NULL) {
            shape2->setVisible(false);
        }

        if(currentObjectItem != NULL) {
            currentObjectItem->setVisible(true);
        }
        //mapGridVisual->setOpacity(0.5f);
    }
}

void TilemapScene::cleanColorizeSelectedItems() {
    QList<QGraphicsItem*> itemList = items();

    for(QList<QGraphicsItem*>::iterator it = itemList.begin(); it != itemList.end(); ++it) {
        QGraphicsItem *qGraphicsItem = *it;

        if(typeid(*qGraphicsItem) == typeid(ObjectGraphicsItem)) {
            ObjectGraphicsItem *objGraphicsItem = (ObjectGraphicsItem*) qGraphicsItem;
            objGraphicsItem->setColorizeEffect(false);
        }
    }
}

void TilemapScene::colorizeSelectedItems() {
    QList<QGraphicsItem*> selectedItemList = selectedItems();

    for(QList<QGraphicsItem*>::iterator it = selectedItemList.begin(); it != selectedItemList.end(); ++it) {
        QGraphicsItem *qGraphicsItem = *it;

        if(typeid(*qGraphicsItem) == typeid(ObjectGraphicsItem)) {
            ObjectGraphicsItem *objGraphicsItem = (ObjectGraphicsItem*) qGraphicsItem;
            objGraphicsItem->setColorizeEffect(true);
        }
    }
}

void TilemapScene::setEditionLayer(int layer) {
    if(layer + 1 > mapGridVisual->getLayerCount()) {
        mapGridVisual->expandLayer();


    }

    layerRect->setZValue(layer*2 - 1);

}

void TilemapScene::setZoom(int zoom) {
    mapGridVisual->setZoom(zoom);
}
