
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



#include "tilesetcolmapscene.h"

TilesetColMapScene::TilesetColMapScene(TileSet *tileset, QObject *parent) :
    QGraphicsScene(parent),
    tileset(tileset)
{
    TilesetLinesGenerator *tilesetLinesGenerator = new TilesetLinesGenerator(this, tileset->tileSize,
                                                                             tileset->width, tileset->height,
                                                                             Qt::DotLine);
    tilesetLinesGenerator->addLinesToScene();



    QPixmap pixmap = QPixmap::fromImage(*tileset->getTilesetAlphaImage());

    if(tileset->hasColorKey) {
        QBitmap bitmap = pixmap.createMaskFromColor(QColor(tileset->colorkey_r, tileset->colorkey_g,
                                          tileset->colorkey_b));

        pixmap.setMask(bitmap);
    }


    tilesetPixmapItem= new QGraphicsPixmapItem(pixmap, 0, this);


    this->addItem(tilesetPixmapItem);



    setBackgroundBrush(QBrush(QColor(255, 255, 255, 255)));
    setSceneRect(0, 0, pixmap.width(), pixmap.height());




    textArray.resize(boost::extents[tileset->width][tileset->height]);

    int i, j;
    for(i = 0; i < tileset->width; i++) {
        for(j = 0; j < tileset->height; j++) {
            QGraphicsDropShadowEffect *qgdse = new QGraphicsDropShadowEffect(0);
            qgdse->setColor(QColor(0, 0, 0));
            qgdse->setOffset(1);

            textArray[i][j] = new QGraphicsTextItem(0, this);
            textArray[i][j]->setPos(i*tileset->tileSize, j*tileset->tileSize);
            if(tileset->collisionMatrix[i][j] == NO_COLLISION) {
                textArray[i][j]->setHtml("<strong>O</strong>");
            } else {
                textArray[i][j]->setHtml("<strong>X</strong>");
            }

            textArray[i][j]->setDefaultTextColor(QColor(255, 255, 255, 255));
            textArray[i][j]->setGraphicsEffect(qgdse);
            this->addItem(textArray[i][j]);
        }
    }



}

void TilesetColMapScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    int i, j;
    i = floor(event->scenePos().x()/tileset->tileSize);
    j = floor(event->scenePos().y()/tileset->tileSize);

    if(i >= 0 && i < tileset->maxX && j >= 0 && j < tileset->maxY) {
        tileset->collisionMatrix[i][j] = !tileset->collisionMatrix[i][j];

        if(tileset->collisionMatrix[i][j] == NO_COLLISION) {
            textArray[i][j]->setHtml("<strong>O</strong>");
        } else {
            textArray[i][j]->setHtml("<strong>X</strong>");
        }
    }


}

void TilesetColMapScene::invert() {
    for(int i = 0; i < tileset->maxX; i++) {
        for(int j = 0; j < tileset->maxY; j++) {
            tileset->collisionMatrix[i][j] = !tileset->collisionMatrix[i][j];


            if(tileset->collisionMatrix[i][j] == NO_COLLISION) {
                textArray[i][j]->setHtml("<strong>O</strong>");
            } else {
                textArray[i][j]->setHtml("<strong>X</strong>");
            }
        }
    }
}

void TilesetColMapScene::allO() {
    for(int i = 0; i < tileset->maxX; i++) {
        for(int j = 0; j < tileset->maxY; j++) {
            tileset->collisionMatrix[i][j] = NO_COLLISION;


            textArray[i][j]->setHtml("<strong>O</strong>");

        }
    }
}

void TilesetColMapScene::allX() {
    for(int i = 0; i < tileset->maxX; i++) {
        for(int j = 0; j < tileset->maxY; j++) {
            tileset->collisionMatrix[i][j] = !NO_COLLISION;


            textArray[i][j]->setHtml("<strong>X</strong>");

        }
    }
}
