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

#include "ItemMovementObject.h"

ItemMovementObject::ItemMovementObject()
	: NpcMovementObject() {

	isSword = false;

}

ItemMovementObject::ItemMovementObject(GameObjectInstance *gameObjectInstance)
	: NpcMovementObject(gameObjectInstance) {
	playerData = PlayerData::getInstance();
	thrower = NULL;

	enemyPhysicalAttackCapable = false;

	autoCollision = false;

	isSword = false;

	timer = 0;

}

ItemMovementObject::~ItemMovementObject() {
	// TODO Auto-generated destructor stub
}

void ItemMovementObject::setSwordMode() {
	isSword = true;
}


int ItemMovementObject::update(int dt) {

	if(NpcMovementObject::update(dt) == -1) {
		return -1;
	}

	if(isSword) {
		timer += dt;

		if(timer > 100) {
			return -1;
		}
	}



	GameData *gameData = GameData::getInstance();


	Rect *thisRect, *playerRect;
	thisRect = this->sprite->getRectWithoutRot();

	if(playerData->getPlayer() != NULL) {
		playerRect = playerData->getPlayer()->sprite->getRectWithoutRot();

		if(thrower == NULL || playerData->getPlayer() != thrower) {
			if(playerData->getPlayer()->position->z == 0 && thisRect->intersectsWith(playerRect)) {
				playSpecialSound();

				if(gameObjectInstance->gameObject->concedePontos) {
					playerData->addPoints(gameObjectInstance->gameObject->concedePontosValor);
				}

				if(gameObjectInstance->gameObject->ganhaPerdeVida) {
					if(thrower != NULL) {
						playerData->addDamage(thrower, -gameObjectInstance->gameObject->ganhaPerdeVidaValor);
					} else {
						playerData->addHp(gameObjectInstance->gameObject->ganhaPerdeVidaValor);
					}

					if(playerData->getPlayer()->hp <= 0) {
						if(this->thrower != NULL) {
							this->thrower->addExp(playerData->getPlayer()->gameObjectInstance->gameObject->experiencePoints);
						}

					}
				}

				if(gameObjectInstance->gameObject->ganhaPerdeMagia) {
					playerData->addMp(gameObjectInstance->gameObject->ganhaPerdeMagiaValor);
				}

				if(gameObjectInstance->gameObject->incrementaVariavel) {
					if(gameObjectInstance->gameObject->incrementaVariavelVariable != NULL) {
						gameObjectInstance->gameObject->incrementaVariavelVariable->value +=
								gameObjectInstance->gameObject->incrementaVariavelValor;
					}
				}

				if(gameObjectInstance->gameObject->ativaEvento) {
					if(gameObjectInstance->gameObject->ativaEventoProcedure != NULL) {
						Interpreter *interpreter = new Interpreter();
						interpreter->executeProcedure(gameObjectInstance->gameObject->ativaEventoProcedure, dt);

						delete interpreter;
					}
				}


				delete thisRect;
				delete playerRect;

				if(!playerData->getPlayer()->gameObjectInstance->gameObject->obtainedItems->at(this->gameObjectInstance->gameObject->id) &&
						!this->gameObjectInstance->gameObject->itemSkills.empty()) {

					for(std::list<std::pair<int, GameObjectClass*> >::iterator it = this->gameObjectInstance->gameObject->itemSkills.begin();
							it != this->gameObjectInstance->gameObject->itemSkills.end(); ++it) {
						std::pair<int, GameObjectClass*> skillPair = *it;
						int idSkill = skillPair.first;

						if(skillPair.second == playerData->getPlayer()->gameObjectInstance->gameObject) {
							modalManager->pushModal(new DialogueText(SkillData::getSkillMessages()->at(idSkill), DialogueText::POS_UP, dt, true));
						}

					}


				}

				playerData->getPlayer()->gameObjectInstance->gameObject->obtainedItems->at(this->gameObjectInstance->gameObject->id) = true;

				if(this->gameObjectInstance->gameObject->desapareceEncostarPersonagem) {
					return -1;
				} else {
					return 0;
				}

			}
		}
	}


	if(getObjectList() != NULL) {
		std::list<GameObject*> *spatialList = spatialHashmap->getNearby(this);
		for(std::list<GameObject*>::iterator it = spatialList->begin(); it != spatialList->end(); ++it) {
			GameObject* gameObject = *it;

			if(gameObject != thrower &&
					gameObject->gameObjectInstance->gameObject->type != GameObjectClass::ITEM &&
					gameObject != playerData->getPlayer() &&
					gameObject->gameObjectInstance->gameObject->derrotaAtirandoItemMagiaInimigo) {
				Rect *specificObjectRect = gameObject->sprite->getRectWithoutRot();
				if(specificObjectRect->intersectsWith(thisRect)) {
					playSpecialSound();
					if(gameObjectInstance->gameObject->concedePontos) {
						playerData->addPoints(gameObjectInstance->gameObject->concedePontosValor);
					}

					if(gameObjectInstance->gameObject->ganhaPerdeVida) {
						if(thrower != NULL) {
							gameObject->addDamage(thrower, -gameObjectInstance->gameObject->ganhaPerdeVidaValor);
						} else {
							gameObject->addHp(gameObjectInstance->gameObject->ganhaPerdeVidaValor);
						}


						if(gameObject->hp <= 0) {

							if(this->thrower != NULL) {
								this->thrower->addExp(gameObject->gameObjectInstance->gameObject->experiencePoints);
							}

						}
					}

					if(gameObjectInstance->gameObject->ganhaPerdeMagia) {
						gameObject->addMp(gameObjectInstance->gameObject->ganhaPerdeMagiaValor);
					}

					if(gameObjectInstance->gameObject->incrementaVariavel) {
						if(gameObjectInstance->gameObject->incrementaVariavelVariable != NULL) {
							gameObjectInstance->gameObject->incrementaVariavelVariable->value +=
									gameObjectInstance->gameObject->incrementaVariavelValor;
						}
					}

					delete specificObjectRect;
					delete thisRect;
					delete playerRect;

					if(gameObject->gameObjectInstance->gameObject->obtainedItems->at(this->gameObjectInstance->gameObject->id) &&
							!this->gameObjectInstance->gameObject->itemSkills.empty()) {

						for(std::list<std::pair<int, GameObjectClass*> >::iterator it = this->gameObjectInstance->gameObject->itemSkills.begin();
								it != this->gameObjectInstance->gameObject->itemSkills.end(); ++it) {
							std::pair<int, GameObjectClass*> skillPair = *it;
							int idSkill = skillPair.first;

							if(skillPair.second == gameObject->gameObjectInstance->gameObject) {
								modalManager->pushModal(new DialogueText(SkillData::getSkillMessages()->at(idSkill), DialogueText::POS_UP, dt, true));
							}

						}


					}

					gameObject->gameObjectInstance->gameObject->obtainedItems->at(this->gameObjectInstance->gameObject->id) = true;


					if(this->gameObjectInstance->gameObject->desapareceEncostarPersonagem) {
						return -1;
					} else {
						return 0;
					}


				}

				delete specificObjectRect;
			}




		}

		delete spatialList;
	}


	if(gameObjectInstance->gameObject->desapareceEncostarParede) {
		if(testBoxCollisionTile(dt)) {
			return -1;
		}
	}



	delete thisRect;
	delete playerRect;



	return 0;
}
