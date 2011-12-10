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
#include "GameObject.h"

GameObject::GameObject() {
	position = new Vector2(0.0f, 0.0f);
	velocity = new Vector2();
	lastDirection = new Vector2();
	acceleration = new Vector2();
	sprite = NULL;
	tilemap = NULL;
	autoCollision = true;
	inputManager = InputManager::getInstance();
	drawShadow = false;
	objectList = NULL;
	enemyPhysicalAttackCapable = false;
	invincibilityTimer = 0;
	invincibilityVisibilityFlag = true;
	interpreter = new Interpreter(this);
	isDragging = false;
	clickFirstFrame = false;
	isMagical = false;
	noAttackTimer = 0;
	soundManager = SoundManager::getInstance();

}

GameObject::GameObject(commtypes::real x, commtypes::real y) {
	position = new Vector2(x, y);
	velocity = new Vector2();
	acceleration = new Vector2();
	lastDirection = new Vector2();

	inputManager = InputManager::getInstance();

	sprite = NULL;
	tilemap = NULL;
	autoCollision = true;
	drawShadow = false;
	objectList = NULL;
	enemyPhysicalAttackCapable = false;
	invincibilityTimer = 0;
	invincibilityVisibilityFlag = true;
	interpreter = new Interpreter(this);
	isDragging = false;
	clickFirstFrame = false;
	noAttackTimer = 0;

	isMagical = false;
	soundManager = SoundManager::getInstance();
}


GameObject::GameObject(std::string *fileName) {
	position = new Vector2(0.0f, 0.0f);
	velocity = new Vector2();
	acceleration = new Vector2();

	if(fileName != NULL) {
		sprite = new Sprite(fileName, position);
	} else {
		sprite = NULL;
	}

	inputManager = InputManager::getInstance();

	tilemap = NULL;
	autoCollision = true;
	drawShadow = false;
	objectList = NULL;
	enemyPhysicalAttackCapable = false;
	invincibilityTimer = 0;
	invincibilityVisibilityFlag = true;
	interpreter = new Interpreter(this);
	isDragging = false;
	clickFirstFrame = false;
	noAttackTimer = 0;

	isMagical = false;
	soundManager = SoundManager::getInstance();

}

GameObject::GameObject(std::string *fileName, commtypes::real x, commtypes::real y) {
	position = new Vector2(x, y);
	velocity = new Vector2();
	acceleration = new Vector2();

	if(fileName != NULL) {
		sprite = new Sprite(fileName, position);
	} else {
		sprite = NULL;
	}

	inputManager = InputManager::getInstance();

	tilemap = NULL;
	autoCollision = true;
	drawShadow = false;
	objectList = NULL;
	enemyPhysicalAttackCapable = false;
	invincibilityTimer = 0;
	invincibilityVisibilityFlag = true;
	interpreter = new Interpreter(this);
	isDragging = false;
	clickFirstFrame = false;
	noAttackTimer = 0;

	isMagical = false;
	soundManager = SoundManager::getInstance();
}


GameObject::GameObject(GameObjectInstance *gameObjectInstance)
	: gameObjectInstance(gameObjectInstance) {
	position = new Vector2(gameObjectInstance->x, gameObjectInstance->y);
	velocity = new Vector2();
	acceleration = new Vector2();
	sprite = new Sprite(gameObjectInstance, position);
	lastDirection = new Vector2();

	inputManager = InputManager::getInstance();

	tilemap = NULL;
	autoCollision = gameObjectInstance->gameObject->resolveCollision;
	drawShadow = false;
	objectList = NULL;

	hp = gameObjectInstance->gameObject->hp;
	mp = gameObjectInstance->gameObject->mp;
	enemyPhysicalAttackCapable = false;
	invincibilityTimer = 0;
	invincibilityVisibilityFlag = true;
	interpreter = new Interpreter(this);
	isDragging = false;
	clickFirstFrame = false;
	noAttackTimer = 0;

	isMagical = false;
	soundManager = SoundManager::getInstance();
}

GameObject::~GameObject() {
	delete position;
	delete acceleration;
	delete sprite;
	delete lastDirection;
	delete velocity;
}

bool GameObject::blockCollidesWith(GameObject *gameObject) {
	return this->sprite->blockCollidesWith(gameObject->sprite);
}

bool GameObject::pixelCollidesWith(GameObject *gameObject) {
	return this->sprite->pixelCollidesWith(gameObject->sprite);
}

