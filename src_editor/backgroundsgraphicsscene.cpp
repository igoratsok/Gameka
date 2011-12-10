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


#include "backgroundsgraphicsscene.h"

BackgroundsGraphicsScene::BackgroundsGraphicsScene()
{
    background = NULL;
}

void BackgroundsGraphicsScene::setBackground(Background *background) {
    GameData *gameData = GameData::getInstance();
    this->background = background;


    if(background != NULL) {
        for(std::vector<QGraphicsPixmapItem*>::iterator it = pixmapItems.begin(); it != pixmapItems.end(); ++it) {
            QGraphicsPixmapItem *graphisPixmapItem = *it;
            delete graphisPixmapItem;
        }

        pixmapItems.clear();

        for(std::vector<BgLayer*>::iterator it = background->layerList->begin(); it != background->layerList->end(); ++it) {
           BgLayer *bgLayer = *it;

           std::cout << "pixmapitem dir: " << gameData->getProjectDirectory().append("/").append(bgLayer->fileName).c_str() << std::endl;

           QGraphicsPixmapItem *graphicsPixmapItem = new QGraphicsPixmapItem(QPixmap(QString(gameData->getProjectDirectory().append("/").append(bgLayer->fileName).c_str())));
           pixmapItems.push_back(graphicsPixmapItem);

           graphicsPixmapItem->setPos(bgLayer->displacementX, bgLayer->displacementY);

           addItem(graphicsPixmapItem);
       }

        this->update();
    }



}

void BackgroundsGraphicsScene::reloadBackground() {
    setBackground(background);
}
