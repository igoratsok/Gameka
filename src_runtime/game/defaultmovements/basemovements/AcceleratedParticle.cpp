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

#include "AcceleratedParticle.h"

AcceleratedParticle::AcceleratedParticle() : GameObject() {
	maxVelocity.x = 0.4f;
	maxVelocity.y = 0.4f;

	accelerationValue.x = 0.002f;
	accelerationValue.y = 0.002f;

	desaccelerationValue.x = 0.002f;
	desaccelerationValue.y = 0.002f;

	accMovementType = 1;

	zDoubleJumping = false;
	glideIntensity = 0;
	flightIntensity = 0;
	sprintIntensity = 0;

}

AcceleratedParticle::AcceleratedParticle(std::string *fileName, commtypes::real x, commtypes::real y)
	:  GameObject(fileName, x, y){
	maxVelocity.x = 0.8f;
	maxVelocity.y = 0.8f;

	accelerationValue.x = 0.002f;
	accelerationValue.y = 0.002f;

	desaccelerationValue.x = 0.002f;
	desaccelerationValue.y = 0.002f;

	accMovementType = 1;

	zDoubleJumping = false;
	glideIntensity = 0;
	flightIntensity = 0;
	sprintIntensity = 0;


}

AcceleratedParticle::AcceleratedParticle(GameObjectInstance *gameObjectInstance)
	: GameObject(gameObjectInstance) {



	maxVelocity.x = 0.8f;
	maxVelocity.y = 0.8f;

	accelerationValue.x = 0.002f;
	accelerationValue.y = 0.002f;

	desaccelerationValue.x = 0.002f;
	desaccelerationValue.y = 0.002f;

	accMovementType = 1;

	zDoubleJumping = false;
	glideIntensity = 0;
	flightIntensity = 0;
	sprintIntensity = 0;


	inputManager = InputManager::getInstance();
}

AcceleratedParticle::~AcceleratedParticle() {


}

int AcceleratedParticle::update(int dt) {

	if(GameObject::update(dt) == -1) {
		return -1;
	}


	/*
	Vector2 nextPosition;
	Vector2 collisionVelocity;



	velocity->addScaledVector(acceleration, dt);
	velocity->limitVector(&maxVelocity);

	nextPosition = *position;
	nextPosition.addScaledVector(velocity, dt);

	collisionVelocity = *velocity;
	collisionVelocity.x *= dt;
	collisionVelocity.y *= dt;

	Vector2 begin;
	begin.x = std::min(position->x, nextPosition.x);
	begin.y = std::min(position->y, nextPosition.y);

	Vector2 end;
	end.x = std::max(position->x, nextPosition.x);
	end.y = std::max(position->y, nextPosition.y);

	float tfirst, tlast;
	int lado = -1;
	tfirst = 1.0f;
	tlast = 1.0f;

	Rectangle *objectRect;
	objectRect = this->sprite->getRectWithoutRot();
	Rectangle newPosition = Rectangle(0, 0, 0, 0);

	bool doubleBreak = false;

	for(float i = begin.x - tilemap->tileWidth*2; i <= end.x + tilemap->tileWidth*2; i += tilemap->tileWidth) {
		for(float j = begin.y - tilemap->tileHeight*2; j <= end.y + tilemap->tileHeight*2; j += tilemap->tileHeight) {
			Tile *tile = tilemap->getTilesetByPosition(i, j);

			if(tile != NULL && tile->collisionType == Tile::COLLISION_BLOCK) {

				Rectangle tileRect = Rectangle(((int)(i/tilemap->tileWidth))*tilemap->tileWidth,
						((int)(j/tilemap->tileHeight))*tilemap->tileHeight,
						tilemap->tileWidth, tilemap->tileHeight);



				if(objectRect->movingIntersectRect(collisionVelocity, tileRect, &tfirst, &tlast, &lado, &newPosition)) {
					std::cout << "Colidiu! " << collisionVelocity.x << " " << collisionVelocity.y << " tfirst: " << tfirst << std::endl;
					doubleBreak = true;
					break;
				} else {
					tfirst = 1.0f;
				}



			}
		}
		if(doubleBreak) {
			break;
		}
	}

	delete objectRect;

	position->addScaledVector(velocity, dt);


	if(doubleBreak) {
		position->x = newPosition.x;
		position->y = newPosition.y;
	}

	if(lado != -1 && doubleBreak) {
		switch(lado) {
		case Rectangle::SIDE_UP:

			break;
		default:
			break;
		}
	}

	*/



	positionAnt.x = position->x;
	positionAnt.y = position->y;


	velocity->addScaledVector(acceleration, dt);
	position->addScaledVector(velocity, dt);






	if(autoCollision && testBoxCollisionTile(dt)) {

		resolveBoxCollisionTile(positionAnt, dt);

	}





	if(glideIntensity == 0 && flightIntensity == 0) {
		acceleration->z = +0.002f;
	} else {
		if(flightIntensity == 0) {
			acceleration->z = 0;
			velocity->z = glideIntensity;
		} else {
			acceleration->z = 0;
			velocity->z = -flightIntensity;
		}

	}



	if(position->z > 0) {
		position->z = 0;
	}





	if(position->z < 0) {
		sprite->setZoom(1 - (position->z)/200.0f);
		setSpriteRotation(1);
	} else {
		setSpriteRotation(0);
	}

	Rect *thisRect = sprite->getRectWithoutRot();

	// verifica colisão de zpulo por cima com inimigos
	if(enemyPhysicalAttackCapable) {
		if(getObjectList() != NULL) {
			std::list<GameObject*> *spatialList = spatialHashmap->getNearby(this);
			for(std::list<GameObject*>::iterator it = spatialList->begin(); it != spatialList->end(); ++it) {
				GameObject* gameObject = *it;

				if(gameObject != this) {
					if(gameObject->gameObjectInstance->gameObject->type == GameObjectClass::INIMIGO) {
						if(gameObject->gameObjectInstance->gameObject->derrotaPulandoSobreInimigo) {
							Rect *objectRect = gameObject->sprite->getRectWithoutRot();



							if(thisRect->intersectsWith(objectRect) && this->position->z != 0 &&
									gameObject->gameObjectInstance->gameObject->derrotaPulandoSobreInimigo) {
								int nextZ = this->position->z + this->velocity->z*dt;
								if(nextZ > - 5) {
									gameObject->addDamage(this);
									gameObject->setInvincibility(1000);
									if(gameObject->hp <= 0) {
										this->addExp(gameObject->gameObjectInstance->gameObject->experiencePoints);
										PlayerData::getInstance()->addPoints(gameObject->gameObjectInstance->gameObject->defeatPoints);
									}
									this->velocity->z = -0.5f;
								}
							}



							delete objectRect;
						}

						if(gameObject->gameObjectInstance->gameObject->derrotaEncostandoInimigo) {
							Rect *objectRect = gameObject->sprite->getRectWithoutRot();

							if(thisRect->intersectsWith(objectRect)) {
								gameObject->addDamage(this);
								if(gameObject->hp <= 0) {
									this->addExp(gameObject->gameObjectInstance->gameObject->experiencePoints);
									PlayerData::getInstance()->addPoints(gameObject->gameObjectInstance->gameObject->defeatPoints);
								}
								this->velocity->x *= -1;
								this->velocity->y *= -1;
							}

							delete objectRect;
						}

					}
				}



			}
		}
	}


	delete thisRect;




	return 0;

}