int GameObject::update(int dt) {
	sprite->update(dt);

	if(velocity->x != 0) {
		lastDirection->x = fabs(velocity->x)/velocity->x;
	}

	if(velocity->y != 0) {
		lastDirection->y = fabs(velocity->y)/velocity->y;
	}

	if(this->hp <= 0) {
		return -1;
	}

	/* tratamento de drag&drop */

	if(gameObjectInstance->gameObject->isDraggable) {
		if(inputManager->isClicking(this)) {
			if(!clickFirstFrame) {
				clickFirstFrame = true;
				dragDropDifference = inputManager->getScenarioMousePosition();
				dragDropDifference.x -= this->position->x;
				dragDropDifference.y -= this->position->y;
				isDragging = true;
			}

		}

		if(isDragging && inputManager->isMouseDown(1)) {
			Vector2 mousePosition = inputManager->getScenarioMousePosition();
			this->position->x = mousePosition.x - dragDropDifference.x;
			this->position->y = mousePosition.y - dragDropDifference.y;
		} else {
			isDragging = false;
			clickFirstFrame = false;
		}
	}





	for(std::list<DamageDisplay*>::iterator it = damageDisplayList.begin(); it != damageDisplayList.end(); ++it) {
		DamageDisplay* damageDisplay = *it;

		int result = damageDisplay->update(dt);

		if(result == -1) {
			std::list<DamageDisplay*>::iterator it_aux = it;
			if(it == damageDisplayList.begin()) {
				it++;
			} else {
				it--;
			}

			damageDisplayList.erase(it_aux);
		}
	}

	invincibilityTimer -= dt;
	if(invincibilityTimer < 0) {
		invincibilityTimer = 0;
	}

	interpreter->executeProcedure(gameObjectInstance->gameObject->procedureGlobalAlways, dt);

	return 0;
}

void GameObject::render(Screen *screen) {
	if(sprite != NULL) {
		if(drawShadow) {
			Rect *rect = sprite->getRectWithoutRot();
			float hdown = rect->h*0.4f;
			int rx, ry;
			Vector2 *center = new Vector2();

			rx = (float)rect->w/3.0f;
			ry = hdown/2.0f;


			center->x = position->x + rect->w/2;
			center->y = position->y + rect->h - hdown/2.0f + 3;

			Sprite::drawFilledEllipse(center, rx, ry, 0, 0, 0, 120, 0, screen);


			delete center;
			delete rect;
		}

		if(isInvincible()) {
			invincibilityVisibilityFlag = !invincibilityVisibilityFlag;
		} else {
			invincibilityVisibilityFlag = true;
		}


		if(invincibilityVisibilityFlag) {
			sprite->render(screen);
		}

	}

	for(std::list<DamageDisplay*>::iterator it = damageDisplayList.begin(); it != damageDisplayList.end(); ++it) {
		DamageDisplay* damageDisplay = *it;

		damageDisplay->render(screen);
	}
}

void GameObject::renderCenter(Screen *screen) {
	if(sprite != NULL) sprite->renderCenter(screen);
}

void GameObject::setCenter() {
	sprite->setCenter();
}

void GameObject::setPositionByCenter(Vector2 center) {
	Rect *rect =  sprite->getRectWithoutRot();

	center.x -= rect->w/2;
	center.y -= rect->h/2;

	this->position->x = center.x;
	this->position->y = center.y;

	delete rect;
}

void GameObject::setSpriteRotation(commtypes::real angle) {
	sprite->setRot(angle);
}

void GameObject::setSpriteDirectionAngle(commtypes::real angle) {
	sprite->setDirectionAngleDegrees(angle);
}

void GameObject::setTilemap(Tilemap *tilemap) {
	this->tilemap = tilemap;
}

void GameObject::setObjectList(std::list<GameObject*> *objectList) {
	this->objectList = objectList;
}

void GameObject::setSpatialHashmap(SpatialHashmap *spatialHashmap) {
	this->spatialHashmap = spatialHashmap;
}

void GameObject::setModalManager(ModalStack *modalManager) {
	this->modalManager = modalManager;
}

std::list<GameObject*>* GameObject::getObjectList() {
	return this->objectList;
}


void GameObject::setInvincibility(int value) {
	this->invincibilityTimer = value;
}

int GameObject::getInvincibility() {
	return invincibilityTimer;
}

bool GameObject::isInvincible() {
	return (invincibilityTimer > 0);
}

