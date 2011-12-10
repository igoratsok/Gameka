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

#include "PlatformerMovement.h"

PlatformerMovement::PlatformerMovement(std::string *fileName, commtypes::real x, commtypes::real y) :
	AcceleratedParticle(fileName, x, y) {
		inputManager = InputManager::getInstance();
		angle = 0;
		automaticRotation = false;
		jumpIntensity = 0.8f;
		gravity = 0.002f;
		maxVelocity.y = 999.9f;
		doubleJumping = false;


		enemyPhysicalAttackCapable = true;

}

PlatformerMovement::PlatformerMovement(GameObjectInstance *gameObjectInstance)
	: AcceleratedParticle(gameObjectInstance) {

	inputManager = InputManager::getInstance();
	angle = 0;
	automaticRotation = false;
	jumpIntensity = gameObjectInstance->gameObject->intensidadePulo/29.0f;
	gravity = gameObjectInstance->gameObject->gravidade/5000.0f;
	initialGravity = gravity;
	maxVelocity.y = 999.9f;
	maxVelocity.x = gameObjectInstance->gameObject->vx/37.5f;
	accelerationValue.x = gameObjectInstance->gameObject->ax/5000.0f;
	desaccelerationValue.x = gameObjectInstance->gameObject->dax/5000.0f;

	doubleJumping = false;
	enemyPhysicalAttackCapable = true;

}

PlatformerMovement::~PlatformerMovement() {
	// TODO Auto-generated destructor stub
}


int PlatformerMovement::update(int dt) {
	if(AcceleratedParticle::update(dt) == -1) {
		return -1;
	}



	if(glideIntensity == 0 && flightIntensity == 0) {
		acceleration->y = gravity;
	} else {
		if(flightIntensity == 0) {
			acceleration->y = 0;
			velocity->y = glideIntensity;
		} else {
			acceleration->y = 0;
			velocity->y = - flightIntensity;
		}

	}




	if(autoCollision && tilemap != NULL && sprite != NULL) {
		Tile *tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, this->position->x + sprite->getRectWithoutRot()->w/2, this->position->y + sprite->getRectWithoutRot()->h + 3);
		Tile *tileEsq = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, this->position->x + 1, this->position->y + sprite->getRectWithoutRot()->h + 3);
		Tile *tileDir = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, this->position->x + sprite->getRectWithoutRot()->w - 1, this->position->y + sprite->getRectWithoutRot()->h + 3);

		if(tile || tileEsq || tileDir) {
			doubleJumping = false;
		}


		if(velocity->y != 0 && !(tile || tileEsq || tileDir)) {
			if(velocity->y <= 0) {
				estadoObjeto = ESTADO_PULANDO;
			} else {
				estadoObjeto = ESTADO_CAINDO;
			}

		} else {
			if(velocity->x != 0) {
				estadoObjeto = ESTADO_ANDANDO;
				if(velocity->x > 1.0f) {
					estadoObjeto = ESTADO_CORRENDO;
				}

			} else {
				estadoObjeto = ESTADO_PARADO;

			}
		}

		sprite->setAnimation(estadoObjeto);

		if(inputManager->isKeyPressed(SDLK_z) &&
					(tile || tileEsq || tileDir)) {
			playSpecialSound();
			velocity->y = -jumpIntensity;
			doubleJumping = false;
		}
	}



	if(gameObjectInstance->gameObject->tipoMovimento == 0) {
		if(inputManager->isKeyDown(SDLK_RIGHT)) {
			velocity->x = maxVelocity.x + sprintIntensity;
			sprite->setDirectionAngleDegrees(0);
		} else if(inputManager->isKeyDown(SDLK_LEFT)) {
			velocity->x = -maxVelocity.x - sprintIntensity;
			sprite->setDirectionAngleDegrees(180);
		} else {
			velocity->x = 0;
		}




	} else {
		acceleration->x = 0;

		if(inputManager->isKeyDown(SDLK_RIGHT) && velocity->x <= maxVelocity.x + sprintIntensity) {
			acceleration->x = accelerationValue.x;
			sprite->setDirectionAngleDegrees(0);
		}

		if(inputManager->isKeyDown(SDLK_LEFT) && velocity->x >= -maxVelocity.x - sprintIntensity) {
			acceleration->x = -accelerationValue.x;
			sprite->setDirectionAngleDegrees(180);
		}

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
	}



	if(position->z != 0) {
		position->z = 0;
	}

	Rect *thisRect = sprite->getRectWithoutRot();

	// verifica colisão de pulo por cima com inimigos
	if(getObjectList() != NULL) {
		std::list<GameObject*> *spatialList = spatialHashmap->getNearby(this);
		for(std::list<GameObject*>::iterator it = spatialList->begin(); it != spatialList->end(); ++it) {
			GameObject* gameObject = *it;

			if(gameObject->gameObjectInstance->gameObject->type == GameObjectClass::INIMIGO &&
					gameObject->gameObjectInstance->gameObject->derrotaPulandoSobreInimigo) {
				Rect *objectRect = gameObject->sprite->getRectWithoutRot();



				int distanciaVerificacaoY = this->velocity->y*dt + 1;
				int distanciaVerificacaoX = this->velocity->x*dt + 1;

				// TODO: ajustar o valor do 3 para a velocidade do objeto
				if(objectRect->contains(Vector2(this->position->x + objectRect->w/2 + distanciaVerificacaoX, this->position->y + objectRect->h + distanciaVerificacaoY)) ||
						objectRect->contains(Vector2(this->position->x + distanciaVerificacaoX, this->position->y + objectRect->h + distanciaVerificacaoY)) ||
						objectRect->contains(Vector2(this->position->x + objectRect->w + distanciaVerificacaoX, this->position->y + objectRect->h + distanciaVerificacaoY))) {
					this->velocity->y = -jumpIntensity/1.5f;
					gameObject->addDamage(this);
					gameObject->setNoAttackTimer(300);
				}

				if(gameObject->hp <= 0) {
					this->addExp(gameObject->gameObjectInstance->gameObject->experiencePoints);
					PlayerData::getInstance()->addPoints(gameObject->gameObjectInstance->gameObject->defeatPoints);
				}



				delete objectRect;
			}

		}
	}

	delete thisRect;











	return 0;
}

