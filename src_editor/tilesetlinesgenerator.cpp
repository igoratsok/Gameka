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



#include "tilesetlinesgenerator.h"

TilesetLinesGenerator::TilesetLinesGenerator(QGraphicsScene *scene, int size, int width, int height, Qt::PenStyle penStyle)
{
    int i;
    this->scene = scene;
    this->width = width;
    this->height = height;

    lines = (QGraphicsLineItem**)calloc(width + height + 2, sizeof(QGraphicsLineItem*));
    for(i = 0; i <= height; i++) {
        lines[i] = new QGraphicsLineItem(0, i*size, width*size, i*size);
        lines[i]->setZValue(15);
        lines[i]->setPen(QPen(penStyle));
    }

    for(i = 0; i <= width; i++) {
        lines[i+height+1] = new QGraphicsLineItem(i*size, 0, i*size, height*size);
        lines[i+height+1]->setZValue(15);
        lines[i+height+1]->setPen(QPen(penStyle));
    }


    addLinesToScene();
}

void TilesetLinesGenerator::addLinesToScene()
{
    int i;
    for(i = 0; i < width + height + 2; i++) {
        scene->addItem(lines[i]);
    }
}