void GameObject::setNoAttackTimer(int timer) {
	this->noAttackTimer = timer;
}


void GameObject::addHp(int damage) {
	PlayerData *playerData = PlayerData::getInstance();
	this->hp += damage;

	if(this == playerData->getPlayer()) {
		playerData->addHp(damage);
	}

	if(damage != 0) {
		DamageDisplay *damageDisplay = new DamageDisplay(damage, getCenter(), DamageDisplay::TYPE_DAMAGE);
		damageDisplayList.push_back(damageDisplay);
	}



}

void GameObject::addMp(int damage) {
	PlayerData *playerData = PlayerData::getInstance();
	this->mp += damage;

	if(this == playerData->getPlayer()) {
		playerData->addMp(damage);
	}


}

/**
 * Adiciona exp para um objeto e calcula o seu novo level, caso exista
 */
void GameObject::addExp(int exp) {
	if(gameObjectInstance->gameObject->evolucaoPorNivel) {
		int v = gameObjectInstance->gameObject->velocidadeEvolucao + 1;
		int l = gameObjectInstance->gameObject->currentLevel;
		int levelJump = 0;

		gameObjectInstance->gameObject->currentExperiencePoints += exp;

		std::cout << "currexp: " << gameObjectInstance->gameObject->currentExperiencePoints << std::endl;

		levelJump = gameObjectInstance->gameObject->currentExperiencePoints/(v*l);

		gameObjectInstance->gameObject->currentLevel += levelJump;

		gameObjectInstance->gameObject->currentExperiencePoints = gameObjectInstance->gameObject->currentExperiencePoints%(v*l);

		if(levelJump > 0) {
			DamageDisplay *damageDisplay = new DamageDisplay(levelJump, getCenter(), DamageDisplay::TYPE_LEVELUP);
			damageDisplayList.push_back(damageDisplay);


			for(std::list<std::pair<int, int> >::iterator it = gameObjectInstance->gameObject->levelSkills.begin();
					it != gameObjectInstance->gameObject->levelSkills.end(); ++it) {
				std::pair<int, int> skillPair = *it;
				int nroSkill = skillPair.first;
				int levelSkill = skillPair.second;

				if(gameObjectInstance->gameObject->currentLevel >= levelSkill) {
					modalManager->pushModal(new DialogueText(SkillData::getSkillMessages()->at(nroSkill), DialogueText::POS_UP, 30, true));

					std::list<std::pair<int, int> >::iterator it2 = it;
					it--;
					gameObjectInstance->gameObject->levelSkills.erase(it2);
				}

			}

		}
	}

}

float GameObject::getAtk() {
	return gameObjectInstance->gameObject->atk +
			((float)gameObjectInstance->gameObject->velocidadeEvolucao/200.0f)*
			gameObjectInstance->gameObject->atk;
}

float GameObject::getDef() {
	return gameObjectInstance->gameObject->def +
				((float)gameObjectInstance->gameObject->velocidadeEvolucao/200.0f)*
				gameObjectInstance->gameObject->def;
}

float GameObject::getInt() {
	return gameObjectInstance->gameObject->intelig +
				((float)gameObjectInstance->gameObject->velocidadeEvolucao/200.0f)*
				gameObjectInstance->gameObject->intelig;
}

/**
 * Função para calcular o dano a ser dado de um damager
 * para este objeto, levando-se em consideração atributos
 * como ataque, inteligência e defesa.
 */
int GameObject::addDamage(GameObject *damager, int extraDamage) {
	float damage;
	playDamageSound();

	if(damager->isMagical) {
		damage = -((damager->getInt()*extraDamage - 1)*0.3 + 1.0f);
	} else {
		damage = -((damager->getAtk()*extraDamage - 1)*0.3 + 1.0f);
	}

	damage /= (this->getDef()*0.2f + 1.0f);

	this->addHp(damage);

	return damage;

}

Sphere GameObject::getSphere() {
	Rect *rect = sprite->getRectWithoutRot();


}

Vector2 GameObject::getCenter() {
	Rect *rec;
	rec = this->sprite->getRectWithoutRot();
	int w = rec->w;
	int h = rec->h;

	delete rec;

	return Vector2((this->position->x + w/2), (this->position->y + h/2));
}

bool GameObject::collidesWith(GameObject* gameObject) {
	Rect *thisRect = this->sprite->getRectWithoutRot();
	Rect *thatRect = gameObject->sprite->getRectWithoutRot();

	if(thisRect->intersectsWith(thatRect)) {
		delete thisRect;
		delete thatRect;
		return true;
	}

	delete thisRect;
	delete thatRect;
	return false;
}

