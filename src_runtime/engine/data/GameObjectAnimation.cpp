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

#include "GameObjectAnimation.h"

GameObjectAnimation::GameObjectAnimation() :
		horizontalInvert(std::vector<bool>(36)),
		verticalInvert(std::vector<bool>(36)),
		adjustments(std::vector<Vector2>(36)) {

    sprites = new std::vector<SpriteRepresentation*>(36);
    animations = new std::vector<AnimationData*>(36);
    types = new std::vector<int>(36);

    for(int i = 0; i < 36; i++) {
		sprites->at(i) = new SpriteRepresentation();
		animations->at(i) = NULL;
		types->at(i) = 0;
		horizontalInvert.at(i) = false;
		verticalInvert.at(i) = false;
		adjustments.at(i) = Vector2();
	}

}

GameObjectAnimation::~GameObjectAnimation() {
	// TODO Auto-generated destructor stub
}