void PlatformerMovement::doubleJump(SkillData *skillData, int intensity, int magicCost) {
	if(autoCollision && tilemap != NULL && sprite != NULL) {
		Tile *tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, this->position->x + sprite->getRectWithoutRot()->w/2, this->position->y + sprite->getRectWithoutRot()->h + 3);


		if(!tile) {
			if(inputManager->isKeyPressed(SDLK_z) && !doubleJumping) {
				skillData->playSound();
				doubleJumping = true;
				float jumpRealIntensity = (float)intensity/29.0f;

				velocity->y = - jumpRealIntensity;
				addMp(-magicCost);
			}


		}
	}
}

void PlatformerMovement::wallKick(SkillData *skillData, int intensity, int magicCost) {
	if(autoCollision && tilemap != NULL && sprite != NULL) {
		Tile *tileRight = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, this->position->x + sprite->getRectWithoutRot()->w + 2, this->position->y + sprite->getRectWithoutRot()->h/2);
		Tile *tileLeft = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, this->position->x - 2, this->position->y + sprite->getRectWithoutRot()->h/2);
		Tile *tileDown = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, this->position->x + sprite->getRectWithoutRot()->w/2, this->position->y + sprite->getRectWithoutRot()->h + 3);

		if(inputManager->isKeyPressed(SDLK_z)) {
			skillData->playSound();
			addMp(-magicCost);
			if(tileRight && !tileDown) {
				velocity->x = - (float)intensity/37.5f;
				velocity->y = - (float)intensity/37.5f;
			} else if(tileLeft && !tileDown) {
				velocity->x = + (float)intensity/37.5f;
				velocity->y = - (float)intensity/37.5f;
			}
		}


	}
}