bool GameObject::collidesPixelWith(GameObject *gameObject) {
	return this->sprite->pixelCollidesWith(gameObject->sprite);
}

void GameObject::follow(Vector2 point, int dt) {}
void GameObject::moveAway(Vector2 point, int dt) {}
void GameObject::follow(Vector2 point, int dt, float velocity) {}
void GameObject::moveAway(Vector2 point, int dt, float velocity) {}
void GameObject::bounce(Rect rect, int dt) {}
void GameObject::bounceEvent(int dt) {}

void GameObject::playSpecialSound() {
	if(!gameObjectInstance->gameObject->soundSpecial.empty()) {
		std::string diretorioSound = std::string("sfx/");
		diretorioSound.append(gameObjectInstance->gameObject->soundSpecial.c_str());
		soundManager->playSound(diretorioSound, 1);
	}
}

void GameObject::playDamageSound() {
	if(!gameObjectInstance->gameObject->soundDamage.empty()) {
		std::string diretorioSound = std::string("sfx/");
		diretorioSound.append(gameObjectInstance->gameObject->soundDamage.c_str());
		soundManager->playSound(diretorioSound, 1);
	}
}

bool GameObject::isInMapLeftSide() {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();
		bool result;

		result = (this->position->x + rect->w < 0);

		delete rect;
		return result;
	}
	return false;
}
bool GameObject::isInMapUpSide() {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();
		bool result;

		result = (this->position->y + rect->h < 0);

		delete rect;
		return result;
	}
	return false;
}
bool GameObject::isInMapRightSide() {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();
		bool result;

		result = (this->position->x > tilemap->tileWidth*tilemap->mapWidth);

		delete rect;
		return result;
	}
	return false;
}
bool GameObject::isInMapDownSide() {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();
		bool result;

		result = (this->position->y > tilemap->tileHeight*tilemap->mapHeight);

		delete rect;
		return result;
	}
	return false;
}

Tile* GameObject::testBoxCollisionTile(int dt) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();

		int x, y;

		Tile *tile;

		if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, rect->x, rect->y))) {
			return tile;
		}

		if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, rect->x + rect->w -1, rect->y))) {
			return tile;
		}

		if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, rect->x + rect->w - 1, rect->y + rect->h - 1))) {
			return tile;
		}

		if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, rect->x, rect->y + rect->h - 1))) {
			return tile;
		}

		for(x = rect->x + tilemap->tileWidth; x < rect->x + rect->w; x += tilemap->tileWidth - 1) {
			for(y = rect->y + tilemap->tileHeight; y < rect->y + rect->h; y+= tilemap->tileHeight - 1) {


				if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, x, y))) {
					return tile;
				}


			}
		}

		delete rect;
	}


	return NULL;


}

bool GameObject::testBoxCollisionTileDown(int dt) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();

		int x;
		for(x = rect->x + 1; x < rect->x + rect->w; x++) {
			Tile *tile;

			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, x, rect->y + rect->h))) {
				return true;
			}
		}

		delete rect;
	}

	return false;

}

bool GameObject::testBoxCollisionTileUp(int dt) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();

		int x;
		for(x = rect->x + 1; x < rect->x + rect->w; x++) {
			Tile *tile;

			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, x, rect->y))) {
				return true;
			}
		}

		delete rect;
	}

	return false;
}

bool GameObject::testBoxCollisionTileLeft(int dt) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();

		int y;
		for(y = rect->y + 1; y < rect->y + rect->h; y++) {
			Tile *tile;
			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, rect->x, y))) {
				return true;
			}
		}

		delete rect;
	}

	return false;
}

bool GameObject::testBoxCollisionTileRight(int dt) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();

		int y;
		for(y = rect->y + 1; y < rect->y + rect->h; y++) {
			Tile *tile;

			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, rect->x + rect->w, y))) {
				return true;
			}
		}

		delete rect;
	}

	return false;
}

/*--*
 */

bool GameObject::testBoxCollisionTileDown(int dt, Vector2 position) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();

		int x;
		for(x = position.x + 1; x < position.x + rect->w - 1; x++) {
			Tile *tile;

			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, x, round(position.y) + rect->h - 1 ))) {
				return true;
			}
		}

		delete rect;
	}

	return false;

}

