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


#include "animationdata.h"


AnimationData::AnimationData()
{
    horizontalFrameNumber = 1;
    verticalFrameNumber = 1;
    horizontalSpacing = 0;
    verticalSpacing = 0;
    order = 0;
    velocity = 50;
    hasLoop = true;
    frameLoop = 0;

    hasColorkey = false;
    colorkey_b = 0;
    colorkey_g = 0;
    colorkey_r = 0;

    activated = false;

    startX = 1;
    startY = 1;
    endX = 1;
    endY = 1;
}


void AnimationData::setHorizontalFrameNumber(int number) {
    horizontalFrameNumber = number;
    endX = horizontalFrameNumber;
}



void AnimationData::setVerticalFrameNumber(int number) {
    verticalFrameNumber = number;
    endY = verticalFrameNumber;
}


int AnimationData::getHorizontalFrameNumber() {
    return horizontalFrameNumber;
}

int AnimationData::getVerticalFrameNumber() {
    return verticalFrameNumber;
}


QImage AnimationData::getIconImage() {
    GameData *gameData = GameData::getInstance();
    std::string directory;

    directory = gameData->getProjectDirectory().append("/").append(this->fileName);

    QImage image = QImage(QString(directory.c_str()));

    int stepX, stepY;
    stepX = image.width()/this->getHorizontalFrameNumber();
    stepY = image.height()/this->getVerticalFrameNumber();



    QImage image2 = image.copy((this->startX - 1)*stepX, (this->startY - 1)*stepY, stepX, stepY);

    return image2;
}
