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

#include "MouseFollowMovement.h"

MouseFollowMovement::MouseFollowMovement(int mouseMovementType)
	: AcceleratedParticle(),
	  mouseMovementType(mouseMovementType){
	inputManager = InputManager::getInstance();
	followPoint = NULL;

	enemyPhysicalAttackCapable = true;

}

MouseFollowMovement::~MouseFollowMovement()  {
	// TODO Auto-generated destructor stub
}

MouseFollowMovement::MouseFollowMovement(std::string *fileName, commtypes::real x, commtypes::real y, int mouseMovementType)
	: AcceleratedParticle(fileName, x, y),
	  mouseMovementType(mouseMovementType) {
	inputManager = InputManager::getInstance();
	followPoint = NULL;

	enemyPhysicalAttackCapable = true;

}

MouseFollowMovement::MouseFollowMovement(GameObjectInstance *gameObjectInstance)
	: AcceleratedParticle(gameObjectInstance),
	  mouseMovementType(gameObjectInstance->gameObject->formaMovimentoMouse){
	inputManager = InputManager::getInstance();
	followPoint = NULL;

	maxVelocity.y = gameObjectInstance->gameObject->vy/37.5f;
	maxVelocity.x = gameObjectInstance->gameObject->vx/37.5f;
	accelerationValue.x = gameObjectInstance->gameObject->ax/5000.0f;
	accelerationValue.y = gameObjectInstance->gameObject->ay/5000.0f;
	desaccelerationValue.x = gameObjectInstance->gameObject->dax/5000.0f;
	desaccelerationValue.y = gameObjectInstance->gameObject->day/5000.0f;

	enemyPhysicalAttackCapable = true;

}

int MouseFollowMovement::update(int dt) {
	if(AcceleratedParticle::update(dt) == -1) {
		return -1;
	}

	Vector2 mousePos = inputManager->getScenarioMousePosition();

	switch(mouseMovementType) {
	case 0:
		setPositionByCenter(mousePos);

		break;
	case 1:
		if(inputManager->isMouseDown(1)) {
			setPositionByCenter(mousePos);
		}

		break;

	case 2:
		follow(mousePos, dt);

		break;

	case 3:
		if(inputManager->isMouseDown(1)) {
			if(followPoint == NULL) {
				followPoint = new Vector2();
			}

			followPoint->x = mousePos.x;
			followPoint->y = mousePos.y;


		}

		if(followPoint != NULL) {
			follow(*followPoint, dt);
		}

		break;

	case 4:

		break;

	case 5:

		break;

	}

	return 0;
}