bool GameObject::testBoxCollisionTileUp(int dt, Vector2 position) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();

		int x;
		for(x = position.x + 1; x < position.x + rect->w - 1 ; x++) {
			Tile *tile;

			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, x, round(position.y)))) {
				return true;
			}
		}

		delete rect;
	}

	return false;
}

bool GameObject::testBoxCollisionTileLeft(int dt, Vector2 position) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();
		rect->x = position.x;
		rect->y = position.y;

		int y;
		for(y = position.y + 1; y < position.y + rect->h - 1; y++) {
			Tile *tile;

			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, round(position.x), y))) {
				return true;
			}
		}

		delete rect;
	}

	return false;
}

bool GameObject::testBoxCollisionTileRight(int dt, Vector2 position) {
	if(tilemap != NULL) {
		Rect *rect = sprite->getRectWithoutRot();
		rect->x = position.x;
		rect->y = position.y;

		int y;
		for(y = position.y + 1; y < position.y + rect->h - 1; y++) {
			Tile *tile;

			if((tile = tilemap->isTilesetColisionBlockByPosition(Tile::COLLISION_BLOCK, round(position.x) + rect->w - 1, y))) {
				return true;
			}
		}

		delete rect;
	}

	return false;
}

void GameObject::setAttributeById(int id, float value) {
	switch(id) {
	case ATT_POSITION_X:
		position->x = value;
		break;
	case ATT_POSITION_Y:
		position->y = value;
		break;
	case ATT_VELOCITY:

		break;
	case ATT_VELOCITY_X:
		velocity->x = value;

		break;
	case ATT_VELOCITY_Y:
		velocity->y = value;
		break;
	case ATT_ACCELERATION:

		break;
	case ATT_ACCELERATION_X:
		acceleration->x = value;
		break;
	case ATT_ACCELERATION_Y:
		acceleration->y = value;
		break;
	case ATT_GRAVITY:
		gravity = value;
		break;
	case ATT_JUMP_INTENSITY:
		jumpIntensity = value;
		break;
	case ATT_HP:
		hp = value;
		break;
	case ATT_MP:
		mp = value;
		break;
	case ATT_GAME_TIMER:
		TimerManager::getInstance()->resetGlobalTimer(value*1000);
		break;
	case ATT_MAP_TIMER:
		TimerManager::getInstance()->resetMapTimer(value*1000);
		break;
	case ATT_OBJECT_LEVEL:
		gameObjectInstance->gameObject->currentLevel = value;
		break;
	default:

		if(id > 300) {
			setVariableById(id - 300, value);
		}
		break;
	}
}

float GameObject::getAttributeById(int id) {
	switch(id) {
	case ATT_POSITION_X:
		return position->x;
		break;
	case ATT_POSITION_Y:
		return position->y;
		break;
	case ATT_VELOCITY:

		break;
	case ATT_VELOCITY_X:
		return velocity->x;

		break;
	case ATT_VELOCITY_Y:
		return velocity->y;
		break;
	case ATT_ACCELERATION:

		break;
	case ATT_ACCELERATION_X:
		return acceleration->x;
		break;
	case ATT_ACCELERATION_Y:
		return acceleration->y;
		break;
	case ATT_GRAVITY:
		return gravity;
		break;
	case ATT_JUMP_INTENSITY:
		return jumpIntensity;
		break;
	case ATT_HP:
		return hp;
		break;
	case ATT_MP:
		return mp;
		break;
	case ATT_INSTANCE_NUMBER:
		return gameObjectInstance->gameObject->instances->size();
		break;
	case ATT_GAME_TIMER:
		return (float)TimerManager::getInstance()->getGlobalTimer()/1000.0f;
		break;
	case ATT_MAP_TIMER:
		return (float)TimerManager::getInstance()->getMapTimer()/1000.0f;
		break;
	case ATT_OBJECT_LEVEL:
		return (float)gameObjectInstance->gameObject->currentLevel;
		break;

	default:

		if(id > 300) {
			std::cout << "varid: " << id - 300 << std::endl;
			return getVariableById(id - 300);
		}
		break;
	}

	return 0;
}


void GameObject::setVariableById(int id, float value) {
	this->gameObjectInstance->gameObject->getVariableById(id)->value = value;
}

float GameObject::getVariableById(int id) {
	std::cout << "Var:: " << this->gameObjectInstance->gameObject->getVariableById(id)->name  << std::endl;
	return this->gameObjectInstance->gameObject->getVariableById(id)->value;
}