void AcceleratedParticle::resolveBoxCollisionTile(Vector2 positionAnt, int dt) {
	if(tilemap != NULL) {

		Vector2 dir;
		dir = velocity->getDirecao();

		Line* line = new Line(&positionAnt, position);
		Rect *rect;
		rect = sprite->getRectWithoutRot();

		bool first = true;
		bool achouColisaoLados = false;

		line->startInterpolation();
		Vector2 interpolationAnt;

		while(!line->finished()) {
			Vector2 interpolation = line->retrieveInterpolation();

			if(first) {
				interpolationAnt.x = positionAnt.x;
				interpolationAnt.y = positionAnt.y;
				first = false;
			}

			/*
			bool teste1q, teste2q, teste3q, teste4q;
			teste1q = tilemap->getTilesetByPosition(interpolation.x + 1, interpolation.y + 1)->collisionType == Tile::COLLISION_BLOCK;
			teste2q = tilemap->getTilesetByPosition(interpolation.x + rect->w - 1, interpolation.y + 1)->collisionType == Tile::COLLISION_BLOCK;
			teste3q = tilemap->getTilesetByPosition(interpolation.x + rect->w - 1, interpolation.y + rect->h - 1)->collisionType == Tile::COLLISION_BLOCK;
			teste4q = tilemap->getTilesetByPosition(interpolation.x + 1, interpolation.y + rect->h - 1)->collisionType == Tile::COLLISION_BLOCK;

			if(teste1q && teste2q && teste3q && teste4q) {
				this->position->x = interpolationAnt.x;
				this->position->y = interpolationAnt.y;



				break;
			}

			if((teste2q && teste3q) || (teste4q && teste1q)) {
				this->position->x = interpolationAnt.x;
				this->velocity->x = 0;
			}
			*/


			/*
			if((teste3q && teste4q) || (teste2q && teste3q)) {
				this->position->y = interpolationAnt.y;
				this->velocity->y = 0;
			}
			*/

			bool testUp, testDown, testLeft, testRight;
			testUp = testBoxCollisionTileUp(dt, interpolation);
			testDown = testBoxCollisionTileDown(dt, interpolation);
			testLeft = testBoxCollisionTileLeft(dt, interpolation);
			testRight = testBoxCollisionTileRight(dt, interpolation);


			if(testUp || testDown) {
				this->position->y = round(interpolationAnt.y);
				if(fabs(this->velocity->y) > 0.2)  {
					if(velocity->y > 0) {
						this->velocity->y = 0.2;
					} else {
						this->velocity->y = -0.2;
					}

				}
				achouColisaoLados = true;
			}

			if(testLeft || testRight) {
				this->position->x = round(interpolationAnt.x);
				if(fabs(this->velocity->x) > 0.2) {
					if(velocity->x > 0) {
						this->velocity->x = 0.2;
					} else {
						this->velocity->x = -0.2;
					}

				}
				achouColisaoLados = true;
			}



			if(achouColisaoLados) {
				break;
			}



			interpolationAnt.x = interpolation.x;
			interpolationAnt.y = interpolation.y;

		}

		if(!achouColisaoLados || testBoxCollisionTile(dt)) {
			this->position->x = positionAnt.x;
			this->position->y = positionAnt.y;
		}

		/*
		Rectangle *rect;
		rect = sprite->getRectWithoutRot();

		while(tilemap->getTilesetByPosition(position->x + rect->w , position->y)->collisionType == Tile::COLLISION_BLOCK) {
			position->x -= 1;
			velocity->x = 0;

		}


		//position->y = positionAnt.y;

		*/

		/*
		do {
			position->x -= dir.x;
			position->y -= dir.y;
		} while(testBoxCollisionTile(dt));
		*/

		delete rect;
		delete line;
	}
}

