
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



#include "tilesetgridvisual.h"

TilesetGridVisual::TilesetGridVisual(QGraphicsScene *scene, QImage *image, int tileSize)
{
    this->image = image;
    this->tileSize = tileSize;
    this->scene = scene;
    int i, j, k;
    int maxX, maxY;

    maxX = floor(image->width()/tileSize);
    maxY = floor(image->height()/tileSize);

    height = maxY;
    width = maxX;



    tileArray.resize(boost::extents[width][height]);

    k = 0;
    for(j = 0; j < height; j++)
        for(i = 0; i < width; i++) {
            printf("%d, %d\n", i, j);
            tileArray[i][j] = new TileItem(image, tileSize, i, j);
            tileArray[i][j]->setPos((k%width)*tileSize, (floor(k/width))*tileSize);
            scene->addItem(tileArray[i][j]);
            k++;
    }
    
    

    linesGenerator = new TilesetLinesGenerator(scene, tileSize, width, height, Qt::DotLine);




}
