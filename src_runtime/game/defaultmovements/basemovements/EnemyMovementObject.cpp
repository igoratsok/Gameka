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

#include "EnemyMovementObject.h"

EnemyMovementObject::EnemyMovementObject()
	: NpcMovementObject() {

	enemyPhysicalAttackCapable = true;
	attackTimer = 0;
}

EnemyMovementObject::EnemyMovementObject(GameObjectInstance *gameObjectInstance)
	: NpcMovementObject(gameObjectInstance) {
	this->accMovementType = 0;
	attackTimer = 0;

}

EnemyMovementObject::~EnemyMovementObject() {
	// TODO Auto-generated destructor stub
}

int EnemyMovementObject::update(int dt) {
	if(NpcMovementObject::update(dt) == -1) {
		return -1;
	}

	if(noAttackTimer > 0) {
		noAttackTimer -= dt;
		if(noAttackTimer < 0) {
			noAttackTimer = 0;
		}
	}



	if(noAttackTimer == 0) {
		Rect *thisRect = sprite->getRectWithoutRot();

		if(getObjectList() != NULL) {
			std::list<GameObject*> *spatialList = spatialHashmap->getNearby(this);
			for(std::list<GameObject*>::iterator it = spatialList->begin(); it != spatialList->end(); ++it) {
				GameObject *gameObject = *it;



				if(gameObject->gameObjectInstance->gameObject->type != GameObjectClass::INIMIGO &&
						gameObject->gameObjectInstance->gameObject->type != GameObjectClass::ITEM) {

					Rect *objectRect = gameObject->sprite->getRectWithoutRot();

					if(!gameObject->isInvincible() && gameObject->position->z == 0 &&  objectRect->intersectsWith(thisRect)) {
						int dmg = gameObject->addDamage(this, this->gameObjectInstance->gameObject->atacaEncostaPersonagemDano);
						if(dmg != 0) {
							gameObject->setInvincibility(1000);
						}


					}

					delete objectRect;

				}
			}

			delete spatialList;
		}

		delete thisRect;
	}




	if(attackTimer/1000.0f > (float)this->gameObjectInstance->gameObject->tempoAtaque) {
		if(this->gameObjectInstance->gameObject->atiraItemMagiaDirecaoPersonagem) {
			ObjectFunctions *objectFunctions = ObjectFunctions::getInstance();

			GameData *gameData = GameData::getInstance();
			PlayerData *playerData = PlayerData::getInstance();
			GameObjectClass *throwed;
			throwed = gameData->searchGameObjectById(this->gameObjectInstance->gameObject->atiraItemMagiaDirecaoPersonagemIdItem);

			if(playerData->getPlayer() != NULL) {
				objectFunctions->throwObject(this, throwed, 2, Vector2(*playerData->getPlayer()->position),  0);
			}

		}

		if(this->gameObjectInstance->gameObject->atiraItemMaginaDirecaoEstiver) {
			ObjectFunctions *objectFunctions = ObjectFunctions::getInstance();

			GameData *gameData = GameData::getInstance();
			GameObjectClass *throwed;
			throwed = gameData->searchGameObjectById(this->gameObjectInstance->gameObject->atiraItemMaginaDirecaoEstiverIdItem);

			objectFunctions->throwObject(this, throwed, 2, 0);
		}

		attackTimer = 0;
	}





	attackTimer += dt;

}
