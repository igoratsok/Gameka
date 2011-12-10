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


#include "animationgraphicsscene.h"

AnimationGraphicsScene::AnimationGraphicsScene(QGraphicsView *graphicsView)
{
    animationGraphicsItem = NULL;
    this->graphicsView = graphicsView;
    graphicsView->setBackgroundBrush(QBrush(QColor(255 , 255, 255, 255)));
    timerId = -1;

    QImage background = QImage(20, 20, QImage::Format_RGB32);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            background.setPixel(i, j, QColor(255, 255, 255, 255).rgb());
            background.setPixel(i + 10, j + 10, QColor(255, 255, 255, 255).rgb()) ;

            background.setPixel(i, j + 10, QColor(180, 180, 180, 255).rgb());
            background.setPixel(i + 10, j, QColor(180, 180, 180, 255).rgb());
        }
    }

    QBrush brush = QBrush(Qt::TexturePattern);
    brush.setTexture(QPixmap::fromImage(background));

    graphicsView->setBackgroundBrush(brush);
    setBackgroundBrush(brush);

    crossLine1 = NULL;
    crossLine2 = NULL;
}

AnimationGraphicsScene::~AnimationGraphicsScene() {
    if(timerId >= 0) {
        killTimer(timerId);
    }
}

void AnimationGraphicsScene::addAnimationData(AnimationData *animationData) {
    if(animationGraphicsItem != NULL) {
        removeItem(animationGraphicsItem);

        delete animationGraphicsItem;
    }

    animationGraphicsItem = new AnimationGraphicsItem(animationData->fileName, animationData->getHorizontalFrameNumber(),
                                                      animationData->getVerticalFrameNumber(), animationData->order,
                                                      animationData->startX, animationData->startY,
                                                      animationData->endX, animationData->endY,
                                                      animationData->horizontalSpacing, animationData->verticalSpacing);

    animationGraphicsItem->setFlag(QGraphicsItem::ItemIsMovable);
    animationGraphicsItem->setFlag(QGraphicsItem::ItemIsSelectable);


    addItem(animationGraphicsItem);

    if(timerId >= 0) {
        killTimer(timerId);
        timerId = -1;
    }

    int animationFrames = (100 - animationData->velocity);


    timerId = startTimer(animationFrames*4);
}

void AnimationGraphicsScene::addSpriteData(std::string sprite) {

    if(animationGraphicsItem != NULL) {
        removeItem(animationGraphicsItem);

        delete animationGraphicsItem;
    }

    animationGraphicsItem = new AnimationGraphicsItem(sprite);

    animationGraphicsItem->setFlag(QGraphicsItem::ItemIsMovable);
    animationGraphicsItem->setFlag(QGraphicsItem::ItemIsSelectable);


    addItem(animationGraphicsItem);

    if(timerId >= 0) {
        killTimer(timerId);
        timerId = -1;
    }

}

void AnimationGraphicsScene::removeGraphics() {
    if(animationGraphicsItem != NULL) {
        removeItem(animationGraphicsItem);

        delete animationGraphicsItem;

        animationGraphicsItem = NULL;

        update();
        graphicsView->update();



        if(timerId >= 0) {
            killTimer(timerId);
            timerId = -1;
        }

    }
}

void AnimationGraphicsScene::timerEvent(QTimerEvent *) {
    if(animationGraphicsItem != NULL) {
        animationGraphicsItem->doStep();

        animationGraphicsItem->update();
        update();
        graphicsView->update();
    }


}

void AnimationGraphicsScene::setAdjustPoint(int x, int y) {
    if(crossLine1 != NULL) {
        removeItem(crossLine1);
        delete crossLine1;

        crossLine1 = NULL;
    }

    if(crossLine2 != NULL) {
        removeItem(crossLine2);
        delete crossLine2;

        crossLine2 = NULL;
    }

    crossLine1 = addLine(x - 2, y, x + 2, y, QPen(QColor(0, 0, 0, 255)));
    crossLine2 = addLine(x, y - 2, x, y + 2, QPen(QColor(0, 0, 0, 255)));
}


