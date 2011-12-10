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

#include "BouncingBall.h"

BouncingBall::BouncingBall() {


}

BouncingBall::BouncingBall(std::string *fileName, commtypes::real x, commtypes::real y) :
	GameObject(fileName, x, y){
	maxVelocity.x = 0.4f;
	maxVelocity.y = 0.4f;

	enemyPhysicalAttackCapable = true;

}

BouncingBall::BouncingBall(GameObjectInstance *gameObjectInstance)
	: GameObject(gameObjectInstance) {
	maxVelocity.x = gameObjectInstance->gameObject->vx/37.5f;
	maxVelocity.y = gameObjectInstance->gameObject->vy/37.5f;

	enemyPhysicalAttackCapable = true;
	velocity = new Vector2(maxVelocity);

}

BouncingBall::~BouncingBall() {
	// TODO Auto-generated destructor stub
}



int BouncingBall::update(int dt) {
	if(GameObject::update(dt) == -1) {
		return -1;
	}

	positionAnt.x = position->x;
	positionAnt.y = position->y;


	position->addScaledVector(velocity, dt);

	Tile *tile;
	if(autoCollision && (tile = testBoxCollisionTile(dt))) {


		if(tile != NULL) {

			Rect tileRect = tile->getTileRect();
			bounce(tileRect, dt);

			/*
			this->velocity->x = this->velocity->x*0.8;

			if(fabs(this->velocity->x) < fabs(maxVelocity.x)) {
				if(this->velocity < 0) {
					this->velocity->x = -fabs(maxVelocity.x);
				} else {
					this->velocity->x = +fabs(maxVelocity.x);
				}

			}



			this->velocity->y = this->velocity->y*0.8;


			if(fabs(this->velocity->y) < fabs(maxVelocity.y)) {
				if(this->velocity < 0) {
					this->velocity->y = -fabs(maxVelocity.y);
				} else {
					this->velocity->y = +fabs(maxVelocity.y);
				}

			}
*/



		}
	}

	bool bouncedOnce = false;

	std::list<GameObject*> *spatialList = spatialHashmap->getNearby(this);
	for(std::list<GameObject*>::iterator it = spatialList->begin(); it != spatialList->end(); ++it) {
		GameObject* gameObject = *it;

		if(autoCollision && gameObject != this &&
				this->collidesWith(gameObject)) {

			if(gameObject->gameObjectInstance->gameObject->derrotaEncostandoInimigo) {
				Rect *objectRect = gameObject->sprite->getRectWithoutRot();
				Rect *thisRect = this->sprite->getRectWithoutRot();

				if(thisRect->intersectsWith(objectRect)) {
					gameObject->addDamage(this);
					if(gameObject->hp <= 0) {
						this->addExp(gameObject->gameObjectInstance->gameObject->experiencePoints);
						PlayerData::getInstance()->addPoints(gameObject->gameObjectInstance->gameObject->defeatPoints);
					}
				}

				delete thisRect;

				delete objectRect;
			}

			if(!bouncedOnce && this->gameObjectInstance->
					gameObject->arrayObjectsToBounce->at(gameObject->gameObjectInstance->gameObject->id)) {
				Rect *gameObjectRect = gameObject->sprite->getRectWithoutRot();
				bounce(*gameObjectRect, dt, gameObject->velocity);
				//this->position->addScaledVector(gameObject->velocity, dt);

				/*
				this->velocity->x = this->velocity->x*0.8;

				if(fabs(this->velocity->x) < fabs(maxVelocity.x)) {
					if(this->velocity < 0) {
						this->velocity->x = -fabs(maxVelocity.x);
					} else {
						this->velocity->x = +fabs(maxVelocity.x);
					}

				}


				this->velocity->y = this->velocity->y*0.8;

				if(fabs(this->velocity->y) < fabs(maxVelocity.y)) {
					if(this->velocity < 0) {
						this->velocity->y = -fabs(maxVelocity.y);
					} else {
						this->velocity->y = +fabs(maxVelocity.y);
					}

				}
				 */

				bouncedOnce = true;

				delete gameObjectRect;

			}






		}
	}


	/*

	if(testBoxCollisionTileRight(dt, *position) || testBoxCollisionTileLeft(dt, *position)) {
		position->x = positionAnt.x;

		velocity->x *= -1;

	}

	if(testBoxCollisionTileUp(dt, *position) || testBoxCollisionTileDown(dt, *position)) {
		position->y = positionAnt.y;

		velocity->y *= -1;

	}
	*/

	return 0;
}

void BouncingBall::render(Screen *screen) {
	GameObject::render(screen);
}

void BouncingBall::follow(Vector2 point, int dt) {
	Vector2 center = getCenter();

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
}

void BouncingBall::moveAway(Vector2 point, int dt) {
	follow(point, dt);
	velocity->x *= -1;
	velocity->y *= -1;
}

void BouncingBall::bounce(Rect rect, int dt, Vector2 *objVelocity) {
	float tfirst, tlast;
	int lado;
	Rect movedRect = Rect(0, 0, 0, 0);
	Vector2 realVelocity = Vector2(velocity->x*dt, velocity->y*dt);

	playSpecialSound();

	Rect *objectRect = this->sprite->getRectWithoutRot();
	objectRect->x = positionAnt.x;
	objectRect->y = positionAnt.y;
	if(objectRect->movingIntersectRect(realVelocity, rect, &tfirst, &tlast, &lado, &movedRect)) {
		position->x = positionAnt.x;
		position->y = positionAnt.y;

		if(lado == Rect::SIDE_RIGHT || lado == Rect::SIDE_LEFT) {
			if(objVelocity != NULL && objVelocity->x != 0) {
				velocity->x = objVelocity->x;
			} else {
				velocity->x *= -1;
			}

		} else {
			if(objVelocity != NULL && objVelocity->y != 0) {
				velocity->y = objVelocity->y;
			} else {
				velocity->y *= -1;
			}


		}

	}
}

void BouncingBall::follow(Vector2 point, int dt, float velocityFollow) {
	Vector2 center = getCenter();

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
}

void BouncingBall::moveAway(Vector2 point, int dt, float velocityFollow) {
	follow(point, dt, velocityFollow);
	velocity->x *= -1;
	velocity->y *= -1;
}

void BouncingBall::bounceEvent(int dt) {
	std::list<GameObject*> *spatialList = spatialHashmap->getNearby(this);
	for(std::list<GameObject*>::iterator it = spatialList->begin(); it != spatialList->end(); ++it) {
		GameObject* gameObject = *it;

		if(autoCollision && gameObject != this &&
				!this->gameObjectInstance->
				gameObject->arrayObjectsToBounce->at(gameObject->gameObjectInstance->gameObject->id) &&
				this->collidesWith(gameObject)) {
			Rect *gameObjectRect = gameObject->sprite->getRectWithoutRot();
			bounce(*gameObjectRect, dt, gameObject->velocity);
			//this->position->addScaledVector(gameObject->velocity, dt);
			std::cout << "Bouncing" << std::endl;

			delete gameObjectRect;

			break;
		}
	}
}

