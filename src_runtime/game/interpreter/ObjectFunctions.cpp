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

#include "ObjectFunctions.h"

ObjectFunctions* ObjectFunctions::singleton = NULL;

ObjectFunctions::ObjectFunctions() {
	gameObjectList = NULL;
	inputManager = InputManager::getInstance();

}

ObjectFunctions::~ObjectFunctions() {
	// TODO Auto-generated destructor stub
}

void ObjectFunctions::setGameObjectList(std::list<GameObject*> *gameObjectList) {
	this->gameObjectList = gameObjectList;

}

void ObjectFunctions::setAddGameObjectList(std::vector<GameObject*> *addGameObjectList) {
	this->addGameObjectList = addGameObjectList;
}


ObjectFunctions* ObjectFunctions::getInstance() {
	if(singleton == NULL) {
		singleton = new ObjectFunctions();
	}

	return singleton;
}



void ObjectFunctions::throwObject(GameObject *thrower, GameObjectClass *throwable, int intensity, int magicCost) {
	if(throwable != NULL) {
		Rect *rect = thrower->sprite->getRectWithoutRot();
		float throwVelocityConstant = 0.8f;

		PlayerData *playerData = PlayerData::getInstance();


		GameObjectInstance *gameObjectInstance = new GameObjectInstance();
		gameObjectInstance->gameObject = throwable;
		gameObjectInstance->x = thrower->position->x + rect->w/2 ;
		gameObjectInstance->y = thrower->position->y + rect->h/2;


		ItemMovementObject *item = ObjectFactory::mountItemMovementObject(gameObjectInstance);
		item->setObjectList(gameObjectList);

		Rect *rectThrowed = item->sprite->getRectWithoutRot();
		item->position->x -= rectThrowed->w/2;
		item->position->y -= rectThrowed->h/2;


		item->thrower = thrower;

		if(thrower == playerData->getPlayer()) {
			switch(inputManager->getCurrentDirection()) {
			case 0:
				item->velocity->x = throwVelocityConstant*intensity;
				item->velocity->y = 0;
				break;
			case 45:
				item->velocity->x = throwVelocityConstant*intensity;
				item->velocity->y = -throwVelocityConstant*intensity;
				break;
			case 90:
				item->velocity->x = 0;
				item->velocity->y = -throwVelocityConstant*intensity;
				break;
			case 135:
				item->velocity->x = -throwVelocityConstant*intensity;
				item->velocity->y = -throwVelocityConstant*intensity;
				break;
			case 180:
				item->velocity->x = -throwVelocityConstant*intensity;
				item->velocity->y = 0;
				break;
			case 225:
				item->velocity->x = -throwVelocityConstant*intensity;
				item->velocity->y = throwVelocityConstant*intensity;
				break;
			case 270:
				item->velocity->x = 0;
				item->velocity->y = throwVelocityConstant*intensity;
				break;
			case 315:
				item->velocity->x = throwVelocityConstant*intensity;
				item->velocity->y = throwVelocityConstant*intensity;
				break;
			}
		} else {
			float maxVelocity = std::max(thrower->velocity->x, thrower->velocity->y);

			if(maxVelocity == 0) {
				item->velocity->x = 0;
				item->velocity->y = 0;
			} else {
				item->velocity->x = (thrower->velocity->x/maxVelocity)*throwVelocityConstant*intensity;
				item->velocity->y = (thrower->velocity->y/maxVelocity)*throwVelocityConstant*intensity;
			}


		}




		thrower->addMp(-magicCost);


		addGameObjectList->push_back(item);

		delete rect;
	}
}

