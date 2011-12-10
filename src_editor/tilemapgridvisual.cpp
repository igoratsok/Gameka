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



#include "tilemapgridvisual.h"

TilemapGridVisual::TilemapGridVisual(QGraphicsScene *scene, QImage *image,
                                 int tileSize, int width, int height, int layers)
{


    this->image = image;
    this->tileSize = tileSize;
    this->scene = scene;
    this->layers = layers;

    this->width = width;
    this->height = height;
    int i, j;


    GameData *gameData = GameData::getInstance();

    tileMap.resize(boost::extents[width][height][layers]);

    for(i = 0; i < width; i++) {
        for(j = 0; j < height; j++) {
            for(int z = 0; z < layers; z++) {
                tileMap[i][j][z] = new TileItem(this, gameData->editingMap->map[i][j][z].x, gameData->editingMap->map[i][j][z].y);
                tileMap[i][j][z]->setPos(i*tileSize, j*tileSize);
                tileMap[i][j][z]->updateTileset(gameData->editingMap->map[i][j][z].z);
                tileMap[i][j][z]->setZValue(2*z);
            }
        }
    }

    addTilesToScene();

    linesGenerator = new TilesetLinesGenerator(scene, tileSize, width, height, Qt::DotLine);


}

void TilemapGridVisual::addTilesToScene() {
    int i, j, z;

    for(i = 0; i < width; i++)
        for(j = 0; j < height; j++)
            for(z = 0; z < layers; z++)
                scene->addItem(tileMap[i][j][z]);
}


void TilemapGridVisual::changeTile(int i, int j, int tileI, int tileJ, int layer, TileSet *tileset) {
    if(i >= 0 && j >= 0 && i < width && j < height) {
        if(tileI >= 0 && tileJ >= 0 && tileset != NULL) {
            tileMap[i][j][layer]->updateTile(tileI, tileJ, tileset);
        }


        if((tileI < 0 || tileJ < 0) && tileset == NULL) {
            tileMap[i][j][layer]->updateTile(tileI, tileJ, tileset);
        }
    }



}

bool TilemapGridVisual::isVisible() {
    return visible;
}

void TilemapGridVisual::setVisible(bool visibility) {
    int i, j;

    for(i = 0; i < width; i++) {
        for(j = 0; j < width; i++) {
            tileMap[i][j][0]->setVisible(visibility);
        }
    }

    visible = visibility;
}

void TilemapGridVisual::setOpacity(float opacity) {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            tileMap[i][j][0]->setOpacity(opacity);

        }
    }
}

int TilemapGridVisual::getLayerCount() {
    return layers;
}

void TilemapGridVisual::expandLayer() {
    GameData *gameData = GameData::getInstance();

    layers++;
    tileMap.resize(boost::extents[width][height][layers]);

    int z = layers - 1;
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            tileMap[i][j][z] = new TileItem(this, gameData->editingMap->map[i][j][z].x, gameData->editingMap->map[i][j][z].y);
            tileMap[i][j][z]->setPos(i*tileSize, j*tileSize);
            tileMap[i][j][z]->updateTileset(gameData->editingMap->map[i][j][z].z);
            tileMap[i][j][z]->setZValue(2*z);
            scene->addItem(tileMap[i][j][z]);
        }
    }

}

void TilemapGridVisual::setZoom(int zoom) {
    float scale = (float)(2.0f*zoom)/10.0f;

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            for(int z = 0; z < layers; z++) {
                tileMap[i][j][0]->setScale(scale);
                tileMap[i][j][z]->setPos(i*tileSize*scale, j*tileSize*scale);
            }
        }
    }
}
