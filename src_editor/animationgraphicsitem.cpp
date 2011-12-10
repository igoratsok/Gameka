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


#include "animationgraphicsitem.h"

AnimationGraphicsItem::AnimationGraphicsItem(std::string fileName, int horizontalFrameNumber, int verticalFrameNumber, int order,
                                             int startX, int startY, int endX, int endY, int spacingX, int spacingY)
{
    GameData *gameData = GameData::getInstance();

    std::string directory =  gameData->getProjectDirectory().append("/").append(fileName);

    image = new QImage(QString(directory.c_str()));

    this->horizontalFrameNumber = horizontalFrameNumber;
    this->verticalFrameNumber = verticalFrameNumber;
    this->order = order;
    this->startX = startX;
    this->startY = startY;
    this->endX = endX;
    this->endY = endY;

    if(startX > horizontalFrameNumber) {
        startX = horizontalFrameNumber;
    }

    if(startY > verticalFrameNumber) {
        startY = verticalFrameNumber;
    }

    if(endX > horizontalFrameNumber) {
        endX = horizontalFrameNumber;
    }

    if(endY > verticalFrameNumber) {
        endY = verticalFrameNumber;
    }

    stepX = (image->width() - spacingX*(horizontalFrameNumber - 1))/horizontalFrameNumber + spacingX;
    stepY = (image->height() - spacingY*(verticalFrameNumber - 1))/verticalFrameNumber + spacingY;

    animX = startX - 1;
    animY = startY - 1;

    animationRect.setRect(0, 0, stepX, stepY);

    isAnimation = true;

    this->setRect(0, 0, stepX, stepY);


}

AnimationGraphicsItem::AnimationGraphicsItem(std::string fileName) {
    GameData *gameData = GameData::getInstance();

    std::string directory =  gameData->getProjectDirectory().append("/").append(fileName);

    image = new QImage(QString(directory.c_str()));

    isAnimation = false;

    this->setRect(0, 0, image->width(), image->height());
}

void AnimationGraphicsItem::doStep() {
    if(order == 0) {
        animX++;
        if(animX >= endX) {
            animX = startX - 1;
            animY++;
            if(animY >= endY) {
                animY = startY - 1;
            }
        }
    } else {
        animY++;
        if(animY > endY) {
            animY = startY - 1;
            animX++;
            if(animX > endX) {
                animX = startX - 1;
            }
        }
    }

    animationRect.setRect(animX*stepX, animY*stepY, stepX, stepY);

}


void AnimationGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(isAnimation) {
        painter->drawImage(QRectF(0, 0, stepX, stepY), *image, QRect(animX*stepX, animY*stepY, stepX, stepY), NULL);
    } else {
        painter->drawImage(QRectF(0, 0, image->width(), image->height()), *image, QRect(0, 0, image->width(), image->height()), NULL);
    }

}