void ObjectFunctions::throwObject(GameObject *thrower, GameObjectClass *throwable, int intensity, Vector2 position, int magicCost) {
	if(throwable != NULL) {
		Rect *rect = thrower->sprite->getRectWithoutRot();
		float throwVelocityConstant = 0.05f;




		GameObjectInstance *gameObjectInstance = new GameObjectInstance();
		gameObjectInstance->gameObject = throwable;
		gameObjectInstance->x = thrower->position->x + rect->w/2 ;
		gameObjectInstance->y = thrower->position->y + rect->h/2;


		ItemMovementObject *item = ObjectFactory::mountItemMovementObject(gameObjectInstance);
		item->setObjectList(gameObjectList);

		Rect *rectThrowed = item->sprite->getRectWithoutRot();
		item->position->x -= rectThrowed->w/2;
		item->position->y -= rectThrowed->h/2;


		item->thrower = thrower;

		float dx, dy;
		dx = thrower->position->x + rect->w/2  - position.x;
		dy = thrower->position->y + rect->h/2 - position.y;

		//		float angle = atan(dy/dx);

		//		item->velocity->x = intensity*throwVelocityConstant*sin(angle);
		//		item->velocity->y = intensity*throwVelocityConstant*cos(angle);

		if(fabs(dx) != 0 || fabs(dy) != 0) {
			if(fabs(dx) < fabs(dy)) {
				item->velocity->y = -(float)intensity*throwVelocityConstant*(fabs(dy)/dy);
				item->velocity->x = -(float)intensity*throwVelocityConstant*(fabs(dx)/fabs(dy))*(fabs(dx)/dx);
			} else {
				item->velocity->x = -(float)intensity*throwVelocityConstant*(fabs(dx)/dx);
				item->velocity->y = -(float)intensity*throwVelocityConstant*(fabs(dy)/fabs(dx))*(fabs(dy)/dy);
			}
		}

		std::cout << "velocity x: " << item->velocity->x << std::endl;
		std::cout << "velocity y: " << item->velocity->y << std::endl;

		thrower->addMp(-magicCost);

		addGameObjectList->push_back(item);

		delete rect;
	}
}

void ObjectFunctions::throwSwordObject(GameObject *thrower, GameObjectClass *throwable, int magicCost) {
	if(throwable != NULL) {
		Rect *rect = thrower->sprite->getRectWithoutRot();
		float throwVelocityConstant = 0.8f;

		PlayerData *playerData = PlayerData::getInstance();


		GameObjectInstance *gameObjectInstance = new GameObjectInstance();
		gameObjectInstance->gameObject = throwable;
		gameObjectInstance->x = thrower->position->x + rect->w/2 ;
		gameObjectInstance->y = thrower->position->y + rect->h/2;

		int intensity = 1;

		ItemMovementObject *item = ObjectFactory::mountItemMovementObject(gameObjectInstance);
		item->setObjectList(gameObjectList);

		Rect *rectThrowed = item->sprite->getRectWithoutRot();
		item->position->x -= rectThrowed->w/2;
		item->position->y -= rectThrowed->h/2;


		item->thrower = thrower;

		if(thrower == playerData->getPlayer()) {
			switch(inputManager->getCurrentDirection()) {
			case 0:
				item->velocity->x = throwVelocityConstant*intensity;
				item->velocity->y = 0;
				break;
			case 45:
				item->velocity->x = throwVelocityConstant*intensity;
				item->velocity->y = -throwVelocityConstant*intensity;
				break;
			case 90:
				item->velocity->x = 0;
				item->velocity->y = -throwVelocityConstant*intensity;
				break;
			case 135:
				item->velocity->x = -throwVelocityConstant*intensity;
				item->velocity->y = -throwVelocityConstant*intensity;
				break;
			case 180:
				item->velocity->x = -throwVelocityConstant*intensity;
				item->velocity->y = 0;
				break;
			case 225:
				item->velocity->x = -throwVelocityConstant*intensity;
				item->velocity->y = throwVelocityConstant*intensity;
				break;
			case 270:
				item->velocity->x = 0;
				item->velocity->y = throwVelocityConstant*intensity;
				break;
			case 315:
				item->velocity->x = throwVelocityConstant*intensity;
				item->velocity->y = throwVelocityConstant*intensity;
				break;
			}
		} else {
			float maxVelocity = std::max(thrower->velocity->x, thrower->velocity->y);

			if(maxVelocity == 0) {
				item->velocity->x = 0;
				item->velocity->y = 0;
			} else {
				item->velocity->x = (thrower->velocity->x/maxVelocity)*1*intensity;
				item->velocity->y = (thrower->velocity->y/maxVelocity)*1*intensity;
			}


		}

		item->position->addScaledVector(item->velocity, 30.0f);

		item->velocity->x = 0;
		item->velocity->y = 0;

		item->setSwordMode();


		thrower->addMp(-magicCost);


		addGameObjectList->push_back(item);

		delete rect;
	}
}


