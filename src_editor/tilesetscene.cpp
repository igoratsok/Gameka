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



#include "tilesetscene.h"

TilesetScene::TilesetScene(TilesetDock *tilesetDock, TileSet *tileSet)
{
    GameData *gameData = GameData::getInstance();

    this->tileSet = tileSet;


    tileSize = tileSet->tileSize;
    this->tilesetDock = tilesetDock;
    gridVisual = new TilesetGridVisual(this, tileSet->getTilesetAlphaImage(), tileSize);

    shape1 = addRect(3, 3, tileSize-6, tileSize-6, QPen(QColor(255, 255, 255, 255)));
    shape2 = addRect(2, 2, tileSize-4, tileSize-4, QPen());

    shape3 = addRect(3, 3, tileSize-6, tileSize-6, QPen(QColor(255, 0, 0, 255)));
    shape4 = addRect(2, 2, tileSize-4, tileSize-4, QPen());

    shape1->setOpacity(1);

    shape1->setZValue(10);
    shape2->setZValue(10);

    shape3->setOpacity(1);

    shape3->setZValue(10);
    shape4->setZValue(10);

    mousePressed = false;


}

void TilesetScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int i, j, diff_i, diff_j, iStart, jStart;

    if(!mousePressed) {
        shape1->setPos(floor(event->scenePos().x()/tileSize)*tileSize, floor(event->scenePos().y()/tileSize)*tileSize);
        shape2->setPos(shape1->pos());
    } else {
        shape1->setPos(floor(event->scenePos().x()/tileSize)*tileSize, floor(event->scenePos().y()/tileSize)*tileSize);
        shape2->setPos(shape1->pos());
        removeItem(shape1);
        removeItem(shape2);
        removeItem(shape3);
        removeItem(shape4);

        i = floor(event->scenePos().x()/tileSize);
        j = floor(event->scenePos().y()/tileSize);

        if(i < 0) i = 0;
        if(j < 0) j = 0;
        
        if(i > (gridVisual->width-1)) {
            i = gridVisual->width-1;
        }
        if(j > (gridVisual->height-1)) {
            j = gridVisual->height-1;
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


        shape1 = addRect(3, 3, (abs(diff_i) + 1)*tileSize-6, (abs(diff_j) + 1)*tileSize-6, QPen(QColor(255, 255, 255, 255)));
        shape2 = addRect(2, 2, (abs(diff_i) + 1)*tileSize-4, (abs(diff_j) + 1)*tileSize-4, QPen());
        shape3 = addRect(3, 3, (abs(diff_i) + 1)*tileSize-6, (abs(diff_j) + 1)*tileSize-6, QPen(QColor(255, 0, 0, 255)));
        shape4 = addRect(2, 2, (abs(diff_i) + 1)*tileSize-4, (abs(diff_j) + 1)*tileSize-4, QPen());



        shape1->setPos(iStart*tileSize, jStart*tileSize);
        shape2->setPos(iStart*tileSize, jStart*tileSize);
        shape3->setPos(iStart*tileSize, jStart*tileSize);
        shape4->setPos(iStart*tileSize, jStart*tileSize);



        update();
    }
    
}

void TilesetScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    int i, j;
    mousePressed = true;

    tilesetDock->setEditorMode(MapEditorController::MODE_MAP);

    i = floor(event->scenePos().x()/tileSize);
    j = floor(event->scenePos().y()/tileSize);

    if(i < 0) i = 0;
    if(j < 0) j = 0;

    if(i > (gridVisual->width-1)) {
        i = gridVisual->width-1;
    }
    if(j > (gridVisual->height-1)) {
        j = gridVisual->height-1;
    }


    iAnt = i;
    jAnt = j;

    iInicial = i;
    jInicial = j;

    tilesetDock->setDrawTile(i, j, 0, 0);

    removeItem(shape3);
    removeItem(shape4);

    shape3 = addRect(3, 3, (i - iInicial + 1)*tileSize-6, (j - jInicial + 1)*tileSize-6, QPen(QColor(255, 0, 0, 255)));
    shape4 = addRect(2, 2, (i - iInicial + 1)*tileSize-4, (j - jInicial + 1)*tileSize-4, QPen());

    shape3->setPos(i*tileSize, j*tileSize);
    shape4->setPos(shape1->pos());

    update();


}

void TilesetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    int i, j, di, dj;

    int iStart, jStart;

    mousePressed = false;

    i = floor(event->scenePos().x()/tileSize);
    j = floor(event->scenePos().y()/tileSize);

    if (i < 0) i = 0;
    if (j < 0) j = 0;

    if(i > (gridVisual->width-1)) {
        i = gridVisual->width-1;
    }
    if(j > (gridVisual->height-1)) {
        j = gridVisual->height-1;
    }

    if(i != iAnt || j != jAnt) {
        di = i - iAnt;
        dj = j - jAnt;

        if(di < 0) {
            iStart = iAnt + di;
        } else {
            iStart = iAnt;
        }

        if(dj < 0) {
            jStart = jAnt + dj;
        } else {
            jStart = jAnt;
        }


        tilesetDock->setDrawTile(iStart, jStart, abs(di), abs(dj));
    }

    /* reestabelecendo os shapes 1 e 2 */

    removeItem(shape1);
    removeItem(shape2);

    shape1 = addRect(3, 3, tileSize-6, tileSize-6, QPen(QColor(255, 255, 255, 255)));
    shape2 = addRect(2, 2, tileSize-4, tileSize-4, QPen());
}
