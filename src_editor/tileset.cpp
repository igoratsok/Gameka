
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



#include "tileset.h"

TileSet::TileSet() {
    hasColorKey = false;
    tilesetImage = NULL;
}

TileSet::TileSet(std::string file, int tileSize)
{


    /* determina os valores dos atributos */
    this->file = file;
    this->tileSize = tileSize;
    this->name = file;
    hasColorKey = false;


    calculateCollisionMatrix();
    tilesetImage = NULL;

}

void TileSet::calculateCollisionMatrix() {
    int i, j;
    GameData *gameData = GameData::getInstance();

    /* abre a imagem pra ver a largura/altura */
    reloadTilesetImage();

    maxX = floor(tilesetImage->width()/tileSize);
    maxY = floor(tilesetImage->height()/tileSize);


    height = maxY;
    width = maxX;

    //height = floor((maxY*maxX)/8);
    //width = 8;



    /* inicializa a tabela de colisoes */
    collisionMatrix.resize(boost::extents[maxX][maxY]);

    for(i = 0; i < maxX; i++)
        for(j = 0; j < maxY; j++) {
            collisionMatrix[i][j] = NO_COLLISION;
    }

}

void TileSet::reloadTilesetImage() {
    GameData *gameData = GameData::getInstance();

    printf("ProjectDirectory: %s\n", gameData->getProjectDirectory().c_str());

    printf("t:: %s\n", gameData->getProjectDirectory().append("/").append(file).c_str());

    tilesetImage = getTilesetAlphaImage(true);


}

QImage* TileSet::getTilesetAlphaImage(bool reset) {
    GameData *gameData = GameData::getInstance();

    if(tilesetImage == NULL || reset) {
        tilesetImage = new QImage(gameData->getProjectDirectory().append("/").append(file).c_str());


        if(hasColorKey) {
            QImage mask = tilesetImage->createMaskFromColor(QColor(colorkey_r, colorkey_g, colorkey_b).rgb());
            mask.invertPixels();
            tilesetImage->setAlphaChannel(mask);

        }

    }



    return tilesetImage;
}

void TileSet::setCollision(int tileI, int tileJ, int collisionType) {
    collisionMatrix[tileI][tileJ] = collisionType;
}
