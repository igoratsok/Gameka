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

#include "VehicleMovement.h"

VehicleMovement::VehicleMovement() {
	angle = 180;
	angularVelocity = 0.03;
	inputManager = InputManager::getInstance();
	isCar = true;

	auxiliarMath = new AuxiliarMath();
	enemyPhysicalAttackCapable = true;

}

VehicleMovement::~VehicleMovement() {

}

VehicleMovement::VehicleMovement(std::string *fileName, commtypes::real x, commtypes::real y)
	: AcceleratedParticle(fileName, x, y) {
	angle = 0;
	angularVelocity = 0.003;
	isCar = true;




	inputManager = InputManager::getInstance();
	enemyPhysicalAttackCapable = true;
}

VehicleMovement::VehicleMovement(GameObjectInstance *gameObjectInstance)
	: AcceleratedParticle(gameObjectInstance) {
	angle = 0;
	isCar = false;

	accelerationValue.x = gameObjectInstance->gameObject->ax/5000.0f;
	desaccelerationValue.x = gameObjectInstance->gameObject->ax/5000.0f;
	angularVelocity = gameObjectInstance->gameObject->ay/5000.0f;

	maxVelocity.x = gameObjectInstance->gameObject->vx/37.5f;
	maxVelocity.y = gameObjectInstance->gameObject->vy/37.5f;

	inputManager = InputManager::getInstance();
	enemyPhysicalAttackCapable = true;

}

int VehicleMovement::update(int dt) {
	if(AcceleratedParticle::update(dt) == -1) {
		return -1;
	}

	if(inputManager->isKeyDown(SDLK_RIGHT) && (!isCar || velocity->y != 0 || velocity->x != 0)) {
		angle -= dt*angularVelocity;
	}
	if(inputManager->isKeyDown(SDLK_LEFT) && (!isCar || velocity->y != 0 || velocity->x != 0)) {
		angle += dt*angularVelocity;
	}

	acceleration->x = 0;
	acceleration->y = 0;

	// auxiliarMath->sin
	if(inputManager->isKeyDown(SDLK_DOWN)) {
		if(velocity->x >= -maxVelocity.x - sprintIntensity) {
			acceleration->x = -sin(angle)*accelerationValue.x;
		}

		if(velocity->x >= -maxVelocity.x - sprintIntensity) {
			acceleration->y = -cos(angle)*accelerationValue.x;
		}
	}
	if(inputManager->isKeyDown(SDLK_UP)) {
		if(velocity->x <= maxVelocity.x + sprintIntensity) {
			acceleration->x = sin(angle)*accelerationValue.x;
		}

		if(velocity->y <= maxVelocity.y + sprintIntensity) {
			acceleration->y = cos(angle)*accelerationValue.x;
		}


	}
	if(!inputManager->isKeyDown(SDLK_DOWN) && !inputManager->isKeyDown(SDLK_UP)) {
		if(velocity->x > 0)	acceleration->x = -desaccelerationValue.x;
		else if(velocity->x < 0) acceleration->x = +desaccelerationValue.x;
		if(velocity->y > 0) acceleration->y = -desaccelerationValue.x;
		else if(velocity->y < 0) acceleration->y = +desaccelerationValue.x;



		if(fabs(velocity->x) < desaccelerationValue.x*dt) {
			velocity->x = 0;
			acceleration->x = 0;
		}

		if(fabs(velocity->y) < desaccelerationValue.x*dt) {
			velocity->y = 0;
			acceleration->y = 0;
		}



	}


	setSpriteRotation(angle*180/M_PI + 180);


	return 0;

}