void AcceleratedParticle::follow(Vector2 point, int dt) {
	Vector2 center = getCenter();
	Vector2 nextPosition;

	if(accMovementType == 0) {
		if(center.x > point.x) {
			velocity->x = -maxVelocity.x;
		} else if(center.x < point.x) {
			velocity->x = maxVelocity.x;
		} else {
			velocity->x = 0.0f;
		}

		if(center.y > point.y) {
			velocity->y = -maxVelocity.y;
		} else if(center.y < point.y) {
			velocity->y = maxVelocity.y;
		} else {
			velocity->y = 0.0f;
		}

	} else {
		if(center.x > point.x) {
			if(velocity->x < maxVelocity.x) {
				velocity->x -= accelerationValue.x*dt;
			}
			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.x < point.x) {
				velocity->x = 0;
			}

		} else if(center.x < point.x) {
			if(velocity->x < maxVelocity.x) {
				velocity->x += accelerationValue.x*dt;
			}

			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.x > point.x) {
				velocity->x = 0;
			}

		} else {
			velocity->x = 0.0f;
		}

		if(center.y > point.y) {
			if(velocity->y < maxVelocity.y) {
				velocity->y -= accelerationValue.y*dt;
			}


			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.y < point.y) {
				velocity->y = 0;
			}

		} else if(center.y < point.y) {
			if(velocity->y < maxVelocity.y) {
				velocity->y += accelerationValue.y*dt;
			}


			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.y > point.y) {
				velocity->y = 0;
			}

		} else {
			velocity->y = 0.0f;
		}
	}

	acceleration->x = 0;
	acceleration->y = 0;



}

void AcceleratedParticle::moveAway(Vector2 point, int dt) {
	Vector2 center = getCenter();
	Vector2 nextPosition;

	if(accMovementType == 0) {
		if(center.x > point.x) {
			velocity->x = +maxVelocity.x;
		} else if(center.x < point.x) {
			velocity->x = -maxVelocity.x;
		} else {
			velocity->x = 0.0f;
		}

		if(center.y > point.y) {
			velocity->y = -maxVelocity.y;
		} else if(center.y < point.y) {
			velocity->y = +maxVelocity.y;
		} else {
			velocity->y = 0.0f;
		}

	} else {
		if(center.x > point.x) {
			if(velocity->x < maxVelocity.x) {
				velocity->x += accelerationValue.x*dt;
			}
			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.x < point.x) {
				velocity->x = 0;
			}

		} else if(center.x < point.x) {
			if(velocity->x > -maxVelocity.x) {
				velocity->x -= accelerationValue.x*dt;
			}

			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.x > point.x) {
				velocity->x = 0;
			}

		} else {
			velocity->x = 0.0f;
		}

		if(center.y > point.y) {
			if(velocity->y < maxVelocity.y) {
				velocity->y += accelerationValue.y*dt;
			}


			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.y < point.y) {
				velocity->y = 0;
			}

		} else if(center.y < point.y) {
			if(velocity->y > -maxVelocity.y) {
				velocity->y -= accelerationValue.y*dt;
			}


			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.y > point.y) {
				velocity->y = 0;
			}

		} else {
			velocity->y = 0.0f;
		}
	}

	acceleration->x = 0;
	acceleration->y = 0;

}


