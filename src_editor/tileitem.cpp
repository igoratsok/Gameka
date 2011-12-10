
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



#include "tileitem.h"

TileItem::TileItem(TilemapGridVisual *mapGridVisual, int i, int j)
{
    this->image = mapGridVisual->image;
    this->size = mapGridVisual->tileSize;
    this->i = i;
    this->j = j;
    this->visible = true;

    setRect(0, 0, size, size);


}

TileItem::TileItem(QImage *image, int size, int i, int j)
{
    this->image = image;
    this->size = size;
    this->i = i;
    this->j = j;
    this->visible = true;



    setRect(0, 0, size, size);
}

void TileItem::updateTileset(TileSet *tileset) {
    if(tileset != NULL)
        this->image = tileset->tilesetImage;
}

void TileItem::updateTile(int i, int j, TileSet *tileset)
{
    this->i = i;
    this->j = j;

    GameData *gameData = GameData::getInstance();


    if(tileset != NULL) {
        this->image = tileset->tilesetImage;
    } else {
        this->image = NULL;
    }


}

bool TileItem::isVisible() {
    return visible;
}

void TileItem::setVisible(bool visibility) {
    this->visible = visibility;
}

void TileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(i >= 0 && j >= 0 && visible)
        painter->drawImage(QRectF(0, 0, size, size), *image, QRectF(i*size,j*size, size, size), NULL);

}
