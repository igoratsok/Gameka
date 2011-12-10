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

#include "NpcMovementObject.h"

NpcMovementObject::NpcMovementObject()
	: AcceleratedParticle() {


	enemyPhysicalAttackCapable = true;
}

NpcMovementObject::NpcMovementObject(GameObjectInstance *gameObjectInstance)
	: AcceleratedParticle(gameObjectInstance) {
	movementType = gameObjectInstance->gameObject->formaMovimentacaoNpcItem;
	playerData = PlayerData::getInstance();

	movementAngle = 0;
	angularVelocity = gameObjectInstance->gameObject->vx/8000.0f;
	movementRadius = gameObjectInstance->gameObject->raioMovimentacao;

	maxVelocity.x = gameObjectInstance->gameObject->vx/250.0f;
	maxVelocity.y = maxVelocity.x;

	direction = 1;

	switch(movementType) {
	case MOVE_ESQUERDA_DIREITA:
		velocity->x = gameObjectInstance->gameObject->vx/250.0f;
		break;
	case MOVE_CIMA_BAIXO:
		velocity->y = gameObjectInstance->gameObject->vx/250.0f;
		break;
	}

	enemyPhysicalAttackCapable = true;





}

NpcMovementObject::~NpcMovementObject() {
	// TODO Auto-generated destructor stub
}

int NpcMovementObject::update(int dt) {

	if(AcceleratedParticle::update(dt) == -1) {
		return -1;
	}


	switch(movementType) {
	case PARADO:

		break;
	case SEGUE_PERSONAGEM:
		if(playerData->getPlayer() != NULL) {
			follow(*playerData->getPlayer()->position, dt);
		}

		break;
	case FOGE_PERSONAGEM:
		moveAway(*playerData->getPlayer()->position, dt);
		break;
	case MOVE_ESQUERDA_DIREITA:
		velocity->y = 0;
		//position->addScaledVector(velocity, dt);
		if(position->x > gameObjectInstance->x + movementRadius) {
			position->x = gameObjectInstance->x + movementRadius - 2;
			direction = -1;
			velocity->x = - gameObjectInstance->gameObject->vx/250.0f;
		} else if(position->x < gameObjectInstance->x - movementRadius) {
			position->x = gameObjectInstance->x - movementRadius + 1;
			direction = 1;
			velocity->x = + gameObjectInstance->gameObject->vx/250.0f;
		}

		break;
	case MOVE_CIMA_BAIXO:
		position->addScaledVector(velocity, dt);
		if(position->y > gameObjectInstance->y + movementRadius) {
			position->y = gameObjectInstance->y + movementRadius - 1;
			direction = -1;
			velocity->y = - gameObjectInstance->gameObject->vx/250.0f;
		} else if(position->y < gameObjectInstance->y - movementRadius) {
			position->y = gameObjectInstance->y - movementRadius + 1;
			direction = 1;
			velocity->y = + gameObjectInstance->gameObject->vx/250.0f;
		}

		break;
	case MOVIMENTO_CIRCULAR:
		movementAngle += angularVelocity*dt;
		if(movementAngle > 2*M_PI) {
			movementAngle = 0;
		}


		this->position->x = gameObjectInstance->x + sin(movementAngle)*movementRadius;
		this->position->y = gameObjectInstance->y + cos(movementAngle)*movementRadius;



		break;
	}

	if(!(velocity->y == 0 && velocity->x == 0)) {
		angle = atan((velocity->x/velocity->y));
		if(velocity->y < 0) {
			angle += M_PI;
		}
	}

	if(playerData->getPlayer() != NULL) {
		if(playerData->getPlayer()->collidesWith(this)){
			if(inputManager->isKeyPressed(SDLK_z) || inputManager->isKeyPressed(SDLK_SPACE)) {
				if(this->gameObjectInstance->dialogueData != NULL) {
					modalManager->pushModal(new DialogueText(this->gameObjectInstance->dialogueData, DialogueText::POS_DOWN, dt));
				}
			}
		}
	}

	setSpriteDirectionAngle((360 - (angle*180/M_PI + 270)));

	return 0;
}
