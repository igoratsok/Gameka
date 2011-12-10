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

#include "EightMovementObject.h"

EightMovementObject::EightMovementObject() : AcceleratedParticle() {

	inputManager->getInstance();
	angle = 0;
	automaticRotation = false;

	enemyPhysicalAttackCapable = true;
}

EightMovementObject::EightMovementObject(std::string *fileName, commtypes::real x, commtypes::real y)
	: AcceleratedParticle(fileName, x, y) {
	inputManager = InputManager::getInstance();
	angle = 0;
	automaticRotation = false;

	enemyPhysicalAttackCapable = true;

}

EightMovementObject::EightMovementObject(GameObjectInstance *gameObjectInstance)
	: AcceleratedParticle(gameObjectInstance) {
	inputManager = InputManager::getInstance();
	angle = 0;
	automaticRotation = false;

	maxVelocity.y = gameObjectInstance->gameObject->vy/37.5f;
	maxVelocity.x = gameObjectInstance->gameObject->vx/37.5f;
	accelerationValue.x = gameObjectInstance->gameObject->ax/5000.0f;
	accelerationValue.y = gameObjectInstance->gameObject->ay/5000.0f;
	desaccelerationValue.x = gameObjectInstance->gameObject->dax/5000.0f;
	desaccelerationValue.y = gameObjectInstance->gameObject->day/5000.0f;

	drawShadow = true;

	enemyPhysicalAttackCapable = true;


}

EightMovementObject::~EightMovementObject() {
	// TODO Auto-generated destructor stub
}

int EightMovementObject::update(int dt) {
	if(AcceleratedParticle::update(dt) == -1) {
		return -1;
	}





	if(position->z < 0) {
		sprite->setAnimation(3);
	} else {
		if(velocity->x == 0 && velocity->y == 0) {
			sprite->setAnimation(0);
		} else {
			sprite->setAnimation(1);
		}
	}

	acceleration->x = 0;
	acceleration->y = 0;


	if(inputManager->isKeyDown(SDLK_RIGHT) && velocity->x <= maxVelocity.x + sprintIntensity) {
		acceleration->x = accelerationValue.x;
	}


	if(inputManager->isKeyDown(SDLK_LEFT) && velocity->x >= -maxVelocity.x - sprintIntensity)
		acceleration->x = -accelerationValue.x;
	if(inputManager->isKeyDown(SDLK_UP) && velocity->y >= -maxVelocity.y - sprintIntensity)
		acceleration->y = -accelerationValue.y;
	if(inputManager->isKeyDown(SDLK_DOWN) && velocity->y <= maxVelocity.y + sprintIntensity)
		acceleration->y = accelerationValue.y;

	if(!inputManager->isKeyDown(SDLK_RIGHT)) {
		if(velocity->x > 0) {
			if(velocity->x <= dt*desaccelerationValue.x) {
				acceleration->x = 0;
				velocity->x = 0;
			} else {
				acceleration->x = -desaccelerationValue.x;
			}
		}

	}

	if(!inputManager->isKeyDown(SDLK_LEFT)) {
		if(velocity->x < 0) {
			if(-velocity->x <= dt*desaccelerationValue.x) {
				acceleration->x = 0;
				velocity->x = 0;
			} else {
				acceleration->x = +desaccelerationValue.x;
			}
		}

	}

	if(!inputManager->isKeyDown(SDLK_DOWN)) {
		if(velocity->y > 0) {
			if(velocity->y <= dt*desaccelerationValue.y) {
				acceleration->y = 0;
				velocity->y = 0;
			} else {
				acceleration->y = -desaccelerationValue.y;
			}
		}

	}

	if(!inputManager->isKeyDown(SDLK_UP)) {
		if(velocity->y < 0) {
			if(-velocity->y <= dt*desaccelerationValue.y) {
				acceleration->y = 0;
				velocity->y = 0;
			} else {
				acceleration->y = +desaccelerationValue.y;
			}
		}

	}



	if(!(velocity->y == 0 && velocity->x == 0)) {
		angle = atan((velocity->x/velocity->y));
		if(velocity->y < 0) {
			angle += M_PI;
		}
	}

	setSpriteDirectionAngle((360 - (angle*180/M_PI + 270)));



	if(automaticRotation) {
		setSpriteRotation(angle*180/M_PI + 180);
	}

	/*
	acceleration->y = 0.002f;

	if(inputManager->isKeyPressed(SDLK_z)) {
		velocity->y = - 5.0f;
	}
	*/


	return 0;


}

void EightMovementObject::setAutomaticRotation(bool value) {
	automaticRotation = value;
}