void ObjectFunctions::processSkills(GameObject *gameObject) {
	for(std::vector<SkillData*>::iterator it = gameObject->gameObjectInstance->gameObject->listaHabilidades.begin();
			it != gameObject->gameObjectInstance->gameObject->listaHabilidades.end(); ++it) {
		SkillData* skillData = *it;

		if((gameObject->gameObjectInstance->gameObject->evolucaoPorNivel && skillData->level > 0  && gameObject->gameObjectInstance->gameObject->currentLevel >= skillData->level) ||
				(skillData->skillProvider != NULL && gameObject->gameObjectInstance->gameObject->obtainedItems->at(skillData->skillProvider->id)) ||
				(skillData->level <= 0 && skillData->skillProvider == NULL)) {
			if(gameObject->mp >= skillData->magicCost) {
				switch(skillData->nroSkill) {
				case SkillData::THROW_OBJECT:
					if(inputManager->isKeyPressed(SDLK_x)) {
						skillData->playSound();
						throwObject(gameObject, skillData->skillObject, skillData->intensity, skillData->magicCost);
					}


					break;
				case SkillData::THROW_OBJECT_MOUSE:
					if(inputManager->isMousePressed(1)) {
						skillData->playSound();
						throwObject(gameObject, skillData->skillObject, skillData->intensity, inputManager->getScenarioMousePosition(), skillData->magicCost);
					}

					break;
				case SkillData::THROW_SWORD:
					if(inputManager->isKeyPressed(SDLK_x)) {
						skillData->playSound();
						throwSwordObject(gameObject, skillData->skillObject,  skillData->magicCost);
					}
					break;

				case SkillData::JUMP:
					switch(gameObject->gameObjectInstance->gameObject->type) {
					case GameObjectClass::PLATFORM_MOVEMENT_OBJECT:

						break;
					case GameObjectClass::EIGHT_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->zJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::CAR_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->zJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::FIGHTING_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->zJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::MOUSE_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->zJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					}
					break;

				case SkillData::DOUBLE_JUMP:
					switch(gameObject->gameObjectInstance->gameObject->type) {
					case GameObjectClass::PLATFORM_MOVEMENT_OBJECT:

						((PlatformerMovement*) gameObject)->doubleJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::EIGHT_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->zDoubleJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::CAR_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->zDoubleJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::FIGHTING_MOVEMENT_OBJECT:
						((PlatformerMovement*) gameObject)->zDoubleJump(skillData, skillData->intensity, skillData->magicCost);
						break;
					}

					break;
				case SkillData::SPRINT:
					switch(gameObject->gameObjectInstance->gameObject->type) {
					case GameObjectClass::PLATFORM_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->sprint(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::EIGHT_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->sprint(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::CAR_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->sprint(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::FIGHTING_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->sprint(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::PONG_BALL_OBJECT:
						((AcceleratedParticle*) gameObject)->sprint(skillData, skillData->intensity, skillData->magicCost);
						break;
					}

					break;

				case SkillData::WALL_KICK:
					if(gameObject->gameObjectInstance->gameObject->type == GameObjectClass::PLATFORM_MOVEMENT_OBJECT) {
						((PlatformerMovement*) gameObject)->wallKick(skillData, skillData->intensity, skillData->magicCost);
					}


					break;
				case SkillData::GLIDE:
					switch(gameObject->gameObjectInstance->gameObject->type) {
					case GameObjectClass::PLATFORM_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->glide(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::EIGHT_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->glide(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::CAR_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->glide(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::FIGHTING_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->glide(skillData, skillData->intensity, skillData->magicCost);
						break;
					}
					break;
				case SkillData::FLY:
					switch(gameObject->gameObjectInstance->gameObject->type) {
					case GameObjectClass::PLATFORM_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->fly(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::EIGHT_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->fly(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::CAR_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->fly(skillData, skillData->intensity, skillData->magicCost);
						break;
					case GameObjectClass::FIGHTING_MOVEMENT_OBJECT:
						((AcceleratedParticle*) gameObject)->fly(skillData, skillData->intensity, skillData->magicCost);
						break;
					}

					break;

				}
			}
		}




	}
}