void AcceleratedParticle::follow(Vector2 point, int dt, float velocityFollow) {
	Vector2 center = getCenter();
	Vector2 nextPosition;

	if(accMovementType == 0) {
		if(center.x > point.x) {
			velocity->x = -velocityFollow;
		} else if(center.x < point.x) {
			velocity->x = velocityFollow;
		} else {
			velocity->x = 0.0f;
		}

		if(center.y > point.y) {
			velocity->y = -velocityFollow;
		} else if(center.y < point.y) {
			velocity->y = velocityFollow;
		} else {
			velocity->y = 0.0f;
		}

	} else {
		if(center.x > point.x) {
			if(velocity->x < velocityFollow) {
				velocity->x -= accelerationValue.x*dt;
			}
			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.x < point.x) {
				velocity->x = 0;
			}

		} else if(center.x < point.x) {
			if(velocity->x < velocityFollow) {
				velocity->x += accelerationValue.x*dt;
			}

			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.x > point.x) {
				velocity->x = 0;
			}

		} else {
			velocity->x = 0.0f;
		}

		if(center.y > point.y) {
			if(velocity->y < velocityFollow) {
				velocity->y -= accelerationValue.y*dt;
			}


			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.y < point.y) {
				velocity->y = 0;
			}

		} else if(center.y < point.y) {
			if(velocity->y < velocityFollow) {
				velocity->y += accelerationValue.y*dt;
			}


			nextPosition = center;
			nextPosition.addScaledVector(velocity, dt);
			if(nextPosition.y > point.y) {
				velocity->y = 0;
			}

		} else {
			velocity->y = 0.0f;
		}
	}

	acceleration->x = 0;
	acceleration->y = 0;



}

void AcceleratedParticle::moveAway(Vector2 point, int dt, float velocityFollow) {
	follow(point, dt, velocityFollow);
	velocity->x *= -1;
	velocity->y *= -1;
}

void AcceleratedParticle::zJump(SkillData *skillData, int intensity, int magicCost) {
	float jumpRealIntensity = (float)intensity/29.0f;

	if(position->z == 0 && inputManager->isKeyPressed(SDLK_z)) {
		skillData->playSound();
		zDoubleJumping = false;
		velocity->z = -jumpRealIntensity;
		addMp(-magicCost);
	}
}

void AcceleratedParticle::zDoubleJump(SkillData *skillData, int intensity, int magicCost) {
	float jumpRealIntensity = (float)intensity/29.0f;

	if(position->z != 0 && !zDoubleJumping && inputManager->isKeyPressed(SDLK_z)) {
		skillData->playSound();
		zDoubleJumping = true;
		velocity->z = -jumpRealIntensity;
		addMp(-magicCost);
	}
}

void AcceleratedParticle::sprint(SkillData *skillData, int intensity, int magicCost) {
	if(inputManager->isKeyDown(SDLK_a)) {
		sprintIntensity = (float)intensity/37.5f;
		addMp(-magicCost);
 	} else {
 		sprintIntensity = 0;
 	}
}

void AcceleratedParticle::glide(SkillData *skillData, int intensity, int magicCost) {
	if(inputManager->isKeyDown(SDLK_c)) {
		glideIntensity = (float)intensity/37.5f;
		addMp(-magicCost);
	} else {
		glideIntensity = 0;
	}
}

void AcceleratedParticle::fly(SkillData *skillData, int intensity, int magicCost) {
	if(inputManager->isKeyDown(SDLK_s)) {
		flightIntensity = (float)intensity/37.5f;
		addMp(-magicCost);
	} else {
		flightIntensity = 0;
	}
}


void AcceleratedParticle::bounce(Rect rect, int dt) {
	float tfirst, tlast;
	int lado;
	Rect movedRect = Rect(0, 0, 0, 0);
	Vector2 realVelocity = Vector2(velocity->x*dt, velocity->y*dt);

	Rect *objectRect = this->sprite->getRectWithoutRot();
	objectRect->x = positionAnt.x;
	objectRect->y = positionAnt.y;
	if(objectRect->movingIntersectRect(realVelocity, rect, &tfirst, &tlast, &lado, &movedRect)) {
		position->x = positionAnt.x;
		position->y = positionAnt.y;

		if(lado == Rect::SIDE_RIGHT || lado == Rect::SIDE_LEFT) {
			velocity->x *= -1;
		} else {
			velocity->y *= -1;
		}

	}
}

void AcceleratedParticle::bounceEvent(int dt) {
	this->velocity->x *= -1;
	this->velocity->y *= -1;
}
